// $Header: /nfs/slac/g/glast/ground/cvs/CalibSvc/src/CalibXMLCnv/cnv/XmlTest1Cnv.h,v 1.4 2003/01/29 18:32:15 jrb Exp $
#ifndef CalibSvc_XmlTest1Cnv_h
#define CalibSvc_XmlTest1Cnv_h

/** @class XmlTest1  

  Converter from xml to very simple calibration data-like class to be 
  used for testing calibration infrastructure

  @author J. Bogart
*/
#include "XmlBaseCnv.h"
#include <xercesc/dom/DOM_Element.hpp>

template <class TYPE> class CnvFactory;

class XmlTest1Cnv : public XmlBaseCnv {

  /// Friend needed for instantiation
  friend class CnvFactory<XmlTest1Cnv>;
public:
  const CLID& objType() const;
  static const CLID& classID();
protected:

  XmlTest1Cnv(ISvcLocator* svcs);

  virtual ~XmlTest1Cnv() {}       // most likely nothing to do 

  virtual StatusCode i_createObj(const DOM_Element& element,
                                 DataObject*& refpObject);

  
};


#endif
