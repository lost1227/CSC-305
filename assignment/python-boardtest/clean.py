#!/usr/bin/python3
from pathlib import Path
import subprocess
from itertools import chain

script_dir = Path(__file__).resolve().parent

for f in chain(script_dir.glob("*.h"), script_dir.glob("*.cpp")):
   subprocess.run(["clang-format-12", "-Werror", "--style=file", "-i", f])
