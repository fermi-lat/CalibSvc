// $Header: /nfs/slac/g/glast/ground/cvs/CalibSvc/src/CalibROOTCnv/CalibRootCnvSvc.cxx,v 1.1 2003/02/05 22:49:00 jrb Exp $

#include "GaudiKernel/IDetDataSvc.h"
#include "GaudiKernel/IConversionSvc.h"

#include "GaudiKernel/MsgStream.h"
#include "GaudiKernel/SvcFactory.h"
#include "GaudiKernel/CnvFactory.h"
#include "GaudiKernel/ISvcLocator.h"
#include "GaudiKernel/IDataProviderSvc.h"
#include "GaudiKernel/GenericAddress.h"
#include "CalibRootCnvSvc.h"

// Make instances only via static factory class
static SvcFactory<CalibRootCnvSvc> calibRootCnvSvc_factory;
const ISvcFactory& CalibRootCnvSvcFactory = calibRootCnvSvc_factory;

CalibRootCnvSvc::CalibRootCnvSvc(const std::string& name, 
                               ISvcLocator* svc) :
  ConversionSvc(name, svc, ROOT_StorageType),
  m_detPersSvc(0), m_detDataSvc(0)   {

  // Some day might have a property to declare having to do with path to
  // xml files.
}

StatusCode CalibRootCnvSvc::queryInterface(const IID& riid,
                                          void** ppvInterface) {
  /* Uncomment if choose to derive from abstract root conv. interface
  if (IID_ICalibRootSvc.versionMatch(riid))  {
    *ppvInterface = (ICalibRootSvc*)this;
  }
  else {
  */
    // Interface is not directly availible: try out a base class
    return ConversionSvc::queryInterface(riid, ppvInterface);
    /*  }  */
  addRef();
  return StatusCode::SUCCESS;
}

StatusCode CalibRootCnvSvc::initialize() {
  StatusCode sc = ConversionSvc::initialize();

  MsgStream log(msgSvc(), "CalibRootCnvSvc");

  if (!sc.isSuccess()) return sc;

  // Locate the Calib Data Service.  Since it inherits from DataSvc
  // it has to implement IDataProviderSvc
  IDataProviderSvc* pCDS = 0;
  sc = serviceLocator()->getService 
    ("CalibDataSvc",  IID_IDataProviderSvc, (IInterface*&)pCDS);
  if ( !sc.isSuccess() ) {
    log << MSG::ERROR << "Could not locate CalibDataSvc" << endreq;
    return sc;
  }

  // Set the CalibDataSvc as data provider service
  sc = setDataProvider(pCDS);
  if ( !sc.isSuccess() ) {
    log << MSG::ERROR << "Could not set data provider" << endreq;
    return sc;
  }


  // Locate IConversionSvc interface of the DetectorPersistencySvc
  sc = serviceLocator()->service 
    ("DetectorPersistencySvc", m_detPersSvc, true);
  if ( !sc.isSuccess() ) {
    log << MSG::ERROR 
	<< "Cannot locate IConversionSvc interface of DetectorPersistencySvc"
	<< endreq;
    return sc;
  } else {
    log << MSG::DEBUG 
	<< "Retrieved IConversionSvc interface of DetectorPersistencySvc"
	<< endreq;
  }
  
  // Query the IAddressCreator interface of the detector persistency service
  IAddressCreator* iAddrCreator;
  sc = m_detPersSvc->queryInterface(IID_IAddressCreator, 
				    (void**) &iAddrCreator);
  if ( !sc.isSuccess() ) {
    log << MSG::ERROR 
	<< "Cannot query IAddressCreator interface of DetectorPersistencySvc" 
	<< endreq;
    return sc;
  } else {
    log << MSG::DEBUG 
	<< "Retrieved IAddressCreator interface of DetectorPersistencySvc" 
	<< endreq;
  }
  log << MSG::DEBUG 
      << "Set it as the address creator of the CalibRootCnvSvc" << endreq;
  sc = setAddressCreator(iAddrCreator);
  if ( !sc.isSuccess() ) {
    log << MSG::ERROR 	<< "Cannot set the address creator" << endreq;
    return sc;
  }

  // set properties if there are any??

  return sc;
}

StatusCode CalibRootCnvSvc::finalize() {
  // If anything was allocated, get rid of it.  So far, nothing was.

  return ConversionSvc::finalize();
}

StatusCode CalibRootCnvSvc::createAddress(unsigned char svc_type,
                                          const CLID& clid,
                                          const std::string* par, 
                                          const unsigned long* ip,
                                          IOpaqueAddress*& refpAddress) {

  MsgStream log( msgSvc(), name() );

  if (svc_type != ROOT_StorageType) {
    log << MSG::ERROR << "bad storage type" << (int)svc_type << endreq;
    return StatusCode::FAILURE;
  }

  std::string dataIdent(par[0]); // file identifier for PDS version of data
  std::string fullpath(par[1]);  // path within TCDS for the object
  std::string fmtVersion(par[2]);
  int         serNo = ip[0];

  // for now have to ignore fmtVersion because of defective implementation
  // of GenericAddress. If we want it, should probably write new
  // opaque address implementation for this package to use.  All
  // dealings with (calibration) opaque addresses are confined to
  // the CalibSvc package.
  refpAddress = new GenericAddress(ROOT_StorageType,
                                   clid,
                                   dataIdent,  
                                   fullpath,
                                   serNo);
                                   
  return StatusCode::SUCCESS; 

}
