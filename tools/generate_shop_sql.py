#!/usr/bin/env python3
"""
Generate SQL INSERT statements for shop tables from legacy contents files.

This script parses contents1.txt and contents2.txt to extract item names,
then looks up item IDs from GameConfigs.db to generate shop_items entries.
"""

import sqlite3
import re
import os

# NPC type to shop ID mappings
# contents1.txt = general shop (NPC type 1 = Shopkeeper)
# contents2.txt = blacksmith shop (NPC type 2 = Blacksmith)
NPC_SHOP_MAPPINGS = [
    (1, 1, "General Shop (Shopkeeper)"),
    (2, 2, "Blacksmith Shop"),
]

# Mapping from content file names to database names
NAME_MAPPING = {
    # Potions
    "RedPotion": "Health Potion",
    "BigRedPotion": "Big Health Potion",
    "BluePotion": "Mana Potion",
    "BigBluePotion": "Big Mana Potion",
    "GreenPotion": "Revitalizing Potion",
    "BigGreenPotion": "Big Revitalizing Potion",
    "DilutionPotion": "Dilution Potion",
    # Swords
    "ShortSword": "Short Sword",
    "ShortSword+1": "Short Sword+1",
    "LongSword": "Long Sword",
    "LongSword+1": "Long Sword+1",
    "BroadSword": "Broad Sword",
    "BroadSword+1": "Broad Sword+1",
    "BastadSword": "Bastad Sword",
    "BastadSword+1": "Bastad Sword+1",
    "GreatSword": "Great Sword",
    "GreatSword+1": "Great Sword+1",
    "GiantSword": "Giant Sword",
    "BlackShadowSword": "Black Shadow Sword",
    "KnightGreatSword": "Knight Great Sword",
    "KnightFlameberge": "Knight Flameberge",
    # Axes
    "LightAxe": "Light Axe",
    "LightAxe+1": "Light Axe+1",
    "Tomahoc": "Tomahawk",
    "Tomahoc+1": "Tomahawk+1",
    "SexonAxe": "Sexon Axe",
    "SexonAxe+1": "Sexon Axe+1",
    "DoubleAxe": "Double Axe",
    "DoubleAxe+1": "Double Axe+1",
    "WarAxe": "War Axe",
    "WarAxe+1": "War Axe+1",
    "KnightWarAxe": "Knight War Axe",
    "BattleAxe": "Battle Axe",
    "BattleAxe+1": "Battle Axe+1",
    "BattleHammer": "Battle Hammer",
    "BarbarianHammer": "Barbarian Hammer",
    # Fencing
    "Esterk": "Estoc",
    "Esterk+1": "Estoc+1",
    "Rapier": "Rapier",
    "Rapier+1": "Rapier+1",
    "KnightRapier": "Knight Rapier",
    # Bows
    "ShortBow": "Short Bow",
    "LongBow": "Long Bow",
    "CompositeBow": "Composite Bow",
    "Fire-Bow": "Fire Bow",
    "Direction-Bow": "Direction Bow",
    # Shields
    "WoodShield": "Wood Shield",
    "LeatherShield": "Leather Shield",
    "TargeShield": "Targe Shield",
    "ScootermShield": "Scooterm Shield",
    "BlondeShield": "Blonde Shield",
    "IronShield": "Iron Shield",
    "LagiShield": "Lagi Shield",
    "KnightShield": "Knight Shield",
    "TowerShield": "Tower Shield",
    # Armor (Male)
    "Hauberk(M)": "Hauberk(M)",
    "WizardHauberk(M)": "Wizard Hauberk(M)",
    "KnightHauberk(M)": "Knight Hauberk(M)",
    "LeatherArmor(M)": "Leather Armor(M)",
    "ScaleMail(M)": "Scale Mail(M)",
    "ChainMail(M)": "Chain Mail(M)",
    "PlateMail(M)": "Plate Mail(M)",
    "KnightPlateMail(M)": "Knight Plate Mail(M)",
    "ChainHose(M)": "Chain Hose(M)",
    "PlateLeggings(M)": "Plate Leggings(M)",
    "KnightPlateLeg(M)": "Knight Plate Leggings(M)",
    # Armor (Female)
    "Hauberk(W)": "Hauberk(W)",
    "WizardHauberk(W)": "Wizard Hauberk(W)",
    "KnightHauberk(W)": "Knight Hauberk(W)",
    "LeatherArmor(W)": "Leather Armor(W)",
    "ScaleMail(W)": "Scale Mail(W)",
    "ChainMail(W)": "Chain Mail(W)",
    "PlateMail(W)": "Plate Mail(W)",
    "KnightPlateMail(W)": "Knight Plate Mail(W)",
    "ChainHose(W)": "Chain Hose(W)",
    "PlateLeggings(W)": "Plate Leggings(W)",
    "KnightPlateLeg(W)": "Knight Plate Leggings(W)",
    # Helms
    "Helm(M)": "Helm(M)",
    "FullHelm(M)": "Full Helm(M)",
    "KnightFullHelm(M)": "Knight Full Helm(M)",
    "Horned-Helm(M)": "Horned Helm(M)",
    "Wings-Helm(M)": "Wings Helm(M)",
    "Helm(W)": "Helm(W)",
    "FullHelm(W)": "Full Helm(W)",
    "KnightFullHelm(W)": "Knight Full Helm(W)",
    "Horned-Helm(W)": "Horned Helm(W)",
    "Wings-Helm(W)": "Wings Helm(W)",
    # Clothing
    "Shirt(M)": "Shirt(M)",
    "Tunic(M)": "Tunic(M)",
    "KneeTrousers(M)": "Knee Trousers(M)",
    "Trousers(M)": "Trousers(M)",
    "Shirt(W)": "Shirt(W)",
    "Chemise(W)": "Chemise(W)",
    "Bodice(W)": "Bodice(W)",
    "LongBodice(W)": "Long Bodice(W)",
    "Skirt(W)": "Skirt(W)",
    "Trousers(W)": "Trousers(W)",
    "KneeTrousers(W)": "Knee Trousers(W)",
    "LongBoots": "Long Boots",
    "SilverNecklace": "Silver Necklace",
    "GoldNecklace": "Gold Necklace",
    "SilverRing": "Silver Ring",
    "GoldRing": "Gold Ring",
    "Robe(M)": "Robe(M)",
    "WizardRobe(M)": "Wizard Robe(M)",
    "Wizard-Cap(M)": "Wizard Cap(M)",
    "Wizard-Hat(M)": "Wizard Hat(M)",
    "Robe(W)": "Robe(W)",
    "WizardRobe(W)": "Wizard Robe(W)",
    "Wizard-Cap(W)": "Wizard Cap(W)",
    "Wizard-Hat(W)": "Wizard Hat(W)",
    "SantaCostume(M)": "Santa Costume(M)",
    "SantaCostume(W)": "Santa Costume(W)",
    "Cape+1": "Cape+1",
    # Manuals
    "HandAttackManual": "Hand Attack Manual",
    "ShortSwordManual": "Short Sword Manual",
    "LongSwordManual": "Long Sword Manual",
    "FencingManual": "Fencing Manual",
    "AxeManual": "Axe Manual",
    "HammerAttackManual": "Hammer Attack Manual",
    "ArcheryManual": "Archery Manual",
    "ShieldManual": "Shield Manual",
    "WandAttackManual": "Wand Attack Manual",
    "MiningManual": "Mining Manual",
    "FishingManual": "Fishing Manual",
    "AlchemyManual": "Alchemy Manual",
    "FarmingManual": "Farming Manual",
    "ManufacturingManual": "Manufacturing Manual",
    "MagicResistManual": "Magic Resist Manual",
    "PretendCorpseManual": "Pretend Corpse Manual",
    # Scrolls
    "RecallScroll": "Recall Scroll",
    "InvisibilityScroll": "Invisibility Scroll",
    "DetectInviScroll": "Detect Invisibility Scroll",
    "BleedingIslandTicket": "Bleeding Island Ticket",
    # Wands
    "MagicWand(MS0)": "Magic Wand(MS0)",
    "MagicWand(MS10)": "Magic Wand(MS10)",
    "MagicWand(MS20)": "Magic Wand(MS20)",
    "WizMagicWand(MS10)": "Wizard Magic Wand(MS10)",
    "WizMagicWand(MS20)": "Wizard Magic Wand(MS20)",
    # Tools
    "FishingRod": "Fishing Rod",
    "CraftingVessel": "Crafting Vessel",
    "AlchemyBowl": "Alchemy Bowl",
    "ManufacturingHammer": "Manufacturing Hammer",
    "PickAxe": "Pick Axe",
    # Food
    "LuckyPrizeTicket": "Lucky Prize Ticket",
    "DecolorationPotion": "Decoloration Potion",
    "MainGauche": "Main Gauche",
    "MainGauche+1": "Main Gauche+1",
    "Gradius": "Gladius",
    "Gradius+1": "Gladius+1",
}

