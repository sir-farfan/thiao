/*

remote.cpp - Rutines that somehow require remote access to the nodes or a service.

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
 *
 * http://skew.org/xml/tutorial/
 *
 * elements and attributes... they define a hierarchy - a tree of data with a
 * root, branches and leaves... an attribute is a granular, inherent property
 * of an element.
 *
 * <HOST> /<HOST> - element = start-tag + end tag = container for its contents
 * which can be more elements, data or both
 *
 * <element att=0> - attributes
 * ONE doesn't use attributes
 *
 * <HOST_POOL> = root element = document element
 *
 */

#include <xmlrpc-c/client_simple.hpp>
#include <xmlrpc-c/base.hpp>
#include <tinyxml.h>

#include "thiao.h"
#include "remote.h"
#include "Host.h"



void fill_host_list(vector<class Host*> *hosts){
    xmlrpc_c::clientSimple client;
    xmlrpc_c::value result_rpc;
    string const service = "one.hostpool.info";

//TODO: put this in a try/catch block
//    cout << "calling hostpool" << endl;
    client.call(serverUrl, service, "s", &result_rpc, rpc_id.c_str());

    if ( result_rpc.type() != 6 ){ // array
        cout << "expected an array but got something else, aborting: " << result_rpc.type() << endl;
        return;
    }
//    cout << "converting to array" << endl;
    xmlrpc_c::value_array result_array(result_rpc);
    vector<xmlrpc_c::value> const result_vector(result_array.vectorValueValue());

//    cout << "vector size: " << result_vector.size() << endl;
    // the first result tell whether it was successful or not
    xmlrpc_c::value_boolean status = static_cast<xmlrpc_c::value>(result_vector[0]);

    // the second is a string with something hopefully useful
    xmlrpc_c::value_string msg = static_cast<xmlrpc_c::value_string>(result_vector[1]);


    //---------- try to do something useful with the result ---------------
    if ( static_cast<bool>(status) ){
        string tmp = static_cast<string>(msg);
//        cout << tmp << endl << endl;
        TiXmlDocument info;
        info.Parse(tmp.c_str());
        TiXmlNode *node = info.FirstChild("HOST_POOL")->FirstChild("HOST");
        //Iterate trough all the hosts
        while (node != NULL){
            Host *host = new Host(node);
            hosts->push_back(host);
            node = node->NextSibling("HOST");
        }

    } else {
        cout << "noo" << endl;
        cout << static_cast<string>(msg) << endl;
    }


}



void fill_vm_list(vector<VirtualMachine*> *vms){
    xmlrpc_c::clientSimple client;
    xmlrpc_c::value result_rpc;
    string const service = "one.vmpool.info";

    client.call(serverUrl, service, "si", &result_rpc, rpc_id.c_str(), -2);

    if ( result_rpc.type() != 6 ){
        cout << "expected an array but got something else, aborting: " << result_rpc.type() << endl;
        return;
    }

    xmlrpc_c::value_array result_array(result_rpc);
    vector<xmlrpc_c::value> const result(result_array.vectorValueValue());
    xmlrpc_c::value_boolean status = static_cast<xmlrpc_c::value>(result[0]);
    xmlrpc_c::value_string vm_xml = static_cast<xmlrpc_c::value_string>(result[1]);

    if ( static_cast<bool>(status) ){
        string xml_str = static_cast<string>(vm_xml);
//        cout << "status ok" << endl << xml_str << endl;
        TiXmlDocument root;
        root.Parse(xml_str.c_str());
        TiXmlNode *element = root.FirstChild("VM_POOL")->FirstChild("VM");
        while(element != NULL){
            cout << "VM found" << endl;
            VirtualMachine *vm = new VirtualMachine(element);
            vms->push_back(vm);
            element = element->NextSibling("VM");
        }
    } else {
        cout << "RPC call failed to retrieve VM list" << endl;
        cout << static_cast<string>(vm_xml) << endl;
    }

}



bool one_rpc(const string service, xmlrpc_c::paramList *params, xmlrpc_c::value *rpc_value){
    xmlrpc_c::clientSimple client;
    xmlrpc_c::value result_rpc;
    xmlrpc_c::paramList param;
    unsigned int i;

    param.add(xmlrpc_c::value_string(rpc_id));

    if (params != NULL)
        for (i=0; i<params->size(); i++)
            param.add((*params)[i]);

    client.call(serverUrl, service, param, &result_rpc);

    if ( result_rpc.type() != result_rpc.TYPE_ARRAY ){
        cout << "expected an array but got something else, aborting: " << result_rpc.type() << endl;
        return false;
    }

    xmlrpc_c::value_array result_array(result_rpc);
    vector<xmlrpc_c::value> const result(result_array.vectorValueValue());
    xmlrpc_c::value_boolean status = static_cast<xmlrpc_c::value>(result[0]);

    //save what we need
    *rpc_value = result[1];

    return static_cast<bool>(status);
}



