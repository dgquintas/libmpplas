import platform, time, sys

#############################################################
#                    SUPPORT FUNCTIONS                      #
#############################################################
def getNativelySupportedArchs():
  natArchs = ['generic']
  x86ArchMachines = ['i386', 'i486', 'i586', 'i686']
  currentPlatformMachine = platform.machine()

  
  if currentPlatformMachine in x86ArchMachines:
    natArchs.append('x86')
    if currentPlatformMachine == 'x86_64':
      natArchs.append('x86_64')
  elif currentPlatformMachine == 'ppc':
    natArchs.append('ppc')

  return tuple(natArchs)
#############################################################


opts  = Options()
opts.AddOptions(
    
    EnumOption('optLevel', 'Compiler optimization level', '2', 
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


#options processing starts
env.Append(CCFLAGS = ' -O' + env['optLevel'])

if env['enableProf']:
  env['arch'] += 'Prof'

env.Append(CPPDEFINES = {'ARCH': env['arch']})
if env['arch'] not in getNativelySupportedArchs():
  print "WARNING: the selected architecture (" + env['arch'] + ") is not natively supported by this system"
  for i in xrange(3):
    time.sleep(1)
    print '.',
    sys.stdout.flush()
  

if env['enableExtraOpt']:
  env.Append(CCFLAGS = ' -ffast-math')

if env['enableDebug']:
  env.Append(CCFLAGS = ' -g')

if env['enableWarnings']:
  env.Append(CCFLAGS = ' -Wall -W -Werror')
#options processing ends

# configuring starts
conf = Configure(env)
if not conf.CheckType('uint32_t', '#include <stdint.h>\n', 'C++'):
  print 'Could not find C99 type "uint32_t". Exiting...'
  Exit(1)
if not conf.CheckType('int32_t', '#include <stdint.h>\n', 'C++'):
  print 'Could not find C99 type "int32_t". Exiting...'
  Exit(1)
env = conf.Finish()
# configuring ends

Export('env')

SConscript("src/SConscript", build_dir="build", duplicate=0)
#SConscript("doc/SConscript")





