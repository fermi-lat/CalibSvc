// $Header: /nfs/slac/g/glast/ground/cvs/CalibSvc/src/CalibXMLCnv/cnv/XmlCalPedCnv.h,v 1.2 2003/03/17 06:55:34 jrb Exp $
#ifndef CalibSvc_XmlCalPedCnv_h
#define CalibSvc_XmlCalPedCnv_h

/** @class XmlCalPed1  

  Converter from xml to TCDS CAL pedestals class

  @author J. Bogart
*/
#include "XmlCalBaseCnv.h"
#include <xercesc/dom/DOM_Element.hpp>

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

  virtual StatusCode i_createObj(const DOM_Element& element,
                                 DataObject*& refpObject);

};


#endif
