/*
 * Host.h
 *
 *  Created on: 22/11/2011
 *      Author: ismael
 */

#ifndef HOST_H_
#define HOST_H_

#include<iostream>

using namespace std;

/*
 * Useful information about a host
 */
class Host{
public:
    Host(int id, string name, int state);
    Host(string h);
    Host(void);

    void get_load(void);

    string name; //host name
    float load;  //CPU load
    int id;
    int state; // 2=on, 4=off
    //TODO: retrieve memory too
};



#endif /* HOST_H_ */
