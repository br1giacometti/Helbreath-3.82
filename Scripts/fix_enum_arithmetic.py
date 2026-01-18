#!/usr/bin/env python3
"""Fix arithmetic operations on EffectType enum"""

import re
import sys
from pathlib import Path

def fix_effect_add(file_path: Path):
    """Fix Effect_Add.cpp: case 114 and AddEffectImpl with arithmetic"""
    content = file_path.read_text(encoding='utf-8')

    # Fix case 114
    content = re.sub(r'case 114:', 'case EffectType::CELEBRATING_LIGHT:', content)

    # Fix AddEffectImpl( 69 + (rand() % 2)
    content = re.sub(r'AddEffectImpl\(\s*69\s*\+\s*\(rand\(\)\s*%\s*2\)',
                    'AddEffectImpl(static_cast<EffectType>(69 + (rand() % 2))',
                    content)

    return content

def fix_effect_draw(file_path: Path):
    """Fix Effect_Draw.cpp: arithmetic on m_sType"""
    content = file_path.read_text(encoding='utf-8')

    # Fix: m_pEffectList[i]->m_sType - 41 and similar patterns
    # Need to cast m_sType to int for arithmetic
    # Only match when followed by arithmetic operator
    content = re.sub(r'->m_sType\s*(-\s*\d+)',
                    r'->static_cast<int>(m_sType)\1',
                    content)

    return content

def fix_effect_update(file_path: Path):
    """Fix Effect_Update.cpp: comparisons and arithmetic on m_sType"""
    content = file_path.read_text(encoding='utf-8')

    # Fix comparisons: m_sType == 41, m_sType != 42, etc.
    content = re.sub(r'->m_sType\s*(==|!=)\s*(\d+)',
                    r'->m_sType \1 EffectType::\2',
                    content)

    # Fix AddEffectImpl with variable: AddEffectImpl( 41 + x
    content = re.sub(r'AddEffectImpl\(\s*(\d+)\s*\+',
                    r'AddEffectImpl(static_cast<EffectType>(\1 +',
                    content)

    return content

def main():
    if len(sys.argv) < 2:
        print("Usage: fix_enum_arithmetic.py <file>")
        sys.exit(1)

    file_path = Path(sys.argv[1])
    if not file_path.exists():
        print(f"Error: File not found: {file_path}")
        sys.exit(1)

    # Backup
    backup_path = file_path.with_suffix(file_path.suffix + '.bak')
    if not backup_path.exists():
        file_path.rename(backup_path)
        file_path.write_text(backup_path.read_text(encoding='utf-8'), encoding='utf-8')

    # Apply fixes
    if "Effect_Add.cpp" in file_path.name:
        converted = fix_effect_add(file_path)
    elif "Effect_Draw.cpp" in file_path.name:
        converted = fix_effect_draw(file_path)
    elif "Effect_Update.cpp" in file_path.name:
        converted = fix_effect_update(file_path)
    else:
        print(f"Unknown file: {file_path.name}")
        sys.exit(1)

    file_path.write_text(converted, encoding='utf-8')
    print(f"[OK] Fixed: {file_path}")

if __name__ == "__main__":
    main()
