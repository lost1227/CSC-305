# General test makefile for multi-target test
# Copyright Clinton Staley 12/1/01


# General definitions
CPP = clang++-12
#CPP = /usr/local/bin/g++
CPPFLAGS = -std=c++11 -g -w -O3 -DLITTLE_ENDIAN
LINKFLAGS = -static-libstdc++

MANCALAOBJS = MancalaBoard.o MancalaMove.o MancalaView.o MancalaDlg.o
OTHELLOOBJS = OthelloBoard.o OthelloMove.o OthelloView.o OthelloDlg.o
PYLOSOBJS = PylosBoard.o PylosMove.o PylosView.o PylosDlg.o
CHECKERSOBJS = CheckersBoard.o CheckersMove.o CheckersView.o CheckersDlg.o
C4POP10OBJS = C4Pop10Board.o C4Pop10Move.o C4Pop10View.o C4Pop10Dlg.o
GAMEOBJS = Board.o Dialog.o Class.o $(OTHELLOOBJS) $(CHECKERSOBJS) $(C4POP10OBJS)
BOARDTESTOBJS = BoardTest.o $(GAMEOBJS)
MYBOARDTESTOBJS = MyBoardTest.o $(GAMEOBJS)
MAKEBOOKOBJS = MakeBook.o Book.o SimpleAIPlayer.o $(GAMEOBJS)
MINIMAXOBJS = MinimaxApp.o Steppable.o AIPlayer.o GameModel.o GameView.o HumanPlayer.o Book.o $(GAMEOBJS)

MinimaxApp : $(MINIMAXOBJS)
	$(CPP) $(LINKFLAGS) $(MINIMAXOBJS) -o MinimaxApp

MakeBook : $(MAKEBOOKOBJS)
	$(CPP) $(LINKFLAGS) $(MAKEBOOKOBJS) -o MakeBook

MyBoardTest : $(MYBOARDTESTOBJS)
	$(CPP) $(LINKFLAGS) $(MYBOARDTESTOBJS) -o MyBoardTest

BoardTest : $(BOARDTESTOBJS)
	$(CPP) $(LINKFLAGS) $(BOARDTESTOBJS) -o BoardTest

BTRelease: BoardTest BoardTest.o
	chmod 755 BoardTest
	chmod 644 BoardTest.o
	mv BoardTest BoardTest.o ../../milestone1

MBRelease: MakeBook
	chmod 755 MakeBook
	mv MakeBook ../../prj2

MMARelease: MinimaxApp
	cp MinimaxApp Pylos.gbk ../../prj3
	chmod 755 ../../prj3/MinimaxApp
	chmod 644 ../../prj3/Pylos.gbk

clean:
	rm BoardTest MyBoardTest *.o

# Buggy version dependencies and definitions
GAMEOBJSB0 = BoardTest.o Board.o Dialog.o Class.o $(CHECKERSOBJS) $(OTHELLOOBJS) $(PYLOSOBJS) $(C4POP10OBJS) MancalaBoard.o MancalaMoveB0.o MancalaView.o MancalaDlg.o

GAMEOBJSB1 = BoardTest.o Board.o Dialog.o Class.o $(CHECKERSOBJS) $(OTHELLOOBJS) $(PYLOSOBJS) $(C4POP10OBJS) MancalaBoardB1.o MancalaMove.o MancalaView.o MancalaDlg.o 

GAMEOBJSB2 = BoardTest.o Board.o Dialog.o Class.o $(CHECKERSOBJS) $(OTHELLOOBJS) $(PYLOSOBJS) $(C4POP10OBJS) MancalaBoardB2.o MancalaMove.o MancalaView.o MancalaDlg.o 

GAMEOBJSB3 = BoardTest.o Board.o Dialog.o Class.o $(CHECKERSOBJS) $(OTHELLOOBJS) $(PYLOSOBJS) $(C4POP10OBJS) MancalaBoardB3.o MancalaMove.o MancalaView.o MancalaDlg.o 

GAMEOBJSB4 = BoardTest.o Board.o Dialog.o Class.o $(CHECKERSOBJS) $(OTHELLOOBJS) $(PYLOSOBJS) $(C4POP10OBJS) MancalaBoardB4.o MancalaMove.o MancalaView.o MancalaDlg.o 

GAMEOBJSB5 = BoardTest.o Board.o Dialog.o Class.o $(CHECKERSOBJS) $(OTHELLOOBJS) $(PYLOSOBJS) $(C4POP10OBJS) MancalaBoard.o MancalaMoveB5.o MancalaView.o MancalaDlg.o

