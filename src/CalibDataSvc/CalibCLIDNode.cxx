#include "CalibCLIDNode.h"
/**  @file CalibCLIDNode.cxx

     $Header: /nfs/slac/g/glast/ground/cvs/CalibSvc/src/CalibDataSvc/CalibCLIDNode.cxx,v 1.1.1.1 2002/11/14 21:30:13 jrb Exp $

     @author Joanne Bogart
*/

// CLID_Calib_CalibCLIDNode gets a value in CalibModel.cxx, but
// this is in a different component; doubt I can pick it up correctly here.
// extern const CLID& CLID_Calib_CalibCLIDNode;
const CLID& CLID_Calib_CalibCLIDNode = 6000;
const CLID& CalibCLIDNode::classID() {
    return CLID_Calib_CalibCLIDNode;
}

std::ostream& CalibCLIDNode::fillStream(std::ostream& s) const {
  return s <<  "Child class ID = " << m_childClassID << std::endl;
}
