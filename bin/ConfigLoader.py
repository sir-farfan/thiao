#!/usr/bin/python3

'''
ConfigLoader.py - Loads the default configuration stored in the file thiao.cfg

--------------------------------------------------------------------------------

Copyright (C) 2011 Ismael Farfán. All rights reserved.

This file is part of Thiao.

Thiao is free software: you can redistribute it and/or modify it under the terms
of the GNU General Public License as published by the Free Software Foundation,
either version 3 of the License, or (at your option) any later version.

Thiao is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
Thiao.  If not, see <http://www.gnu.org/licenses/>.

-------------------------------------------------------------------------------- 

http://docs.python.org/py3k/library/configparser.html
'''

import configparser

config = configparser.ConfigParser()
config.read("/opt/thiao/thiao.cfg")

thiaoHome = config.get("Thiao", "ThiaoHome")
dbFile    = config.get("Thiao", "DBfile") 
tcleanLog = config.get("Thiao", "tcleanLog")
oneAuth   = config.get("Thiao", "OneAuth")
suspendLog= config.get("Thiao", "SuspendLog")
resumeLog = config.get("Thiao", "ResumeLog")

createVMFile = config.getboolean("vm", "CreateVMFile")
vmTemplate   = config.get("vm", "VMTemplate")
vmScriptDir  = config.get("vm", "VMScriptDir")
hostnameIsVMfile = config.getboolean("vm", "HostnameIsVMfile")

#unit test, print variables
if __name__ == "__main__":
    print ("[Thiao]")
    print ("ThiaoHome", thiaoHome)
    print ("DBfile", dbFile)
    print ("tcleanLog", tcleanLog)
    print ("OneAuth", oneAuth)
    print ("SuspendLog", suspendLog)
    print ("ResumeLog", resumeLog)
    print ("[vm]")
    print ("CreateVMFile", createVMFile)
    print ("VMTemplate", vmTemplate)
    print ("VMScriptDir", vmScriptDir)
    print ("HostnameIsVMfile", hostnameIsVMfile)
    
    
    
    