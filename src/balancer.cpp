/*
balancer.cpp - Searches for the load of the indicated hosts and then tries to
    live migrate VMs from one with too much load to one with less.

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
 *
 * /proc/loadavg  -  1, 5 and 15
 * uptime
 * w
 * qemu-img resize vm-103-disk-1.qcow2 +5G
 * qemu-img convert -O qcow2 original_image.qcow2 deduplicated_image.qcow2
 * http://www.opennebula.org/documentation:archives:rel2.2:api
 * virsh -c qemu+ssh:///system migrate --live 9 qemu+ssh://s80r/system
 *
*/



#include<list>

#include "remote.h"
#include "Host.h"
#include "VirtualMachine.h"

using namespace std;

// if the load is above, move a VM from here to semewhere else
#define desired_top_load 0.75
// if the load is below, put a VM here
#define desired_min_load 0.25




int main(int argc, char **argv){
//TODO: learn to use iterators
    vector<class Host*> hlist;
    vector<class VirtualMachine*> vms;
    list<class Host*> sorted;
    class Host *hl;
    unsigned int i = 0, j;

    fill_host_list(&hlist);

    while( i < hlist.size() ){
        hl = hlist[i];
        cout << hl->getName() << endl;
        //work with the current workload instead with the ~10 minute workload
        //reported by OpenNebula
//        cout << "load: " << hl->retrieveHostLoad() << endl;
        sorted.push_back( hlist[i] );

        i++;
    }



    sorted.sort(compare_host_load);
    for (i=0; i<hlist.size(); i++){
        hlist[i] = sorted.front();
        sorted.pop_front();
        cout << "used: " << hlist[i]->getUsedCpu() << " percentage: " <<
                hlist[i]->getCpuUsagePercentage() << endl;
    }



    fill_vm_list(&vms);
    for (i=0; i<vms.size(); i++){
        cout << "vmid " << vms[i]->id << endl;
        cout << "host " << vms[i]->host_id << endl;
    }

    // Put every virtual machine with it's host
    match_vm_host(&hlist, &vms);

    /*
     * The host in the top of the list is the one        H >--vm--\
     * with the greatest load, the one in the bottom     H >---\  |
     * is the one with the smallest, I'll try migrate   ...    |  |
     * VMs among opposites in the list to even the       h <---/  |
     * load.                                             h <--vm--/
     */

    // use only enabled hosts
    for (i=0; i<hlist.size(); i++)
        if (hlist[i]->getState() != Host::NODE_ON){
            cout << hlist[i]->getName() << " --> is offline, dropping from the list" << endl;
            hlist.erase(hlist.begin()+i);
            i--;
        }

    i = 0;
    j = hlist.size() - 1;
    while (i < j){
        hlist[i]->migrateVmFrom(hlist[j]);
        i++; j--;
    }


    return 0;
}


