//$Header: /nfs/slac/g/glast/ground/cvs/GlastRelease-scons/CalibSvc/src/test/UseLATAlignment.cxx,v 1.4.236.1 2010/10/18 02:50:20 heather Exp $
#include <stdio.h>
#include "GaudiKernel/Algorithm.h"
#include "GaudiKernel/AlgFactory.h"
#include "GaudiKernel/IDataProviderSvc.h"
#include "GaudiKernel/Service.h"
#include "GaudiKernel/MsgStream.h"
#include "GaudiKernel/SmartDataPtr.h"
#include "CalibData/Nas/CalibLATAlignment.h"
#include "CalibSvc/ICalibPathSvc.h"

/// Simple algorithm to test functioning of "the other" TDS
class UseLATAlignment : public Algorithm {

public:
  UseLATAlignment(const std::string& name, ISvcLocator* pSvcLocator); 

  StatusCode initialize();

  StatusCode execute();

  StatusCode finalize();

private:
  IDataProviderSvc* m_pCalibDataSvc;
  ICalibPathSvc*    m_pCalibPathSvc;
  std::string       m_path;
  std::string       m_flavor;

};

/// Instantiation of a static factory to create instances of this algorithm
//static const AlgFactory<UseLATAlignment> Factory;
//const IAlgFactory& UseLATAlignmentFactory = Factory;
DECLARE_ALGORITHM_FACTORY(UseLATAlignment);


UseLATAlignment::UseLATAlignment( const std::string&  name, 
		    ISvcLocator*        pSvcLocator )
  : Algorithm     ( name, pSvcLocator ), m_pCalibDataSvc(0)
{
  // Declare properties here.
  declareProperty("CalibFlavor", m_flavor = "vanilla");
}


StatusCode UseLATAlignment::initialize() {
  StatusCode sc;
  MsgStream log(msgSvc(), name());
  log << MSG::INFO << "Initialize()" << endreq;

  setProperties();


  sc = service("CalibDataSvc", m_pCalibDataSvc, true);

  if ( !sc.isSuccess() ) {
    log << MSG::ERROR 
	<< "Could not get IDataProviderSvc interface of CalibDataSvc" 
	<< endreq;
    return sc;
  } else {
    log << MSG::DEBUG 
	<< "Retrieved IDataProviderSvc interface of CalibDataSvc" 
	<< endreq;
  }

  sc = service("CalibDataSvc", m_pCalibPathSvc, true);

  if ( !sc.isSuccess() ) {
    log << MSG::ERROR 
	<< "Could not get ICalibPathSvc interface of CalibDataSvc" 
	<< endreq;
    return sc;
  }

  m_path = 
    m_pCalibPathSvc->getCalibPath(ICalibPathSvc::Calib_NAS_LATAlignment,
                                  m_flavor);

  // Get properties from the JobOptionsSvc
  sc = setProperties();
  return StatusCode::SUCCESS;

}


StatusCode UseLATAlignment::execute( ) {

  MsgStream log(msgSvc(), name());

  static unsigned serial = 0;

  SmartDataPtr<CalibData::CalibLATAlignment> alignCalib(m_pCalibDataSvc, m_path);

  if (!alignCalib) {
    log << MSG::ERROR << "Failed access to CalibLATAlignment via smart ptr" << endreq;
    return StatusCode::FAILURE;
  }

  unsigned newSerial = alignCalib->getSerNo();

  if (serial != newSerial) {
    serial = newSerial;
    double rx, ry, rz;
  
    rx = alignCalib->getRx();
    ry = alignCalib->getRy();
    rz = alignCalib->getRz();
    std::string units = alignCalib->getUnits();
  
    log << MSG::INFO 
        << "LAT alignment obj, serial #" <<  newSerial << endreq;
    
    log << MSG::INFO << "Vstart: " <<  (alignCalib->validSince()).hour(true)
        << "  Vend: " << (alignCalib->validTill()).hour(true) << endreq;

    log << MSG::INFO << "Rx: "   << rx  << endreq;
    log << MSG::INFO << "Ry: " << ry   << endreq;
    log << MSG::INFO << "Rz: "   << rz   << endreq;

    const CalibData::ALIGN_ROT* r = alignCalib->getR();
    log << MSG::INFO << "Or equivalently, array is " << (*r)[0] << ", "
        << (*r)[1] << ", " << (*r)[2] << endreq;

    log << MSG::INFO << "in units of "   << units   << endreq;
  }
  else log << MSG::INFO << "Alignment calib. serial number " << serial 
           << " unchanged since previous event" << endreq;
  return StatusCode::SUCCESS;
}

StatusCode UseLATAlignment::finalize( ) {

  MsgStream log(msgSvc(), name());
  log << MSG::INFO 
      << "        UseLATAlignment FINALIZE!! "
      << endreq;
  
  return StatusCode::SUCCESS;
}