GAMEOBJSB6 = BoardTest.o Board.o Dialog.o Class.o $(CHECKERSOBJS) $(OTHELLOOBJS) $(PYLOSOBJS) $(C4POP10OBJS) MancalaBoard.o MancalaMoveB6.o MancalaView.o MancalaDlg.o

GAMEOBJSB7 = BoardTest.o Board.o Dialog.o Class.o $(CHECKERSOBJS) $(OTHELLOOBJS) $(PYLOSOBJS) $(C4POP10OBJS) MancalaBoardB7.o MancalaMove.o MancalaView.o MancalaDlg.o 

GAMEOBJSB8 = BoardTest.o Board.o Dialog.o Class.o $(CHECKERSOBJS) $(OTHELLOOBJS) $(PYLOSOBJS) $(C4POP10OBJS) MancalaBoard.o MancalaMove.o MancalaView.o MancalaDlgB8.o 

GAMEOBJSB9 = BoardTest.o Board.o Dialog.o Class.o $(CHECKERSOBJS) $(OTHELLOOBJS) $(PYLOSOBJS) $(C4POP10OBJS) MancalaBoard.o MancalaMove.o MancalaView.o MancalaDlgB9.o 


GAMEOBJSB10 = BoardTest.o Board.o Dialog.o Class.o $(CHECKERSOBJS) $(OTHELLOOBJS) $(MANCALAOBJS) PylosBoardB10.o PylosMove.o PylosView.o PylosDlg.o

GAMEOBJSB11 = BoardTest.o Board.o Dialog.o Class.o $(CHECKERSOBJS) $(OTHELLOOBJS) $(MANCALAOBJS) PylosBoard.o PylosMoveB11.o PylosView.o PylosDlg.o

GAMEOBJSB12 = BoardTest.o Board.o Dialog.o Class.o $(CHECKERSOBJS) $(OTHELLOOBJS) $(MANCALAOBJS) PylosBoard.o PylosMoveB12.o PylosView.o PylosDlg.o

GAMEOBJSB13 = BoardTest.o Board.o Dialog.o Class.o $(CHECKERSOBJS) $(OTHELLOOBJS) $(MANCALAOBJS) PylosBoard.o PylosMoveB13.o PylosView.o PylosDlg.o

GAMEOBJSB14 = BoardTest.o Board.o Dialog.o Class.o $(CHECKERSOBJS) $(OTHELLOOBJS) $(MANCALAOBJS) PylosBoard.o PylosMoveB14.o PylosView.o PylosDlg.o

GAMEOBJSB15 = BoardTest.o Board.o Dialog.o Class.o $(CHECKERSOBJS) $(OTHELLOOBJS) $(MANCALAOBJS) PylosBoardB15.o PylosMove.o PylosView.o PylosDlg.o

GAMEOBJSB16 = BoardTest.o Board.o Dialog.o Class.o $(CHECKERSOBJS) $(OTHELLOOBJS) $(MANCALAOBJS) PylosBoardB16.o PylosMove.o PylosView.o PylosDlg.o

GAMEOBJSB17 = BoardTest.o Board.o Dialog.o Class.o $(CHECKERSOBJS) $(OTHELLOOBJS) $(MANCALAOBJS) PylosBoardB17.o PylosMove.o PylosView.o PylosDlg.o

GAMEOBJSB18 = BoardTest.o Board.o Dialog.o Class.o $(CHECKERSOBJS) $(OTHELLOOBJS) $(MANCALAOBJS) PylosBoardB18.o PylosMove.o PylosView.o PylosDlg.o

GAMEOBJSB19 = BoardTest.o Board.o Dialog.o Class.o $(CHECKERSOBJS) $(OTHELLOOBJS) $(MANCALAOBJS) PylosBoardB19.o PylosMove.o PylosView.o PylosDlg.o

GAMEOBJSB20 = BoardTest.o Board.o Dialog.o Class.o $(CHECKERSOBJS) $(OTHELLOOBJS) $(MANCALAOBJS) PylosBoardB20.o PylosMove.o PylosView.o PylosDlg.o



GAMEOBJSB21 = BoardTest.o Board.o Dialog.o Class.o $(CHECKERSOBJS) $(PYLOSOBJS) $(C4POP10OBJS) $(MANCALAOBJS) OthelloBoardB21.o OthelloMove.o OthelloView.o OthelloDlg.o

GAMEOBJSB22 = BoardTest.o Board.o Dialog.o Class.o $(CHECKERSOBJS) $(PYLOSOBJS) $(C4POP10OBJS) $(MANCALAOBJS) OthelloBoardB22.o OthelloMove.o OthelloView.o OthelloDlg.o

