// $Header: /nfs/slac/g/glast/ground/cvs/CalibSvc/src/CalibXMLCnv/cnv/XmlCalMuSlopeCnv.h,v 1.2 2004/06/11 20:48:35 jrb Exp $
#ifndef CalibSvc_XmlCalMuSlopeCnv_h
#define CalibSvc_XmlCalMuSlopeCnv_h

/** @class XmlCalMuSlopeCnv

  Converter from xml to TCDS CAL mu slope class

  @author J. Bogart
*/
#include "XmlCalBaseCnv.h"

template <class TYPE> class CnvFactory;

class XmlCalMuSlopeCnv : public XmlCalBaseCnv {

  /// Friend needed for instantiation
  friend class CnvFactory<XmlCalMuSlopeCnv>;
public:
  const CLID& objType() const;
  static const CLID& classID();
protected:

  XmlCalMuSlopeCnv(ISvcLocator* svcs);

  virtual ~XmlCalMuSlopeCnv() {}       // most likely nothing to do 

  virtual StatusCode i_createObj(const DOMElement* element,
                                 DataObject*& refpObject);

};


#endif
