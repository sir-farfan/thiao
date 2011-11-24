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
    Host(0, name, Host::NODE_OFF);
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



bool Host::operator <(const Host &h2){
    cout << this->load_m1 << " < " << h2.load_m1;
    return this->load_m1 < h2.load_m1;
}



bool Host::operator <(const Host *h2){
    cout << this->load_m1 << " < " << h2->load_m1;
    return this->load_m1 < h2->load_m1;
}



bool compare_host_load(class Host *h1, class Host *h2){
    cout << "comare: " << h1->load_m1 << " < " << h2->load_m1 << endl;
    return h1->load_m1 < h2->load_m1;
}



