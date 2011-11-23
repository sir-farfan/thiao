/*
 * Host.cpp
 *
 *  Created on: 22/11/2011
 *      Author: ismael
 */

#include "Host.h"

/*
 * Constructor with parameters
 */
Host::Host(int id, string name, int state){
    this->name = name;
    this->id = id;
    this->state = state;
}

/*
 * Only the name of the host
 */
Host::Host(string h){
//    Host(h, 0, 0);
}

/*
 * Default constructor
 */
Host::Host(){
    Host("");
}

/*
 * Creates the host out of a xmlrpc host definition node
 */
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


