#!/bin/bash
set -e
nb=`mount | grep "/usr/local/src" | wc -l`
set +e
if [ $nb -eq 1 ]; then
	nb2=`ls /usr/local/src -1 |wc -l`
	if [ -f /usr/local/src/lock -o $nb2 -eq 0 ]; then
		exit 0
	fi
	cd /usr/local/src
	chmod o-t /usr/local/src
	chmod o-x /usr/local/src
	touch /usr/local/src/lock
	rsync --exclude-from=/home/mat/exploit/data/ram_exclude --delete-after -a . /usr/local/srcmirror >/dev/null 2>&1
	rm /usr/local/src/lock
	rm /usr/local/srcmirror/lock
fi