GAMEOBJSB23 = BoardTest.o Board.o Dialog.o Class.o $(CHECKERSOBJS) $(PYLOSOBJS) $(C4POP10OBJS) $(MANCALAOBJS) OthelloBoardB23.o OthelloMove.o OthelloView.o OthelloDlg.o

GAMEOBJSB24 = BoardTest.o Board.o Dialog.o Class.o $(CHECKERSOBJS) $(PYLOSOBJS) $(C4POP10OBJS) $(MANCALAOBJS) OthelloBoardB24.o OthelloMove.o OthelloView.o OthelloDlg.o

GAMEOBJSB25 = BoardTest.o Board.o Dialog.o Class.o $(CHECKERSOBJS) $(PYLOSOBJS) $(C4POP10OBJS) $(MANCALAOBJS) OthelloBoard.o OthelloMoveB25.o OthelloView.o OthelloDlg.o

GAMEOBJSB26 = BoardTest.o Board.o Dialog.o Class.o $(CHECKERSOBJS) $(PYLOSOBJS) $(C4POP10OBJS) $(MANCALAOBJS) OthelloBoard.o OthelloMoveB26.o OthelloView.o OthelloDlg.o

GAMEOBJSB27 = BoardTest.o Board.o Dialog.o Class.o $(CHECKERSOBJS) $(PYLOSOBJS) $(C4POP10OBJS) $(MANCALAOBJS) OthelloBoardB27.o OthelloMove.o OthelloView.o OthelloDlg.o


GAMEOBJSB28 = BoardTest.o Board.o Dialog.o Class.o $(OTHELLOOBJS) $(PYLOSOBJS) $(C4POP10OBJS) $(MANCALAOBJS) CheckersBoardB28.o CheckersMove.o CheckersView.o CheckersDlg.o

GAMEOBJSB29 = BoardTest.o Board.o Dialog.o Class.o $(OTHELLOOBJS) $(PYLOSOBJS) $(C4POP10OBJS) $(MANCALAOBJS) CheckersBoardB29.o CheckersMove.o CheckersView.o CheckersDlg.o

GAMEOBJSB30 = BoardTest.o Board.o Dialog.o Class.o $(OTHELLOOBJS) $(PYLOSOBJS) $(C4POP10OBJS) $(MANCALAOBJS) CheckersBoardB30.o CheckersMove.o CheckersView.o CheckersDlg.o

GAMEOBJSB31 = BoardTest.o Board.o Dialog.o Class.o $(OTHELLOOBJS) $(PYLOSOBJS) $(C4POP10OBJS) $(MANCALAOBJS) CheckersBoard.o CheckersMoveB31.o CheckersView.o CheckersDlg.o

GAMEOBJSB32 = BoardTest.o Board.o Dialog.o Class.o $(OTHELLOOBJS) $(PYLOSOBJS) $(C4POP10OBJS) $(MANCALAOBJS) CheckersBoard.o CheckersMoveB32.o CheckersView.o CheckersDlg.o

GAMEOBJSB33 = BoardTest.o Board.o Dialog.o Class.o $(OTHELLOOBJS) $(PYLOSOBJS) $(C4POP10OBJS) $(MANCALAOBJS) CheckersBoardB33.o CheckersMove.o CheckersView.o CheckersDlg.o

GAMEOBJSB34 = BoardTest.o Board.o Dialog.o Class.o $(OTHELLOOBJS) $(PYLOSOBJS) $(C4POP10OBJS) $(MANCALAOBJS) CheckersBoardB34.o CheckersMove.o CheckersView.o CheckersDlg.o

GAMEOBJSB35 = BoardTest.o Board.o Dialog.o Class.o $(OTHELLOOBJS) $(PYLOSOBJS) $(C4POP10OBJS) $(MANCALAOBJS) CheckersBoardB35.o CheckersMove.o CheckersView.o CheckersDlg.o

GAMEOBJSB36 = BoardTest.o Board.o Dialog.o Class.o $(OTHELLOOBJS) $(PYLOSOBJS) $(MANCALAOBJS) $(CHECKERSOBJS) C4Pop10Board.o C4Pop10MoveB36.o C4Pop10View.o C4Pop10Dlg.o

GAMEOBJSB37 = BoardTest.o Board.o Dialog.o Class.o $(OTHELLOOBJS) $(PYLOSOBJS) $(MANCALAOBJS) $(CHECKERSOBJS) C4Pop10Board.o C4Pop10MoveB37.o C4Pop10View.o C4Pop10Dlg.o

