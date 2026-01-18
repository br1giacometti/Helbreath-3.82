#!/usr/bin/env python3
"""Remove the remaining AdminOrder_CreateItem function from Game.cpp"""

import re

GAME_CPP = r"C:\Users\ShadowEvil\source\Repos3\Helbreath-3.82\Sources\Server\Game.cpp"

def main():
    with open(GAME_CPP, 'r', encoding='utf-8', errors='replace') as f:
        lines = f.readlines()

    # Find the AdminOrder_CreateItem function
    func_pattern = re.compile(r'^void CGame::AdminOrder_CreateItem\(')

    func_start = None
    for i, line in enumerate(lines):
        if func_pattern.match(line):
            func_start = i
            print(f"Found function start at line {i+1}: {line.strip()}")
            break

    if func_start is None:
        print("AdminOrder_CreateItem function not found")
        return

    # Find function end - look for a line that is exactly "}" at column 0
    func_end = None
    for i in range(func_start + 1, len(lines)):
        if lines[i].rstrip() == '}':
            func_end = i
            print(f"Found function end at line {i+1}")
            break

    if func_end is None:
        print("Could not find end of function")
        return

    print(f"Found AdminOrder_CreateItem at lines {func_start+1}-{func_end+1}")

    # Remove any blank lines before the function
    orig_start = func_start
    while func_start > 0 and lines[func_start-1].strip() == '':
        func_start -= 1

    # Remove the function
    del lines[func_start:func_end+1]

    with open(GAME_CPP, 'w', encoding='utf-8') as f:
        f.writelines(lines)

    print(f"Removed AdminOrder_CreateItem function ({func_end - func_start + 1} lines)")

if __name__ == '__main__':
    main()
