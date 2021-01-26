import subprocess
import re
import sys
import random

class BoardTest:
    def __init__(self):
        self.run = subprocess.Popen(['./BoardTest', 'CheckersBoard'], stdin=subprocess.PIPE, stdout=subprocess.PIPE, universal_newlines=True, bufsize=1)
        self._movepattern = re.compile("[A-H][1-8](?: -> [A-H][1-8])+")
        self.leafs = []

    def _parseState(self):
        self._current_moves = []
        self.write("showBoard\n")
        doubleline = 0
        self._board = ""
        for i in range(15):
            line = self.readline()
            self._board += line
        assert len(self._board) == 300
        self.readline().strip()
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
        self.readline()
    
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

    def go(self, depth, prev=[]):
        # print("  " * len(prev), prev)
        if depth <= 0:
            return
        self._parseState()
        moves = self._current_moves
        if len(self._current_moves) == 0:
            board = self.real_board().lower()
            white_count = board.count("w")
            black_count = board.count("b")
            if white_count == black_count:
                self.leafs.append((prev, self._board))
            return

        if len(self.leafs) > 0:
            return

        for move in moves:
            self._doMove(move)
            self.go(depth - 1, prev + [move])
            self._undoMove()

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
test.go(14)

    

test.print_leafs()

print(testPlay)
