// $Header: /nfs/slac/g/glast/ground/cvs/CalibSvc/src/CalibXMLCnv/cnv/XmlSAABoundaryCnv.cxx,v 1.1 2007/08/01 16:39:09 markusa Exp $

#include <string>
#include "XmlLATAlignmentCnv.h"
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

#include "CalibData/CalibLATAlignment.h"
#include "CalibData/CalibTime.h"
#include "xmlBase/Dom.h"

// Temporary.  Hope to find a better way to do this
#include "CalibData/CalibModel.h"

static CnvFactory<XmlLATAlignmentCnv> s_factory;
const  ICnvFactory& XmlLATAlignmentCnvFactory = s_factory;


XmlLATAlignmentCnv::XmlLATAlignmentCnv( ISvcLocator* svc) :
  XmlBaseCnv(svc, CLID_Calib_NAS_LATAlignment) { 
}


const CLID& XmlLATAlignmentCnv::objType() const {
  return CLID_Calib_NAS_LATAlignment;
}

const CLID& XmlLATAlignmentCnv::classID() {
  return CLID_Calib_NAS_LATAlignment;
}

 
// Create our specific object
StatusCode XmlLATAlignmentCnv::i_createObj(const DOMElement* element, 
                                           DataObject*& refpObject)
{
   using xmlBase::Dom;

  // Fetch quantities we need: the edges of the polygon
   DOMElement* angle = Dom::findFirstChildByName(element, "angle");
   if (angle == 0) return StatusCode::FAILURE;

   try {
     m_roll   = Dom::getDoubleAttribute(angle, "roll");
     m_pitch = Dom::getDoubleAttribute(angle, "pitch");
     m_yaw   = Dom::getDoubleAttribute(angle, "yaw");
   } catch (xmlBase::DomException ex) {
	std::cerr << "From CalibSvc::XmlLATAlignmentCnv::i_crateObj " << std::endl;
	std::cerr << ex.getMsg() << std::endl;
   }
    
   refpObject = new  
     CalibData::CalibLATAlignment(m_roll, m_pitch, m_yaw, *m_vstart, *m_vend,m_serNo);

   return StatusCode::SUCCESS;
}
