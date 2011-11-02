#!/usr/bin/python3
# -*- coding: UTF-8 -*-

'''
DBdriver - Manages the query system to the database, this is the driver for
    sqlite3
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

* vm_id - local identifier, used for contextualization
* onevm_id - id of the running instance
* job_id - id of a batch job
* state - numerical state of the running machine

'''

import sqlite3
import ConfigLoader

print ("Opening db ", ConfigLoader.thiaoHome + "/" + ConfigLoader.dbFile)
con = sqlite3.connect(ConfigLoader.thiaoHome + "/" + ConfigLoader.dbFile)
con.isolation_level = None #auto-commit??



query_list_down_vms = "select vm_id from vm_job_map where onevm_id = -1" 

query_list_vms4job = "select onevm_id from vm_job_map where job_id = %d"

query_clean_vm4job = "update vm_job_map set job_id=-1, onevm_id=-1 where onevm_id=%d"



'''
Updates the database with the information of the vms running a job
@param vmid: contextualized vm
@param oneid: OpenNebula identifier for the vm
@param jid: SLURM job id
'''
query_register_vm_job = "update vm_job_map set onevm_id=%d, job_id=%d where vm_id=%d" #%(one_id, tid, v) 


query_register_hosname_oneid = "update ps_mode set hostname = %s, onevm_id = %d"

query_get_oneid_from_hostname = "select onevm_id from ps_mode where hostname = %s"

query_delete_hostname = "delete from ps_mode where hostname=%s"


# unit tests here
if __name__ == "__main__":
    print ("retrieving vm information")
    cur = con.execute("select vm_id, onevm_id, job_id, state from vm_job_map")
    print ("vm  onevm  job  state")
    for i in cur:
        print (i)
    cur = con.execute("select hostname, onevm_id from ps_mode")
    print ("hostname  onevm")
    for i in cur:
        print (i)


