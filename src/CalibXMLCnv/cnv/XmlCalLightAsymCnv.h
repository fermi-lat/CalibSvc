// $Header: /nfs/slac/g/glast/ground/cvs/CalibSvc/src/CalibXMLCnv/cnv/XmlCalLightAsymCnv.h,v 1.1 2004/05/21 00:02:49 jrb Exp $
#ifndef CalibSvc_XmlCalLightAsymCnv_h
#define CalibSvc_XmlCalLightAsymCnv_h

/** @class XmlCalLightAsymCnv

  Converter from xml to TCDS CAL LightAtt class

  @author J. Bogart
*/
#include "XmlCalBaseCnv.h"
#include <xercesc/dom/DOM_Element.hpp>

template <class TYPE> class CnvFactory;

class XmlCalLightAsymCnv : public XmlCalBaseCnv {

  /// Friend needed for instantiation
  friend class CnvFactory<XmlCalLightAsymCnv>;
public:
  const CLID& objType() const;
  static const CLID& classID();
protected:

  XmlCalLightAsymCnv(ISvcLocator* svcs);

  virtual ~XmlCalLightAsymCnv() {}       // most likely nothing to do 

  virtual StatusCode i_createObj(const DOM_Element& element,
                                 DataObject*& refpObject);

};


#endif
