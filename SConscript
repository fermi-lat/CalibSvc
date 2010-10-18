# -*- python -*-
# $Header: /nfs/slac/g/glast/ground/cvs/CalibSvc/SConscript,v 1.18 2010/06/12 01:33:17 jrb Exp $
# Authors: Joanne Bogart <jrb@slac.stanford.edu>
# Version: CalibSvc-00-40-04-gr01

Import('baseEnv')
Import('listFiles')
Import('packages')
progEnv = baseEnv.Clone()
libEnv = baseEnv.Clone()

libEnv.Tool('addLinkDeps', package='CalibSvc', toBuild='component')
CalibSvc =libEnv.SharedLibrary('CalibSvc',
                               listFiles(['src/*.cxx','src/CalibDataSvc/*.cxx',
                                          'src/CalibMySQLCnv/*.cxx',
                                          'src/CalibXMLCnv/*.cxx',
                                          'src/CalibXMLCnv/cnv/*.cxx',
                                          'src/CalibROOTCnv/*.cxx',
                                          'src/CalibROOTCnv/cnv/*.cxx',
                                          'src/util/*.cxx', 'src/Dll/*.cxx']))
progEnv.Tool('CalibSvcLib')

test_CalibSvc = progEnv.GaudiProgram('test_CalibSvc',
                                     listFiles(['src/test/*.cxx']),
                                     test = 1, package='CalibSvc')

progEnv.Tool('registerTargets', package = 'CalibSvc',
             libraryCxts = [[CalibSvc, libEnv]],
             testAppCxts = [[test_CalibSvc, progEnv]],
             includes = listFiles(['CalibSvc/*.h']),
             jo=listFiles(['src/test/*.txt', 'src/test/jobOptions.txt.*',
                           'src/defaultOptions.txt'] ))
