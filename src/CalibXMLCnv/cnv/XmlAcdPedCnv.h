// $Header: /nfs/slac/g/glast/ground/cvs/CalibSvc/src/CalibXMLCnv/cnv/XmlAcdPedCnv.h,v 1.1 2004/06/11 20:51:49 jrb Exp $
#ifndef CalibSvc_XmlAcdPedCnv_h
#define CalibSvc_XmlAcdPedCnv_h

/** @class XmlAcdPedCnv

  Converter from xml to TCDS ACD gains class

  @author J. Bogart
*/
#include "XmlAcdBaseCnv.h"

template <class TYPE> class CnvFactory;

class XmlAcdPedCnv : public XmlAcdBaseCnv {

  /// Friend needed for instantiation
  friend class CnvFactory<XmlAcdPedCnv>;
public:
  const CLID& objType() const;
  static const CLID& classID();
protected:

  XmlAcdPedCnv(ISvcLocator* svcs);

  virtual ~XmlAcdPedCnv() {}       // most likely nothing to do 

  virtual StatusCode i_createObj(const DOMElement* element,
                                 DataObject*& refpObject);

};


#endif
