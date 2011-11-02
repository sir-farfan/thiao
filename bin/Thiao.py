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



def launch_vm_by_name(host):
    '''
    launches the VM specified in host, looking for the appropriate [host].one
    file in VMScriptDir
    @param hosts: vector with the id of the VMs to launch 
    '''
    
#    f = open(ruta+"vm%d.one"%host, "w")
#    f.write( definicion%(host, mem, host, host, host) )
#    f.close()
    param = shlex.split( "onevm -host create " + ConfigLoader.vmScriptDir + host + ".one")
    p = subprocess.Popen(param, stdout=subprocess.PIPE)
    one_id = p.communicate()
    print (one_id)
    one_id = int ( one_id[0].split()[1] ) # ('ID: 40\n', None)
    print ("updating db")
    print (DBdriver.query_register_vm_job%(host, one_id))
    DBdriver.con.execute(DBdriver.query_register_hosname_oneid%(host, one_id))



def shutdown_vm_by_name(host):
    '''
    Shuts down the VM corresponding to the hostname host
    @param host: name of the host to shutdown
    '''
    
#    f = open(ruta+"vm%d.one"%host, "w")
#    f.write( definicion%(host, mem, host, host, host) )
#    f.close()
    cur = DBdriver.con.execute(DBdriver.query_get_oneid_from_hostname%host)
    for i in cur: oneid = i[0]
    param = shlex.split( "onevm -v shutdown " oneid)
    p = subprocess.Popen(param, stdout=subprocess.PIPE)
    msg = p.communicate()
    print (msg)
    print ("updating db")
    print (DBdriver.query_delete_hostname%h)
    DBdriver.con.execute(DBdriver.query_delete_hostname%h)



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
        


def extend_host_list(hosts):
    '''
    Given a list of hosts using the format of SLURM (ex: fg0,fg[7-9]),
    return the extended list of hosts (ex: fg0,fg7,fg8,fg9)
    @param hosts: list to extend
    @return: extended list of hosts 
    '''
    hlist = []
    for h in hosts.split(","):
        if "[" in h:
            name, ran = h.split("[")
            ran = ran[:-1]
            ran = ran.split("-")
            for i in range( int(ran[0]), int(ran[1])+1 ):
                hlist.append(name + str(i))
        else: hlist.append(h)
    return hlist

        
        
if __name__ == "__main__":
    print ( get_job_requirements(172) )



    
    
    
    