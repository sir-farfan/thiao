/*
thiao.cpp - a static library with common functions and variables for the rest
    of the project.

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
*/
#include <stdlib.h>

#include "thiao.h"
using namespace std;



/*
 * Callback function for sqlite3, will issue the shutdown command for each
 * host that was returned
 * @param NotUsed: ??
 * @param argc: number of columns
 * @param argv: row
 * @param azColName: name of the columns retrieved
 * @return: ??
 */
int suspend(void *NotUsed, int argc, char **argv, char **azColName){
   int i;
   string cmd = "onevm -v shutdown ";
   cout << "suspending " << endl;

   if (argv[0]){
       cmd += argv[0];
       cout << cmd << endl;
       system( cmd.c_str() );
       //popen(cmd.c_str(), "r");
   }

   return 0;
}




/*
 * Given a list of hosts using the format of SLURM (ex: fg0,fg[7-9]),
 * return the extended list of hosts (ex: fg0,fg7,fg8,fg9)
 * @param hosts: list to extend
 * @return: extended list of hosts
 */
list<string> extend_host_list(string hosts){
    list<string> hlist;
    string h2, host;
    int comma, from, to;
    char aux[30];
    while( hosts.length() > 0 ){
        //split by host name
        comma = hosts.find_first_of(",");
        if (comma > 0){ //multiple hostnames
            h2 = hosts.substr(0, comma);
            hosts = hosts.substr(comma + 1, hosts.size());
//            cout << h2 << "   " << hosts << endl;
        } else { //only one host... probably
            h2 = hosts;
            hosts = "";
//            cout << h2 << "   " << hosts << endl;
        }

        //split list of hosts
        comma = h2.find_first_of("[");
        if ( comma > 0 ){ // list of hosts
            host = h2.substr(0, comma);
            from = atoi( h2.substr(comma+1, h2.find_first_of("-") ).c_str() );
            to = atoi( h2.substr( h2.find_first_of("-")+1, h2.size() ).c_str() );
//            cout << "from " << from << " to " << to << endl;
            while (from <= to){
//                cout << " while " ;
                sprintf(aux, (host+"%d").c_str(), from);
                hlist.push_back(aux);
                from++;
            }
        } else { //only one host
//            cout << " push only ";
            hlist.push_back(h2);
        }
    }
    return hlist;
}


