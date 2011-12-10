/*
Resume.cpp - for use with SLURM as ResumeProgram, it will read the hostname
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
*/

#include <sqlite3.h>
#include <xmlrpc-c/client_simple.hpp>
#include <xmlrpc-c/base.hpp>

#include <stdlib.h>
#include <string.h>
#include <fstream>

#include "thiao.h"
#include "remote.h"

using namespace std;



void usage(){
    cout << "Creates a virtual machine based on its hostname and registers its ID" << endl;
    cout << "    Resume hostname[,hostname] [-f|--force]" << endl;
    cout << "    -f, --force  Will start a VM even if there is already one registed" << endl;
    cout << "                 under the same hostname" << endl;
    cout << "ex: to start fg0,fg3,fg4 and fg5:" << endl;
    cout << "    Resume fg0,fg[3-5]" << endl;
}

int main(int argc, char ** argv){
    sqlite3 *db;
    list <string> hlist, running_vms;
    int rc;
    char *errmsg = NULL, oneid[10];
    bool force_vm_creation = false;

    //--------argument validation-------
    if (argc < 2 || argc > 3){
        usage();
        return 1;
    }

    if (argc == 3){
        if ( argv[1] == string("-f") || argv[1] == string("--force") ){
            force_vm_creation = true;
            hlist = extend_host_list(argv[2]);
        } else if ( argv[2] == string("-f") || argv[2] == string("--force") ) {
            force_vm_creation = true;
            hlist = extend_host_list(argv[1]);
        } else {
            usage();
            return 1;
        }
    } else
        hlist = extend_host_list(argv[1]);
    putenv((char*)one_auth);

    //--------db setup------------
    rc = sqlite3_open((char*)db_file, &db);
    if (rc){
        cout << "Couldn't open the database, aborting..." << endl;
        sqlite3_close(db);
        return 1;
    }
    rc = sqlite3_exec(db, "PRAGMA journal_mode =  OFF", NULL, 0, &errmsg);

    //---------iterating over the list of hosts to create----------
    while ( ! hlist.empty() ){
        //check if this VM was created before
        while ( !running_vms.empty() ) running_vms.pop_back();
        rc = sqlite3_exec(db,
                (oneid_from_hostname + hlist.front() + "'").c_str(),
                make_list_callback, (void*)&running_vms, &errmsg);

        if ( running_vms.empty() || force_vm_creation ){
            if ( !running_vms.empty() && force_vm_creation )
                cout << "forcing the creation of " << hlist.front() << endl;
            //create the VM

            ifstream t((vm_script_dir + "/" + hlist.front() + ".one").c_str());
            string vm_def((istreambuf_iterator<char>(t)), istreambuf_iterator<char>());

            xmlrpc_c::value value;
            xmlrpc_c::paramList param;
            param.add(xmlrpc_c::value_string(vm_def));
            if ( one_rpc("one.vm.allocate", &param, &value) ){
                xmlrpc_c::value_int vi = static_cast<xmlrpc_c::value_int>(value);
                sprintf(oneid, "%d", static_cast<int>(vi));
                cout << "oneid: " << oneid << endl;
            }
            else{
                cout << "error trying to create the VM," << endl;
                return 0;
            }

            //register hostname and OpenNebula id
            string query = register_hostname_oneid + hlist.front() + string("', ") + oneid + string(")");
            cout << query << endl;
            rc = sqlite3_exec(db, query.c_str(), NULL, 0, &errmsg); //where hostname = '%s'")
        } else {
            cout << "This VM seems to exists: " << hlist.front() << " NOT starting it again, "
                    "you can change this with --force." << endl;
        }

        hlist.pop_front();
    }
    return 0;

}





