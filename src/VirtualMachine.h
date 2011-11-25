/*
VirtualMachine.h - Definition of the class for storing information about the
    virtual machines.

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

#ifndef VIRTUALMACHINE_H_
#define VIRTUALMACHINE_H_


#include <iostream>
#include <tinyxml.h>

using namespace std;


class VirtualMachine {
public:
    VirtualMachine(TiXmlNode *vm_node);
//    virtual ~VirtualMachine();

    string name;
    int id;
    int state; // 3=running
    int vcpu; // templates > vcpu
    int host_id; // history > hid
};


#endif /* VIRTUALMACHINE_H_ */