GAMEOBJSB38 = BoardTest.o Board.o Dialog.o Class.o $(OTHELLOOBJS) $(PYLOSOBJS) $(MANCALAOBJS) $(CHECKERSOBJS) C4Pop10Board.o C4Pop10MoveB38.o C4Pop10View.o C4Pop10Dlg.o

GAMEOBJSB39 = BoardTest.o Board.o Dialog.o Class.o $(OTHELLOOBJS) $(PYLOSOBJS) $(MANCALAOBJS) $(CHECKERSOBJS) C4Pop10BoardB39.o C4Pop10Move.o C4Pop10View.o C4Pop10Dlg.o

GAMEOBJSB40 = BoardTest.o Board.o Dialog.o Class.o $(OTHELLOOBJS) $(PYLOSOBJS) $(MANCALAOBJS) $(CHECKERSOBJS) C4Pop10BoardB40.o C4Pop10Move.o C4Pop10View.o C4Pop10Dlg.o

GAMEOBJSB41 = BoardTest.o Board.o Dialog.o Class.o $(OTHELLOOBJS) $(PYLOSOBJS) $(MANCALAOBJS) $(CHECKERSOBJS) C4Pop10BoardB41.o C4Pop10Move.o C4Pop10View.o C4Pop10Dlg.o

GAMEOBJSB42 = BoardTest.o Board.o Dialog.o Class.o $(OTHELLOOBJS) $(PYLOSOBJS) $(MANCALAOBJS) $(CHECKERSOBJS) C4Pop10BoardB42.o C4Pop10Move.o C4Pop10View.o C4Pop10Dlg.o

GAMEOBJSB43 = BoardTest.o Board.o Dialog.o Class.o $(OTHELLOOBJS) $(PYLOSOBJS) $(MANCALAOBJS) $(CHECKERSOBJS) C4Pop10BoardB43.o C4Pop10Move.o C4Pop10View.o C4Pop10Dlg.o

GAMEOBJSB44 = BoardTest.o Board.o Dialog.o Class.o $(OTHELLOOBJS) $(PYLOSOBJS) $(MANCALAOBJS) $(CHECKERSOBJS) C4Pop10BoardB44.o C4Pop10Move.o C4Pop10View.o C4Pop10Dlg.o

GAMEOBJSB45 = BoardTest.o Board.o Dialog.o Class.o $(OTHELLOOBJS) $(PYLOSOBJS) $(MANCALAOBJS) $(CHECKERSOBJS) C4Pop10BoardB45.o C4Pop10Move.o C4Pop10View.o C4Pop10Dlg.o

GAMEOBJSB46 = BoardTest.o Board.o Dialog.o Class.o $(OTHELLOOBJS) $(PYLOSOBJS) $(MANCALAOBJS) $(CHECKERSOBJS) C4Pop10BoardB46.o C4Pop10Move.o C4Pop10View.o C4Pop10Dlg.o


MancalaMoveB0.o : MancalaMove.cpp
	$(CPP) $(CPPFLAGS) -c -DBUG0 MancalaMove.cpp -o MancalaMoveB0.o

MancalaBoardB1.o : MancalaBoard.cpp
	$(CPP) $(CPPFLAGS) -c -DBUG1 MancalaBoard.cpp -o MancalaBoardB1.o

MancalaBoardB2.o : MancalaBoard.cpp
	$(CPP) $(CPPFLAGS) -c -DBUG2 MancalaBoard.cpp -o MancalaBoardB2.o

MancalaBoardB3.o : MancalaBoard.cpp
	$(CPP) $(CPPFLAGS) -c -DBUG3 MancalaBoard.cpp -o MancalaBoardB3.o

MancalaBoardB4.o : MancalaBoard.cpp
	$(CPP) $(CPPFLAGS) -c -DBUG4 MancalaBoard.cpp -o MancalaBoardB4.o

MancalaMoveB5.o : MancalaMove.cpp
	$(CPP) $(CPPFLAGS) -c -DBUG5 MancalaMove.cpp -o MancalaMoveB5.o

MancalaMoveB6.o : MancalaMove.cpp
	$(CPP) $(CPPFLAGS) -c -DBUG6 MancalaMove.cpp -o MancalaMoveB6.o

MancalaBoardB7.o : MancalaBoard.cpp
	$(CPP) $(CPPFLAGS) -c -DBUG7 MancalaBoard.cpp -o MancalaBoardB7.o

MancalaDlgB8.o : MancalaDlg.cpp
	$(CPP) $(CPPFLAGS) -c -DBUG8 MancalaDlg.cpp -o MancalaDlgB8.o

