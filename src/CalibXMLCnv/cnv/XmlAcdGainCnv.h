// $Header: /nfs/slac/g/glast/ground/cvs/CalibSvc/src/CalibXMLCnv/cnv/XmlCalGainCnv.h,v 1.2 2003/03/17 06:55:34 jrb Exp $
#ifndef CalibSvc_XmlAcdGainCnv_h
#define CalibSvc_XmlAcdGainCnv_h

/** @class XmlAcdGainCnv

  Converter from xml to TCDS ACD gains class

  @author J. Bogart
*/
#include "XmlAcdBaseCnv.h"
#include <xercesc/dom/DOM_Element.hpp>

template <class TYPE> class CnvFactory;

class XmlAcdGainCnv : public XmlAcdBaseCnv {

  /// Friend needed for instantiation
  friend class CnvFactory<XmlAcdGainCnv>;
public:
  const CLID& objType() const;
  static const CLID& classID();
protected:

  XmlAcdGainCnv(ISvcLocator* svcs);

  virtual ~XmlAcdGainCnv() {}       // most likely nothing to do 

  virtual StatusCode i_createObj(const DOM_Element& element,
                                 DataObject*& refpObject);

};


#endif