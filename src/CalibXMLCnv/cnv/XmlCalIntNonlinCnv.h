// $Header: /nfs/slac/g/glast/ground/cvs/CalibSvc/src/CalibXMLCnv/cnv/XmlCalIntNonlinCnv.h,v 1.1 2004/05/21 00:02:49 jrb Exp $
#ifndef CalibSvc_XmlCalIntNonlinCnv_h
#define CalibSvc_XmlCalIntNonlinCnv_h

/** @class XmlCalIntNonlinCnv

  Converter from xml to TCDS CAL IntNonlin class

  @author J. Bogart
*/
#include "XmlBaseCnv.h"
#include <xercesc/dom/DOM_Element.hpp>

template <class TYPE> class CnvFactory;

class XmlCalIntNonlinCnv : public XmlBaseCnv {

  /// Friend needed for instantiation
  friend class CnvFactory<XmlCalIntNonlinCnv>;
public:
  const CLID& objType() const;
  static const CLID& classID();
protected:

  XmlCalIntNonlinCnv(ISvcLocator* svcs);

  virtual ~XmlCalIntNonlinCnv() {}       // most likely nothing to do 

  virtual StatusCode i_createObj(const DOM_Element& element,
                                 DataObject*& refpObject);

};


#endif