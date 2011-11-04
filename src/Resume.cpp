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
#include <stdlib.h>
#include <string.h>
#include "thiao.h"

using namespace std;

int main(int argc, char ** argv){
    sqlite3 *db;
    list <string> hlist;
    int rc;
    char *errmsg = NULL;
    char onemsg[10], oneid[10];
    const string register_hostname_oneid = "insert into ps_mode (hostname, onevm_id) values ( '"; //%s', %d );
    const string cmd = "onevm -v create ";

    //argument validation
    if (argc != 2){
        cout << "Must receive only the host name as parameter" << endl;
        return 1;
    }
    putenv("ONE_AUTH=/var/lib/one/.one/one_auth");
    hlist = extend_host_list(argv[1]);

    //db setup
    rc = sqlite3_open("/opt/thiao/thiao.db", &db);
    if (rc){
        cout << "Couldn't open the database, aborting..." << endl;
        sqlite3_close(db);
        return 1;
    }
    rc = sqlite3_exec(db, "PRAGMA journal_mode =  OFF", NULL, 0, &errmsg);

    // iterating over the list of hosts to create
    while ( ! hlist.empty() ){
        //create the VM
        string exec = cmd + "/opt/thiao/examples/" + string("/");
        exec += hlist.back() + ".one";

        //FILE *f = popen("cat /tmp/o", "r");
        FILE *f = popen(exec.c_str(), "r");
        fscanf(f, "%s %s", onemsg, oneid); //ID: 40
        cout << onemsg << " " << oneid << endl;
        if ( strcmp(onemsg, "ID:") ){
            cout << "error trying to create the VM," << endl;
            return 0;
        }

        //register hostname and OpenNebula id
        string query = register_hostname_oneid + hlist.back() + string("', ") + oneid + string(")");
        cout << query << endl;
        rc = sqlite3_exec(db, query.c_str(), NULL, 0, &errmsg); //where hostname = '%s'")
    }
    return 0;

}




