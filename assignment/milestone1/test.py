#!/usr/bin/python3

import subprocess
from pathlib import Path
import shutil
import tempfile
import threading
import multiprocessing

debug = []
# debug=["C4Pop10.3"]

script_dir = Path(__file__).resolve().parent

makefile = script_dir / "BoardTest.mak"

genScript = script_dir / "../milestone0/gen.py"

builtFiles = script_dir / "../milestone0/build"

testDir = script_dir / "test"

goodBoardTest = script_dir / "../milestone0/BoardTest"
myBoardTest = script_dir / "./BoardTest"

assert not testDir.is_file()
assert genScript.exists()

if not testDir.exists():
    testDir.mkdir()

completion = subprocess.run(["python3", "./clean.py"])
if completion.returncode > 0:
    print("Clean error")
    exit(1)
completion = subprocess.run(["make", "-f", str(makefile), "-j", str(multiprocessing.cpu_count())])
if completion.returncode > 0:
    print("Compile error")
    exit(1)

def run_file(f, currDir, tmpDir):
    if currDir.is_dir():
        shutil.rmtree(currDir)
    currDir.mkdir()
    assert currDir.is_dir()
    inPath = currDir / "input.txt"
    expectedPath = currDir / "expected.txt"
    actualPathOut = currDir / "actual.out.txt"
    actualPathErr = currDir / "actual.err.txt"
    diffOutPath = currDir / "diff.txt"

    assert not inPath.exists()
    assert not expectedPath.exists()
    assert not actualPathOut.exists()
    assert not actualPathErr.exists()
    assert not diffOutPath.exists()

    shutil.copy(f, inPath)
    with inPath.open("r") as inF:
        with expectedPath.open("w") as oF:
            if currDir.name in debug:
                subprocess.run(["python3", str(script_dir / "debug.py"), currDir.stem + "Board", "-b", goodBoardTest], cwd=tmpDir, stdin=inF, stdout=oF)
            else:
                subprocess.run([str(goodBoardTest), currDir.stem + "Board"], cwd=tmpDir, stdin=inF, stdout=oF)
        inF.seek(0)
        with actualPathOut.open("w") as ooF, actualPathErr.open("w") as oef:
            if currDir.name in debug:
                subprocess.run(["python3", str(script_dir / "debug.py"), currDir.stem + "Board", "-b", myBoardTest], cwd=tmpDir, stdin=inF, stdout=ooF, stderr=oef)
            else:
                subprocess.run([str(myBoardTest), currDir.stem + "Board"], cwd=tmpDir, stdin=inF, stdout=ooF, stderr=oef)
    message = "\033[92mSUCCESS\033[0m"
    with diffOutPath.open("w") as oF:
        res = subprocess.run(["diff", "-y", str(expectedPath), str(actualPathOut), "--width=200"], cwd=tmpDir, stdout=oF)
        message = "\033[92mSUCCESS\033[0m"
        if res.returncode != 0:
            message = "\033[91mFAIL\033[0m"
    if not "FAIL" in message:
        if actualPathErr.stat().st_size > 0:
            message = "\033[93mWARN\033[0m"
    print("{:>12} {}".format(currDir.name, message))

thds = []

with tempfile.TemporaryDirectory() as tmpDir:
    subprocess.run(["python3", genScript], cwd=tmpDir)

    assert builtFiles.is_dir()
    for f in builtFiles.iterdir():
        currDir = testDir / f.name
        thd = threading.Thread(target=run_file, args=(f, currDir, tmpDir))
        thd.start()
        thds.append(thd)

    for thd in thds:
        thd.join()
