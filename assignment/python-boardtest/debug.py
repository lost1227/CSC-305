#!/usr/bin/python3
import subprocess
import threading
import time
import fcntl
import os
from sys import stdout, stdin

import argparse
from enum import Enum

class BoardTest:
    def __init__(self, boardType, boardFile, boardTest):
        self.run = subprocess.Popen([boardTest, boardType], stdin=subprocess.PIPE, stdout=subprocess.PIPE, universal_newlines=True, bufsize=1)
        self.out = self.run.stdout
        fl = fcntl.fcntl(self.out, fcntl.F_GETFL)
        fcntl.fcntl(self.out, fcntl.F_SETFL, fl | os.O_NONBLOCK)
        self.boardFile = boardFile
        self.output = ""

    def read(self):
        self.output = ""
        while self.do_read:
            try:
                self.output += self.out.readline()
            except IOError:
                time.sleep(0.001)
    
    def read_with_timeout(self):
        self.do_read = True
        t = threading.Thread(target=self.read)
        t.start()
        time.sleep(0.1)
        self.do_read = False
        t.join()

    def communicate(self):
        for line in self.boardFile:
            if self.run.poll() != None:
                break
            
            color_in = ""
            color_out = ""
            if stdout.isatty():
                color_in = '\033[92m'
                color_out = '\033[93m'

            print(color_in + ">>" + line.strip())
            self.run.stdin.write(line)
            self.read_with_timeout()
            print(color_out, end='')
            print(self.output, end='')
    
    def end(self):
        if self.run.poll() == None:
            self.run.kill()
            self.run.wait()


parser = argparse.ArgumentParser()

parser.add_argument("board_type", choices=["C4Pop10Board", "CheckersBoard", "OthelloBoard"])
parser.add_argument("-file", type=argparse.FileType('r'), default=stdin)

parser.add_argument("-bt", default="./BoardTest")

args = parser.parse_args()

it = BoardTest(args.board_type, args.file, args.bt)

try:
    it.communicate()
finally:
    it.end()
