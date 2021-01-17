#!/bin/sh

set -e

ORIG_DIR=$(pwd)

cd $(dirname "$0")

python3 ./gen.py

ssh -t jjpowers@unix3.csc.calpoly.edu "rm -f /home/jjpowers/Documents/CSC-305/milestone0/*"
scp -r build/* jjpowers@unix3.csc.calpoly.edu:/home/jjpowers/Documents/CSC-305/milestone0/

cd ${ORIG_DIR}