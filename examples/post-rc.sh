#!/bin/bash
#----------------------------------------------------------
# Copyright 2011-2012, Ismael Farfán for the Thiao project - 2011
#
# Script to execute after rc.local in order to mount filesystems, update configuration files and restart services 
#----------------------------------------------------------

echo ... post-rc.sh ...

con=/mnt

if [ -f /mnt/context.sh ]
then
  echo cargando el contexto
  . /mnt/context.sh
else
  echo no hay contexto
  exit -1
fi

#--------------------------------------------

if [ -f $con/slurm.conf ]; then
	cp $con/slurm.conf /etc/slurm-llnl/
fi

if [ -f $con/munge.key ]; then
        cp $con/munge.key /etc/munge/
fi

if [ -f $con/prolog.sh ]; then
        cp $con/prolog.sh /usr/local/bin/
        chmod a+x /usr/local/bin/prolog.sh
fi

for i in  rc.local  hosts  resolv.conf  fstab  groups  group  shadow  passwd ; do 
   if [ -f $con/$i ]; then
      cp $con/$i /etc
   fi
done

sleep 5
mkdir -p /distrib
#/etc/init.d/nfs-common restart
mount -a

/etc/init.d/slurm-llnl restart

mount -a

