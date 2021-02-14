#!/usr/bin/python3
from pathlib import Path
import re
import subprocess
from itertools import chain

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
   "Dialog.cpp": 33
}

pat = re.compile("(\d+) countable lines")

ec = 0

for f in chain(script_dir.glob("*.h"), script_dir.glob("*.cpp")):
   subprocess.run(["clang-format-12", "-Werror", "--style=file", "-i", f])
   completion = subprocess.run([script_dir / "smartcount" , f], stdout=subprocess.PIPE, text=True)
   match = pat.search(completion.stdout)
   if f.name in limits:
      if int(match.group(1)) > limits[f.name]:
         ec = 1
         print("{}: \033[91mFAIL\033[0m".format(f.name))

exit(ec)