/*
VirtualMachine.cpp - Implementation of the class for storing information about
    Virtual machines and other management functions.

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

#include "VirtualMachine.h"



VirtualMachine::VirtualMachine(TiXmlNode *vm_node) {
    TiXmlNode *child;
    TiXmlNode *templa, *history;


    if ( vm_node->ValueStr() != "VM" ){
        cout << "Error: this is not a VM node" << endl;
        return;
    }
//    cout << "vm node weeee" << endl;

    child = vm_node->FirstChild("NAME");
    name = child->FirstChild()->ValueStr();

    child = vm_node->FirstChild("ID");
    id = atoi(child->FirstChild()->Value());

    child = vm_node->FirstChild("STATE");
    state = atoi(child->FirstChild()->Value());

    templa = vm_node->FirstChild("TEMPLATE");
    child = templa->FirstChild("VCPU");
    vcpu = atoi(child->FirstChild()->Value());

    history = vm_node->FirstChild("HISTORY");
    child = history->FirstChild("HID");
    host_id = atoi( child->FirstChild()->Value() );
}

//VirtualMachine::~VirtualMachine() {
    // TODO Auto-generated destructor stub
//}


