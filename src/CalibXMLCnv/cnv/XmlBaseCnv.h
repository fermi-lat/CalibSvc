// $Header: /nfs/slac/g/glast/ground/cvs/CalibSvc/src/CalibXMLCnv/cnv/XmlBaseCnv.h,v 1.3 2003/01/09 22:33:48 jrb Exp $
#ifndef CalibData_XmlBaseCnv_h
#define CalibData_XmlBaseCnv_h

/** @class XmlBaseCnv 

  Base class for calibration converters from XML files to TCDS.
  All such converters need to do certain things, which are
  handled here.

  @author J. Bogart
*/
#include "GaudiKernel/Converter.h"
#include "GaudiKernel/CnvFactory.h"
#include <dom/DOM_Element.hpp>

class ISvcLocator;
class GenericAddress;
class ICalibXmlSvc;
class ICalibMetaCnvSvc;

namespace CalibData {
  class CalibTime;
}

// template <class TYPE> class CnvFactory;

class  XmlBaseCnv : public Converter {
  //  friend class CnvFactory<XmlBaseCnv>;

public:
  //  const CLID& objType() const;
  //  static const CLID& classID();

  virtual ~XmlBaseCnv();

  virtual StatusCode initialize();

  virtual StatusCode finalize();

  /**
   Create the transient representation of an object, given an opaque
   address.  This and the following update method comprise the core 
   functionality of calibration converters.
  */
  virtual StatusCode createObj(IOpaqueAddress* addr,
                               DataObject*& refpObject);

  /**
     Update the transient representation of an object, given an opaque
     address.  This and the preceding create method comprise the core 
     functionality of calibration converters.
  */
  //  virtual StatusCode updateObj(IOpaqueAddress* addr,
  //                           DataObject*& refpObject);

  /** 
      Convert transient object to requested representation. This
      method is required since XmlBaseCnv inherits from Converter,
      but in practice it should not be called.
      Creation of persistent calibration data will 
      be accomplished by other means. 
  */
  //  virtual StatusCode createRep(DataObject *, IOpaqueAddress *&);

  /** 
      Updated converted representation of the transient object.  This
      method is required since XmlBaseCnv inherits from Converter,
      but in practice it should not be called.
  */
  //  virtual StatusCode updateRep(IOpaqueAddress *&, DataObject *);

  //  virtual StatusCode fillRepRefs(IOpaqueAddress *&, DataObject *);

  //  virtual StatusCode updateRepRefs(IOpaqueAddress *&, DataObject *);

  ICalibXmlSvc* getCalibXmlSvc() {
    return m_xmlSvc;
  }

  static const unsigned char storageType();

  /**
     Constructor for this converter
     @param svc a ISvcLocator interface to find services
     @param clid the type of object the converter is able to convert
   */
  //  XmlBaseCnv(ISvcLocator* svc, const CLID& clid = 0);
  XmlBaseCnv(ISvcLocator* svc, const CLID& clid);

protected:
  /** This creates the transient representation of an object from the
   *  DOM_Element representing it, then fills it and process it.
   *  This implementation actually only calls the i_* methods of the
   *  "right" converter to do the job; so the very first thing it
   *  does is get a pointer to the appropriate derived converter.
   *  Converters typically don't need to override this method
   *  but only to  override/implement some of the i_* methods.
   *  @param element the DOM_Element (typically the root element of the
   *   document) to be used to build the object
   *  @param refpObject the object to be built
   *  @param address the opaque address for this object
   *  @return status depending on the completion of the call
   */
  virtual StatusCode internalCreateObj (const DOM_Element& element,
                                        DataObject*& refpObject,
                                        IOpaqueAddress* address);
  
  /** This creates the transient representation of an object from the
   *  DOM_Element representing it. This actually does the "new" operation
   *  and deals with the attributes of the node. This base class implementation
   *  does nothing; it should not normally be called because it doesn't
   *  correspond to any TCDS class.  Instead, 
   *  i_createObj of some derived class will be called.
   *  @param element the DOM_Element (typically root element of document)
   *  to be used to builds the object
   *  @param refpObject the object to be built
   *  @return status depending on the completion of the call
   */
  virtual StatusCode i_createObj (const DOM_Element& element,
                                  DataObject*& refpObject);

  /// In case there is additional work to do on the created object
  virtual StatusCode i_processObj(DataObject* pObject,
                                  IOpaqueAddress* address);

  // Might want to verify that instrument, calType are correct,
  // for example.  If so, might as well provide the service in
  // the base converter.
  virtual StatusCode readHeader(const DOM_Element&);

  ICalibXmlSvc* m_xmlSvc;
  ICalibMetaCnvSvc* m_metaSvc;

  int m_serNo;
  CalibData::CalibTime*  m_vstart;
  CalibData::CalibTime*  m_vend;
};


#endif
