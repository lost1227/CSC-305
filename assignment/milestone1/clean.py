#!/usr/bin/python3
from pathlib import Path
import re
import subprocess

script_dir = Path(__file__).resolve().parent

limits = {
   "C4Pop10Board.h" : 78,
   "C4Pop10Board.cpp" : 340,
   "C4Pop10Move.h" : 42,
   "C4Pop10Move.cpp" : 115,
   "C4Pop10View.h": 15,
   "C4Pop10View.cpp": 40,
   "C4Pop10Dlg.h": 15,
   "C4Pop10Dlg.cpp": 40,
   "CheckersBoard.h": 90,
   "CheckersBoard.cpp": 320,
   "CheckersMove.h": 32,
   "CheckersMove.cpp": 125,
   "CheckersView.h": 13,
   "CheckersView.cpp": 27,
   "CheckersDlg.h": 13,
   "CheckersDlg.cpp": 30,
   "Dialog.cpp": 24
}

pat = re.compile("(\d+) countable lines")

for h in script_dir.glob("*.h"):
   completion = subprocess.run([script_dir / "smartcount" , h], stdout=subprocess.PIPE, text=True)
   match = pat.search(completion.stdout)
   if h.name in limits:
      if int(match.group(1)) > limits[h.name]:
         print("{}: FAIL".format(h.name))
   else:
      print("{}: not found".format(h.name))