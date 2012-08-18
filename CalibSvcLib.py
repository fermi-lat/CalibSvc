# $Header: /nfs/slac/g/glast/ground/cvs/GlastRelease-scons/CalibSvc/CalibSvcLib.py,v 1.2 2008/11/05 21:15:33 ecephas Exp $
def generate(env, **kw):
    if not kw.get('depsOnly', 0):
        env.Tool('addLibrary', library = ['CalibSvc'])
        if env['PLATFORM']=='win32' and env.get('CONTAINERNAME','')=='GlastRelease':
	    env.Tool('findPkgPath', package = 'CalibSvc') 
    env.Tool('CalibDataLib')
    env.Tool('xmlBaseLib')
    env.Tool('calibUtilLib')
    env.Tool('EventLib')
    env.Tool('commonRootDataLib')
    env.Tool('calibRootDataLib')
    env.Tool('addLibrary', library = env['rootLibs'])
    env.Tool('addLibrary', library = env['rootGuiLibs'])
    env.Tool('LdfEventLib')
    if env['PLATFORM']=='win32' and env.get('CONTAINERNAME','')=='GlastRelease':
        env.Tool('findPkgPath', package = 'MootSvc') 
def exists(env):
    return  1;
