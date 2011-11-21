#!/usr/bin/python3
'''
***This module is DEPRECATED, use the c++ version instead: /src/Suspend.cpp***

hostSuspend.py - for use with SLURM as SuspendProgram, it will read the hostname
    from the parameters and attempt to shutdown the corresponding virtual machines
    
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

slurm scontrol update nodename=fg10 state=[idle|down]

params: fg10

$ env
CONSOLE=/dev/console
SHELL=/bin/sh
TERM=linux
rootmnt=/root
LD_LIBRARY_PATH=/usr/lib
INIT_VERSION=sysvinit-2.88
init=/sbin/init
COLUMNS=200
PATH=/sbin:/usr/sbin:/bin:/usr/bin
RUNLEVEL=2
runlevel=2
PWD=/var/log/slurm-llnl
VERBOSE=no
previous=N
PREVLEVEL=N
LINES=56
SHLVL=1
BOOT_IMAGE=/boot/vmlinuz-3.0.0-1-amd64
_=/usr/bin/env

user: slurm
'''

import sys
import os

import Thiao

if __name__ == '__main__':
    try: # save the log
        sys.stdout = open(Thiao.ConfigLoader.suspendLog, "a")
        sys.stderr = sys.stdout
        pass
    except: pass
    
    if not "ONE_AUTH" in os.environ:
        print ("trying to set ONE_AUTH")
        os.environ["ONE_AUTH"] = Thiao.ConfigLoader.oneAuth
        
    #hosts = "fg10,fg[0-9],vm[2-12]"
    print ("Warning: This module is DEPRECATED, use the c++ version instead: /src/Suspend.cpp")
    hosts = sys.argv[1]
    hlist = Thiao.extend_host_list(hosts)
    print ("shutting down the following hosts: ", hlist)
    for h in hlist:
        Thiao.shutdown_vm_by_name(h)
    



    