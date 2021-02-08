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
        #print("doMove " + move.strip())
        self.write("doMove " + move.strip() + "\n")
        line = self.readline()
        if len(line) != 1:
            print(line)
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
            
            parts = move.split(' -> ')
            for i, part in enumerate(parts):
                if i == 0 or i == len(parts) - 1:
                    continue
                if part in parts[i+1]:
                    print("Found one!")
                    print(self._board)
                    print(prev)

            for m in moves:
                moveQueue.put((m, prev))

            #self._doCmd("undoLastMove 1000")
            self._doCmd("loadBoard init.board")

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

preMoves = [
"C1 -> D2",
"F8 -> E7",      
"D2 -> E1",
"E7 -> D8",
"C3 -> D2",
"G7 -> F8",
"B2 -> C1",      
"F2 -> E3",
"A3 -> B2",
"G3 -> F2",
"E1 -> G3",
"H4 -> F2",      
"C7 -> D6",
"H2 -> G3",
"B8 -> C7",
"F4 -> E5",
"D2 -> F4 -> H2",
"F2 -> E3",
"D6 -> F4",
"F6 -> E5"
]
for move in preMoves:
    test._doMove(move)

test._doCmd("saveBoard init.board")

test.go(8)

print("No results :(")
