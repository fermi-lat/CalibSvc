// $Header: /nfs/slac/g/glast/ground/cvs/CalibSvc/src/CalibXMLCnv/cnv/XmlCalLightAttCnv.cxx,v 1.4 2003/03/25 02:06:31 jrb Exp $

#include <string>
#include "XmlCalLightAttCnv.h"

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

#include "CalibData/Cal/CalCalibLightAtt.h"
#include "CalibData/CalibTime.h"
#include "xml/Dom.h"

// Temporary.  Hope to find a better way to do this
#include "CalibData/CalibModel.h"

static CnvFactory<XmlCalLightAttCnv> s_factory;
const  ICnvFactory& XmlCalLightAttCnvFactory = s_factory;



XmlCalLightAttCnv::XmlCalLightAttCnv( ISvcLocator* svc) :
  XmlBaseCnv(svc, CLID_Calib_CAL_LightAtt) { 
}


const CLID& XmlCalLightAttCnv::objType() const {
  return CLID_Calib_CAL_LightAtt;
}

const CLID& XmlCalLightAttCnv::classID() {
  return CLID_Calib_CAL_LightAtt;
}

// Don't need to override in this case
/*
StatusCode XmlBaseCnv::i_processObj(DataObject*, // pObject,
                                    IOpaqueAddress*)  {  //pAddress
  return StatusCode::SUCCESS;
}
*/

namespace {
  /// Local utility which knows how to get the information out of a
  /// <calLightAtt> element and make a CalibData::LightAtt with it
  CalibData::LightAtt* processRange(DOM_Element lightAttElt) {
    using xml::Dom;

    // Could check here to make sure it really is a <calLightAtt>

    std::string att = Dom::getAttribute(lightAttElt, "att");
    float light_att = atof(att.c_str());
    att = Dom::getAttribute(lightAttElt, "norm");
    float norm = atof(att.c_str());

    return new CalibData::LightAtt(light_att, norm);
  }
}

// Create our specific object
StatusCode XmlCalLightAttCnv::i_createObj(const DOM_Element& docElt, 
                                     DataObject*& refpObject)
{
  using xml::Dom;
  using CalibData::LightAtt;

  unsigned nRow, nCol, nLayer, nXtal, nFace, nRange;
  // need dimensions to call the constructor
  StatusCode status = 
    readDimension(docElt, nRow, nCol, nLayer, nXtal, nFace, nRange);
  if (status == StatusCode::FAILURE) return status;
  
  // refpObject
  CalibData::CalCalibLightAtt* pObj = 
    new CalibData::CalCalibLightAtt(nRow, nCol, nLayer, nXtal, nFace, nRange);
  refpObject = pObj;
  if (!pObj) return StatusCode::FAILURE;

  setBaseInfo(pObj);

  DOM_Element rangeElt = findFirstRange(docElt);

  while (rangeElt != DOM_Element() ) {
    LightAtt* pLightAtt = processRange(rangeElt);
    pObj->putRange(m_nRow, m_nCol, m_nLayer, m_nXtal, m_nRange, 
                   m_nFace, pLightAtt);
    rangeElt = findNextRange(rangeElt);
  }

  return StatusCode::SUCCESS;
}