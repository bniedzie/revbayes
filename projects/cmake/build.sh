#!/bin/sh

all_args=$@
mpi="false"
travis="false"
# parse command line arguments
while echo $1 | grep ^- > /dev/null; do
    # intercept help while parsing "-key value" pairs
    if [ "$1" = "--help" ] || [ "$1" = "-h" ]
    then
        echo '
Command line options are:
-h                              : print this help and exit.
'
        exit
    fi

    # parse pairs
    eval $( echo $1 | sed 's/-//g' | tr -d '\012')=$2
    shift
    shift
done

if [ "$mpi" = "true" ] && [ "$travis" = "false" ]; then
    BUILD_DIR="build-mpi"
else
    BUILD_DIR="build"
fi

if [ "$1" = "clean" ]
then
	rm -rf ${BUILD_DIR}
else
if [ ! -d ${BUILD_DIR} ]; then
	mkdir ${BUILD_DIR}
fi

    #################
    # generate git version number
    ./generate_version_number.sh
    cp ../../src/revlanguage/utils/GitVersion.cpp GitVersion_backup.cpp
    mv GitVersion.cpp ../../src/revlanguage/utils/

	./regenerate.sh ${all_args}
	cd ${BUILD_DIR} 
	CC=gcc CXX=g++ cmake -D Boost_NO_BOOST_CMAKE:BOOL=ON .
	make -j 4
	cd ..
	
    cp GitVersion_backup.cpp ../../src/revlanguage/utils/GitVersion.cpp
    rm GitVersion_backup.cpp
fi