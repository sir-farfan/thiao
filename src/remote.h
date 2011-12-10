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

#include <xmlrpc-c/base.hpp>

#include <vector>
#include <string.h>

#include "Host.h"
#include "VirtualMachine.h"

using namespace std;

/*
 * Sends a RPC call to OpenNebula to retrieve the list of working hosts
 * @param hosts: (empty) list in which to put the names of the hosts
 */
void fill_host_list(vector<Host*> *hosts);



/*
 * Gets the list of VMs using an RPC call to OpenNebula
 * @param vms: (empty) list in which to save the VMs
 */
void fill_vm_list(vector<VirtualMachine*> *vms);



/*
 * Realices the actual RPC call, relieving some stress from other pieces of code
 * @param service: string of the function to call
 * @param params: paramList object with the parameters of the function, NULL for
 *                no parameters. Exclude session string
 * @param rpc_value: (out) ONE stores the actual result/information here
 * @return: true if RPC is successful
 */
bool one_rpc(string service, xmlrpc_c::paramList *params, xmlrpc_c::value *result);


#endif /* REMOTE_H_ */
