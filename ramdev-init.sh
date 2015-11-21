#!/bin/bash 

cd /usr/local/srcmirror
mount /ram1 2>/dev/null
dd if=/dev/zero of=/ram1/disk bs=4M count=10000 >/dev/null 2>&1
lo=`losetup -v -f /ram1/disk | sed s@.*/dev/@@`
mkfs.ext4 /dev/$lo >/dev/null 2>&1
mount -o acl /dev/$lo /usr/local/src

nb=`mount | grep /usr/local/src |wc -l`

if [ $nb -eq 1 ];then
	rm lock 2>/dev/null
	touch /usr/local/src/lock
	chmod o-t /usr/local/src
	chmod o-x /usr/local/src
	cp -a . /usr/local/src
	rm /usr/local/src/lock
fi
