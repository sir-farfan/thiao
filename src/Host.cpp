/*
 * Host.cpp
 *
 *  Created on: 22/11/2011
 *      Author: ismael
 */

#include "Host.h"


Host::Host(int id, string name, int state){
    this->name = name;
    this->id = id;
    this->state = state;
}



Host::Host(string name){
//    Host(h, 0, 0);
}



Host::Host(){
    Host("");
}



Host::Host(TiXmlNode *host_node){
    TiXmlNode *child;

//    cout << "type: " << host_node->Type();
//    cout << " value: " << host_node->ValueStr() << endl;
    if ( host_node->ValueStr() != "HOST" ){
        cout << "Error, this is not a HOST node";
        Host();
        return;
    }

    child = host_node->FirstChild("ID");
//    cout << "ID type: " << child->Type() << endl;
//    cout << "ID child type: " << child->FirstChild()->Type() << endl;
//    cout << "id child value: " << child->FirstChild()->Value() << endl;
    this->id = atoi( child->FirstChild()->Value() );

    child = host_node->FirstChild("NAME");
    this->name = child->FirstChild()->ValueStr();

    child = host_node->FirstChild("STATE");
    this->state = atoi( child->FirstChild()->Value() );
}



void Host::get_load(void){
    //TODO
}



float Host::retrieve_host_load(void){
    string cmd = "ssh oneadmin@" + this->name + " cat /proc/loadavg";
//    cout << cmd << endl;
    FILE *f = popen(cmd.c_str(), "r");
    fscanf(f, "%f %f %f", &this->load_m1, &this->load_m5, &this->load_m15);
//        load = Host(hosts.front(), min1);
    fclose(f);
    return this->load_m1;
}



/*
 * Compare the load of 2 hosts
 * @param h1: host 1
 * @param h2: host 2
 * @return: true if the load of host 1 is lower than the load of host 2
 */
bool compare_host_load(class Host h1, class Host h2){
    return h1.load_m1 < h2.load_m1;
}

