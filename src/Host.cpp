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

#include <xmlrpc-c/client_simple.hpp>
#include <xmlrpc-c/base.hpp>

#include "Host.h"
#include "thiao.h"



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



bool Host::addVm(class VirtualMachine *vm) {
    if (this->id == vm->host_id){
        this->vms.push_back(vm);
        return true;
    }
    return false;
}



bool Host::migrateVmFrom(class Host *hfrom){
    xmlrpc_c::clientSimple client;
    xmlrpc_c::value result_rpc;
    string const service = "one.vm.migrate";
    class VirtualMachine *vm = hfrom->getMigrateableVm();

    if (vm == NULL || this->state != Host::NODE_ON)
        return false;

    cout << "Migrating VM " << vm->id << " from " << hfrom->id << " to " << this->id << endl;

    client.call(serverUrl, service, "siib", &result_rpc, rpc_id.c_str(),
            vm->id, this->id, true); // use live migration

    xmlrpc_c::value_array result_array(result_rpc);
    vector<xmlrpc_c::value> const result(result_array.vectorValueValue());
    xmlrpc_c::value_boolean status = static_cast<xmlrpc_c::value>(result[0]);

    if ( static_cast<bool>(status))
        return true;
    else{ //an error occurred
        xmlrpc_c::value_string msg = static_cast<xmlrpc_c::value_string>(result[1]);
        cout << static_cast<string>(msg) << endl;
    }
    return false;
}



class VirtualMachine * Host::getMigrateableVm(){
    //Get rid of a vm as long as it doesn't turn idle.
    if (this->vms.size()<=1)
        return NULL;
    return this->vms.back(); //greatest vm-id
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



void match_vm_host(vector<class Host*> *host, vector<class VirtualMachine*> *vms){
    unsigned int i;
    VirtualMachine *vm;

    while ( !vms->empty() ){
        vm = vms->back();
        for (i=0; i<host->size(); i++) // O(vm*host)
            if ( (*host)[i]->addVm(vm) )
                break;
        vms->pop_back();
    }
}


