#!/usr/bin/python3

'''
fsub.py - Used instead of sbatch to submit jobs, it will additionally create the
    virtual machines that will run the job.

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
http://docs.python.org/py3k/library/subprocess.html
'''


import sys

import Thiao




def usage():
    print ("usage:\n"
           "fusb.py /path/to/script.sh\n"
           "fsub.py [jobid]\n")




if __name__ == '__main__':
    if len(sys.argv) != 2:
        usage()
        quit()
    try:
        jid = int(sys.argv[1])
    except:
        print ("trying to submit the job")
        jid = Thiao.job_submit(sys.argv[1])    
    print ("got this job id: ", jid)
    print ("retrieving job requirements")
    nodes, memory = Thiao.get_job_requirements(jid)
    print ("nodes: ", nodes)
    vms = Thiao.list_down_vms()
    if len(vms) >= nodes:
        print ("launching VMs for job")
        vms = vms[:nodes]
        Thiao.launch_vm(vms, jid)
    else:
        print("not enough vms to launch the job")
    
    




