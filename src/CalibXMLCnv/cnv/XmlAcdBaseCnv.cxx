// $Header: $
#include "GaudiKernel/MsgStream.h"
#include "XmlAcdBaseCnv.h"
#include "xml/Dom.h"
// #include "idents/AcdId.h"


XmlAcdBaseCnv::XmlAcdBaseCnv(ISvcLocator* svc, const CLID& clid) :
  XmlBaseCnv(svc, clid), m_nFace(10000), m_nRow(10000), m_nCol(10000), 
  m_nPmt(10000), m_nRange(10000) {}

StatusCode XmlAcdBaseCnv::readAcdDimension(const DOM_Element& docElt, 
                                        unsigned& nFace,
                                        unsigned& nRow, unsigned& nCol, 
                                        unsigned& nPmt, unsigned& nRange) {
  using xml::Dom;

  MsgStream log(msgSvc(), "XmlBaseCnv" );
  DOM_Element dimElt = Dom::findFirstChildByName(docElt, "dimension");
  if (dimElt == DOM_Element()) return StatusCode::FAILURE;

  try {
    nFace = Dom::getIntAttribute(dimElt, "nFace");
    nRow = Dom::getIntAttribute(dimElt, "nRow");
    nCol = Dom::getIntAttribute(dimElt, "nCol");
    nPmt = Dom::getIntAttribute(dimElt, "nPmt");
    nRange = Dom::getIntAttribute(dimElt, "nRange");
  }
  catch (xml::DomException ex) {
    std::cerr << "From CalibSvc::XmlAcdBaseCnv::readAcdDimension" << std::endl;
    std::cerr << ex.getMsg() << std::endl;
    throw ex;
  }
  return StatusCode::SUCCESS;
}

DOM_Element XmlAcdBaseCnv::findFirstRange(const DOM_Element& docElt) {
  using xml::Dom;
  //  using idents::CalXtalId;

  /*  Rewrite for ACD */
  DOM_Element faceElt = Dom::findFirstChildByName(docElt, "face");
  // If no <face> elements, this file is useless
  if (faceElt == DOM_Element()) return faceElt;
  DOM_Element rowElt = Dom::getFirstChildElement(faceElt);
  if (rowElt == DOM_Element()) return rowElt;
  DOM_Element colElt = Dom::getFirstChildElement(rowElt);
  if (colElt == DOM_Element()) return colElt;
  DOM_Element pmtElt = Dom::getFirstChildElement(colElt);
  if (pmtElt == DOM_Element()) return pmtElt;

  DOM_Element rangeElt = Dom::getFirstChildElement(pmtElt);
  if (rangeElt == DOM_Element()) return rangeElt;
  
  try {
    m_nFace = Dom::getIntAttribute(faceElt, "iFace");
    m_nRow = Dom::getIntAttribute(rowElt, "iRow");
    m_nCol = Dom::getIntAttribute(colElt, "iCol");
    m_nPmt = Dom::getIntAttribute(pmtElt, "iPmt");
    m_nRange = Dom::getIntAttribute(rangeElt, "range");
  }
  catch (xml::DomException ex) {
    std::cerr << "From CalibSvc::XmlAcdBaseCnv::findFirstRange" << std::endl;
    std::cerr << ex.getMsg() << std::endl;
    throw ex;
  }

  return rangeElt;
}

/// Still another one to navigate XML file and find next set of range data
DOM_Element XmlAcdBaseCnv::findNextRange(const DOM_Element& rangeElt) {
  using xml::Dom;


  DOM_Element elt = Dom::getSiblingElement(rangeElt);

  if (elt != DOM_Element()) {
    m_nRange = Dom::getIntAttribute(elt, "range");
    return elt;
  }


  // Done with this pmt; look for sibling
  DOM_Node node = rangeElt.getParentNode();
  elt = static_cast<DOM_Element &>(node);   // current pmt
  elt = Dom::getSiblingElement(elt);          // next pmt

  if (elt != DOM_Element()) {
    m_nPmt = Dom::getIntAttribute(elt, "iPmt");

    elt = Dom::getFirstChildElement(elt);
    m_nRange = Dom::getIntAttribute(elt, "range");
    return elt;
  }


  // Done with this <col>
  node = node.getParentNode();  // current <col> element
  elt = static_cast<DOM_Element &>(node);
  elt = Dom::getSiblingElement(elt);         // next <col>

  if (elt != DOM_Element()) {
    try {
      m_nCol = Dom::getIntAttribute(elt, "iCol");
    }
    catch (xml::DomException ex) {
      std::cerr << "From CalibSvc::XmlAcdBaseCnv::findNextRange" << std::endl;
      std::cerr << ex.getMsg() << std::endl;
      throw ex;
    }

    // All child elements of col are pmt elements
    elt = Dom::getFirstChildElement(elt);
    m_nPmt = Dom::getIntAttribute(elt, "iPmt");

    elt = Dom::getFirstChildElement(elt);
    m_nRange = Dom::getIntAttribute(elt, "range");
    return elt;
  }

  // Done with this row
  node = node.getParentNode();  // current row
  elt = static_cast<DOM_Element &>(node);
  elt = Dom::getSiblingElement(elt);         // next row

  if (elt != DOM_Element()) {              // find first range in row
    try {
      m_nRow = Dom::getIntAttribute(elt, "iRow");
    }
    catch (xml::DomException ex) {
      std::cerr << "From CalibSvc::XmlAcdBaseCnv::findNextRange" << std::endl;
      std::cerr << ex.getMsg() << std::endl;
      throw ex;
    }
    

    // All child elements of row elements are column elements
    elt = Dom::getFirstChildElement(elt);

    try {
      m_nCol = Dom::getIntAttribute(elt, "iCol");
    }
    catch (xml::DomException ex) {
      std::cerr << "From CalibSvc::XmlAcdBaseCnv::findNextRange" << std::endl;
      std::cerr << ex.getMsg() << std::endl;
      throw ex;
    }

    // All child elements of col are pmt elements
    elt = Dom::getFirstChildElement(elt);
    m_nPmt = Dom::getIntAttribute(elt, "iPmt");
    
    elt = Dom::getFirstChildElement(elt);
    m_nRange = Dom::getIntAttribute(elt, "range");
    return elt;
  }

  // Done with this face
  node = node.getParentNode();  // current face
  elt = static_cast<DOM_Element &>(node);
  elt = Dom::getSiblingElement(elt);         // next face

  if (elt == DOM_Element()) return elt;

  // otherwise we've got a new face; go through the whole
  // rigamarole


  try {
    m_nFace = Dom::getIntAttribute(elt, "iFace");

    // All child elements of a face are row elements
    elt = Dom::getFirstChildElement(elt);
    m_nRow = Dom::getIntAttribute(elt, "iRow");

    // All child elements of row elements are col elements
    elt = Dom::getFirstChildElement(elt);
    m_nCol = Dom::getIntAttribute(elt, "iCol");


    // All child elements of col are pmt elements
    elt = Dom::getFirstChildElement(elt);
    m_nPmt = Dom::getIntAttribute(elt, "iPmt");
  }
  catch (xml::DomException ex) {
    std::cerr << "From CalibSvc::XmlAcdBaseCnv::findFirstRange" << std::endl;
    std::cerr << ex.getMsg() << std::endl;
    throw ex;
  }

  // All child elements of pmt elements are the thing we actually want!
  elt = Dom::getFirstChildElement(elt);
  m_nRange = Dom::getIntAttribute(elt, "range");

  return elt;
}