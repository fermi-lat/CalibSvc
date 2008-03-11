//$Header: /nfs/slac/g/glast/ground/cvs/CalibSvc/src/MootSvc/MootSvc.cxx,v 1.4 2008/03/08 02:37:36 jrb Exp $
#include <cstdio>
#include <cstdlib>
#include <stdexcept>

#include <utility>   // for std::pair
// <vector>, <string> included by MootSvc.h

#include "MootSvc.h"
#include "mootCore/MoodConnection.h"
#include "mootCore/MootQuery.h"
#include "mootCore/FileDescrip.h"
#include "facilities/Util.h"
#include "facilities/commonUtilities.h"
#include "CalibData/Moot/MootData.h"

#include "LdfEvent/LsfMetaEvent.h" //includes everything we need for fsw keys


#include "GaudiKernel/ISvcLocator.h"

#include "GaudiKernel/MsgStream.h"
#include "GaudiKernel/SvcFactory.h"
#include "GaudiKernel/IDataProviderSvc.h"
#include "GaudiKernel/SmartDataPtr.h"


/// Instantiation of a static factory to create instances of this service
static SvcFactory<MootSvc>          MootSvc_factory;
const ISvcFactory& MootSvcFactory = MootSvc_factory;

MootSvc::MootSvc(const std::string& name, ISvcLocator* svc)
  : Service(name, svc), m_q(0), m_c(0), m_log(0), m_mootParmCol(0)
{
  declareProperty("MootArchive", m_archive = std::string("") );
  declareProperty("UseEventKeys", m_useEventKeys = false);
  declareProperty("Verbose", m_verbose = false);
}

MootSvc::~MootSvc(){ }

StatusCode MootSvc::initialize()
{
  // Initialize base class
  if (m_log) {    // already attempted initialization
    return (m_q) ? StatusCode::SUCCESS : StatusCode::FAILURE;
  }

  StatusCode sc = Service::initialize();
  if ( !sc.isSuccess() ) return sc;

  m_log = new MsgStream(msgSvc(), "MootSvc");

  (*m_log) << MSG::INFO << "Specific initialization starting" << endreq;


  // Get properties from the JobOptionsSvc
  sc = setProperties();
  if ( !sc.isSuccess() ) {
    (*m_log) << MSG::ERROR << "Could not set jobOptions properties" << endreq;
    return sc;
  }
  (*m_log) << MSG::DEBUG << "Properties were read from jobOptions" << endreq;

  // Needed for access for fsw keys
  sc = serviceLocator()->service("EventDataSvc", m_eventSvc, true);
  if (sc .isFailure() ) {
    (*m_log) << MSG::ERROR << "Unable to find EventDataSvc " << endreq;
    return sc;
  }

  /*
    Might want to add something here to force use of
    user-supplied LATC master key if so requested
  */

  // Make a MOOT::MootQuery instance
  m_q = makeConnection(m_verbose); 
  if (!m_q) return StatusCode::FAILURE;
 
  // Get local info
  sc = getPrecincts();

  m_mootParmCol = new CalibData::MootParmCol(CalibData::MOOTSUBTYPE_latcParm);


  (*m_log) << MSG::INFO << "Specific initialization completed" << endreq;
  return sc;
}


StatusCode MootSvc::finalize()
{
  (*m_log) << MSG::DEBUG << "Finalizing" << endreq;
  if (m_q) delete m_q;
  if (m_c) delete m_c;
  delete m_log;
  m_q = 0;  m_c = 0; m_log = 0;
    
  return Service::finalize();
}

MOOT::MootQuery* MootSvc::makeConnection(bool verbose) {
  if (m_q) return m_q;

  const std::string slacDefault("/afs/slac/glast/g/moot/archive-mood");

  std::string archEnv("$(MOOT_ARCHIVE)");
  std::string archEnvName("MOOT_ARCHIVE");

  bool envSet = false;

  // To make a connection, need definition for env. var MOOT_ARCHIVE
  //   If path has been supplied in job options, do setenv for it
  //     Special value of "*" means use default 
  //     (/afs/slac/g/glast/moot/archive-mood)
  //   else if $MOOT_ARCHIVE already has def, use that
  //   else try default value above 

  if (m_archive.size() == 0 ) {
    // Check to see if MOOT_ARCHIVE has a value.  
    int nExpand = facilities::Util::expandEnvVar(&archEnv);
    if (nExpand > 0) envSet = true;
    // If not, set m_archive to 
    else m_archive = slacDefault;
  }
  if (!envSet) {
    if (m_archive == std::string("*"))   { // use slac default
      m_archive = slacDefault;
    }
    facilities::commonUtilities::setEnvironment(archEnvName, m_archive, true);
  }
  // Maybe should have some logic here to get verbose connection
  // depending on debug level?
  m_c = new MOOT::MoodConnection(false, verbose);
  if (m_c) m_q = new MOOT::MootQuery(m_c);

  if (!m_q) {
    (*m_log) << MSG::ERROR 
             << "Could not open connection to MOOT dbs for archive " 
             << m_archive << endreq;
  }
  else if (!verbose) {
    (*m_log) << MSG::INFO
             << "Successfully connect to MOOT dbs for archive "
             << m_archive << endreq;
  }
  
  return m_q;
}


