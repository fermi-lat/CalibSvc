/** 
* @file CalibSvc_load.cpp
* @brief This is needed for forcing the linker to load all components
* of the library.
*
*  $Header: /nfs/slac/g/glast/ground/cvs/CalibSvc/src/Dll/CalibSvc_load.cxx,v 1.12 2004/06/11 20:49:07 jrb Exp $
*/

#include "GaudiKernel/DeclareFactoryEntries.h"

DECLARE_FACTORY_ENTRIES(CalibSvc) {
  // Useful for now to fake event time  
  DECLARE_ALGORITHM(CalibEvtClock);

  DECLARE_SERVICE(CalibDataSvc);


  DECLARE_SERVICE(CalibMySQLCnvSvc);
  DECLARE_SERVICE(CalibXmlCnvSvc);

  DECLARE_CONVERTER(XmlTest1Cnv);
  DECLARE_CONVERTER(XmlBadStripsCnv);
  DECLARE_CONVERTER(XmlCalPedCnv);
  DECLARE_CONVERTER(XmlCalGainCnv);
  DECLARE_CONVERTER(XmlCalMuSlopeCnv);
  DECLARE_CONVERTER(XmlCalLightAttCnv);
  DECLARE_CONVERTER(XmlCalLightAsymCnv);
  DECLARE_CONVERTER(XmlCalIntNonlinCnv);

  DECLARE_CONVERTER(XmlAcdPedCnv);
  DECLARE_CONVERTER(XmlAcdGainCnv);


  DECLARE_SERVICE(CalibRootCnvSvc);
  DECLARE_CONVERTER(RootCalGainCnv)
} 
