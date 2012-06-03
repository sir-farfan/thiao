#!/bin/bash
#----------------------------------------------------------
# Copyright 2011-2012, Ismael Farfán for the Thiao project - 2011
#
# Script to execute before rc.local in order to set missing environment variables
#----------------------------------------------------------

echo ... pre-rc.sh ...

if [ -f /mnt/context.sh ]; then
	. /mnt/context.sh
fi

#IP=5.6.7.8
#HN_BASE=vir
#IP0=no

if [ -n "$IP" -a -n "$HN_BASE" -a -z "$IP0" ]; then
	IP0=$IP
	IP=${IP:`expr index $IP .`}
	IP=${IP:`expr index $IP .`}
	IP=${IP:`expr index $IP .`}
	HOSTNAME=$HN_BASE$IP
	#echo siii
fi



