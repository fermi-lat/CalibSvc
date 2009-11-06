# -*- python -*-
# $Header: /nfs/slac/g/glast/ground/cvs/GlastRelease-scons/CalibSvc/SConscript,v 1.13 2009/11/05 18:43:14 heather Exp $
# Authors: Joanne Bogart <jrb@slac.stanford.edu>
# Version: CalibSvc-00-40-02
Import('baseEnv')
Import('listFiles')
Import('packages')
progEnv = baseEnv.Clone()
libEnv = baseEnv.Clone()

libEnv.Tool('CalibSvcLib', depsOnly = 1)
CalibSvc = libEnv.SharedLibrary('CalibSvc',
                                listFiles(['src/*.cxx', 'src/CalibDataSvc/*.cxx',
                                           'src/CalibMySQLCnv/*.cxx',
                                           'src/CalibXMLCnv/*.cxx',
                                           'src/CalibXMLCnv/cnv/*.cxx',
                                           'src/CalibROOTCnv/*.cxx',
                                           'src/CalibROOTCnv/cnv/*.cxx',
                                           'src/util/*.cxx', 'src/Dll/*.cxx']))
progEnv.Tool('CalibSvcLib')
test_CalibSvc = progEnv.GaudiProgram('test_CalibSvc',
                                     listFiles(['src/test/*.cxx']), test = 1)

progEnv.Tool('registerTargets', package = 'CalibSvc',
             libraryCxts = [[CalibSvc, libEnv]],
                             testAppCxts = [[test_CalibSvc, progEnv]],
                             includes = listFiles(['CalibSvc/*.h']))




