#!/bin/sh

set -e

ORIG_DIR=$(pwd)

cd $(dirname "$0")

[ ! -d build ] && mkdir build

python3 ./gen.py

ssh -t jjpowers@unix3.csc.calpoly.edu "cd /home/jjpowers/Documents/CSC-305/milestone0/ && ./clean.sh"
scp -r build/* jjpowers@unix3.csc.calpoly.edu:/home/jjpowers/Documents/CSC-305/milestone0/

rm -r build

cd ${ORIG_DIR}