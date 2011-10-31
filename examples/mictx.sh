#!/bin/bash

if [ -f /mnt/context.sh ]; then
	. /mnt/context.sh
fi

if [ -n "$VMID" ]; then
	if [ "$HN_BASE" = "fg" ]; then
		VMID=$(($VMID%11))
		IP_LOCAL=$IP2_BASE$(($VMID%11+240))
	else
		VMID=$(($VMID%4+9))
	fi
fi

if [ -n "$VMID" -a -n "$HN_BASE" ]; then
	HOSTNAME=$HN_BASE$VMID
fi

if [ -n "$VMID" -a -n "$IP_BASE" ]; then
	IP_PUBLIC=$IP_BASE$VMID
fi

