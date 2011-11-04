/*
 * thiao.h -
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
