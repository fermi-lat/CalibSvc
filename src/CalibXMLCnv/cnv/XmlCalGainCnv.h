// $Header: /nfs/slac/g/glast/ground/cvs/CalibSvc/src/CalibXMLCnv/cnv/XmlCalGainCnv.h,v 1.2 2003/03/17 06:55:34 jrb Exp $
#ifndef CalibSvc_XmlCalGainCnv_h
#define CalibSvc_XmlCalGainCnv_h

/** @class XmlCalGainCnv

  Converter from xml to TCDS CAL gains class

  @author J. Bogart
*/
#include "XmlCalBaseCnv.h"
#include <xercesc/dom/DOM_Element.hpp>

template <class TYPE> class CnvFactory;

class XmlCalGainCnv : public XmlCalBaseCnv {

  /// Friend needed for instantiation
  friend class CnvFactory<XmlCalGainCnv>;
public:
  const CLID& objType() const;
  static const CLID& classID();
protected:

  XmlCalGainCnv(ISvcLocator* svcs);

  virtual ~XmlCalGainCnv() {}       // most likely nothing to do 

  virtual StatusCode i_createObj(const DOM_Element& element,
                                 DataObject*& refpObject);

};


#endif
