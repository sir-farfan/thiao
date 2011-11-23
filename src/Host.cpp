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



void Host::get_load(void){
    //TODO
}


