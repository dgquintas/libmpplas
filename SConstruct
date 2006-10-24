

opts  = Options()
opts.AddOptions(
    
    EnumOption('optLevel', 'Compiler optimization level', '3', 
                allowed_values=('0','1','2','3')),
    
    EnumOption('arch', 'Target architecture', 'x86',
                allowed_values=('generic','x86','ppc')),
    
    BoolOption('enableProf','Use the profiling version of the kernel', 0),
    BoolOption('enableExtraOpt', 'Use extra optimization flags', 1),
    BoolOption('enableDebug', 'Generate debug symbols', 0),
    BoolOption('enableWarnings', 'Compile with -Wall and similar flags', 1)
    )   

env = Environment(options = opts)
Help(opts.GenerateHelpText(env))
env['CONFIG_LOG'] = '#/config.log'
env['INSTALL_DIR'] = '#/bin'
env['INSTALL_DIR_TESTS'] = '#/bin/tests'


#options processing starts

Export('env')


SConscript(dirs="src", duplicate=0)

#SConscript("doc/SConscript")





