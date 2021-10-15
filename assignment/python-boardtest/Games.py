from abc import ABC
import BoardTest
import struct
import io

class Game(ABC):
   _initialized = False
   _boardStateSynched = False
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
      self._boardStateSynched = False
      BoardTest.enterMove(move)
      BoardTest.applyMove()

   def saveBoardState(self):
      return BoardTest.saveBoardState()
   
   def loadBoardState(self, boardState: bytes):
      self._boardStateSynched = False
      BoardTest.loadBoardState(boardState)

   def undoMoves(self, moveCount: int):
      self._boardStateSynched = False
      BoardTest.undMoves(moveCount)

   def showBoard(self):
      return BoardTest.showBoard()

   def getValidMoves(self):
      return BoardTest.getValidMoves()
   
   def getMoveHist(self):
      return BoardTest.getMoveHist()



class CheckersGame(Game):
   _dim = -1
   _board = []
   _move = "??"

   def __init__(self):
      super().__init__("CheckersBoard")

   def _parseBoardState(self):
      binData = BoardTest.getBinaryBoard()
      with io.BytesIO(binData) as strm:

         dim = struct.unpack('B', strm.read(1))[0]
         self._dim = dim
         self._board = []
         for _ in range(dim-1, -1, -1):
            rowArr = []
            for _ in range(0, dim):
               rowArr.append(struct.unpack('B', strm.read(1))[0])
            self._board.append(rowArr)
         self._move = struct.unpack('B', strm.read(1))[0]

   def _verifyStateSync(self):
      if not self._boardStateSynched:
         self._parseBoardState()
         self._boardStateSynched = True

   def getWhoseMove(self):
      self._verifyStateSync()
      if self._move == 0:
         return "BLACK"
      else:
         return "WHITE"

   def getDim(self):
      self._verifyStateSync()
      return self._dim
   
   def getPieceAtPos(self, row, col):
      self._verifyStateSync()

      assert row < self._dim and col < self._dim

      piece = self._board[row][col]

      pieceStr = ""

      if piece & 0x01 != 0:
         if piece & 0x02 != 0:
            pieceStr = 'w'
         else:
            pieceStr = 'b'
      else:
         pieceStr = '.'
      
      if piece & 0x04 != 0:
         pieceStr = pieceStr.upper()
      
      return pieceStr

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
      for i in range(0, game.getDim()):
         row = ""
         for j in range(0, game.getDim()):
            row += game.getPieceAtPos(i, j)
         print(row)
      print(game.getWhoseMove())
      print("\n\n")

      #print(game.showBoard())

      moves = game.getValidMoves()
      if len(moves) == 0:
         break
      move = random.choice(moves)
      print(move)
      game.doMove(move)

      time.sleep(0.2)

   print(game.getMoveHist())
