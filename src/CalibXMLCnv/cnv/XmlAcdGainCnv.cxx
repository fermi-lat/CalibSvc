// $Header: /nfs/slac/g/glast/ground/cvs/CalibSvc/src/CalibXMLCnv/cnv/XmlAcdPedCnv.cxx,v 1.3 2005/01/03 19:32:38 jrb Exp $

#include <string>

#include "GaudiKernel/CnvFactory.h"
#include "GaudiKernel/IOpaqueAddress.h"
#include "GaudiKernel/DataObject.h"
#include "GaudiKernel/IAddressCreator.h"
#include "GaudiKernel/IDataProviderSvc.h"
#include "GaudiKernel/IConversionSvc.h"
#include "GaudiKernel/MsgStream.h"
#include "GaudiKernel/GenericAddress.h"

#include "CalibSvc/ICalibXmlSvc.h"
#include "CalibSvc/ICalibMetaCnvSvc.h"

#include "CalibData/Acd/AcdCalibGain.h"
#include "CalibData/CalibTime.h"
#include "xmlBase/Dom.h"

// Temporary.  Hope to find a better way to do this
#include "CalibData/CalibModel.h"



/** @class XmlAcdGainCnv

  Converter from xml to TCDS ACD gains class

  @author J. Bogart
*/
#include "XmlAcdBaseCnv.h"

class XmlAcdGainCnv;

// template <class TYPE> class CnvFactory;
static CnvFactory<XmlAcdGainCnv> s_factory;
const  ICnvFactory& XmlAcdGainCnvFactory = s_factory;

class XmlAcdGainCnv : public XmlAcdBaseCnv {

  /// Friend needed for instantiation
  friend class CnvFactory<XmlAcdGainCnv>;
public:
  const CLID& objType() const;
  static const CLID& classID();
protected:

  XmlAcdGainCnv(ISvcLocator* svcs);

  virtual ~XmlAcdGainCnv() {}       // most likely nothing to do 

  virtual StatusCode i_createObj(const DOMElement* element,
                                 DataObject*& refpObject);

};


//

XmlAcdGainCnv::XmlAcdGainCnv( ISvcLocator* svc) :
  XmlAcdBaseCnv(svc, CLID_Calib_ACD_ElecGain) { 
}


const CLID& XmlAcdGainCnv::objType() const {
  return CLID_Calib_ACD_ElecGain;
}

const CLID& XmlAcdGainCnv::classID() {
  return CLID_Calib_ACD_ElecGain;
}

namespace {
  /// Local utility which knows how to get the information out of a
  /// <acdGain> element and make a CalibData::AcdGain with it
  CalibData::AcdGain* processPmt(DOMElement* pmtElt) {
    using xmlBase::Dom;

    // Element we're interested in is child of <pmt>
    DOMElement* gainElt = xmlBase::Dom::getFirstChildElement(pmtElt);

    // Could check here to make sure it really is an <acdGain>
    float peak, width;
    unsigned   status;
    try {
      peak = xmlBase::Dom::getDoubleAttribute(gainElt, "peak");
      width = xmlBase::Dom::getDoubleAttribute(gainElt, "width");
      status = xmlBase::Dom::getIntAttribute(gainElt, "status");
    }
    catch (xmlBase::DomException ex) {
      std::cerr << "From CalibSvc::XmlAcdGainCnv::processPmt" << std::endl;
      std::cerr << ex.getMsg() << std::endl;
      throw ex;
    }

    return new CalibData::AcdGain(peak, width, status);
  }
}

// Create our specific object
StatusCode XmlAcdGainCnv::i_createObj(const DOMElement* docElt, 
                                     DataObject*& refpObject)
{
  using xmlBase::Dom;
  using CalibData::AcdGain;

  unsigned nFace, nRow, nCol, nPmt, nDet, nNA;
  // need dimensions to call the constructor
  StatusCode status = 
    readAcdDimension(docElt, nDet, nFace, nRow, nCol, nNA, nPmt);
  if (status == StatusCode::FAILURE) return status;
  
  // refpObject
  CalibData::AcdCalibGain* pObj = 
    new CalibData::AcdCalibGain(nFace, nRow, nCol, nNA, nPmt);
  refpObject = pObj;
  if (!pObj) return StatusCode::FAILURE;

  setBaseInfo(pObj);

  DOMElement* pmtElt = findFirstPmt(docElt);

  while (pmtElt != 0 ) {
    AcdGain* pGain = processPmt(pmtElt);
    pObj->putPmt(m_id, m_nPmt, pGain);
    pmtElt = findNextPmt(pmtElt);
  }

  return StatusCode::SUCCESS;
}
