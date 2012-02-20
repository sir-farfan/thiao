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
 * return the extended list of hosts (ex: fg0,fg7,fg8,fg9,fg[0-3,5])
 * @param hosts: list to extend
 * @return: extended list of hosts
 */
list<string> extend_host_list(string hosts){
    list<string> hlist;
    string host, from_str, to_str;
    unsigned int current=0, from, to;
    char aux[30];
    while( hosts.length() > current ){
        //get the next host name
        host = from_str = to_str = "";
        while (hosts.length() > current &&
               hosts[current] != ',' && hosts[current] != '['){ // , separates hosts, [ indicates range or list
            host += hosts[current];
            current ++;
        }
        //lets see why it stopped
        if (hosts.length() <= current){ //finished parsing
            hlist.push_back(host);
            break;
        }

        if (hosts[current]==','){ //read a whole host name
            hlist.push_back(host);
            current ++;
        }
        else
        { //-----------got a range of hosts--------------
            while ( hosts[current] != ']' ){
                current++; // it was positioned over ,, [ or ], lets move it
                from_str = to_str = "";
                while ( isdigit( hosts[current] ) ){ //read the start of the range of hosts requested
                    from_str += hosts[current];
                    current ++;
                }
                // finished reading the first part
                if ( hosts[current] == ',' || hosts[current] == ']' ){ //is in this form [5,7,9]
                    to_str = from_str;
                } else { //range [1-3]
                    current ++; //it was over a -, lets move it
                    while ( isdigit( hosts[current] ) ){ //read the end of the range of hosts requested
                        to_str += hosts[current];
                        current ++;
                    } // it is over either , or ]
                }
                from = atoi( from_str.c_str() );
                to = atoi( to_str.c_str() );
                for (; from <= to; from++){
                    sprintf(aux, (host+"%d").c_str(), from);
                    hlist.push_back( aux );
                }
            }
            current++; //it was over ], otherwise it wouldn't have finished
            current++; //now is either over , or beyond the end of the string
        }

//        hlist.push_back(h2);
    }
    return hlist;
}



int make_list_callback(void *ids, int argc, char **argv, char **azColName){
    if (ids == NULL){
        cout << "warning: ids is NULL" << endl;
        return 0; // return 1 to abort...
    }
    list<string> *idlist = (list<string> *) ids;
    if (argv[0])
        idlist->push_back(argv[0]);
    return 0;
}



void readConfig(){
    /*
     * ifstream.getline(char *buffer)
     */
}

