/** 
* @file CalibSvc_load.cpp
* @brief This is needed for forcing the linker to load all components
* of the library.
*
*  $Header: /nfs/slac/g/glast/ground/cvs/CalibSvc/src/Dll/CalibSvc_load.cxx,v 1.5 2003/01/29 18:32:50 jrb Exp $
*/

#include "GaudiKernel/DeclareFactoryEntries.h"

DECLARE_FACTORY_ENTRIES(CalibSvc) {
  DECLARE_SERVICE(CalibDataSvc);


  DECLARE_SERVICE(CalibMySQLCnvSvc);
  DECLARE_SERVICE(CalibXmlCnvSvc);

  DECLARE_CONVERTER(XmlTest1Cnv);
  DECLARE_CONVERTER(XmlBadStripsCnv);
  DECLARE_CONVERTER(XmlCalPedCnv);
  DECLARE_CONVERTER(XmlCalGainCnv);

  // Following doesn't exist yet.
  //  DECLARE_SERVICE(CalibRootCnvSvc);

} 
