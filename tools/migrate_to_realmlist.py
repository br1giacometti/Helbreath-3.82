#!/usr/bin/env python3
"""Migrate GameConfigs.db from program_config to realmlist table"""

import sqlite3
import os

DB_PATH = r"C:\Users\ShadowEvil\source\Repos3\Helbreath-3.82\Binaries\Server\GameConfigs.db"

def main():
    if not os.path.exists(DB_PATH):
        print(f"Database not found: {DB_PATH}")
        return False

    conn = sqlite3.connect(DB_PATH)
    cursor = conn.cursor()

    # Check if realmlist already exists
    cursor.execute("SELECT name FROM sqlite_master WHERE type='table' AND name='realmlist';")
    if cursor.fetchone():
        print("realmlist table already exists!")
        cursor.execute("SELECT * FROM realmlist;")
        rows = cursor.fetchall()
        if rows:
            print(f"  Found {len(rows)} realm(s)")
            for row in rows:
                print(f"    {row}")
            conn.close()
            return True
        else:
            print("  Table is empty, will insert default realm")
    else:
        # Create realmlist table
        print("Creating realmlist table...")
        cursor.execute("""
            CREATE TABLE IF NOT EXISTS realmlist (
                id INTEGER PRIMARY KEY,
                realm_name TEXT UNIQUE NOT NULL,
                login_listen_ip TEXT NOT NULL DEFAULT '0.0.0.0',
                login_listen_port INTEGER NOT NULL DEFAULT 2848,
                game_server_listen_ip TEXT NOT NULL DEFAULT '0.0.0.0',
                game_server_listen_port INTEGER NOT NULL DEFAULT 2858,
                game_server_connection_ip TEXT DEFAULT NULL,
                game_server_connection_port INTEGER DEFAULT NULL
            );
        """)
        print("  Created realmlist table")

    # Try to migrate from program_config if it exists
    cursor.execute("SELECT name FROM sqlite_master WHERE type='table' AND name='program_config';")
    if cursor.fetchone():
        print("Found program_config table, extracting values...")
        cursor.execute("SELECT key, value FROM program_config;")
        old_config = dict(cursor.fetchall())

        realm_name = old_config.get('game-server-name', 'Helbreath')
        game_addr = old_config.get('game-server-address', '0.0.0.0')
        game_port = int(old_config.get('game-server-port', 2858))
        log_addr = old_config.get('log-server-address', '0.0.0.0')
        log_port = int(old_config.get('internal-log-server-port', 2848))

        print(f"  Migrating: realm={realm_name}, login={log_addr}:{log_port}, game={game_addr}:{game_port}")

        cursor.execute("""
            INSERT OR REPLACE INTO realmlist
            (id, realm_name, login_listen_ip, login_listen_port, game_server_listen_ip, game_server_listen_port)
            VALUES (1, ?, ?, ?, ?, ?);
        """, (realm_name, log_addr, log_port, game_addr, game_port))

        print("  Migrated config to realmlist")
    else:
        # Insert default realm
        print("No program_config found, inserting default realm...")
        cursor.execute("""
            INSERT OR REPLACE INTO realmlist
            (id, realm_name, login_listen_ip, login_listen_port, game_server_listen_ip, game_server_listen_port)
            VALUES (1, 'Helbreath', '0.0.0.0', 2848, '0.0.0.0', 2858);
        """)
        print("  Inserted default realm: Helbreath (Login: 0.0.0.0:2848, Game: 0.0.0.0:2858)")

    conn.commit()

    # Verify
    cursor.execute("SELECT * FROM realmlist;")
    rows = cursor.fetchall()
    print(f"\nFinal realmlist contents ({len(rows)} realm(s)):")
    for row in rows:
        print(f"  ID={row[0]}, Name={row[1]}, Login={row[2]}:{row[3]}, Game={row[4]}:{row[5]}")

    conn.close()
    print("\nMigration complete!")
    return True

if __name__ == '__main__':
    main()
