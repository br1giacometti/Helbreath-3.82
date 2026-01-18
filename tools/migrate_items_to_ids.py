#!/usr/bin/env python3
"""
Migration script to convert character_items and character_bank_items tables
from storing item_name (TEXT) to item_id (INTEGER).

This script:
1. Loads item name->ID mapping from GameConfigs.db
2. For each account database in Accounts/:
   - Backs up the original file
   - Creates new tables with item_id INTEGER
   - Copies data, converting names to IDs
   - Drops old tables, renames new ones
   - Updates schema version to 4

Usage:
    python migrate_items_to_ids.py [--server-dir PATH] [--dry-run]

Options:
    --server-dir PATH   Path to Binaries/Server directory (default: auto-detect)
    --dry-run           Show what would be done without making changes
"""

import sqlite3
import os
import sys
import shutil
import argparse
from pathlib import Path


def find_server_dir():
    """Find the Binaries/Server directory relative to this script."""
    script_dir = Path(__file__).parent
    server_dir = script_dir.parent / "Binaries" / "Server"
    if server_dir.exists():
        return server_dir
    return None


def load_item_mapping(game_configs_path):
    """Load item name -> item_id mapping from GameConfigs.db."""
    if not os.path.exists(game_configs_path):
        print(f"ERROR: GameConfigs.db not found at {game_configs_path}")
        return None

    mapping = {}
    conn = sqlite3.connect(game_configs_path)
    cursor = conn.cursor()

    try:
        cursor.execute("SELECT item_id, name FROM items")
        for row in cursor.fetchall():
            item_id, name = row
            mapping[name] = item_id
    except sqlite3.Error as e:
        print(f"ERROR: Failed to read items from GameConfigs.db: {e}")
        conn.close()
        return None

    conn.close()
    print(f"Loaded {len(mapping)} items from GameConfigs.db")
    return mapping


def get_schema_version(conn):
    """Get the current schema version from an account database."""
    cursor = conn.cursor()
    try:
        cursor.execute("SELECT value FROM meta WHERE key='schema_version'")
        row = cursor.fetchone()
        if row:
            return int(row[0])
    except sqlite3.Error:
        pass
    return 0


