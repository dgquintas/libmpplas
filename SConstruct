import os

opts  = Options()
opts.AddOptions(
    
    EnumOption('optLevel', 'Compiler optimization level', '0', 
                allowed_values=('0','1','2','3','s')),
    
    EnumOption('arch', 'Target architecture', 'auto',
                allowed_values=('auto', 'generic','x86','x86Prof','ppc','x86_64','x86_64Prof')),
    
    BoolOption('enableExtraOpt', 'Use extra optimization flags', 0),
    BoolOption('enableDebug', 'Generate debug symbols', 0),
    BoolOption('enableAOPProf', 'Enable the profiling mechanisms via AOP', 0),
    BoolOption('enableOpenmp', 'Use OpenMP (if available)', 1),
    BoolOption('enableRelease', 'Generate a RELEASE version (optimized)', 0),
    BoolOption('enableWarnings', 'Compile with -Wall and similar flags', 0),
    BoolOption('abortOnWarnings', 'Compile with -Werror: a compilation warning aborts the build', 0),
    EnumOption('enableSIMD', 'Use the given SIMD kernel (if available)', 'auto',
                allowed_values=('auto', 'nosimd', 'sse', 'sse2') )
    )   

env = Environment( options = opts, ENV=os.environ)

if os.environ.has_key('CXX'):
  env.Replace(CXX = os.environ['CXX'])   
if os.environ.has_key('CXXFLAGS'):
  env.Replace(CXXFLAGS = os.environ['CXXFLAGS'])   


Help(opts.GenerateHelpText(env))
env['CONFIG_LOG'] = '#/.config.log'
env['INSTALL_DIR_BIN'] = '#/bin'
env['INSTALL_DIR_LIB'] = '#/lib'
env['INSTALL_DIR_TESTS'] = '#/bin/tests'

Export('env')

SConscript(dirs="src", duplicate=0)

SConscript(dirs="doc", duplicate=0)

