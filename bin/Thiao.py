# -*- coding: UTF-8 -*-

'''
Thiao.py - common functions used by most Thiao files

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


import shlex
import subprocess
import ConfigLoader
import DBdriver




def job_submit(script):
    '''
    Calls sbatch to submit the job script
    @param script: job script to submit
    @return: SLURM job id 
    '''
    
    '''
    sbatch /pub/ismael/o5.sh 
    Submitted batch job 174
    '''
    param = shlex.split( "sbatch " + script) 
    p = subprocess.Popen(param, stdout=subprocess.PIPE)
    rt = p.communicate()
    print (rt)
    jid = int ( rt[0].split()[-1] )
    return jid




def get_job_requirements(job_id):
    '''
    Queries SLURM job_id requirements
    @param job_id: id of the job to request requirements
    @return: number of nodes required, memory 
    '''
    # %D = nodes, %m = memory
    param = shlex.split( "squeue -o '%5D %7m' -j" + str(job_id) )
    p = subprocess.Popen(param, stdout=subprocess.PIPE)
    rt = p.communicate()
    print (rt)
    rt = rt[0].split()
    nodes   = int( rt[2] )
    memory = int( rt[3] )
    if memory < 50: memory = 1000
    return nodes, memory




def launch_vm(vm_id, job):
    '''
    launches the VMs specified in the vm_id vector, the id can be passed to the
    vm definition file
    @param vm_id: vector with the id of the VMs to launch
    @param job: id of the job supposed to run in the VMs 
    '''
    for v in vm_id:
#        f = open(ruta+"vm%d.one"%v, "w")
#        f.write( definicion%(v, mem, v, v, v) )
#        f.close()
        param = shlex.split( "onevm -v create " + ConfigLoader.vmTemplate )
        p = subprocess.Popen(param, stdout=subprocess.PIPE)
        one_id = p.communicate()
        print (one_id)
        one_id = int ( one_id[0].split()[1] ) # ('ID: 40\n', None)
        print ("updating db")
        print (DBdriver.query_register_vm_job%(one_id, job, v))
        DBdriver.con.execute(DBdriver.query_register_vm_job%(one_id, job, v))




def clean_job(job):
    '''
    Shuts down the VMs that were supposed to execute the job and updates the
    database
    @param job: id of the (finished) job 
    '''
    print ("--------cleanning---------- ", job)
    vms = list_vms4job(job)
    for v in vms:
        print ("shutting down vm", v)
        print ("onevm -v shutdown %d"%v)
        param = shlex.split( "onevm -v shutdown %d"%v )
        p = subprocess.Popen(param, stdout=subprocess.PIPE)
        print ( p.communicate() )
        DBdriver.con.execute(DBdriver.query_clean_vm4job%v)
        
 
 
 
def list_down_vms():
    '''
    Get the list of VMs that are expected to be shutdown (ie: no onevm id known)
    @return: list of VM ids 
    '''
    cur = DBdriver.con.execute(DBdriver.query_list_down_vms)
    vms = []
    for i in cur:
        vms.append(i[0])
    return vms



def list_vms4job(job):
    '''
    Gets the list of vms that are running (or ran) the job
    @param job: slurm job id 
    @return: list of OpenNebula IDs of the VMs running the job
    '''
    print (DBdriver.query_list_vms4job%job)
    cur = DBdriver.con.execute( DBdriver.query_list_vms4job%job )
    vms = []
    for i in cur:
        vms.append(i[0])
    return vms
        
        
        
if __name__ == "__main__":
    print ( get_job_requirements(172) )
    
    
    
    