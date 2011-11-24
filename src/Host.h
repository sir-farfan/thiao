/*
 * Host.h
 *
 *  Created on: 22/11/2011
 *      Author: ismael
 */

#ifndef HOST_H_
#define HOST_H_

#include<iostream>
#include<tinyxml.h>

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

    void get_load(void);

    /*
     * Access to the node to get its load
     */
    float retrieve_host_load(void);


    /*
     *
     */
    bool operator < (const Host &h2);
    bool operator < (const Host *h2);


    string name; //host name
    float load_m1;  //Average CPU load in the last minute
    float load_m5;  //Average CPU load in the last 5 minutes
    float load_m15; //Average CPU load in the last 15 minutes
    int id;
    int state; // 2=on, 4=off
    //TODO: retrieve memory too

    enum NodeState{
        NODE_OFF = 4,
        NODE_ON  = 2,
    };
};



/*
 * Compare the load of 2 hosts
 * @param h1: host 1
 * @param h2: host 2
 * @return: true if the load of host 1 is lower than the load of host 2
 */
bool compare_host_load(class Host *h1, class Host *h2);



#endif /* HOST_H_ */