def migrate_account_db(db_path, item_mapping, dry_run=False):
    """Migrate a single account database from item names to item IDs."""
    print(f"\nProcessing: {db_path}")

    conn = sqlite3.connect(db_path)
    schema_version = get_schema_version(conn)

    if schema_version >= 4:
        print(f"  Already at schema version {schema_version}, skipping")
        conn.close()
        return True

    if schema_version < 3:
        print(f"  Schema version {schema_version} is too old, skipping (need at least version 3)")
        conn.close()
        return False

    cursor = conn.cursor()

    # Check if old tables have item_name column
    try:
        cursor.execute("PRAGMA table_info(character_items)")
        columns = [row[1] for row in cursor.fetchall()]
        if 'item_id' in columns and 'item_name' not in columns:
            print(f"  Already migrated (has item_id column), updating version only")
            if not dry_run:
                cursor.execute("UPDATE meta SET value='4' WHERE key='schema_version'")
                conn.commit()
            conn.close()
            return True
        if 'item_name' not in columns:
            print(f"  ERROR: Neither item_name nor item_id column found")
            conn.close()
            return False
    except sqlite3.Error as e:
        print(f"  ERROR: Failed to check table structure: {e}")
        conn.close()
        return False

    # Count items to migrate
    try:
        cursor.execute("SELECT COUNT(*) FROM character_items")
        item_count = cursor.fetchone()[0]
        cursor.execute("SELECT COUNT(*) FROM character_bank_items")
        bank_count = cursor.fetchone()[0]
        print(f"  Found {item_count} inventory items and {bank_count} bank items to migrate")
    except sqlite3.Error as e:
        print(f"  ERROR: Failed to count items: {e}")
        conn.close()
        return False

    if dry_run:
        print(f"  DRY RUN: Would migrate {item_count + bank_count} items")
        conn.close()
        return True

    # Create backup
    backup_path = str(db_path) + ".backup_v3"
    if not os.path.exists(backup_path):
        shutil.copy2(db_path, backup_path)
        print(f"  Created backup: {backup_path}")

    try:
        # Begin transaction
        cursor.execute("BEGIN TRANSACTION")

        # Create new character_items table with item_id
        cursor.execute("""
            CREATE TABLE IF NOT EXISTS character_items_new (
                character_name TEXT NOT NULL,
                slot INTEGER NOT NULL,
                item_id INTEGER NOT NULL,
                count INTEGER NOT NULL,
                touch_effect_type INTEGER NOT NULL,
                touch_effect_value1 INTEGER NOT NULL,
                touch_effect_value2 INTEGER NOT NULL,
                touch_effect_value3 INTEGER NOT NULL,
                item_color INTEGER NOT NULL,
                spec_effect_value1 INTEGER NOT NULL,
                spec_effect_value2 INTEGER NOT NULL,
                spec_effect_value3 INTEGER NOT NULL,
                cur_lifespan INTEGER NOT NULL,
                attribute INTEGER NOT NULL,
                pos_x INTEGER NOT NULL,
                pos_y INTEGER NOT NULL,
                is_equipped INTEGER NOT NULL,
                PRIMARY KEY(character_name, slot),
                FOREIGN KEY(character_name) REFERENCES characters(character_name) ON DELETE CASCADE
            )
        """)

        # Copy data from old table, converting item_name to item_id
        cursor.execute("""
            SELECT character_name, slot, item_name, count, touch_effect_type,
                   touch_effect_value1, touch_effect_value2, touch_effect_value3,
                   item_color, spec_effect_value1, spec_effect_value2, spec_effect_value3,
                   cur_lifespan, attribute, pos_x, pos_y, is_equipped
            FROM character_items
        """)

        items_migrated = 0
        items_failed = 0
        for row in cursor.fetchall():
            char_name, slot, item_name = row[0], row[1], row[2]
            rest = row[3:]

            if item_name not in item_mapping:
                print(f"    WARNING: Unknown item '{item_name}' for {char_name} slot {slot}, skipping")
                items_failed += 1
                continue

            item_id = item_mapping[item_name]
            cursor.execute("""
                INSERT INTO character_items_new VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)
            """, (char_name, slot, item_id) + rest)
            items_migrated += 1

        # Create new character_bank_items table with item_id
        cursor.execute("""
            CREATE TABLE IF NOT EXISTS character_bank_items_new (
                character_name TEXT NOT NULL,
                slot INTEGER NOT NULL,
                item_id INTEGER NOT NULL,
                count INTEGER NOT NULL,
                touch_effect_type INTEGER NOT NULL,
                touch_effect_value1 INTEGER NOT NULL,
                touch_effect_value2 INTEGER NOT NULL,
                touch_effect_value3 INTEGER NOT NULL,
                item_color INTEGER NOT NULL,
                spec_effect_value1 INTEGER NOT NULL,
                spec_effect_value2 INTEGER NOT NULL,
                spec_effect_value3 INTEGER NOT NULL,
                cur_lifespan INTEGER NOT NULL,
                attribute INTEGER NOT NULL,
                PRIMARY KEY(character_name, slot),
                FOREIGN KEY(character_name) REFERENCES characters(character_name) ON DELETE CASCADE
            )
        """)

        # Copy data from old bank table
        cursor.execute("""
            SELECT character_name, slot, item_name, count, touch_effect_type,
                   touch_effect_value1, touch_effect_value2, touch_effect_value3,
                   item_color, spec_effect_value1, spec_effect_value2, spec_effect_value3,
                   cur_lifespan, attribute
            FROM character_bank_items
        """)

        bank_migrated = 0
        bank_failed = 0
        for row in cursor.fetchall():
            char_name, slot, item_name = row[0], row[1], row[2]
            rest = row[3:]

            if item_name not in item_mapping:
                print(f"    WARNING: Unknown bank item '{item_name}' for {char_name} slot {slot}, skipping")
                bank_failed += 1
                continue

            item_id = item_mapping[item_name]
            cursor.execute("""
                INSERT INTO character_bank_items_new VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?)
            """, (char_name, slot, item_id) + rest)
            bank_migrated += 1

        # Drop old tables and rename new ones
        cursor.execute("DROP TABLE character_items")
        cursor.execute("DROP TABLE character_bank_items")
        cursor.execute("ALTER TABLE character_items_new RENAME TO character_items")
        cursor.execute("ALTER TABLE character_bank_items_new RENAME TO character_bank_items")

        # Update schema version
        cursor.execute("UPDATE meta SET value='4' WHERE key='schema_version'")

        # Commit transaction
        conn.commit()

        print(f"  Migrated {items_migrated} inventory items ({items_failed} failed)")
        print(f"  Migrated {bank_migrated} bank items ({bank_failed} failed)")
        print(f"  Updated schema version to 4")

        conn.close()
        return True

    except sqlite3.Error as e:
        print(f"  ERROR: Migration failed: {e}")
        conn.rollback()
        conn.close()
        return False


def main():
    parser = argparse.ArgumentParser(description="Migrate item storage from names to IDs")
    parser.add_argument("--server-dir", type=str, help="Path to Binaries/Server directory")
    parser.add_argument("--dry-run", action="store_true", help="Show what would be done without making changes")
    args = parser.parse_args()

    # Find server directory
    if args.server_dir:
        server_dir = Path(args.server_dir)
    else:
        server_dir = find_server_dir()

    if not server_dir or not server_dir.exists():
        print("ERROR: Could not find Binaries/Server directory")
        print("Please specify with --server-dir option")
        return 1

    print(f"Server directory: {server_dir}")

    # Load item mapping from GameConfigs.db
    game_configs_path = server_dir / "GameConfigs.db"
    item_mapping = load_item_mapping(game_configs_path)
    if item_mapping is None:
        return 1

    # Find all account databases
    accounts_dir = server_dir / "Accounts"
    if not accounts_dir.exists():
        print(f"ERROR: Accounts directory not found at {accounts_dir}")
        return 1

    account_dbs = list(accounts_dir.glob("*.db"))
    if not account_dbs:
        print("No account databases found in Accounts/")
        return 0

    print(f"\nFound {len(account_dbs)} account database(s)")

    if args.dry_run:
        print("\n*** DRY RUN MODE - No changes will be made ***\n")

    # Migrate each account database
    success_count = 0
    fail_count = 0

    for db_path in account_dbs:
        if migrate_account_db(db_path, item_mapping, args.dry_run):
            success_count += 1
        else:
            fail_count += 1

    print(f"\n{'=' * 50}")
    print(f"Migration complete: {success_count} succeeded, {fail_count} failed")

    return 0 if fail_count == 0 else 1


if __name__ == "__main__":
    sys.exit(main())
