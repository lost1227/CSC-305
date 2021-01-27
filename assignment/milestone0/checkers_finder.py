import subprocess
import re
import sys
import random
import queue
import time

class BoardTest:
    def __init__(self):
        self.run = subprocess.Popen(['./BoardTest', 'CheckersBoard'], stdin=subprocess.PIPE, stdout=subprocess.PIPE, universal_newlines=True, bufsize=1)
        self._movepattern = re.compile("[A-H][1-8](?: -> [A-H][1-8])+")
        self.boards = {}

    def _parseState(self):
        self._current_moves = []
        self.write("showBoard\n")
        doubleline = 0
        self._board = ""
        for i in range(15):
            line = self.readline()
            self._board += line
        assert len(self._board) == 300
        turn = self.readline().strip()
        self.turn = "white" if turn.lower().find("white") > 0 else "black"
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

    def real_board(self):
        out = ""
        boardlines = self._board.split('\n')
        for line in boardlines[2:10]:
            out += line[2:].strip() + "\n"
        return out

    def board_key(self):
        real = self.real_board()
        pieces = real.split()
        key = 0
        for i in range(len(pieces)):
            piece = pieces[i]
            if piece == ".":
                val = 0
            elif piece == "b":
                val = 1
            elif piece == "w":
                val = 1
            elif piece == "B":
                val = 2
            elif piece == "W":
                val = 3
            else:
                print("Invalid piece ", piece)
                assert False
            key += val * (4 ** i)
        return key

    def go(self, prev=[]):
        # print("  " * len(prev), prev)

        moveQueue = queue.SimpleQueue()

        self._parseState()
        moves = self._current_moves

        for move in moves:
            moveQueue.put((move, []))

        while not moveQueue.empty():
            move, prev = moveQueue.get()

            prev = prev + [move]

            for p in prev:
                self._doMove(p)

            self._parseState()
            moves = self._current_moves

            if len(moves) == 0:
                board_lower = self.real_board().lower()
                if board_lower.count("w") > 0 and board_lower.count("b") > 0:
                    print("found one!")
                    print(prev)
                    print(self._board)
            
            key = self.board_key()
            if key in self.boards:
                print("found one!")
                print(prev)
                print(self.boards[key])
            else:
                self.boards[key] = prev

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
testPlay = ""

sys.setrecursionlimit(10000)

prev_tests = {}

# while len(test.leafs) == 0:
    # seed = random.randint(0,99)
    # steps = random.randint(30,50)
    # if seed in prev_tests:
    #     for step in sorted(prev_tests[seed]):
    #         if steps >= step and steps < step + 8:
    #             steps = step + 8
    #     prev_tests[seed].add(steps)
    # else:
    #    prev_tests[seed] = set([steps])

    #testPlay = "testPlay {} {}".format(seed, steps)
    
    
    # testPlay = "testPlay 65 54"
    #test._doCmd("undoLastMove 1000")
    #test._doCmd(testPlay)

    #print(testPlay)
test.go(8)

print("No results :(")
