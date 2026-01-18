#!/usr/bin/env python3
"""
Convert Effect system switch statements to use EffectType enum.

Usage:
    python Scripts/convert_effect_enum.py Sources/Client/Effect/Effect_Add.cpp --dry-run
    python Scripts/convert_effect_enum.py Sources/Client/Effect/Effect_Add.cpp --apply
"""

import re
import sys
from pathlib import Path

# Mapping of integer values to enum names
EFFECT_TYPE_MAP = {
    1: "NORMAL_HIT",
    2: "ARROW_FLYING",
    4: "GOLD_DROP",
    5: "FIREBALL_EXPLOSION",
    6: "ENERGY_BOLT_EXPLOSION",
    7: "MAGIC_MISSILE_EXPLOSION",
    8: "BURST_SMALL",
    9: "BURST_MEDIUM",
    10: "LIGHTNING_ARROW_EXPLOSION",
    11: "BURST_SMALL_GRENADE",
    12: "BURST_LARGE",
    13: "BUBBLES_DRUNK",
    14: "FOOTPRINT",
    15: "RED_CLOUD_PARTICLES",
    16: "PROJECTILE_GENERIC",
    17: "ICE_STORM",
    18: "IMPACT_BURST",
    20: "CRITICAL_STRIKE_1",
    21: "CRITICAL_STRIKE_2",
    22: "CRITICAL_STRIKE_3",
    23: "CRITICAL_STRIKE_4",
    24: "CRITICAL_STRIKE_5",
    25: "CRITICAL_STRIKE_6",
    26: "CRITICAL_STRIKE_7",
    27: "CRITICAL_STRIKE_8",
    30: "MASS_FIRE_STRIKE_CALLER1",
    31: "MASS_FIRE_STRIKE_CALLER3",
    32: "FOOTPRINT_RAIN",
    33: "IMPACT_EFFECT",
    35: "MASS_MAGIC_MISSILE_AURA1",
    36: "MASS_MAGIC_MISSILE_AURA2",
    40: "CHILL_WIND_IMPACT",
    41: "ICE_STRIKE_VARIANT_1",
    42: "ICE_STRIKE_VARIANT_2",
    43: "ICE_STRIKE_VARIANT_3",
    44: "ICE_STRIKE_VARIANT_4",
    45: "ICE_STRIKE_VARIANT_5",
    46: "ICE_STRIKE_VARIANT_6",
    47: "BLIZZARD_VARIANT_1",
    48: "BLIZZARD_VARIANT_2",
    49: "BLIZZARD_VARIANT_3",
    50: "SMOKE_DUST",
    51: "SPARKLE_SMALL",
    52: "PROTECTION_RING",
    53: "HOLD_TWIST",
    54: "STAR_TWINKLE",
    56: "MASS_CHILL_WIND",
    57: "BUFF_EFFECT_LIGHT",
    60: "METEOR_FLYING",
    61: "FIRE_AURA_GROUND",
    62: "METEOR_IMPACT",
    63: "FIRE_EXPLOSION_CRUSADE",
    64: "WHITE_HALO",
    65: "MS_CRUSADE_CASTING",
    66: "MS_CRUSADE_EXPLOSION",
    67: "MS_FIRE_SMOKE",
    68: "WORM_BITE",
    69: "LIGHT_EFFECT_1",
    70: "LIGHT_EFFECT_2",
    71: "BLIZZARD_PROJECTILE",
    72: "BLIZZARD_IMPACT",
    73: "AURA_EFFECT_1",
    74: "AURA_EFFECT_2",
    75: "ICE_GOLEM_EFFECT_1",
    76: "ICE_GOLEM_EFFECT_2",
    77: "ICE_GOLEM_EFFECT_3",
    80: "EARTH_SHOCK_WAVE_PARTICLE",
    81: "STORM_BLADE",
    82: "GATE_APOCALYPSE",
    100: "MAGIC_MISSILE_FLYING",
    101: "HEAL",
    102: "CREATE_FOOD",
    110: "ENERGY_BOLT_FLYING",
    111: "STAMINA_DRAIN",
    112: "RECALL",
    113: "DEFENSE_SHIELD",
    120: "FIRE_BALL_FLYING",
    121: "GREAT_HEAL",
    123: "STAMINA_RECOVERY",
    124: "PROTECT_FROM_NM",
    125: "HOLD_PERSON",
    126: "POSSESSION",
    127: "POISON",
    128: "GREAT_STAMINA_RECOVERY",
    130: "FIRE_STRIKE_FLYING",
    131: "SUMMON_CREATURE",
    132: "INVISIBILITY",
    133: "PROTECT_FROM_MAGIC",
    134: "DETECT_INVISIBILITY",
    135: "PARALYZE",
    136: "CURE",
    137: "LIGHTNING_ARROW_FLYING",
    138: "TREMOR",
    142: "CONFUSE_LANGUAGE",
    143: "LIGHTNING",
    144: "GREAT_DEFENSE_SHIELD",
    145: "CHILL_WIND",
    147: "TRIPLE_ENERGY_BOLT",
    150: "BERSERK",
    151: "LIGHTNING_BOLT",
    152: "POLYMORPH",
    153: "MASS_POISON",
    156: "MASS_LIGHTNING_ARROW",
    157: "ICE_STRIKE",
    160: "ENERGY_STRIKE",
    161: "MASS_FIRE_STRIKE_FLYING",
    162: "CONFUSION",
    163: "MASS_CHILL_WIND_SPELL",
    164: "WORM_BITE_MASS",
    165: "ABSOLUTE_MAGIC_PROTECTION",
    166: "ARMOR_BREAK",
    170: "BLOODY_SHOCK_WAVE",
    171: "MASS_CONFUSION",
    172: "MASS_ICE_STRIKE",
    174: "LIGHTNING_STRIKE",
    176: "CANCELLATION",
    177: "ILLUSION_MOVEMENT",
    178: "HASTE",
    180: "ILLUSION",
    181: "METEOR_STRIKE_DESCENDING",
    182: "MASS_MAGIC_MISSILE_FLYING",
    183: "INHIBITION_CASTING",
    190: "MASS_ILLUSION",
    191: "BLIZZARD",
    194: "RESURRECTION",
    195: "MASS_ILLUSION_MOVEMENT",
    196: "EARTH_SHOCK_WAVE",
    200: "SHOTSTAR_FALL_1",
    201: "SHOTSTAR_FALL_2",
    202: "SHOTSTAR_FALL_3",
    203: "EXPLOSION_FIRE_APOCALYPSE",
    204: "CRACK_OBLIQUE",
    205: "CRACK_HORIZONTAL",
    206: "STEAMS_SMOKE",
    242: "MAGE_HERO_SET",
    243: "WAR_HERO_SET",
    244: "MASS_MM_AURA_CASTER",
    250: "GATE_ROUND",
    251: "SALMON_BURST",
    252: "SALMON_BURST_IMPACT",
}

