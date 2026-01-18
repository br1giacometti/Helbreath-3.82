#!/usr/bin/env python3
"""Remove all AdminOrder_* functions from Game.h and Game.cpp"""

import re

GAME_H = r"C:\Users\ShadowEvil\source\Repos3\Helbreath-3.82\Sources\Server\Game.h"
GAME_CPP = r"C:\Users\ShadowEvil\source\Repos3\Helbreath-3.82\Sources\Server\Game.cpp"

def remove_declarations_from_header():
    """Remove AdminOrder_* declarations from Game.h"""
    with open(GAME_H, 'r', encoding='utf-8', errors='replace') as f:
        lines = f.readlines()

    new_lines = []
    removed = 0
    for line in lines:
        if 'AdminOrder_' in line:
            removed += 1
            continue
        new_lines.append(line)

    with open(GAME_H, 'w', encoding='utf-8') as f:
        f.writelines(new_lines)

    print(f"Removed {removed} AdminOrder declarations from Game.h")
    return removed

def find_function_end(lines, start_idx):
    """Find the end of a function by counting braces"""
    brace_count = 0
    found_first_brace = False

    for i in range(start_idx, len(lines)):
        line = lines[i]
        for char in line:
            if char == '{':
                brace_count += 1
                found_first_brace = True
            elif char == '}':
                brace_count -= 1
                if found_first_brace and brace_count == 0:
                    return i
    return -1

def remove_implementations_from_cpp():
    """Remove AdminOrder_* implementations from Game.cpp"""
    with open(GAME_CPP, 'r', encoding='utf-8', errors='replace') as f:
        lines = f.readlines()

    # Pattern to match function definition start
    func_pattern = re.compile(r'^void CGame::AdminOrder_\w+\(')

    # Find all function start lines
    func_starts = []
    for i, line in enumerate(lines):
        if func_pattern.match(line):
            func_starts.append(i)

    print(f"Found {len(func_starts)} AdminOrder function implementations")

    # Find ranges to remove (start, end) for each function
    ranges_to_remove = []
    for start_idx in func_starts:
        end_idx = find_function_end(lines, start_idx)
        if end_idx != -1:
            ranges_to_remove.append((start_idx, end_idx))
            func_name = lines[start_idx].strip()[:60]
            print(f"  {start_idx+1}-{end_idx+1}: {func_name}...")

    # Remove functions (process in reverse to maintain indices)
    ranges_to_remove.sort(reverse=True)
    for start_idx, end_idx in ranges_to_remove:
        # Also remove any blank lines before the function
        while start_idx > 0 and lines[start_idx-1].strip() == '':
            start_idx -= 1
        del lines[start_idx:end_idx+1]

    with open(GAME_CPP, 'w', encoding='utf-8') as f:
        f.writelines(lines)

    print(f"\nRemoved {len(ranges_to_remove)} AdminOrder function implementations from Game.cpp")
    return len(ranges_to_remove)

def main():
    print("=== Removing AdminOrder functions ===\n")

    print("Step 1: Remove declarations from Game.h")
    remove_declarations_from_header()

    print("\nStep 2: Remove implementations from Game.cpp")
    remove_implementations_from_cpp()

    print("\n=== Done ===")

if __name__ == '__main__':
    main()