def parse_content_file(filepath):
    """Parse a contents file and extract item names."""
    items = []
    with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
        for line in f:
            line = line.strip()
            # Skip comments and empty lines
            if not line or line.startswith(';'):
                continue
            # Match lines like "Item  = ItemName ..."
            match = re.match(r'^Item\s*=\s*(\S+)', line)
            if match:
                item_name = match.group(1)
                items.append(item_name)
    return items

def lookup_item_ids(db_path, item_names):
    """Look up item IDs from the database by name."""
    conn = sqlite3.connect(db_path)
    cursor = conn.cursor()

    name_to_id = {}
    not_found = []

    for name in item_names:
        # Try to map the name first
        db_name = NAME_MAPPING.get(name, name)

        cursor.execute("SELECT item_id FROM items WHERE name = ?", (db_name,))
        row = cursor.fetchone()
        if row:
            name_to_id[name] = row[0]
        else:
            # Try without the mapping as fallback
            cursor.execute("SELECT item_id FROM items WHERE name = ?", (name,))
            row = cursor.fetchone()
            if row:
                name_to_id[name] = row[0]
            else:
                not_found.append(f"{name} -> {db_name}")

    conn.close()
    return name_to_id, not_found

def generate_sql(npc_mappings, shop_items):
    """Generate SQL INSERT statements."""
    sql_lines = []

    sql_lines.append("-- Shop System Data")
    sql_lines.append("-- Generated from contents1.txt and contents2.txt")
    sql_lines.append("")

    # NPC shop mappings
    sql_lines.append("-- NPC to Shop mappings")
    for npc_type, shop_id, description in npc_mappings:
        sql_lines.append(f"INSERT OR REPLACE INTO npc_shop_mapping (npc_type, shop_id, description) VALUES ({npc_type}, {shop_id}, '{description}');")

    sql_lines.append("")
    sql_lines.append("-- Shop items")

    for shop_id, item_ids in shop_items.items():
        sql_lines.append(f"-- Shop {shop_id}")
        for item_id in item_ids:
            sql_lines.append(f"INSERT OR REPLACE INTO shop_items (shop_id, item_id) VALUES ({shop_id}, {item_id});")

    return "\n".join(sql_lines)

