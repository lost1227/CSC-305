#!/usr/bin/python3

from pathlib import Path
import subprocess
import re

script_dir = Path(__file__).resolve().parent

in_dir = script_dir / "src"
out_dir = script_dir / "build"

boardTest = script_dir / "BoardTest"

max_outsize = 50000 # 50kB
max_outtime = 0.1 # seconds

substitutions = {
    "state" : "showBoard\nshowVal\nshowMove\nshowMoveHist\nkeyMoveCount",
    "pstate": "showMove\nshowMoveHist",
    "vstate": "showVal\nkeyMoveCount"
}

if not out_dir.exists():
    out_dir.mkdir()

def process_file(in_path):
    out_path = out_dir / in_path.stem

    with in_path.open('r') as fin:
        with out_path.open('w') as fout:
            while True:
                line = fin.readline()
                if not line:
                    break

                comment_idx = line.find('#')
                if comment_idx >= 0:
                    line = line[:comment_idx]

                line = line.strip()
                if len(line) > 0 and line[0] == '_':
                    keyword = line[1:]
                    line = substitutions[keyword]

                if len(line) > 0:
                    fout.write(line + '\n')

elapsed_re = re.compile("(\\d+):(\\d{2})\\.(\\d{2})elapsed")
usersys_re = re.compile("(\\d+)\\.(\\d{2})(?:user|system)")

def check_limits(file):
    boardName = file.stem + "Board"
    with file.open("r") as f:
        completion = subprocess.run([
            "time",
            boardTest,
            boardName,
            "1000",
        ], stdin=f,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE)
        
        output_size = len(completion.stdout)

        times = completion.stderr.decode().split(' ')[:3]

        user_m = usersys_re.match(times[0])
        system_m = usersys_re.match(times[1])
        real_m = elapsed_re.match(times[2])

        if user_m is None or system_m is None or real_m is None:
            print("regex error")
            return
        
        user_t = int(user_m.group(1)) + (int(user_m.group(2)) / 100)
        system_t = int(system_m.group(1)) + (int(system_m.group(2)) / 100)
        real_t = (int(real_m.group(1)) * 60) + int(real_m.group(2)) + (int(real_m.group(3)) / 100)

        success = True

        if output_size >= max_outsize:
            print("FAILURE! {}".format(file))
            print("  output is {} bytes ({:.1f}kB)".format(output_size, output_size / 1000))
            success = False
        
        if real_t > max_outtime:
            if success:
                print("FAILURE! {}".format(file))
            print("  execution took {:.2f} seconds".format(real_t))
        
        return success

for child in in_dir.iterdir():
    process_file(child)

for child in out_dir.iterdir():
    if not check_limits(child):
        exit(1)

for child in Path(".").glob("*.board"):
    child.unlink()