def convert_switch_cases(content: str) -> str:
    """Convert 'case 1:' to 'case EffectType::NORMAL_HIT:'"""
    def replace_case(match):
        num = int(match.group(1))
        if num in EFFECT_TYPE_MAP:
            return f"case EffectType::{EFFECT_TYPE_MAP[num]}:"
        return match.group(0)  # Keep original if not in map

    return re.sub(r'\bcase\s+(\d+):', replace_case, content)

def convert_add_effect_calls(content: str) -> str:
    """Convert 'AddEffect(5,' and 'AddEffectImpl(5,' to use EffectType enum"""
    def replace_call(match):
        func_name = match.group(1)
        num = int(match.group(2))
        if num in EFFECT_TYPE_MAP:
            return f"{func_name}(EffectType::{EFFECT_TYPE_MAP[num]},"
        return match.group(0)

    # Handle both AddEffect and AddEffectImpl
    content = re.sub(r'\b(AddEffect(?:Impl)?)\((\d+),', replace_call, content)
    return content

def main():
    if len(sys.argv) < 2:
        print("Usage: convert_effect_enum.py <file> [--dry-run|--apply]")
        sys.exit(1)

    file_path = Path(sys.argv[1])
    dry_run = "--dry-run" in sys.argv or len(sys.argv) == 2

    if not file_path.exists():
        print(f"Error: File not found: {file_path}")
        sys.exit(1)

    content = file_path.read_text(encoding='utf-8')

    # Determine which conversions to apply based on filename
    if "Effect_" in file_path.name:
        converted = convert_switch_cases(content)
        converted = convert_add_effect_calls(converted)  # Also convert internal AddEffect calls
    elif file_path.suffix == ".cpp" or file_path.suffix == ".h":
        # For any other C++ file, just convert AddEffect calls
        converted = convert_add_effect_calls(content)
    else:
        print(f"Warning: Unknown file type: {file_path.name}")
        converted = content

    if dry_run:
        print(f"=== DRY RUN: {file_path} ===")
        # Show diff-like output
        changes = []
        for i, (old, new) in enumerate(zip(content.splitlines(), converted.splitlines())):
            if old != new:
                changes.append((i+1, old, new))

        if changes:
            print(f"Changes detected: {len(changes)} lines")
            # Show first 20 changes
            for line_num, old, new in changes[:20]:
                print(f"  Line {line_num}:")
                print(f"    - {old}")
                print(f"    + {new}")
            if len(changes) > 20:
                print(f"  ... and {len(changes) - 20} more changes")
        else:
            print("No changes needed.")
    else:
        if content != converted:
            # Create backup
            backup_path = file_path.with_suffix(file_path.suffix + '.bak')
            file_path.rename(backup_path)
            print(f"Backup created: {backup_path}")

            # Write converted content
            file_path.write_text(converted, encoding='utf-8')
            print(f"[OK] Converted: {file_path}")
        else:
            print(f"[SKIP] No changes: {file_path}")

if __name__ == "__main__":
    main()
