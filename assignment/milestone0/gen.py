#!/usr/bin/python3

from pathlib import Path

in_dir = Path("./src")
out_dir = Path("./build")

def process_file(in_path):
    out_path = out_dir / in_path.stem

    with in_path.open('r') as fin:
        with out_path.open('w') as fout:
            mode = "normal"
            char = fin.read(1)
            while True:
                next_char = fin.read(1)
                if not char:
                    break
                
                if mode == "normal":
                    if char == "#":
                        mode = "line_comment"
                    elif char == "/" and next_char == "*":
                        mode = "block_comment"
                    else:
                        if char != "\n" or next_char != "\n":
                            fout.write(char)
                elif mode == "line_comment":
                    if char == "\n":
                        mode = "normal"
                        fout.write(char)
                elif mode == "block_comment":
                    if char == "*" and next_char == "/":
                        next_char = fin.read(1)
                        mode = "normal"
                
                char = next_char
            fout.write('\n')

for child in in_dir.iterdir():
    process_file(child)