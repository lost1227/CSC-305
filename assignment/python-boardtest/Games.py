from abc import ABC
import BoardTest
import struct
import io

class Game(ABC):
   _initialized = False
   def __init__(self, gamestr):
      if Game._initialized:
         raise Exception("Only one game at a time is supported")
      self._boardStateSynched = False
      Game._initialized = True
      BoardTest.init(gamestr)

   def enterMove(move: str):
      """ Load a move as the 'current' move, ready to be executed. """
      BoardTest.enterMove(move)

   def applyMove():
      """ Execute the currently loaded move. """
      BoardTest.applyMove()

   def getCurrMove(self):
      """ Get the currently loaded move"""
      return BoardTest.getCurrMove()

   def doMove(self, move: str):
      """ Load and execute a move. Shorthand for enterMove() followed by
      applyMove(). """
      self._boardStateSynched = False
      BoardTest.enterMove(move)
      BoardTest.applyMove()

   def saveBoardState(self):
      """ Get the current board state as a binary blob. This can be later used
      by loadBoardState() to restore the board state. """
      return BoardTest.saveBoardState()
   
   def loadBoardState(self, boardState: bytes):
      """ Restore a board state saved by saveBoardState(). """
      self._boardStateSynched = False
      BoardTest.loadBoardState(boardState)

   def undoMoves(self, moveCount: int):
      """ Undo moveCount moves. If moveCount is greater than the number of 
      moves that have been executed, the board will be reset to its initial
      state. """
      self._boardStateSynched = False
      BoardTest.undoMoves(moveCount)

   def getBoardKey(self):
      return BoardTest.getBoardKey()

   def showBoard(self):
      return BoardTest.showBoard()

   def getValidMoves(self):
      return BoardTest.getValidMoves()
   
   def getMoveHist(self):
      return BoardTest.getMoveHist()



class CheckersGame(Game):
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
      """ Get the dimensions of the chess board. The board will have size
      getDim() x getDim(). """
      self._verifyStateSync()
      return self._dim
   
   def getPieceAtPos(self, row, col):
      """ Get the value of a piece at a certain board position. (0, 0) is in the
      upper-left corner. A dot (.) indicates no piece. A letter ("w" or "b")
      indicates the color of the piece. Capitalized letters are kinged. """
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

   def _parseBoardState(self):
      binData = BoardTest.getBinaryBoard()
      with io.BytesIO(binData) as strm:
         dim = struct.unpack('B', strm.read(1))[0]
         self._dim = dim
         self._board = []
         for _ in range(dim):
            rowArr = []
            for _ in range(dim):
               rowArr.append(struct.unpack('b', strm.read(1))[0])
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
      """ Get the dimensions of the chess board. The board will have size
      getDim() x getDim(). """
      self._verifyStateSync()
      return self._dim
   
   def getPieceAtPos(self, row, col):
      """ Get the value of a piece at a certain board position. (0, 0) is in the
      upper-left corner. A dot (.) indicates no piece. A letter ("W" or "B")
      indicates the color of the piece. """
      self._verifyStateSync()

      assert row < self._dim and col < self._dim

      piece = self._board[row][col]

      if piece == -1:
         return 'W'
      elif piece == 0:
         return '.'
      elif piece == 1:
         return 'B'
      else:
         raise ValueError("Unknown Othello board value (0x{:0X})".format(piece))

class C4Pop10Game(Game):
   class C4Pop10GameScore:
      """An object representing a player's score in C4Pop10. The score contains
      three values: safe disks, threat disks, and kept disks. A safe disc is one
      that can be removed and kept on this or a later move, with no opportunity
      for the opponent to interfere. A threat disk is a disc that the opponent
      can remove and keep unless the player does something to interfere. A kept
      disk is a disc the player has already removed and kept."""
      def __init__(self):
         self.safeDisks = 0
         self.threatDisks = 0
         self.keptDisks = 0

   def __init__(self):
      super().__init__("C4Pop10Board")

   def _parseBoardState(self):
      binData = BoardTest.getBinaryBoard()
      byte = struct.iter_unpack('b', binData)
      byte = map(lambda b: b[0], byte)
      self._width = next(byte)
      self._height = next(byte)
      self._board = []
      for _ in range(self._height):
         row = []
         for _ in range(self._width):
            row.append(next(byte))
         self._board.append(row)
      assert len(self._board) == self._height
      assert len(self._board[0]) == self._width
      self._move = next(byte)

      self._redScore = C4Pop10Game.C4Pop10GameScore()
      self._yellowScore = C4Pop10Game.C4Pop10GameScore()

      self._redScore.safeDisks = next(byte)
      self._redScore.threatDisks = next(byte)
      self._redScore.keptDisks = next(byte)

      self._yellowScore.safeDisks = next(byte)
      self._yellowScore.threatDisks = next(byte)
      self._yellowScore.keptDisks = next(byte)

   def _verifyStateSync(self):
      if not self._boardStateSynched:
         self._parseBoardState()
         self._boardStateSynched = True

   def getWhoseMove(self):
      self._verifyStateSync()
      if self._move == 0:
         return "YELLOW"
      else:
         return "RED"
   
   def getBoardDimensions(self):
      """ Get the dimensions of the checkers board. The return value is a
      tuple of (width, height)."""
      self._verifyStateSync()
      return (self._width, self._height)
   
   def getPieceAtPos(self, row, col):
      """Get the value of a piece at a certain board position. (0, 0) is in the
      upper-left corner. A dot (.) indicates no piece. A letter ("R" or "Y")
      indicates the color of the piece. """
      self._verifyStateSync()

      assert row < self._height and col < self._width

      piece = self._board[row][col]

      if piece & 0x01 != 0:
         if piece & 0x02 != 0:
            return "R"
         else:
            return "Y"
      else:
         return "."

   def getRedScore(self):
      """Gets the score of the red player. Returns a C4Pop10GameScore object."""
      self._verifyStateSync()
      return self._redScore

   def getYellowScore(self):
      self._verifyStateSync()
      return self._yellowScore

