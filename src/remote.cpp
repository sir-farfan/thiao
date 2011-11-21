/*

remote.cpp - Rutines that somehow require remote access to the nodes or a service.

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

 */

#include "thiao.h"
#include "remote.h"



/*
 * Constructor with parameters
 */
HostLoad::HostLoad(string h, float l){
    this->host = h;
    this->load = l;
}


/*
 * Default constructor
 */
HostLoad::HostLoad(){
    this->host = "";
    this->load = 0;
}



/*
 * Compare the load of 2 hosts
 * @param h1: host 1
 * @param h2: host 2
 * @return: true if the load of host 1 is lower than the load of host 2
 */
bool compare_host_load(class HostLoad h1, class HostLoad h2){
    return h1.load < h2.load;
}


/*
 * Check the CPU load of a set of hosts
 * @param hosts: list of hosts to check the load
 * @return: Host + load ordered by CPU loads
 * //TODO: declare hosts as const?
 */
list<class HostLoad> get_host_load(list<string> hosts){
    list<class HostLoad> hl;
    HostLoad load;
    float min1, min5, min15;

    while( !hosts.empty() ){
        string cmd = "ssh oneadmin@" + hosts.front() + " cat /proc/loadavg";
        cout << cmd << endl;
        FILE *f = popen(cmd.c_str(), "r");
        fscanf(f, "%f %f %f", &min1, &min5, &min15);
        load = HostLoad(hosts.front(), min1);
        hl.push_back(load);
        hosts.pop_front();
        fclose(f);
    }
    hl.sort(compare_host_load);
    return hl;
}