MancalaDlgB9.o : MancalaDlg.cpp
	$(CPP) $(CPPFLAGS) -c -DBUG9 MancalaDlg.cpp -o MancalaDlgB9.o


PylosBoardB10.o : PylosBoard.cpp
	$(CPP) $(CPPFLAGS) -c -DBUG10 PylosBoard.cpp -o PylosBoardB10.o

PylosMoveB11.o : PylosMove.cpp
	$(CPP) $(CPPFLAGS) -c -DBUG11 PylosMove.cpp -o PylosMoveB11.o

PylosMoveB12.o : PylosMove.cpp
	$(CPP) $(CPPFLAGS) -c -DBUG12 PylosMove.cpp -o PylosMoveB12.o

PylosMoveB13.o : PylosMove.cpp
	$(CPP) $(CPPFLAGS) -c -DBUG13 PylosMove.cpp -o PylosMoveB13.o

PylosMoveB14.o : PylosMove.cpp
	$(CPP) $(CPPFLAGS) -c -DBUG14 PylosMove.cpp -o PylosMoveB14.o

PylosBoardB15.o : PylosBoard.cpp
	$(CPP) $(CPPFLAGS) -c -DBUG15 PylosBoard.cpp -o PylosBoardB15.o

PylosBoardB16.o : PylosBoard.cpp
	$(CPP) $(CPPFLAGS) -c -DBUG16 PylosBoard.cpp -o PylosBoardB16.o

PylosBoardB17.o : PylosBoard.cpp
	$(CPP) $(CPPFLAGS) -c -DBUG17 PylosBoard.cpp -o PylosBoardB17.o

PylosBoardB18.o : PylosBoard.cpp
	$(CPP) $(CPPFLAGS) -c -DBUG18 PylosBoard.cpp -o PylosBoardB18.o

PylosBoardB19.o : PylosBoard.cpp
	$(CPP) $(CPPFLAGS) -c -DBUG19 PylosBoard.cpp -o PylosBoardB19.o

PylosBoardB20.o : PylosBoard.cpp
	$(CPP) $(CPPFLAGS) -c -DBUG20 PylosBoard.cpp -o PylosBoardB20.o



OthelloBoardB21.o : OthelloBoard.cpp
	$(CPP) $(CPPFLAGS) -c -DBUG21 OthelloBoard.cpp -o OthelloBoardB21.o

OthelloBoardB22.o : OthelloBoard.cpp
	$(CPP) $(CPPFLAGS) -c -DBUG22 OthelloBoard.cpp -o OthelloBoardB22.o

OthelloBoardB23.o : OthelloBoard.cpp
	$(CPP) $(CPPFLAGS) -c -DBUG23 OthelloBoard.cpp -o OthelloBoardB23.o

OthelloBoardB24.o : OthelloBoard.cpp
	$(CPP) $(CPPFLAGS) -c -DBUG24 OthelloBoard.cpp -o OthelloBoardB24.o

OthelloMoveB25.o : OthelloMove.cpp
	$(CPP) $(CPPFLAGS) -c -DBUG25 OthelloMove.cpp -o OthelloMoveB25.o

OthelloMoveB26.o : OthelloMove.cpp
	$(CPP) $(CPPFLAGS) -c -DBUG26 OthelloMove.cpp -o OthelloMoveB26.o

OthelloBoardB27.o : OthelloBoard.cpp
	$(CPP) $(CPPFLAGS) -c -DBUG27 OthelloBoard.cpp -o OthelloBoardB27.o



CheckersBoardB28.o : CheckersBoard.cpp
	$(CPP) $(CPPFLAGS) -c -DBUG28 CheckersBoard.cpp -o CheckersBoardB28.o

CheckersBoardB29.o : CheckersBoard.cpp
	$(CPP) $(CPPFLAGS) -c -DBUG29 CheckersBoard.cpp -o CheckersBoardB29.o

CheckersBoardB30.o : CheckersBoard.cpp
	$(CPP) $(CPPFLAGS) -c -DBUG30 CheckersBoard.cpp -o CheckersBoardB30.o

CheckersMoveB31.o : CheckersMove.cpp
	$(CPP) $(CPPFLAGS) -c -DBUG31 CheckersMove.cpp -o CheckersMoveB31.o

CheckersMoveB32.o : CheckersMove.cpp
	$(CPP) $(CPPFLAGS) -c -DBUG32 CheckersMove.cpp -o CheckersMoveB32.o

CheckersBoardB33.o : CheckersBoard.cpp
	$(CPP) $(CPPFLAGS) -c -DBUG33 CheckersBoard.cpp -o CheckersBoardB33.o

