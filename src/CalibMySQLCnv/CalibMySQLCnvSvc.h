//$Header: /nfs/slac/g/glast/ground/cvs/CalibSvc/src/CalibMySQLCnv/CalibMySQLCnvSvc.h,v 1.8 2003/01/15 01:22:58 jrb Exp $
#ifndef CalibMySQLCnvSvc_h
#define CalibMySQLCnvSvc_h  1

/// Include files
#include "CalibSvc/ICalibMetaCnvSvc.h"
#include "CalibSvc/IInstrumentName.h"
#include "GaudiKernel/ConversionSvc.h"

/// Forward and external declarations
// class ConditionsDBGate;
template <class TYPE> class SvcFactory;
class IDetDataSvc;
class IOpaqueAddress;

///---------------------------------------------------------------------------
/** @class CalibMySQLCnvSvc

    A conversion service for GLAST calibration metadata database persistency.
    Allows to create and update condition data objects (i.e. DataObjects
    implementing IValidity).

    Adapted from LHCb class DetCond/ConditionsDBCnvSvc by Andrea Valassi
    @author J. Bogart
    @date November 2002
*///--------------------------------------------------------------------------

class CalibMySQLCnvSvc : public ConversionSvc, 
                         virtual public ICalibMetaCnvSvc
{
  /// Only factories can access protected constructors
  friend class SvcFactory<CalibMySQLCnvSvc>;

 protected:

  CalibMySQLCnvSvc(const std::string& name, ISvcLocator* svc );
  virtual ~CalibMySQLCnvSvc();

 public:
  
  // Reimplemented from IInterface

  virtual StatusCode queryInterface( const InterfaceID& riid, 
				     void** ppvInterface );  

 public:

  // Overloaded from ConversionSvc

  virtual StatusCode initialize();
    virtual StatusCode finalize();
  
  /// Create a transient representation from another rep of this object.
  virtual StatusCode createObj     ( IOpaqueAddress* pAddress, 
				     DataObject*&    refpObject );
  
  /// Resolve the references of the created transient object.
  virtual StatusCode fillObjRefs   ( IOpaqueAddress* pAddress, 
				     DataObject* pObject );
  
  /// Update a transient representation from another rep of this object.
  virtual StatusCode updateObj     ( IOpaqueAddress* pAddress, 
				     DataObject* pObject );

  /// Update the references of an updated transient object.
  virtual StatusCode updateObjRefs ( IOpaqueAddress* pAddress, 
				     DataObject* pObject );

  /// Convert a transient object to a requested representation.
  virtual StatusCode createRep     ( DataObject* pObject, 
				     IOpaqueAddress*& refpAddress );

  /// Resolve the references of a converted object. 
  virtual StatusCode fillRepRefs   ( IOpaqueAddress* pAddress,
				     DataObject* pObject );

  /// Update a converted representation of a transient object.
  virtual StatusCode updateRep     ( IOpaqueAddress* pAddress, 
				     DataObject* pObject );

  /// Update the references of an already converted object.
  virtual StatusCode updateRepRefs ( IOpaqueAddress* pAddress, 
				     DataObject* pObject );

  /// Create an address using explicit arguments to identify a single object.
  virtual StatusCode createAddress ( unsigned char svc_type,
				     const CLID& clid,
				     const std::string* par, 
				     const unsigned long* ip,
				     IOpaqueAddress*& refpAddress );
  
 public:
  // Implementation of ICalibMetaCnvSvc.
  // Create/update calib DataObject not necessarily registered in the TDS.
  
  /// Create a calib DataObject by calib type name, flavor and time.
  /// This method does not register DataObject in the transient data store.
  /// The string storage type is discovered at runtime in the Metadata dbs.
  virtual StatusCode createCalib(DataObject*& refpObject,
                                 const std::string& fullpath,
                                 const ITime&       time,
                                 const std::string& instrument,
                                 const CLID&        classID,
                                 IRegistry*         entry=0);
  
  /// Update a condition DataObject by 
  /// This method does not register DataObject in the transient data store.
  /// The string storage type is discovered at runtime in the metadata dbs.
  virtual StatusCode updateCalib(DataObject*        pObject,
                                 const std::string& fullpath,
                                 const ITime&       time,
                                 const std::string& instName,
                                 const CLID&        classID,
                                 IRegistry*         entry=0);
  
  /// Decode the string storage type to enumerated storage type
  virtual StatusCode decodeDescription(unsigned int   description,
                                       unsigned char&       type);

  virtual calibUtil::Metadata* getMeta();

  virtual StatusCode getValidInterval(unsigned int& serNo,
                                      ITime** pvStart, ITime** pvEnd);

 private:

  /// Handle for metadata access
  calibUtil::Metadata*    m_meta;

  /// How official does a calibration have to be in order to be acceptable
  /// Should default to calibUtil::Metadata::LEVELProd
  unsigned int m_calibLevelMask;

  /// Handle to the IConversionSvc interface of the DetectorPersistencySvc
  IConversionSvc*      m_detPersSvc;

  /// Handle to the IDetDataSvc interface of the CalibDataSvc
  IDetDataSvc*         m_detDataSvc;

  // Maybe also handle to IInstrumentName interface? Or do we really
  // need all these different handles to the same class??
  // Keep them separate for now to preserve possibility of putting
  // CalibDataSvc in a separate package.
  IInstrumentName*  m_instrSvc;

};
#endif   

