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



#include "remote.h"

using namespace std;

// if the load is above, move a VM from here to semewhere else
#define desired_top_load 0.75
// if the load is below, put a VM here
#define desired_min_load 0.25






int main(int argc, char **argv){
    list <class Host> load;
    class Host hl;

    fill_host_list(&load);
    while( !load.empty() ){
        cout << load.front().name << endl;
        load.pop_front();
    }
    return 0;
}






