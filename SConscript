# -*- python -*-
# $Header: /nfs/slac/g/glast/ground/cvs/GlastRelease-scons/CalibSvc/SConscript,v 1.11 2009/09/14 19:25:05 jrb Exp $
# Authors: Joanne Bogart <jrb@slac.stanford.edu>
# Version: CalibSvc-00-40-01
Import('baseEnv')
Import('listFiles')
Import('packages')
progEnv = baseEnv.Clone()
libEnv = baseEnv.Clone()

libEnv.Tool('CalibSvcLib', depsOnly = 1)
CalibSvc = libEnv.SharedLibrary('CalibSvc', listFiles(['src/*.cxx', 'src/CalibDataSvc/*.cxx', 'src/CalibMySQLCnv/*.cxx',
                                                       'src/CalibXMLCnv/*.cxx', 'src/CalibXMLCnv/cnv/*.cxx',
                                                       'src/CalibROOTCnv/*.cxx', 'src/CalibROOTCnv/cnv/*.cxx',
                                                       'src/util/*.cxx', 'src/Dll/*.cxx']))
progEnv.Tool('CalibSvcLib')
test_CalibSvc = progEnv.GaudiProgram('test_CalibSvc', listFiles(['src/test/*.cxx']), test = 1)

progEnv.Tool('registerObjects', package = 'CalibSvc', libraries = [CalibSvc], testApps = [test_CalibSvc], includes = listFiles(['CalibSvc/*.h']))




