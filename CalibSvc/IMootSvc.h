//$Header: /nfs/slac/g/glast/ground/cvs/CalibSvc/CalibSvc/IMootSvc.h,v 1.2 2008/03/08 01:45:46 jrb Exp $
#ifndef IMootSvc_h
#define IMootSvc_h 1

#include "GaudiKernel/IInterface.h"

// External constants
#include "GaudiKernel/ClassID.h"


// Forward declarations

namespace MOOT {
  class MootQuery;
}

namespace CalibData {
  class MootParm;
  class MootParmCol;
}

static const InterfaceID IID_IMootSvc ("IMootSvc", 1, 0);

/** @class IMootSvc 

    Abstract interface of a service for access to MOOT information.
    See also data class definitions in CalibData/Moot


    @author Joanne Bogart
*/

class IMootSvc : virtual public IInterface   {

public:
  // Re-implemented from IInterface
  static const InterfaceID& interfaceID() { return IID_IMootSvc; }

  /// Return absolute path for parameter source file of specified class.
  /// If none return empty string.
  virtual std::string getMootParmPath(const std::string& cl, 
                                      unsigned& hw)=0;


  /// Return MootParm structure for parameter source file of specified class.
  /// If none return blank structure.
  virtual const CalibData::MootParm* getMootParm(const std::string& cl, 
                                                 unsigned& hw)=0;

  // Return pointer to Moot parameter collection.  Also set output
  // arg. hw to current hw key
  virtual const CalibData::MootParmCol* getMootParmCol(unsigned& hw)=0;


  /// Return last LATC master key seen in data
  virtual unsigned getHardwareKey()=0;


  /// Return index in MootParmCol of specified class
  virtual int latcParmIx(const std::string& parmClass) const =0;


  // Get handle for metadata access from mootCore.
  virtual MOOT::MootQuery* getConnection() const = 0;
};

#endif

