// $Header: /nfs/slac/g/glast/ground/cvs/CalibSvc/CalibSvc/ICalibRootSvc.h,v 1.1 2004/07/27 05:48:28 jrb Exp $

#ifndef ICalibRootSvc_h 
#define ICalibRootSvc_h

/** @class ICalibRootSvc
   Abstract interface to be satisfied by any ROOT conversion implementation.
 
   Support write-on-demand of a calibration object in the TDS

*/
#include "GaudiKernel/IInterface.h"
#include "GaudiKernel/ClassID.h"    // for storage types
#include <string>

// Can't use ROOT_StorageType as our storage type or the 
// Persistency service will get confused.  Instead give an alias
// to one we can be pretty sure is unused for GLAST

unsigned const long CALIBROOT_StorageType  = CDF_StorageType;


static const InterfaceID IID_ICalibRootSvc("ICalibRootSvc", 1, 0);

class DataObject;

namespace CalibData {
  class CalibBase;
}

class ICalibRootSvc : virtual public IInterface 
{
public:
  // Re-implemented from IInterface
  static const InterfaceID& interfaceID() { return IID_ICalibRootSvc; }
  
  /**
   * Method to write a ROOT file corresponding to TDS object
   * 
   * @param fileName the name of the file to be written
   * @return the document issued from the parsing
   */
  virtual StatusCode writeToRoot(const std::string& outputFile, 
                                 const std::string& tdsPath) = 0;
  virtual StatusCode writeToRoot(const std::string& outputFile, 
                                 CalibData::CalibBase *calib) = 0;

  // Do we also want a "reset" or "clearDocument" ?  Can in any case
  // do this internally when a new document is to be parsed so might not
  // be necessary to have explicit public method.
};


#endif
