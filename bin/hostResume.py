#!/usr/bin/python3
'''
hostResume.py - for use with SLURM as ResumeProgram, it will read the hostname
    from the parameters and attempt to start the appropriate virtual machines
    
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
'''

import sys
import Thiao

if __name__ == '__main__':
    try: # save the log
        sys.stdout = open(Thiao.ConfigLoader.resumeLog, "a")
        sys.stderr = sys.stdout
        pass
    except: pass
    #hosts = "fg10,fg[0-9],vm[2-12]"
    hosts = sys.argv[1]
    hlist = Thiao.extend_host_list(hosts)
    print ("booting the following hosts: ", hlist)
    for h in hlist:
        Thiao.launch_vm_by_name(h)
    



    