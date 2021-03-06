// $Header: /nfs/slac/g/glast/ground/cvs/CalibSvc/src/CalibXMLCnv/cnv/XmlCalPedCnv.h,v 1.3 2004/06/11 20:48:35 jrb Exp $
#ifndef CalibSvc_XmlCalPedCnv_h
#define CalibSvc_XmlCalPedCnv_h

/** @class XmlCalPed1  

  Converter from xml to TCDS CAL pedestals class

  @author J. Bogart
*/
#include "XmlCalBaseCnv.h"

template <class TYPE> class CnvFactory;

class XmlCalPedCnv : public XmlCalBaseCnv {

  /// Friend needed for instantiation
  friend class CnvFactory<XmlCalPedCnv>;
public:
  const CLID& objType() const;
  static const CLID& classID();
protected:

  XmlCalPedCnv(ISvcLocator* svcs);

  virtual ~XmlCalPedCnv() {}       // most likely nothing to do 

  virtual StatusCode i_createObj(const DOMElement* element,
                                 DataObject*& refpObject);

};


#endif
