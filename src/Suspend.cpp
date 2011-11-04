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
#include <iostream>

using namespace std;

// lo llaman una vez por cada fila de resultados!!
static int suspend(void *NotUsed, int argc, char **argv, char **azColName){
   int i;
   string cmd = "onevm -v shutdown ";

   if (argv[0]){
       cmd += argv[0];
       cout << cmd << endl;
       system( cmd.c_str() );
       //popen(cmd.c_str(), "r");
   }

   return 0;
}



int main(int argc, char ** argv){
    sqlite3 *db;
    int rc;
    char *errmsg = NULL;
    string oneid_from_hostname = "select onevm_id from ps_mode where hostname='";
    string delete_hostname = "delete from ps_mode where hostname='"; //%s'"

    //arguments validation
    if (argc != 2){
        cout << "Must receive only the host name as parameter" << endl;
        return 1;
    }
    putenv("ONE_AUTH=/var/lib/one/.one/one_auth");

    //openning db
    rc = sqlite3_open("/opt/thiao/thiao.db", &db);
    if (rc){
        cout << "Couldn't open the database, aborting..." << endl;
        sqlite3_close(db);
        return 1;
    }
    rc = sqlite3_exec(db, "PRAGMA journal_mode =  OFF", NULL, 0, &errmsg);

    //retrieving the ids of the VMs and shutting them down
    oneid_from_hostname += argv[1] + string("'");
    cout << oneid_from_hostname << endl;
    rc = sqlite3_exec(db, oneid_from_hostname.c_str(), suspend, 0, &errmsg); //where hostname = '%s'")

    //cleaning the register from the database
    delete_hostname += argv[1] + string("'");
    cout << delete_hostname << endl;
    rc = sqlite3_exec(db, delete_hostname.c_str(), NULL, 0, &errmsg);

    return 0;

}