def main():
    # Paths
    script_dir = os.path.dirname(os.path.abspath(__file__))
    project_root = os.path.dirname(script_dir)

    contents1_path = r"C:\Users\ShadowEvil\source\Repos3\HelbreathServer-main\Helbreath\CONTENTS\contents1.txt"
    contents2_path = r"C:\Users\ShadowEvil\source\Repos3\HelbreathServer-main\Helbreath\CONTENTS\contents2.txt"
    db_path = os.path.join(project_root, "Binaries", "Server", "GameConfigs.db")

    print(f"Looking for database at: {db_path}")

    if not os.path.exists(db_path):
        print(f"ERROR: Database not found at {db_path}")
        print("Please ensure GameConfigs.db exists in Binaries/Server/")
        return

    # Parse content files
    print(f"\nParsing {contents1_path}...")
    items1 = parse_content_file(contents1_path)
    print(f"  Found {len(items1)} items")

    print(f"\nParsing {contents2_path}...")
    items2 = parse_content_file(contents2_path)
    print(f"  Found {len(items2)} items")

    # Look up item IDs
    print(f"\nLooking up item IDs in database...")
    name_to_id1, not_found1 = lookup_item_ids(db_path, items1)
    name_to_id2, not_found2 = lookup_item_ids(db_path, items2)

    print(f"  Shop 1: {len(name_to_id1)} items found, {len(not_found1)} not found")
    print(f"  Shop 2: {len(name_to_id2)} items found, {len(not_found2)} not found")

    if not_found1:
        print(f"\n  Items not found in Shop 1:")
        for name in not_found1[:10]:  # Show first 10
            print(f"    - {name}")
        if len(not_found1) > 10:
            print(f"    ... and {len(not_found1) - 10} more")

    if not_found2:
        print(f"\n  Items not found in Shop 2:")
        for name in not_found2[:10]:  # Show first 10
            print(f"    - {name}")
        if len(not_found2) > 10:
            print(f"    ... and {len(not_found2) - 10} more")

    # Prepare shop items data
    shop_items = {
        1: list(name_to_id1.values()),
        2: list(name_to_id2.values()),
    }

    # Generate SQL
    sql = generate_sql(NPC_SHOP_MAPPINGS, shop_items)

    # Output SQL file
    output_path = os.path.join(project_root, "Binaries", "Server", "shop_data.sql")
    with open(output_path, 'w') as f:
        f.write(sql)

    print(f"\nSQL written to: {output_path}")
    print(f"\nTo import, run in sqlite3:")
    print(f"  sqlite3 GameConfigs.db < shop_data.sql")

if __name__ == "__main__":
    main()
