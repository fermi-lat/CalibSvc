// $Header: /nfs/slac/g/glast/ground/cvs/CalibSvc/src/CalibXMLCnv/cnv/XmlCalBaseCnv.h,v 1.2 2004/09/23 20:49:08 jrb Exp $
#ifndef CalibData_XmlCalBaseCnv_h
#define CalibData_XmlCalBaseCnv_h

/** @class XmlCalBaseCnv 

  Base class for CAL calibration converters from XML files to TCDS.
  All such converters need to do certain things, which are
  handled here.  Methods common to *all* calibrations are in the
  base class XmlBaseCnv

  @author J. Bogart
*/

#include "XmlBaseCnv.h"

class XmlCalBaseCnv : public XmlBaseCnv {

public:

  XmlCalBaseCnv(ISvcLocator* svc, const CLID& clid);
  virtual ~XmlCalBaseCnv() {};


  //  virtual StatusCode finalize();

  /**
   Create the transient representation of an object, given an opaque
   address.  This and the following update method comprise the core 
   functionality of calibration converters.
  */
  //  virtual StatusCode createObj(IOpaqueAddress* addr,
  //                               DataObject*& refpObject);

  //  virtual StatusCode i_createObj (const DOM_Element& element,
  //                                  DataObject*& refpObject);

  //  virtual StatusCode i_processObj(DataObject* pObject,
  //

  /// Convenience routine used by most CAL calibration types, which
  /// have a <dimension> element describing how the remainder of the
  /// data is laid out.
  StatusCode readDimension(const DOMElement* docElt, 
                           unsigned& nRow, unsigned& nCol, 
                           unsigned& nLayer,
                           unsigned& nXtal, unsigned& nFace,
                           unsigned& nRange,
                           unsigned* nDacCol=0,
                           unsigned* nXpos=0);

  /// Another one to find first range element
  DOMElement* findFirstRange(const DOMElement* docElt);

  /// Still another one to navigate XML file and find next set of range data
  DOMElement* findNextRange(const DOMElement* rangeElt);

protected:
  /// A place to keep track of where we are if we're handling CAL data
  unsigned m_nRow;
  unsigned m_nCol;
  unsigned m_nLayer;
  unsigned m_nXtal;
  unsigned m_nFace;
  unsigned m_nRange;

};

#endif
