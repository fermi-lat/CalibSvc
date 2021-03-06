//$Header: /nfs/slac/g/glast/ground/cvs/CalibSvc/src/test/EvtClock.h,v 1.2 2003/01/14 23:26:06 jrb Exp $
#ifndef CALIBEVTCLOCK_H
#define CALIBEVTCLOCK_H 1

#include "facilities/Timestamp.h"

// Base class
#include "GaudiKernel/Algorithm.h"

// Forward declarations
class IDetDataSvc;

/** @class CalibEvtClock CalibEvtClock.h

    Simple algorithm to set fake event times on the detector data service.

    @author Joanne Bogart, adapted from similar class of Andrea Valassi 
*/

class CalibEvtClock : public Algorithm {

 public:

  CalibEvtClock( const std::string& name, ISvcLocator* pSvcLocator ); 
  
  // Algorithm standard methods
  StatusCode initialize();
  StatusCode execute();
  StatusCode finalize();
  
 private:

  /// Absolute time of current event
  //  longlong i_evtTime();
  facilities::Timestamp i_evtTime();

 private:

  /// Current event number
  long m_eventNumber;

  /// Absolute time of first event (yyyy-mm-dd_hh:mm, trailing fields
  /// optional)
  std::string m_startTimeAsc;

  /// Absolute time of first event (seconds)
  long m_startTime;

  /// Absolute time spacing between events
  long m_delayTime;

  /// Handle to the IDetDataSvc interface of the CalibDataSvc
  IDetDataSvc* m_detDataSvc;
  
};

#endif    // CALIBEVTCLOCK_H

