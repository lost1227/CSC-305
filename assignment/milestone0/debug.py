#!/usr/bin/python3
import subprocess
import threading
import time
import fcntl
import os
from sys import stdout

import argparse
from enum import Enum

class BoardTest:
    def __init__(self, boardType, boardFile):
        self.run = subprocess.Popen(['./BoardTest', boardType], stdin=subprocess.PIPE, stdout=subprocess.PIPE, universal_newlines=True, bufsize=1)
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
        time.sleep(0.01)
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

parser.add_argument("board_type", choices=["c4pop10", "checkers", "othello"])
parser.add_argument("file", type=argparse.FileType('r'))

args = parser.parse_args()

btype = ""
if args.board_type == "c4pop10":
    btype = "C4Pop10Board"
elif args.board_type == "checkers":
    btype = "CheckersBoard"
elif args.board_type == "othello":
    btype = "OthelloBoard"
else:
    assert False

it = BoardTest(btype, args.file)

try:
    it.communicate()
finally:
    it.end()