CheckersBoardB34.o : CheckersBoard.cpp
	$(CPP) $(CPPFLAGS) -c -DBUG34 CheckersBoard.cpp -o CheckersBoardB34.o

CheckersBoardB35.o : CheckersBoard.cpp
	$(CPP) $(CPPFLAGS) -c -DBUG35 CheckersBoard.cpp -o CheckersBoardB35.o

C4Pop10MoveB36.o : C4Pop10Move.cpp
	$(CPP) $(CPPFLAGS) -c -DBUG36 C4Pop10Move.cpp -o C4Pop10MoveB36.o

C4Pop10MoveB37.o : C4Pop10Move.cpp
	$(CPP) $(CPPFLAGS) -c -DBUG37 C4Pop10Move.cpp -o C4Pop10MoveB37.o

C4Pop10MoveB38.o : C4Pop10Move.cpp
	$(CPP) $(CPPFLAGS) -c -DBUG38 C4Pop10Move.cpp -o C4Pop10MoveB38.o

C4Pop10BoardB39.o : C4Pop10Board.cpp
	$(CPP) $(CPPFLAGS) -c -DBUG39 C4Pop10Board.cpp -o C4Pop10BoardB39.o

C4Pop10BoardB40.o : C4Pop10Board.cpp
	$(CPP) $(CPPFLAGS) -c -DBUG40 C4Pop10Board.cpp -o C4Pop10BoardB40.o

C4Pop10BoardB41.o : C4Pop10Board.cpp
	$(CPP) $(CPPFLAGS) -c -DBUG41 C4Pop10Board.cpp -o C4Pop10BoardB41.o

C4Pop10BoardB42.o : C4Pop10Board.cpp
	$(CPP) $(CPPFLAGS) -c -DBUG42 C4Pop10Board.cpp -o C4Pop10BoardB42.o

C4Pop10BoardB43.o : C4Pop10Board.cpp
	$(CPP) $(CPPFLAGS) -c -DBUG43 C4Pop10Board.cpp -o C4Pop10BoardB43.o

C4Pop10BoardB44.o : C4Pop10Board.cpp
	$(CPP) $(CPPFLAGS) -c -DBUG44 C4Pop10Board.cpp -o C4Pop10BoardB44.o

C4Pop10BoardB45.o : C4Pop10Board.cpp
	$(CPP) $(CPPFLAGS) -c -DBUG45 C4Pop10Board.cpp -o C4Pop10BoardB45.o

C4Pop10BoardB46.o : C4Pop10Board.cpp
	$(CPP) $(CPPFLAGS) -c -DBUG46 C4Pop10Board.cpp -o C4Pop10BoardB46.o


BoardTestB0 : $(GAMEOBJSB0)
	$(CPP)  $(LINKFLAGS) $(GAMEOBJSB0) -o BoardTestB0

BoardTestB1 : $(GAMEOBJSB1)
	$(CPP)  $(LINKFLAGS) $(GAMEOBJSB1) -o BoardTestB1

BoardTestB2 : $(GAMEOBJSB2)
	$(CPP)  $(LINKFLAGS) $(GAMEOBJSB2) -o BoardTestB2

BoardTestB3 : $(GAMEOBJSB3)
	$(CPP)  $(LINKFLAGS) $(GAMEOBJSB3) -o BoardTestB3

BoardTestB4 : $(GAMEOBJSB4)
	$(CPP)  $(LINKFLAGS) $(GAMEOBJSB4) -o BoardTestB4

BoardTestB5 : $(GAMEOBJSB5)
	$(CPP)  $(LINKFLAGS) $(GAMEOBJSB5) -o BoardTestB5

BoardTestB6 : $(GAMEOBJSB6)
	$(CPP)  $(LINKFLAGS) $(GAMEOBJSB6) -o BoardTestB6

BoardTestB7 : $(GAMEOBJSB7)
	$(CPP)  $(LINKFLAGS) $(GAMEOBJSB7) -o BoardTestB7

BoardTestB8 : $(GAMEOBJSB8)
	$(CPP)  $(LINKFLAGS) $(GAMEOBJSB8) -o BoardTestB8

BoardTestB9 : $(GAMEOBJSB9)
	$(CPP)  $(LINKFLAGS) $(GAMEOBJSB9) -o BoardTestB9

BoardTestB10 : $(GAMEOBJSB10)
	$(CPP)  $(LINKFLAGS) $(GAMEOBJSB10) -o BoardTestB10

