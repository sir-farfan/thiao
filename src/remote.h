/*

remote.h - Rutines that somehow require remote access to the nodes or a service.

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

#ifndef REMOTE_H_
#define REMOTE_H_

#include "thiao.h"

using namespace std;



/*
 * Useful information about a host
 */
class Host{
public:
    Host(string h, float l);
    Host(string h);
    Host();

    string host; //host name
    float load;  //CPU load
    //TODO: retrieve memory too
};



/*
 * Check the CPU load of a set of hosts
 * @param hosts: list of hosts to check the load
 * @return: Host + load ordered by CPU loads
 * TODO: declare hosts as const?
 */
list<class Host> get_host_load(list<string> hosts);


/*
 * Sends a RPC call to OpenNebula to retrieve the list of working hosts
 * @param hosts: (empty) list in which to put the names of the hosts
 */
void fill_host_list(list<Host> hosts);



#endif /* REMOTE_H_ */
