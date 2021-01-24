import subprocess
import re

# This file was used to find two different sequences of moves that lead to the same othello board
# Using a brute-force algorithm, it can find such sequences

class BoardTest:
    def __init__(self):
        self.run = subprocess.Popen(['./BoardTest', 'OthelloBoard'], stdin=subprocess.PIPE, stdout=subprocess.PIPE, universal_newlines=True, bufsize=1)
        self._movepattern = re.compile("\\[(\\d), (\\d)\\]")
        self.leafs = []

    def _parseState(self):
        self._current_moves = []
        self.run.stdin.write("showBoard\n")
        doubleline = 0
        self._board = ""
        while True:
            line = self.run.stdout.readline()
            if len(line.strip()) == 0:
                break
            self._board += line
        
        allmoves = self.run.stdout.readline().strip()
        while True:
            line = self.run.stdout.readline().strip()
            if len(line) == 0:
                break
            for match in self._movepattern.finditer(line):
                self._current_moves.append("[{}, {}]".format(match.group(1), match.group(2)))

    def _doMove(self, move):
        print("doMove " + move.strip())
        self.run.stdin.write("doMove " + move.strip() + "\n")
        self.run.stdout.readline()
    
    def _undoMove(self):
        self.run.stdin.write("undoLastMove 1\n")
        self.run.stdout.readline()

    def go(self, num, prev=[]):
        self._parseState()
        if num == 0:
            self.leafs.append((prev, self._board))
            return
        moves = self._current_moves

        for move in moves:
            self._doMove(move)
            self.go(num - 1, prev + [move])
            self._undoMove()

    def print_leafs(self):
        for leaf in self.leafs:
            movestr = ""
            for move in leaf[0]:
                movestr += move + ","
            movestr = movestr[:-1]
            print(movestr)
            print(leaf[1])
            print()
    
    def find_equal(self):
        for i in range(len(self.leafs)):
            for j in range(i+1, len(self.leafs)):
                if self.leafs[i][1] == self.leafs[j][1]:
                    print(self.leafs[i][0])
                    print(self.leafs[j][0])
                    print(self.leafs[i][1])
                
        

test = BoardTest()

test.go(3)

test.find_equal()
