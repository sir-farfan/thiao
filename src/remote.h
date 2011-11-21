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

class HostLoad{
public:
    HostLoad(string h, float l);
    HostLoad();

    string host; //host name
    float load;  //CPU load
    //TODO: retrieve memory too
};


list<class HostLoad> get_host_load(list<string> hosts);



#endif /* REMOTE_H_ */
