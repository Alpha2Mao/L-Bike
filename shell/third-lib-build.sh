#! /bin/bash

THIRD_LIB_DIR=$(cd $(dirname $0);pwd)/..
echo ${THIRD_LIB_DIR}
for option
do
  echo "The option is ${option}"
  opt="$opt `echo $option | sed -e \"s/\(--[^=]*=\)\(.* .*\)/\1'\2'/\"`"
#  echo $option | sed -e 's/\(--[^=]*=\)\(.* .*\)/\1'\2'/'
  echo ${opt}
done