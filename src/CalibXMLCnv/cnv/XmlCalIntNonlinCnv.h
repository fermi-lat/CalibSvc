// $Header: /nfs/slac/g/glast/ground/cvs/CalibSvc/src/CalibXMLCnv/cnv/XmlCalIntNonlinCnv.h,v 1.2 2004/06/11 20:48:35 jrb Exp $
#ifndef CalibSvc_XmlCalIntNonlinCnv_h
#define CalibSvc_XmlCalIntNonlinCnv_h

/** @class XmlCalIntNonlinCnv

  Converter from xml to TCDS CAL IntNonlin class

  @author J. Bogart
*/
#include "XmlCalBaseCnv.h"

template <class TYPE> class CnvFactory;

class XmlCalIntNonlinCnv : public XmlCalBaseCnv {

  /// Friend needed for instantiation
  friend class CnvFactory<XmlCalIntNonlinCnv>;
public:
  const CLID& objType() const;
  static const CLID& classID();
protected:

  XmlCalIntNonlinCnv(ISvcLocator* svcs);

  virtual ~XmlCalIntNonlinCnv() {}       // most likely nothing to do 

  virtual StatusCode i_createObj(const DOMElement* element,
                                 DataObject*& refpObject);

};


#endif
