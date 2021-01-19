#!/usr/bin/python3

from pathlib import Path

script_dir = Path(__file__).resolve().parent

in_dir = script_dir / "src"
out_dir = script_dir / "build"

if not out_dir.exists():
    out_dir.mkdir()

substitutions = {
    "state" : "showBoard\nshowVal\nshowMove\nshowMoveHist\nkeyMoveCount",
    "pstate": "showMove\nshowMoveHist"
}

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

for child in in_dir.iterdir():
    process_file(child)
