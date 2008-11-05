# $Header: /nfs/slac/g/glast/ground/cvs/GlastRelease-scons/CalibSvc/CalibSvcLib.py,v 1.1 2008/07/09 21:13:41 glastrm Exp $
def generate(env, **kw):
    if not kw.get('depsOnly', 0):
        env.Tool('addLibrary', library = ['CalibSvc'])
    env.Tool('CalibDataLib')
    env.Tool('xmlBaseLib')
    env.Tool('calibUtilLib')
    env.Tool('EventLib')
    env.Tool('commonRootDataLib')
    env.Tool('calibRootDataLib')
    env.Tool('addLibrary', library = env['rootLibs'])
    env.Tool('addLibrary', library = env['rootGuiLibs'])
    env.Tool('LdfEventLib')
def exists(env):
    return  1;
