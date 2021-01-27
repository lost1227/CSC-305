import subprocess
import re
import sys
import random
import queue
import time

class BoardTest:
    def __init__(self):
        self.run = subprocess.Popen(['./BoardTest', 'OthelloBoard'], stdin=subprocess.PIPE, stdout=subprocess.PIPE, universal_newlines=True, bufsize=1)
        self._movepattern = re.compile("(?:\\[[0-7], [0-7]\\]|Pass)")

    def _parseState(self):
        self._current_moves = []
        self.write("showBoard\n")
        self._board = ""
        for i in range(8):
            line = self.readline()
            self._board += line
        assert len(self._board) == 72
        turn = self.readline().strip()
        self.turn = "white" if turn[0] == "W" else "black"
        self.readline().strip()
        while True:
            line = self.readline().strip()
            if len(line) == 0:
                break
            for match in self._movepattern.finditer(line):
                self._current_moves.append(match.group(0))

    def write(self, text):
        self.run.stdin.write(text)

    def readline(self):
        line = self.run.stdout.readline()
        return line

    def _doMove(self, move):
        # print("doMove " + move.strip())
        self.write("doMove " + move.strip() + "\n")
        line = self.readline()
        assert len(line) == 1
    
    def _doCmd(self, cmd):
        self.write(cmd + "\n")
        line = self.readline()
        # print(cmd, "->", line)
        assert len(line) == 1
    
    def _undoMove(self):
        self.write("undoLastMove 1\n")
        self.readline()

    def go(self, prev=[]):
        # print("  " * len(prev), prev)

        moveQueue = queue.SimpleQueue()

        self._parseState()
        moves = self._current_moves

        for move in moves:
            moveQueue.put((move, []))

        depth = 0

        while not moveQueue.empty():
            move, prev = moveQueue.get()

            prev = prev + [move]

            if len(prev) > depth:
                depth = len(prev)
                print("Depth:", depth)

            for p in prev:
                self._doMove(p)

            self._parseState()
            moves = self._current_moves

            if len(moves) == 1 and moves[0] == "Pass":
                print("found one!")
                print(self._board)
                print(prev)

            for m in moves:
                moveQueue.put((m, prev))

            self._doCmd("undoLastMove 1000")

    def print_leafs(self):
        for leaf in self.leafs:
            #for move in leaf[0]:
            #    print("doMove", move)
            print(leaf[0])
            print(leaf[1])
            print()

                
        

test = BoardTest()

test.go(8)

print("No results :(")
