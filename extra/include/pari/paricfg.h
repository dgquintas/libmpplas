/*  This file was created by Configure. Any change made to it will be lost
 *  next time Configure is run. */
#ifndef __CONFIG_H__
#define __CONFIG_H__
#define UNIX
#define GPHELP "/afs/cern.ch/user/d/dgquinta/bin/gphelp"
#define GPDATADIR "/afs/cern.ch/user/d/dgquinta/share/pari"
#define SHELL_Q '\''

#define PARIVERSION "GP/PARI CALCULATOR Version 2.3.1 (released)"
#ifdef __cplusplus
# define PARIINFO "C++ amd64 running linux (x86-64 kernel) 64-bit version"
#else
# define PARIINFO "amd64 running linux (x86-64 kernel) 64-bit version"
#endif
#define PARI_VERSION_CODE 131841
#define PARI_VERSION(a,b,c) (((a) << 16) + ((b) << 8) + (c))
#define PARI_VERSION_SHIFT 8

#define PARI_DOUBLE_FORMAT -
#define GCC_VERSION "3.4.6 20060404 (Red Hat 3.4.6-3)"
#define ASMINLINE

/*  Location of GNU gzip program (enables reading of .Z and .gz files). */
#define GNUZCAT
#define ZCAT "/usr/bin/gzip -dc"

/*  Use GNU readline library
 *  This is incompatible with SUN commandtools (not with shelltools).
 */
#define READLINE "4.3"
#define HAS_COMPLETION_APPEND_CHAR
#define HAS_RL_GENERIC_BIND
#define HAS_RL_SAVE_PROMPT
#define HAS_RL_MESSAGE
#define HAS_RL_COMPLETION_MATCHES
#define HAS_RL_COMPLETION_FUNC_T
#define HAS_HISTORY_H
#define HAS_RL_ATTEMPTED_COMPLETION_OVER
#define HAS_RL_COMPLETION_QUERY_ITEMS
#define HAS_RL_BIND_KEY_IN_MAP
#define HAS_RL_LIBRARY_VERSION

#define LONG_IS_64BIT
#define USE_GETRUSAGE 1
#define HAS_SIGACTION
#define HAS_DLOPEN
#define STACK_CHECK
#define HAS_VSNPRINTF
#define HAS_TIOCGWINSZ
#define HAS_STRFTIME
#define HAS_STAT
#endif
