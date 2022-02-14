#! /bin/bash

THIRD_LIB_DIR=$(cd $(dirname $0);pwd)/../third
echo ${THIRD_LIB_DIR}

GLOG_LIB_DIR=${THIRD_LIB_DIR}/glog-0.5.0

cd ${GLOG_LIB_DIR}
#if [ -d build ];then
#    rm -rf build
#    mkidr build
#fi
#cmake -B build
cd build
make
cp -r glog ../../../include
cp -r libglog.0.5.0.dylib libglog.0.dylib libglog.pc libglog.dylib ../../../lib