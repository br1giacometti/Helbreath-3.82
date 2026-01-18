#!/usr/bin/env python3
"""Remove all m_iAdminLevel* check blocks from Game.cpp"""

import re

GAME_CPP = r"C:\Users\ShadowEvil\source\Repos3\Helbreath-3.82\Sources\Server\Game.cpp"

# Pattern to match the admin level check blocks
# Matches:
#   if (m_pClientList[iClientH]->m_iAdminUserLevel < m_iAdminLevel*) {
#       // comment (optional)
#       SendNotifyMsg(0, iClientH, DEF_NOTIFY_ADMINUSERLEVELLOW, 0, 0, 0, 0);
#       return;
#   }
pattern = re.compile(
    r'\tif \(m_pClientList\[iClientH\]->m_iAdminUserLevel < m_iAdminLevel\w+\) \{\s*\n'
    r'(?:\t\t//[^\n]*\n)?'  # Optional comment line
    r'\t\tSendNotifyMsg\(0, iClientH, DEF_NOTIFY_ADMINUSERLEVELLOW, 0, 0, 0, 0\);\s*\n'
    r'\t\treturn;\s*\n'
    r'\t\}\s*\n',
    re.MULTILINE
)

def main():
    with open(GAME_CPP, 'r', encoding='utf-8', errors='replace') as f:
        content = f.read()

    # Find all matches first
    matches = list(pattern.finditer(content))
    print(f"Found {len(matches)} admin level check blocks to remove")

    for i, m in enumerate(matches):
        # Show first 50 chars of each match
        preview = m.group()[:80].replace('\n', '\\n')
        print(f"  {i+1}: {preview}...")

    if matches:
        # Remove all matches
        new_content = pattern.sub('', content)

        with open(GAME_CPP, 'w', encoding='utf-8') as f:
            f.write(new_content)

        print(f"\nSuccessfully removed {len(matches)} admin level check blocks")
    else:
        print("\nNo matches found - check pattern")

if __name__ == '__main__':
    main()
