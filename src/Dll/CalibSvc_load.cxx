/** 
* @file CalibSvc_load.cpp
* @brief This is needed for forcing the linker to load all components
* of the library.
*
*  $Header: /nfs/slac/g/glast/ground/cvs/GlastSvc/src/Dll/GlastSvc_load.cpp,v 1.20 2002/05/10 19:19:11 burnett Exp $
*/

#include "GaudiKernel/DeclareFactoryEntries.h"

DECLARE_FACTORY_ENTRIES(CalibSvc) {
  DECLARE_SERVICE(CalibDataSvc);


  DECLARE_SERVICE(CalibMySQLCnvSvc);

  // Following don't exist yet.  besides, they will be private,
  // invoked only by the MySQL converter, so maybe they don't
  // have to be declared here at all.
  //  DECLARE_SERVICE(CalibXMLCnvSvc);
  //  DECLARE_SERVICE(CalibROOTCnvSvc);

  DECLARE_CONVERTER(MetadataCnv);   // to convert MetadataEntryCol. NYW.


} 
