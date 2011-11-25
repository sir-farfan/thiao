/*
Host.cpp - Class Host to store information about the physical nodes, this is the
    implementation file.

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
    TiXmlNode *share;
    TiXmlNode *child;

//    cout << "type: " << host_node->Type();
//    cout << " value: " << host_node->ValueStr() << endl;
    if ( host_node->ValueStr() != "HOST" ){
        cout << "Error, this is not a HOST node";
        Host();
        return;
    }

    share = host_node->FirstChild("HOST_SHARE");

    child = host_node->FirstChild("ID");
//    cout << "ID type: " << child->Type() << endl;
//    cout << "ID child type: " << child->FirstChild()->Type() << endl;
//    cout << "id child value: " << child->FirstChild()->Value() << endl;
    this->id = atoi( child->FirstChild()->Value() );

    child = host_node->FirstChild("NAME");
    this->name = child->FirstChild()->ValueStr();

    child = host_node->FirstChild("STATE");
    this->state = atoi( child->FirstChild()->Value() );

    child = share->FirstChild("MAX_MEM");
    this->max_mem = atoi( child->FirstChild()->Value() );

    child = share->FirstChild("USED_MEM");
    this->used_mem = atoi( child->FirstChild()->Value() );

    child = share->FirstChild("MAX_CPU");
    this->max_cpu = atoi( child->FirstChild()->Value() );
    this->cores = this->max_cpu / 100; // this seems to be the percentage per core

    child = share->FirstChild("USED_CPU");
    this->used_cpu = atoi( child->FirstChild()->Value() );
}



float Host::retrieveHostLoad(void){
    string cmd = "ssh oneadmin@" + this->name + " cat /proc/loadavg";
//    cout << cmd << endl;
    FILE *f = popen(cmd.c_str(), "r");
    fscanf(f, "%f %f %f", &this->load_m1, &this->load_m5, &this->load_m15);
//        load = Host(hosts.front(), min1);
    fclose(f);
    // this are the numbers that ONE gets... I think
    used_cpu = load_m1 * 100;
    return used_cpu;
}



bool Host::operator <(const Host &h2){
//    cout << "comare: " << this->getCpuUsagePercentage() << " < " << ((class Host)h2).getCpuUsagePercentage() << endl;
//    cout << this->load_m1 << " < " << h2.load_m1;
    return getCpuUsagePercentage() < ((class Host)h2).getCpuUsagePercentage();
}



//bool Host::operator <(const Host *h2){
//    cout << this->load_m1 << " < " << h2->load_m1;
//    return this->load_m1 < h2->load_m1;
//}


float Host::getCpuUsagePercentage(){
    return this->getUsedCpu() / (float)max_cpu;
}



int Host::getId() const { return id; }

int Host::getMaxCpu() const { return max_cpu; }

int Host::getMaxMem() const { return max_mem; }

string Host::getName() const { return name; }

int Host::getState() const { return state; }

int Host::getUsedCpu() const { return used_cpu; }

int Host::getUsedMem() const { return used_mem; }

void Host::setId(int id) { this->id = id; }

void Host::setName(string name) { this->name = name; }



bool compare_host_load(class Host *h1, class Host *h2){
    return *h1 < *h2;
}


