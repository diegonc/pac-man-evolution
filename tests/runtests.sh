#!/bin/sh

BLACKLIST="OGL test_map_editor"

TESTS=`ls`
CWD=`pwd`

for i in ${TESTS}; do
	if [ -d ${i} ]; then
		if echo ${BLACKLIST} | grep -q $i; then
			continue;
		fi
		
		cd $i
		make
		cd ${CWD}
	fi
done
