// $Header: /nfs/slac/g/glast/ground/cvs/CalibSvc/src/CalibXMLCnv/cnv/XmlCalGainCnv.h,v 1.2 2003/03/17 06:55:34 jrb Exp $
#ifndef CalibSvc_XmlAcdPedCnv_h
#define CalibSvc_XmlAcdPedCnv_h

/** @class XmlAcdPedCnv

  Converter from xml to TCDS ACD gains class

  @author J. Bogart
*/
#include "XmlAcdBaseCnv.h"
#include <xercesc/dom/DOM_Element.hpp>

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

  virtual StatusCode i_createObj(const DOM_Element& element,
                                 DataObject*& refpObject);

};


#endif
