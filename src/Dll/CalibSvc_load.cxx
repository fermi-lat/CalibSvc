/** 
* @file CalibSvc_load.cpp
* @brief This is needed for forcing the linker to load all components
* of the library.
*
*  $Header: /nfs/slac/g/glast/ground/cvs/CalibSvc/src/Dll/CalibSvc_load.cxx,v 1.1.1.1 2002/11/14 21:30:13 jrb Exp $
*/

#include "GaudiKernel/DeclareFactoryEntries.h"

DECLARE_FACTORY_ENTRIES(CalibSvc) {
  DECLARE_SERVICE(CalibDataSvc);


  DECLARE_SERVICE(CalibMySQLCnvSvc);

  // Following don't exist yet.
  //  DECLARE_SERVICE(CalibXmlCnvSvc);
  //  DECLARE_SERVICE(CalibRootCnvSvc);

  DECLARE_CONVERTER(MetadataCnv);   // to convert MetadataEntryCol. NYW.


} 
