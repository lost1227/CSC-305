#!/bin/sh

set -e

ORIG_DIR=$(pwd)

cd $(dirname "$0")

make -f BoardTest.mak clean
make -f BoardTest.mak

ssh -t jjpowers@unix3.csc.calpoly.edu "cd /home/jjpowers/Documents/CSC-305/milestone1/ && ./clean.sh"
scp -r *.h *.cpp jjpowers@unix3.csc.calpoly.edu:/home/jjpowers/Documents/CSC-305/milestone1/

cd ${ORIG_DIR}