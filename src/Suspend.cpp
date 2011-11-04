/*
Suspend.cpp - for use with SLURM as SuspendProgram, it will read the hostname
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
*/

#include <stdlib.h>
#include <sqlite3.h>
#include "thiao.h"


using namespace std;



int main(int argc, char ** argv){
    list <string> hlist;
    sqlite3 *db;
    int rc;
    char *errmsg = NULL;
    const string oneid_from_hostname = "select onevm_id from ps_mode where hostname='";
    const string delete_hostname = "delete from ps_mode where hostname='"; //%s'"

    //arguments validation
    if (argc != 2){
        cout << "Must receive only the host name as parameter" << endl;
        return 1;
    }
    putenv("ONE_AUTH=/var/lib/one/.one/one_auth");
    hlist = extend_host_list(argv[1]);

    //openning db
    rc = sqlite3_open("/opt/thiao/thiao.db", &db);
    if (rc){
        cout << "Couldn't open the database, aborting..." << endl;
        sqlite3_close(db);
        return 1;
    }
    rc = sqlite3_exec(db, "PRAGMA journal_mode =  OFF", NULL, 0, &errmsg);

    //iterating through the hosts to shutdown
    while ( ! hlist.empty() ){
        cout << hlist.back() << " ";

        //retrieving the ids of the VMs and shutting them down
        string exec = oneid_from_hostname + hlist.back() + "'";
        cout << exec << endl;
        rc = sqlite3_exec(db, exec.c_str(), suspend, 0, &errmsg); //where hostname = '%s'")

        //cleaning the register from the database
        string query = delete_hostname + hlist.back() + "'";
        cout << query << endl;
        rc = sqlite3_exec(db, query.c_str(), NULL, 0, &errmsg);

        hlist.pop_back(); //drop the current host
    }

    return 0;

}




