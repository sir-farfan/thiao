#!/bin/bash
#----------------------------------------------------------
# Copyright 2011-2012, Ismael Farfán for the Thiao project - 2011
#
# Script to execute before rc.local in order to set missing environment variables
#----------------------------------------------------------

if [ -f /mnt/context.sh ]; then
	. /mnt/context.sh
fi

#IP=2.2.2.2
#HN_BASE=vir
#IP1=no

if [ -n "$IP" -a -n "$HN_BASE" -a -z "$IP1" ]; then
	IP1=$IP
	IP=${IP:`expr index $IP .`}
	IP=${IP:`expr index $IP .`}
	IP=${IP:`expr index $IP .`}
	HOSTNAME=$HN_BASE$IP
	#echo siii
fi



if [ -n "$VMID" ]; then
	if [ "$HN_BASE" = "fg" ]; then
		VMID=$(($VMID%11))
		IP_LOCAL=$IP2_BASE$(($VMID%11+240))
	else
		VMID=$(($VMID%4+9))
	fi
fi


