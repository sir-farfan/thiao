/*
thiao.h - header file for the common functions

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

#ifndef THIAO_H_
#define THIAO_H_

#include <list>
#include <stdio.h>
#include <iostream>


// configuration
const std::string vm_script_dir = "/opt/thiao/examples/";
const char one_auth[] = "ONE_AUTH=/var/lib/one/.one/one_auth";
const char db_file[]  = "/opt/thiao/thiao.db";

//---------do not edit below unless you know what you are doing----------------

// database
const std::string register_hostname_oneid = "insert into ps_mode (hostname, onevm_id) values ( '"; //%s', %d );
const std::string oneid_from_hostname = "select onevm_id from ps_mode where hostname='";
const std::string delete_hostname     = "delete from ps_mode where hostname='"; //%s'"

// opennebula
const std::string cmd = "onevm -v create ";


/*
 * Given a list of hosts using the format of SLURM (ex: fg0,fg[7-9]),
 * return the extended list of hosts (ex: fg0,fg7,fg8,fg9)
 * @param hosts: list to extend
 * @return: extended list of hosts
 */
std::list<std::string> extend_host_list(std::string hosts);



/*
 * Callback function for sqlite3, will issue the shutdown command for each
 * host that was returned
 * @param NotUsed: ??
 * @param argc: number of columns
 * @param argv: row
 * @param azColName: name of the columns retrieved
 * @return: ??
 */
int suspend(void *NotUsed, int argc, char **argv, char **azColName);


#endif /* THIAO_H_ */