StatusCode MootSvc::getPrecincts() {

  std::vector<std::string> prNames;
  m_q->getPrecincts(prNames);
  std::vector<std::string> pclasses;
  pclasses.reserve(50);   // lots for precinct 'generic'
  m_parmPrecincts.reserve(60);

  int pclassIx = 0;
  for (unsigned ix = 0; ix < prNames.size(); ix++) {
    // Get parm classes 
    pclasses.clear();
    m_q->getParmClasses(pclasses, prNames[ix]);
    for (unsigned jx = 0; jx < pclasses.size(); jx++) {
      m_parmPrecincts.push_back(ParmPrecinct(pclasses[jx], prNames[ix]));
      pclassIx++;
    }
  }

  return StatusCode::SUCCESS;
}

StatusCode MootSvc::queryInterface(const InterfaceID& riid, 
                                   void** ppvInterface)
{
  if ( IID_IMootSvc == riid )  {
    // With the highest priority return the specific interface of this service
    *ppvInterface = dynamic_cast<IMootSvc*> (this);
  } else  {
    // Interface is not directly available: try out a base class
    return Service::queryInterface(riid, ppvInterface);
  }
  addRef();
  return StatusCode::SUCCESS;
}



int MootSvc::latcParmIx(const std::string& parmClass) const {
  if (!m_mootParmCol) return -2;
  const CalibData::MootParmVec& vec = m_mootParmCol->getMootParmVec();
  for (unsigned ix = 0; ix < vec.size(); ix++) {
    if (parmClass.compare(vec[ix].getClass()) == 0)
      return ix;
  }
  return -1;
}



StatusCode  MootSvc::updateFswKeys() {
  // For now either we update from event or we don't update at all
  if (!m_useEventKeys) return StatusCode::SUCCESS;
  using namespace enums;

  SmartDataPtr<LsfEvent::MetaEvent> metaEvt(m_eventSvc, "/Event/MetaEvent");

  unsigned newMasterKey;
  switch (metaEvt->keyType()) {

  case Lsf::LpaKeys: {
    const lsfData::LpaKeys *lpaKeysTds = metaEvt->keys()->castToLpaKeys();
    newMasterKey = lpaKeysTds->LATC_master();
    break;
  }

  case Lsf::LciKeys: {
    const lsfData::LciKeys *lciKeysTds = metaEvt->keys()->castToLciKeys();
    newMasterKey = lciKeysTds->LATC_master();
    break;
  }
  default: 
   // tilt!
    return StatusCode::FAILURE;
  }

  if (newMasterKey)     m_hw = newMasterKey;
  return StatusCode::SUCCESS;
}

unsigned MootSvc::getHardwareKey()  {
  updateFswKeys();
  return m_hw;
}

std::string MootSvc::getMootParmPath(const std::string& cl, unsigned& hw) {
  const CalibData::MootParm* pParm = getMootParm(cl, hw);
  if (pParm) return pParm->getSrc();
  else return std::string("");
}

const CalibData::MootParm* MootSvc::getMootParm(const std::string& cl,
                                                   unsigned& hw) {
  updateFswKeys();
  hw = m_hw;
  if (hw != m_mootParmCol->fswKey() ) {
    StatusCode sc = updateMootParmCol();
    if (!sc.isSuccess() ) return 0;
  }
  // Find desired parm
  int ix = latcParmIx(cl);
  if (ix < 0) return 0;
  else return &m_mootParmCol->m_v[ix];
}

const CalibData::MootParmCol* MootSvc::getMootParmCol(unsigned& hw)  {
  updateFswKeys();
  hw = m_hw;
  if (hw != m_mootParmCol->fswKey() ) {
    StatusCode sc = updateMootParmCol();
    if (!sc.isSuccess() ) return 0;
  }
  return m_mootParmCol;
}

StatusCode MootSvc::updateMootParmCol( ) {

  using CalibData::MootParmCol;
  using CalibData::MootParm;
  using CalibData::MootParmVec;

  MootParmVec& v = m_mootParmCol->m_v;
  v.clear();

  m_mootParmCol->m_key = m_hw;

  std::vector<MOOT::ParmOffline> parmsOff;

  if (!(m_q->getParmsFromMaster(m_hw, parmsOff)) ) {
    (*m_log) << MSG::ERROR 
             << "Unable to fetch parameter collection from Moot" << std::endl;
    return StatusCode::FAILURE;
  }
   
  v.reserve(parmsOff.size() );
  std::vector<MOOT::ParmOffline>::const_iterator poff = parmsOff.begin();

  while (poff != parmsOff.end() ) {

    std::string path(m_archive);
    path += std::string("/") + poff->getSrc();
    
    // Find pclass in parm-precinct vector; prec = elt.second;
    std::string prec = findPrecinct(poff->getClass());
    
    MootParm p(poff->getKey(), poff->getClass(), poff->getClassFk(),
               path, poff->getSrcFmt(), poff->getStatus(),
               prec);
    v.push_back(p);

    poff++;
  }
  return StatusCode::SUCCESS;   // for now
}

std::string MootSvc::findPrecinct(const std::string& pclass) {
  for (unsigned ix = 0; ix < m_parmPrecincts.size(); ix++) {
    if (pclass.compare(m_parmPrecincts[ix].first) == 0)
      return m_parmPrecincts[ix].second;
  }
  return std::string("");
}