BoardTestB11 : $(GAMEOBJSB11)
	$(CPP)  $(LINKFLAGS) $(GAMEOBJSB11) -o BoardTestB11

BoardTestB12 : $(GAMEOBJSB12)
	$(CPP)  $(LINKFLAGS) $(GAMEOBJSB12) -o BoardTestB12

BoardTestB13 : $(GAMEOBJSB13)
	$(CPP)  $(LINKFLAGS) $(GAMEOBJSB13) -o BoardTestB13

BoardTestB14 : $(GAMEOBJSB14)
	$(CPP)  $(LINKFLAGS) $(GAMEOBJSB14) -o BoardTestB14

BoardTestB15 : $(GAMEOBJSB15)
	$(CPP)  $(LINKFLAGS) $(GAMEOBJSB15) -o BoardTestB15

BoardTestB16 : $(GAMEOBJSB16)
	$(CPP)  $(LINKFLAGS) $(GAMEOBJSB16) -o BoardTestB16

BoardTestB17 : $(GAMEOBJSB17)
	$(CPP)  $(LINKFLAGS) $(GAMEOBJSB17) -o BoardTestB17

BoardTestB18 : $(GAMEOBJSB18)
	$(CPP)  $(LINKFLAGS) $(GAMEOBJSB18) -o BoardTestB18

BoardTestB19 : $(GAMEOBJSB19)
	$(CPP)  $(LINKFLAGS) $(GAMEOBJSB19) -o BoardTestB19

BoardTestB20 : $(GAMEOBJSB20)
	$(CPP)  $(LINKFLAGS) $(GAMEOBJSB20) -o BoardTestB20

BoardTestB21 : $(GAMEOBJSB21)
	$(CPP)  $(LINKFLAGS) $(GAMEOBJSB21) -o BoardTestB21

BoardTestB22 : $(GAMEOBJSB22)
	$(CPP)  $(LINKFLAGS) $(GAMEOBJSB22) -o BoardTestB22

BoardTestB23 : $(GAMEOBJSB23)
	$(CPP)  $(LINKFLAGS) $(GAMEOBJSB23) -o BoardTestB23

BoardTestB24 : $(GAMEOBJSB24)
	$(CPP)  $(LINKFLAGS) $(GAMEOBJSB24) -o BoardTestB24

BoardTestB25 : $(GAMEOBJSB25)
	$(CPP)  $(LINKFLAGS) $(GAMEOBJSB25) -o BoardTestB25

BoardTestB26 : $(GAMEOBJSB26)
	$(CPP)  $(LINKFLAGS) $(GAMEOBJSB26) -o BoardTestB26

BoardTestB27 : $(GAMEOBJSB27)
	$(CPP)  $(LINKFLAGS) $(GAMEOBJSB27) -o BoardTestB27

BoardTestB28 : $(GAMEOBJSB28)
	$(CPP)  $(LINKFLAGS) $(GAMEOBJSB28) -o BoardTestB28

BoardTestB29 : $(GAMEOBJSB29)
	$(CPP)  $(LINKFLAGS) $(GAMEOBJSB29) -o BoardTestB29

BoardTestB30 : $(GAMEOBJSB30)
	$(CPP)  $(LINKFLAGS) $(GAMEOBJSB30) -o BoardTestB30

BoardTestB31 : $(GAMEOBJSB31)
	$(CPP)  $(LINKFLAGS) $(GAMEOBJSB31) -o BoardTestB31

BoardTestB32 : $(GAMEOBJSB32)
	$(CPP)  $(LINKFLAGS) $(GAMEOBJSB32) -o BoardTestB32

BoardTestB33 : $(GAMEOBJSB33)
	$(CPP)  $(LINKFLAGS) $(GAMEOBJSB33) -o BoardTestB33

BoardTestB34 : $(GAMEOBJSB34)
	$(CPP)  $(LINKFLAGS) $(GAMEOBJSB34) -o BoardTestB34

BoardTestB35 : $(GAMEOBJSB35)
	$(CPP)  $(LINKFLAGS) $(GAMEOBJSB35) -o BoardTestB35

BoardTestB36 : $(GAMEOBJSB36)
	$(CPP)  $(LINKFLAGS) $(GAMEOBJSB36) -o BoardTestB36

BoardTestB37 : $(GAMEOBJSB37)
	$(CPP)  $(LINKFLAGS) $(GAMEOBJSB37) -o BoardTestB37

BoardTestB38 : $(GAMEOBJSB38)
	$(CPP)  $(LINKFLAGS) $(GAMEOBJSB38) -o BoardTestB38

