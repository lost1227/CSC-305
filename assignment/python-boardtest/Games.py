from abc import ABC, abstractmethod
import BoardTest

class Game(ABC):
   _initialized = False
   def __init__(self, gamestr):
      if self._initialized:
         raise Exception("Only one game at a time is supported")
      self._initialized = True
      BoardTest.init(gamestr)

   def enterMove(move: str):
      BoardTest.enterMove(move)

   def getCurrMove(self):
      return BoardTest.getCurrMove()

   def doMove(self, move: str):
      BoardTest.enterMove(move)
      BoardTest.applyMove()

   def saveBoardState(self):
      return BoardTest.saveBoardState()
   
   def loadBoardState(self, boardState: bytes):
      BoardTest.loadBoardState(boardState)

   def undoMoves(self, moveCount: int):
      BoardTest.undMoves(moveCount)

   def showBoard(self):
      return BoardTest.showBoard()

   def getValidMoves(self):
      return BoardTest.getValidMoves()
   
   def getMoveHist(self):
      return BoardTest.getMoveHist()


class CheckersGame(Game):
   def __init__(self):
      super().__init__("CheckersBoard")

class OthelloGame(Game):
   def __init__(self):
      super().__init__("OthelloBoard")

class C4Pop10Game(Game):
   def __init__(self):
      super().__init__("C4Pop10Board")

if __name__ == "__main__":
   import random
   import time

   game = CheckersGame()

   while True:
      print(game.showBoard())
      moves = game.getValidMoves()
      if len(moves) == 0:
         break
      move = random.choice(moves)
      print(move)
      game.doMove(move)

      time.sleep(0.2)

   print(game.getMoveHist())
