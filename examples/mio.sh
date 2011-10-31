#!/bin/bash

con=/mnt

if [ -f /mnt/mictx.sh ]
then
  echo cargando el contexto
  . /mnt/mictx.sh
else
  echo no hay contexto
  exit -1
fi

#--------------------------------------------

if [ -f $con/slurm.conf ]
then
	cp $con/slurm.conf /etc/slurm-llnl/
fi

if [ -f $con/rc.local ]
then
	cp $con/rc.local /etc/rc.local
	chmod +x /etc/rc.local
fi

if [ -f $con/hosts ]
then
	cp $con/hosts /etc
fi

if [ -f $con/resolv.conf ]
then
	cp $con/resolv.conf /etc
fi

if [ "$HN_BASE" = "fg" ]; then
	echo 192.168.11.85 nas-0-0 nas-0-0.idpm >> /etc/hosts
	echo nas-0-0:/fgstorage/project/opennebula   /pub    nfs     defaults        0 0 >> /etc/fstab
else
	echo cosa
	#echo kriemhild:/pub    /pub    nfs     defaults        0 0 >> /etc/fstab 
fi

/etc/init.d/nfs-common restart
mount -a

/etc/init.d/slurm-llnl restart

#IP=2435
#echo $(($IP%50+2))

