#!/usr/bin/python3

import subprocess
from pathlib import Path
import shutil
import tempfile

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

subprocess.run(["make", "-f", str(makefile)])

with tempfile.TemporaryDirectory() as tmpDir:
    subprocess.run(["python3", genScript], cwd=tmpDir)

    assert builtFiles.is_dir()
    for f in builtFiles.iterdir():
        currDir = testDir / f.name
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
                subprocess.run([goodBoardTest, currDir.stem + "Board"], cwd=tmpDir, stdin=inF, stdout=oF)
            inF.seek(0)
            with actualPathOut.open("w") as ooF, actualPathErr.open("w") as oef:
                subprocess.run([myBoardTest, currDir.stem + "Board"], cwd=tmpDir, stdin=inF, stdout=ooF, stderr=oef)
        
        with diffOutPath.open("w") as oF:
            res = subprocess.run(["diff", str(expectedPath), str(actualPathOut)], cwd=tmpDir, stdout=oF)
            message = "FAIL" if res.returncode != 0 else "SUCCESS"
            print("{:>12} {}".format(currDir.name, message))
