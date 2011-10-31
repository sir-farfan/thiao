#!/usr/bin/python3
'''
Setup.py - Helps configure Thiao

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



if __name__ != "__main__":
    print ("Some module is trying to call the configuration utility!!")

#if os.getgid() != 0:
#    print ("This program should be executed as root?")

#import configparser
#config = configparser.ConfigParser()

#print ("press ENTER to use the DEFAULTS")

#default = config["Default"]
#i = input("Path to Thiao's installation (/opt/thiao): ")
#default["Path"] = i  if  i.replate(" ","") != "" else "/opt/thiao"

#print ("configuring the SQLite database")
#vm = config["vm"]

#vm["Path"] = input ("Path to store the database (/opt/thiao): ")
#if vm["Path"] == "": vm["Path"] = "/opt/thiao"
#vm["Path"] += "/thiao.db"

#vm["Database"] = input("Name of the database (thiao): ")
#if vm["Database"] == "": vm["Database"] = "thiao"


import sqlite3
import ConfigLoader

con = sqlite3.connect(ConfigLoader.thiaoHome + "/" + ConfigLoader.dbFile)
con.isolation_level = None #auto-commit??

reset = input("reset the database? y/n (n): ")
reset = False  if "y" not in reset.lower()  else True

if reset:
    print ("deleting table in case it exists")
    try: con.execute("drop table vm_job_map")
    except: print ("no table found, ignoring")
    # vm_id: for VM management purposes
    # onevm_id: id return by [onevm create] command
    # job_id: id return by [sbatch] command
    # state: will hold numerical codes to represent the state of the job
    print ("creating the table")
    con.execute("create table vm_job_map(vm_id integer, onevm_id integer, job_id integer, state integer)")


print ("Which range of virtual machines do you wan to use?")
print ("this defines the amount of VMs that can be launched, and it can be written "
       "to the VM template file if needed")
ran = input("in the form [from to] (inclusive), ex: 0 10 ")
ran = ran  if  ran != ""  else  "0 10"
ran = ran.split()
ran[0] = int( ran[0] )
ran[1] = int( ran[1] )

for r in range(ran[0], ran[1]+1):
    print ("registering vm", r)
    con.execute("insert into vm_job_map values(%d, -1, -1, -1)"%r)




