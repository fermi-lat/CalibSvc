// $Header: /nfs/slac/g/glast/ground/cvs/CalibSvc/src/CalibXMLCnv/cnv/XmlCalPedCnv.cxx,v 1.4 2004/01/31 01:53:56 jrb Exp $

#include <string>
#include "XmlCalPedCnv.h"

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

#include "CalibData/Cal/CalCalibPed.h"
#include "CalibData/CalibTime.h"
#include "xml/Dom.h"

// Temporary.  Hope to find a better way to do this
#include "CalibData/CalibModel.h"

static CnvFactory<XmlCalPedCnv> s_factory;
const  ICnvFactory& XmlCalPedCnvFactory = s_factory;



XmlCalPedCnv::XmlCalPedCnv( ISvcLocator* svc) :
  XmlBaseCnv(svc, CLID_Calib_CAL_Ped) { 
}


const CLID& XmlCalPedCnv::objType() const {
  return CLID_Calib_CAL_Ped;
}

const CLID& XmlCalPedCnv::classID() {
  return CLID_Calib_CAL_Ped;
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
  /// <calPed> element and make a CalibData::Ped with it
  CalibData::Ped* processRange(DOM_Element pedElt) {
    using xml::Dom;

    // Could check here to make sure it really is a <calPed>
    float avg, sig, cos;
    try {
      avg = xml::Dom::getDoubleAttribute(pedElt, "avg");
      sig = xml::Dom::getDoubleAttribute(pedElt, "sig");
      cos = xml::Dom::getDoubleAttribute(pedElt, "cos");
    }
    catch (xml::DomException ex) {
      std::cerr << "From CalibSvc::XmlCalPedCnv::processRange" << std::endl;
      std::cerr << ex.getMsg() << std::endl;
      throw ex;
    }

    return new CalibData::Ped(avg, sig, cos);
  }
}

// Create our specific object
StatusCode XmlCalPedCnv::i_createObj(const DOM_Element& docElt, 
                                     DataObject*& refpObject)
{
  using xml::Dom;
  using CalibData::Ped;

  unsigned nRow, nCol, nLayer, nXtal, nFace, nRange;
  // need dimensions to call the constructor
  StatusCode status = 
    readDimension(docElt, nRow, nCol, nLayer, nXtal, nFace, nRange);
  if (status == StatusCode::FAILURE) return status;
  
  // refpObject
  CalibData::CalCalibPed* pObj = 
    new CalibData::CalCalibPed(nRow, nCol, nLayer, nXtal, nFace, nRange);
  refpObject = pObj;
  if (!pObj) return StatusCode::FAILURE;

  setBaseInfo(pObj);

  DOM_Element rangeElt = findFirstRange(docElt);

  while (rangeElt != DOM_Element() ) {
    Ped* ped = processRange(rangeElt);
    pObj->putRange(m_nRow, m_nCol, m_nLayer, m_nXtal, m_nRange, m_nFace, ped);
    rangeElt = findNextRange(rangeElt);
  }

  return StatusCode::SUCCESS;
}
