#!/usr/bin/python
# -*- coding: UTF-8 -*-
import os

modo = ARGUMENTS.get('mode', 'release')
if not modo in ['debug', 'release']:
    print "Advertencia: no especificó un modo adecuado, usando debug"
    modo = 'debug'

if modo == 'release':
    try:
        banderas = os.environ["CFLAGS"]
    except:
        banderas = ['-O2']
else: banderas = ["-O0", "-g3", "-Wall", "-c", "-fmessage-length=0"]

print "compilando en modo %s"%modo, banderas

env = Environment()
env.Append(CXXFLAGS=banderas)
env.Append(CPPFLAGS=banderas)
env.Append(CFLAGS=banderas)
 

env.StaticLibrary( "src/thiao.cpp" )
env.StaticLibrary( "src/remote.cpp" )
env.StaticLibrary( "src/Host.cpp" )
env.StaticLibrary( "src/VirtualMachine.cpp" )


libs   = ["xmlrpc++",
#		"xmlrpc_packetsocket", 
		"xmlrpc_client++",
#		"xmlrpc_client", 
#		"xmlrpc_parse", 
#		"xmlrpc_xmltok", 
#		"xmlrpc", 
#		"xmlrpc_util"
		"remote",
		"tinyxml",
		"Host",
		"VirtualMachine",
		"sqlite3",
		"thiao",
]


env.Program( target="bin/Suspend",  source="src/Suspend.cpp",    LIBS=libs, LIBPATH="./src/" )
env.Program( target="bin/Resume",   source="src/Resume.cpp",     LIBS=libs, LIBPATH="./src/" )
env.Program( target="bin/balancer", source=["src/balancer.cpp"], LIBS=libs, LIBPATH="./src/" )


