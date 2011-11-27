/*
Host.h - Definition of the Host class for storing information about the hosts.

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

#ifndef HOST_H_
#define HOST_H_

#include<iostream>
#include<vector>
#include<tinyxml.h>

#include "VirtualMachine.h"

using namespace std;



/*
 * Useful information about a host
 */
class Host{
public:
    /*
     * Constructor
     * @param id: OpenNebula ID
     * @param name: (fully) qualified name
     * @param state: on, off, err
     */
    Host(int id, string name, int state);

    /*
     * Constructor
     * @param name: (fully) qualified name
     */
    Host(string name);

    /*
     * Empty constructor
     */
    Host(void);

    /*
     * Constructor
     * @param host_node: pointer to a xml HOST element
     */
    Host(TiXmlNode *host_node);

    /*
     * Access to the node to get its average load, the difference with what I
     * get from ONE is that ONE waits some time to get this information, and
     * with this is immediate
     */
    float retrieveHostLoad(void);

    enum NodeState{
        NODE_OFF = 4,
        NODE_ON = 2
    };

    /*
     * Calculate the overall percentage of CPU usage: used/max
     */
    float getCpuUsagePercentage();

    /*
     * Asks the other host which VM it doens't want and makes it one of its own
     */
    bool migrateVmFrom(class Host *hfrom);

    /*
     * Returns a VM that is eligible for migration (in any)
     */
    class VirtualMachine * getMigrateableVm();

    /*
     * getters and setters
     */
    bool operator < (const Host &h2);
//    bool operator < (const Host *h2);
    int getId() const;
    int getMaxCpu() const;
    int getMaxMem() const;
    string getName() const;
    int getState() const;
    int getUsedCpu() const;
    int getUsedMem() const;
    void setId(int id);
    void setName(string name);

    bool addVm(class VirtualMachine *vm);


private:
    string name; //host name
    float load_m1;  //Average CPU load in the last minute
    float load_m5;  //Average CPU load in the last 5 minutes
    float load_m15; //Average CPU load in the last 15 minutes
    int cores;

    // stuff from ONE
    int id;
    int state; // 2=on, 4=off
    int max_mem; // RAM
    int used_mem;
    int max_cpu;
    int used_cpu; // this corresponds to one of the load_m* properties

    vector<class VirtualMachine*> vms; //VMs running in this host


};



/*
 * Compare the load of 2 hosts
 * @param h1: host 1
 * @param h2: host 2
 * @return: true if the load of host 1 is lower than the load of host 2
 */
bool compare_host_load(class Host *h1, class Host *h2);



/*
 * Fill the VM list of the host using
 */
void match_vm_host(vector<class Host*> *host, vector<class VirtualMachine*> *vms);



#endif /* HOST_H_ */
