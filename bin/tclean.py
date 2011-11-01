#!/usr/bin/python3
# -*- coding: UTF-8 -*-

'''
tclean.py - shuts down the virtual machines assigned to a job and updates the
    database according.
    
If set as EpilogSlurmctld, it will read the job id from the environment (run as
slurm user), make sure slurm can write the db:
SLURM_JOBID=178
SLURM_JOB_ID=178
SLURM_JOB_EXIT_CODE=0
SLURM_JOB_NODELIST=fg10

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
'''


import sys
import os

import Thiao


    

def usage():
    print ("tclean.py [jobid]\n")
    


if __name__ == '__main__':
    #sys.stdout = open("/tmp/tclean.log", "a")
    try: # save the log
        #sys.stdout = open(Thiao.ConfigLoader.tcleanLog, "a")
        #sys.stderr = sys.stdout
        pass
    except: pass
    
    try:# read job id from the arguments
        job = int(sys.argv[1])
    except:
        try: # read the job id from the environment
            job = int( os.getenv("SLURM_JOB_ID"))
        except:
            usage()
            exit()
    if not "ONE_AUTH" in os.environ:
        print ("trying to set ONE_AUTH")
        os.environ["ONE_AUTH"] = Thiao.ConfigLoader.oneAuth
    Thiao.clean_job(job)
        
        
        
        
        