BoardTestB39 : $(GAMEOBJSB39)
	$(CPP)  $(LINKFLAGS) $(GAMEOBJSB39) -o BoardTestB39

BoardTestB40 : $(GAMEOBJSB40)
	$(CPP)  $(LINKFLAGS) $(GAMEOBJSB40) -o BoardTestB40

BoardTestB41 : $(GAMEOBJSB41)
	$(CPP)  $(LINKFLAGS) $(GAMEOBJSB41) -o BoardTestB41

BoardTestB42 : $(GAMEOBJSB42)
	$(CPP)  $(LINKFLAGS) $(GAMEOBJSB42) -o BoardTestB42

BoardTestB43 : $(GAMEOBJSB43)
	$(CPP)  $(LINKFLAGS) $(GAMEOBJSB43) -o BoardTestB43

BoardTestB44 : $(GAMEOBJSB44)
	$(CPP)  $(LINKFLAGS) $(GAMEOBJSB44) -o BoardTestB44

BoardTestB45 : $(GAMEOBJSB45)
	$(CPP)  $(LINKFLAGS) $(GAMEOBJSB45) -o BoardTestB45

BoardTestB46 : $(GAMEOBJSB46)
	$(CPP)  $(LINKFLAGS) $(GAMEOBJSB46) -o BoardTestB46

AllBugs : BoardTestB0 BoardTestB1 BoardTestB2 BoardTestB3 BoardTestB4 BoardTestB5 BoardTestB6 BoardTestB7 BoardTestB8 BoardTestB9 BoardTestB10 BoardTestB11 BoardTestB12 BoardTestB13 BoardTestB14 BoardTestB15 BoardTestB16 BoardTestB17 BoardTestB18 BoardTestB19 BoardTestB20 BoardTestB21 BoardTestB22 BoardTestB23 BoardTestB24 BoardTestB25 BoardTestB26 BoardTestB27 BoardTestB28 BoardTestB29 BoardTestB30 BoardTestB31 BoardTestB32 BoardTestB33 BoardTestB34 BoardTestB35 BoardTestB36 BoardTestB37 BoardTestB38 BoardTestB39 BoardTestB40 BoardTestB41 BoardTestB42 BoardTestB43 BoardTestB44 BoardTestB45 BoardTestB46
	mv BoardTestB* /home/grade-cstaley/305/milestone0/turnin/tests

# Header file interdependencies

CheckersDlg.h OthelloDlg.h MancalaDlg.h PylosDlg.h: Dialog.h
	touch MancalaDlg.h PylosDlg.h CheckersDlg.h OthelloDlg.h

MancalaView.h PylosView.h OthelloView.h CheckersView.h : View.h
	touch MancalaView.h PylosView.h OthelloView.h CheckersView.h

MancalaBoard.cpp: Class.h Board.h
	touch MancalaBoard.cpp
MancalaMove.cpp: MancalaBoard.h Class.h Board.h
	touch MancalaMove.cpp
MancalaView.cpp: MancalaBoard.h View.h Class.h Board.h
	touch MancalaView.cpp
MancalaDlg.cpp: MancalaBoard.h Dialog.h Class.h
	touch MancalaDlg.cpp

OthelloBoard.cpp: Class.h Board.h
	touch OthelloBoard.cpp
OthelloMove.cpp: OthelloBoard.h Class.h Board.h
	touch OthelloMove.cpp
OthelloView.cpp: OthelloBoard.h View.h Class.h Board.h
	touch OthelloView.cpp
OthelloDlg.cpp: OthelloBoard.h Dialog.h Class.h
	touch OthelloDlg.cpp

PylosBoard.cpp: Class.h Board.h
	touch PylosBoard.cpp
PylosMove.cpp: PylosView.h PylosBoard.h  Board.h
	touch PylosMove.cpp
PylosView.cpp: PylosBoard.h View.h Class.h  Board.h
	touch PylosView.cpp
PylosDlg.cpp: PylosBoard.h Dialog.h Class.h 
	touch PylosDlg.cpp

CheckersBoard.cpp: Class.h Board.h
	touch CheckersBoard.cpp
CheckersMove.cpp: CheckersView.h CheckersBoard.h  Board.h
	touch CheckersMove.cpp
CheckersView.cpp: CheckersBoard.h View.h Class.h  Board.h
	touch CheckersView.cpp
CheckersDlg.cpp: CheckersBoard.h Dialog.h Class.h 
	touch CheckersDlg.cpp

BoardTest.cpp: Board.h View.h Dialog.h

%.cpp: %.h
	touch $@

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -c $< -o $@

# DO NOT DELETE
