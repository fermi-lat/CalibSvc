/** 
* @file CalibSvc_load.cpp
* @brief This is needed for forcing the linker to load all components
* of the library.
*
*  $Header: /nfs/slac/g/glast/ground/cvs/CalibSvc/src/Dll/CalibSvc_load.cxx,v 1.2 2002/12/14 00:12:18 jrb Exp $
*/

#include "GaudiKernel/DeclareFactoryEntries.h"

DECLARE_FACTORY_ENTRIES(CalibSvc) {
  DECLARE_SERVICE(CalibDataSvc);


  DECLARE_SERVICE(CalibMySQLCnvSvc);
  DECLARE_SERVICE(CalibXmlCnvSvc);

  DECLARE_CONVERTER(XmlBaseCnv);  

  // Following don't exist yet.
  //  DECLARE_SERVICE(CalibRootCnvSvc);
  // DECLARE_CONVERTER(XmlTest1Cnv);


} 
