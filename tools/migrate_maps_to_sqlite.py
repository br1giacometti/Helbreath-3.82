#!/usr/bin/env python3
"""
Helbreath 3.82 Map Configuration Migration Tool
Converts map configuration text files to SQLite database (MapInfo.db)
"""

import os
import re
import sqlite3
import sys
from pathlib import Path
from dataclasses import dataclass, field
from typing import List, Dict, Optional, Tuple

# Default paths
SCRIPT_DIR = Path(__file__).parent
PROJECT_ROOT = SCRIPT_DIR.parent
MAPDATA_DIR = PROJECT_ROOT / "Binaries" / "Server" / "MAPDATA"
OUTPUT_DB = PROJECT_ROOT / "Binaries" / "Server" / "MapInfo.db"


@dataclass
class MapConfig:
    """Holds all configuration data for a single map"""
    map_name: str = ""
    location_name: str = ""
    maximum_object: int = 1000
    level_limit: int = 0
    upper_level_limit: int = 0
    map_type: int = 0
    random_mob_generator_enabled: int = 0
    random_mob_generator_level: int = 0
    mineral_generator_enabled: int = 0
    mineral_generator_level: int = 0
    max_fish: int = 0
    max_mineral: int = 0
    fixed_day_mode: int = 0
    recall_impossible: int = 0
    apocalypse_map: int = 0
    apocalypse_mob_gen_type: int = 0
    citizen_limit: int = 0
    is_fight_zone: int = 0
    heldenian_map: int = 0
    heldenian_mode_map: int = 0
    mob_event_amount: int = 15
    energy_sphere_auto_creation: int = 0
    pk_mode: int = 0

    # Child data
    teleport_locations: List[Tuple] = field(default_factory=list)
    initial_points: List[Tuple] = field(default_factory=list)
    waypoints: List[Tuple] = field(default_factory=list)
    no_attack_areas: List[Tuple] = field(default_factory=list)
    npc_avoid_rects: List[Tuple] = field(default_factory=list)
    spot_mob_generators: List[Tuple] = field(default_factory=list)
    fish_points: List[Tuple] = field(default_factory=list)
    mineral_points: List[Tuple] = field(default_factory=list)
    strategic_points: List[Tuple] = field(default_factory=list)
    energy_sphere_creation: List[Tuple] = field(default_factory=list)
    energy_sphere_goal: List[Tuple] = field(default_factory=list)
    strike_points: List[Tuple] = field(default_factory=list)
    item_events: List[Tuple] = field(default_factory=list)
    heldenian_towers: List[Tuple] = field(default_factory=list)
    heldenian_gate_doors: List[Tuple] = field(default_factory=list)
    npcs: List[Tuple] = field(default_factory=list)
    apocalypse_boss: Optional[Tuple] = None
    dynamic_gate: Optional[Tuple] = None


def parse_map_file(filepath: Path) -> Optional[MapConfig]:
    """Parse a single map configuration file"""
    try:
        # Try different encodings
        content = None
        for encoding in ['utf-8', 'cp1252', 'latin-1', 'euc-kr']:
            try:
                content = filepath.read_text(encoding=encoding)
                break
            except UnicodeDecodeError:
                continue

        if content is None:
            print(f"  WARNING: Could not decode {filepath.name}")
            return None

        # Extract map name from filename (without extension, max 10 chars)
        map_name = filepath.stem[:10].lower()

        config = MapConfig(map_name=map_name)

        # Track teleport index since they don't have explicit indices
        teleport_idx = 0

        for line in content.splitlines():
            line = line.strip()

            # Skip comments and empty lines
            if not line or line.startswith('//') or line.startswith('['):
                continue

            # Remove inline comments
            if '//' in line:
                line = line[:line.index('//')].strip()

            # Parse key = value pairs
            if '=' not in line:
                continue

            parts = line.split('=', 1)
            if len(parts) != 2:
                continue

            key = parts[0].strip().lower()
            value = parts[1].strip()

            # Split value into tokens
            tokens = value.split()

            try:
                # Core settings
                if key == 'map-location':
                    config.location_name = tokens[0][:10] if tokens else ""

                elif key == 'maximum-object':
                    config.maximum_object = int(tokens[0]) if tokens else 1000

                elif key == 'level-limit':
                    config.level_limit = int(tokens[0]) if tokens else 0

                elif key == 'upper-level-limit':
                    config.upper_level_limit = int(tokens[0]) if tokens else 0

                elif key == 'type':
                    config.map_type = int(tokens[0]) if tokens else 0

                elif key == 'random-mob-generator':
                    if len(tokens) >= 2:
                        config.random_mob_generator_enabled = int(tokens[0])
                        config.random_mob_generator_level = int(tokens[1])

                elif key == 'mineral-generator':
                    if len(tokens) >= 2:
                        config.mineral_generator_enabled = int(tokens[0])
                        config.mineral_generator_level = int(tokens[1])

                elif key == 'max-fish':
                    config.max_fish = int(tokens[0]) if tokens else 0

                elif key == 'max-mineral':
                    config.max_mineral = int(tokens[0]) if tokens else 0

                elif key == 'fixed-dayornight-mode':
                    config.fixed_day_mode = int(tokens[0]) if tokens else 0

                elif key == 'recallimpossible':
                    config.recall_impossible = int(tokens[0]) if tokens else 0

                elif key == 'apocalypsemap':
                    config.apocalypse_map = int(tokens[0]) if tokens else 0

                elif key == 'apocalypsemobgentype':
                    config.apocalypse_mob_gen_type = int(tokens[0]) if tokens else 0

                elif key == 'citizenlimit':
                    config.citizen_limit = int(tokens[0]) if tokens else 0

                elif key == 'heldenianmap':
                    config.heldenian_map = int(tokens[0]) if tokens else 0

                elif key == 'heldenianmodemap':
                    config.heldenian_mode_map = int(tokens[0]) if tokens else 0

                elif key == 'mobevent-amount':
                    config.mob_event_amount = int(tokens[0]) if tokens else 15

                elif key == 'energy-sphere-auto-creation':
                    config.energy_sphere_auto_creation = int(tokens[0]) if tokens else 0

                elif key == 'pk-mode':
                    config.pk_mode = int(tokens[0]) if tokens else 0

                # Teleport locations: sx sy dest_map dx dy dir
                elif key == 'teleport-loc':
                    if len(tokens) >= 6:
                        config.teleport_locations.append((
                            teleport_idx,
                            int(tokens[0]),  # src_x
                            int(tokens[1]),  # src_y
                            tokens[2][:10],  # dest_map
                            int(tokens[3]),  # dest_x
                            int(tokens[4]),  # dest_y
                            int(tokens[5])   # direction
                        ))
                        teleport_idx += 1

                # Initial points: index x y
                elif key == 'initial-point':
                    if len(tokens) >= 3:
                        config.initial_points.append((
                            int(tokens[0]) - 1,  # 1-based to 0-based index
                            int(tokens[1]),
                            int(tokens[2])
                        ))

                # Waypoints: index x y
                elif key == 'waypoint':
                    if len(tokens) >= 3:
                        config.waypoints.append((
                            int(tokens[0]),
                            int(tokens[1]),
                            int(tokens[2])
                        ))

                # No-attack areas: index left top right bottom
                elif key == 'no-attack-area':
                    if len(tokens) >= 5:
                        config.no_attack_areas.append((
                            int(tokens[0]) - 1,  # 1-based to 0-based
                            int(tokens[1]),
                            int(tokens[2]),
                            int(tokens[3]),
                            int(tokens[4])
                        ))

                # NPC avoid rects: index left top right bottom
                elif key == 'npc-avoidrect':
                    if len(tokens) >= 5:
                        config.npc_avoid_rects.append((
                            int(tokens[0]) - 1,
                            int(tokens[1]),
                            int(tokens[2]),
                            int(tokens[3]),
                            int(tokens[4])
                        ))

                # Spot mob generators: index type left top right bottom mob_type max_mobs
                # OR for type 2: index type waypoints... mob_type max_mobs
                elif key == 'spot-mob-generator':
                    if len(tokens) >= 8:
                        idx = int(tokens[0]) - 1
                        gen_type = int(tokens[1])

                        if gen_type == 1:
                            # Type 1: RandomArea with rect
                            config.spot_mob_generators.append((
                                idx,
                                gen_type,
                                int(tokens[2]),   # left
                                int(tokens[3]),   # top
                                int(tokens[4]),   # right
                                int(tokens[5]),   # bottom
                                "",               # no waypoints
                                int(tokens[6]),   # mob_type
                                int(tokens[7])    # max_mobs
                            ))
                        elif gen_type == 2:
                            # Type 2: RandomWaypoint with waypoint list
                            # Format: index type wp0 wp1 ... wp9 mob_type max_mobs
                            waypoints = ",".join(tokens[2:12])  # up to 10 waypoints
                            mob_type = int(tokens[-2])
                            max_mobs = int(tokens[-1])
                            config.spot_mob_generators.append((
                                idx,
                                gen_type,
                                0, 0, 0, 0,  # no rect
                                waypoints,
                                mob_type,
                                max_mobs
                            ))

                # Fish points: index x y
                elif key == 'fish-point':
                    if len(tokens) >= 3:
                        config.fish_points.append((
                            int(tokens[0]),
                            int(tokens[1]),
                            int(tokens[2])
                        ))

                # Mineral points: index x y
                elif key == 'mineral-point':
                    if len(tokens) >= 3:
                        config.mineral_points.append((
                            int(tokens[0]),
                            int(tokens[1]),
                            int(tokens[2])
                        ))

                # Strategic points: index side value x y
                elif key == 'strategic-point':
                    if len(tokens) >= 5:
                        config.strategic_points.append((
                            int(tokens[0]) - 1,
                            int(tokens[1]),
                            int(tokens[2]),
                            int(tokens[3]),
                            int(tokens[4])
                        ))

                # Energy sphere creation: index type x y
                elif key == 'energy-sphere-creation-point':
                    if len(tokens) >= 4:
                        config.energy_sphere_creation.append((
                            int(tokens[0]) - 1,
                            int(tokens[1]),
                            int(tokens[2]),
                            int(tokens[3])
                        ))

                # Energy sphere goal: index result aresden_x aresden_y elvine_x elvine_y
                elif key == 'energy-sphere-goal-point':
                    if len(tokens) >= 6:
                        config.energy_sphere_goal.append((
                            int(tokens[0]) - 1,
                            int(tokens[1]),
                            int(tokens[2]),
                            int(tokens[3]),
                            int(tokens[4]),
                            int(tokens[5])
                        ))

                # Strike points: index x y hp effect_coords... related_map
                elif key == 'strike-point':
                    if len(tokens) >= 15:
                        config.strike_points.append((
                            int(tokens[0]) - 1,
                            int(tokens[1]),   # x
                            int(tokens[2]),   # y
                            int(tokens[3]),   # hp
                            int(tokens[4]),   # effect_x1
                            int(tokens[5]),   # effect_y1
                            int(tokens[6]),   # effect_x2
                            int(tokens[7]),   # effect_y2
                            int(tokens[8]),   # effect_x3
                            int(tokens[9]),   # effect_y3
                            int(tokens[10]),  # effect_x4
                            int(tokens[11]),  # effect_y4
                            int(tokens[12]),  # effect_x5
                            int(tokens[13]),  # effect_y5
                            tokens[14][:10]   # related_map
                        ))

                # Item events: index item_name amount total_num month day type mob_list...
                elif key == 'item-event':
                    if len(tokens) >= 7:
                        idx = int(tokens[0]) - 1
                        item_name = tokens[1][:20]
                        amount = int(tokens[2])
                        total_num = int(tokens[3])
                        month = int(tokens[4])
                        day = int(tokens[5])
                        event_type = int(tokens[6])

                        # Parse mob list until EOL
                        mob_list = []
                        for i in range(7, len(tokens)):
                            if tokens[i].upper() == 'EOL':
                                break
                            mob_list.append(tokens[i])

                        config.item_events.append((
                            idx, item_name, amount, total_num, month, day, event_type,
                            " ".join(mob_list)
                        ))

                # Heldenian towers: type_id side x y
                elif key == 'heldeniantower':
                    if len(tokens) >= 4:
                        tower_idx = len(config.heldenian_towers)
                        config.heldenian_towers.append((
                            tower_idx,
                            int(tokens[0]),  # type_id
                            int(tokens[1]),  # side
                            int(tokens[2]),  # x
                            int(tokens[3])   # y
                        ))

                # Heldenian gate doors: dir x y
                elif key == 'heldeniangatedoor':
                    if len(tokens) >= 3:
                        door_idx = len(config.heldenian_gate_doors)
                        config.heldenian_gate_doors.append((
                            door_idx,
                            int(tokens[0]),  # direction
                            int(tokens[1]),  # x
                            int(tokens[2])   # y
                        ))

                # NPCs: name move_type waypoints... name_prefix
                elif key == 'npc':
                    if len(tokens) >= 3:
                        npc_name = tokens[0][:20]
                        move_type = int(tokens[1])
                        # Waypoints are tokens[2:-1], name_prefix is last
                        waypoints = ",".join(tokens[2:-1]) if len(tokens) > 3 else ""
                        name_prefix = tokens[-1][:1] if tokens[-1].isalpha() else ""
                        config.npcs.append((npc_name, move_type, waypoints, name_prefix))

                # Apocalypse boss: npc_id x1 y1 x2 y2
                elif key == 'apocalypsebossmob':
                    if len(tokens) >= 5:
                        config.apocalypse_boss = (
                            int(tokens[0]),
                            int(tokens[1]),
                            int(tokens[2]),
                            int(tokens[3]),
                            int(tokens[4])
                        )

                # Dynamic gate type
                elif key == 'dynamicgatetype':
                    # Just store the type, coordinates come separately
                    if config.dynamic_gate is None:
                        config.dynamic_gate = [int(tokens[0]), 0, 0, 0, 0, "", 0, 0]
                    else:
                        config.dynamic_gate[0] = int(tokens[0])

                # Dynamic gate coords: x1 y1 x2 y2 dest_map dest_x dest_y
                elif key == 'dynamicgatecoord':
                    if len(tokens) >= 7:
                        if config.dynamic_gate is None:
                            config.dynamic_gate = [0, 0, 0, 0, 0, "", 0, 0]
                        config.dynamic_gate[1] = int(tokens[0])
                        config.dynamic_gate[2] = int(tokens[1])
                        config.dynamic_gate[3] = int(tokens[2])
                        config.dynamic_gate[4] = int(tokens[3])
                        config.dynamic_gate[5] = tokens[4][:10]
                        config.dynamic_gate[6] = int(tokens[5])
                        config.dynamic_gate[7] = int(tokens[6])

            except (ValueError, IndexError) as e:
                # Skip malformed lines
                continue

        # Auto-detect fight zone and ice map from name
        if 'fightzone' in map_name.lower():
            config.is_fight_zone = 1

        return config

    except Exception as e:
        print(f"  ERROR parsing {filepath.name}: {e}")
        return None


def create_schema(conn: sqlite3.Connection):
    """Create the database schema"""
    cursor = conn.cursor()

    schema_sql = """
    -- Meta table
    CREATE TABLE IF NOT EXISTS meta (
        key TEXT PRIMARY KEY,
        value TEXT NOT NULL
    );
    INSERT OR REPLACE INTO meta(key, value) VALUES('schema_version', '1');

    -- Core map settings
    CREATE TABLE IF NOT EXISTS maps (
        map_name TEXT PRIMARY KEY CHECK(length(map_name) <= 10),
        location_name TEXT NOT NULL DEFAULT '' CHECK(length(location_name) <= 10),
        maximum_object INTEGER NOT NULL DEFAULT 1000,
        level_limit INTEGER NOT NULL DEFAULT 0,
        upper_level_limit INTEGER NOT NULL DEFAULT 0,
        map_type INTEGER NOT NULL DEFAULT 0,
        random_mob_generator_enabled INTEGER NOT NULL DEFAULT 0,
        random_mob_generator_level INTEGER NOT NULL DEFAULT 0,
        mineral_generator_enabled INTEGER NOT NULL DEFAULT 0,
        mineral_generator_level INTEGER NOT NULL DEFAULT 0,
        max_fish INTEGER NOT NULL DEFAULT 0,
        max_mineral INTEGER NOT NULL DEFAULT 0,
        fixed_day_mode INTEGER NOT NULL DEFAULT 0,
        recall_impossible INTEGER NOT NULL DEFAULT 0,
        apocalypse_map INTEGER NOT NULL DEFAULT 0,
        apocalypse_mob_gen_type INTEGER NOT NULL DEFAULT 0,
        citizen_limit INTEGER NOT NULL DEFAULT 0,
        is_fight_zone INTEGER NOT NULL DEFAULT 0,
        heldenian_map INTEGER NOT NULL DEFAULT 0,
        heldenian_mode_map INTEGER NOT NULL DEFAULT 0,
        mob_event_amount INTEGER NOT NULL DEFAULT 15,
        energy_sphere_auto_creation INTEGER NOT NULL DEFAULT 0,
        pk_mode INTEGER NOT NULL DEFAULT 0
    );

    -- Teleport locations
    CREATE TABLE IF NOT EXISTS map_teleport_locations (
        map_name TEXT NOT NULL,
        teleport_index INTEGER NOT NULL,
        src_x INTEGER NOT NULL,
        src_y INTEGER NOT NULL,
        dest_map_name TEXT NOT NULL CHECK(length(dest_map_name) <= 10),
        dest_x INTEGER NOT NULL,
        dest_y INTEGER NOT NULL,
        direction INTEGER NOT NULL CHECK(direction >= 0 AND direction <= 8),
        PRIMARY KEY (map_name, teleport_index),
        FOREIGN KEY (map_name) REFERENCES maps(map_name) ON DELETE CASCADE
    );

    -- Initial spawn points
    CREATE TABLE IF NOT EXISTS map_initial_points (
        map_name TEXT NOT NULL,
        point_index INTEGER NOT NULL,
        x INTEGER NOT NULL,
        y INTEGER NOT NULL,
        PRIMARY KEY (map_name, point_index),
        FOREIGN KEY (map_name) REFERENCES maps(map_name) ON DELETE CASCADE
    );

    -- Waypoints
    CREATE TABLE IF NOT EXISTS map_waypoints (
        map_name TEXT NOT NULL,
        waypoint_index INTEGER NOT NULL,
        x INTEGER NOT NULL,
        y INTEGER NOT NULL,
        PRIMARY KEY (map_name, waypoint_index),
        FOREIGN KEY (map_name) REFERENCES maps(map_name) ON DELETE CASCADE
    );

    -- No-attack areas
    CREATE TABLE IF NOT EXISTS map_no_attack_areas (
        map_name TEXT NOT NULL,
        area_index INTEGER NOT NULL,
        rect_left INTEGER NOT NULL,
        rect_top INTEGER NOT NULL,
        rect_right INTEGER NOT NULL,
        rect_bottom INTEGER NOT NULL,
        PRIMARY KEY (map_name, area_index),
        FOREIGN KEY (map_name) REFERENCES maps(map_name) ON DELETE CASCADE
    );

    -- NPC avoid rects
    CREATE TABLE IF NOT EXISTS map_npc_avoid_rects (
        map_name TEXT NOT NULL,
        rect_index INTEGER NOT NULL,
        rect_left INTEGER NOT NULL,
        rect_top INTEGER NOT NULL,
        rect_right INTEGER NOT NULL,
        rect_bottom INTEGER NOT NULL,
        PRIMARY KEY (map_name, rect_index),
        FOREIGN KEY (map_name) REFERENCES maps(map_name) ON DELETE CASCADE
    );

    -- Spot mob generators
    CREATE TABLE IF NOT EXISTS map_spot_mob_generators (
        map_name TEXT NOT NULL,
        generator_index INTEGER NOT NULL,
        generator_type INTEGER NOT NULL CHECK(generator_type IN (1, 2)),
        rect_left INTEGER NOT NULL DEFAULT 0,
        rect_top INTEGER NOT NULL DEFAULT 0,
        rect_right INTEGER NOT NULL DEFAULT 0,
        rect_bottom INTEGER NOT NULL DEFAULT 0,
        waypoints TEXT NOT NULL DEFAULT '',
        mob_type INTEGER NOT NULL,
        max_mobs INTEGER NOT NULL,
        PRIMARY KEY (map_name, generator_index),
        FOREIGN KEY (map_name) REFERENCES maps(map_name) ON DELETE CASCADE
    );

    -- Fish points
    CREATE TABLE IF NOT EXISTS map_fish_points (
        map_name TEXT NOT NULL,
        point_index INTEGER NOT NULL,
        x INTEGER NOT NULL,
        y INTEGER NOT NULL,
        PRIMARY KEY (map_name, point_index),
        FOREIGN KEY (map_name) REFERENCES maps(map_name) ON DELETE CASCADE
    );

    -- Mineral points
    CREATE TABLE IF NOT EXISTS map_mineral_points (
        map_name TEXT NOT NULL,
        point_index INTEGER NOT NULL,
        x INTEGER NOT NULL,
        y INTEGER NOT NULL,
        PRIMARY KEY (map_name, point_index),
        FOREIGN KEY (map_name) REFERENCES maps(map_name) ON DELETE CASCADE
    );

    -- Strategic points
    CREATE TABLE IF NOT EXISTS map_strategic_points (
        map_name TEXT NOT NULL,
        point_index INTEGER NOT NULL,
        side INTEGER NOT NULL,
        point_value INTEGER NOT NULL,
        x INTEGER NOT NULL,
        y INTEGER NOT NULL,
        PRIMARY KEY (map_name, point_index),
        FOREIGN KEY (map_name) REFERENCES maps(map_name) ON DELETE CASCADE
    );

    -- Energy sphere creation points
    CREATE TABLE IF NOT EXISTS map_energy_sphere_creation (
        map_name TEXT NOT NULL,
        point_index INTEGER NOT NULL,
        sphere_type INTEGER NOT NULL,
        x INTEGER NOT NULL,
        y INTEGER NOT NULL,
        PRIMARY KEY (map_name, point_index),
        FOREIGN KEY (map_name) REFERENCES maps(map_name) ON DELETE CASCADE
    );

    -- Energy sphere goal points
    CREATE TABLE IF NOT EXISTS map_energy_sphere_goal (
        map_name TEXT NOT NULL,
        point_index INTEGER NOT NULL,
        result INTEGER NOT NULL,
        aresden_x INTEGER NOT NULL,
        aresden_y INTEGER NOT NULL,
        elvine_x INTEGER NOT NULL,
        elvine_y INTEGER NOT NULL,
        PRIMARY KEY (map_name, point_index),
        FOREIGN KEY (map_name) REFERENCES maps(map_name) ON DELETE CASCADE
    );

    -- Strike points
    CREATE TABLE IF NOT EXISTS map_strike_points (
        map_name TEXT NOT NULL,
        point_index INTEGER NOT NULL,
        x INTEGER NOT NULL,
        y INTEGER NOT NULL,
        hp INTEGER NOT NULL,
        effect_x1 INTEGER NOT NULL,
        effect_y1 INTEGER NOT NULL,
        effect_x2 INTEGER NOT NULL,
        effect_y2 INTEGER NOT NULL,
        effect_x3 INTEGER NOT NULL,
        effect_y3 INTEGER NOT NULL,
        effect_x4 INTEGER NOT NULL,
        effect_y4 INTEGER NOT NULL,
        effect_x5 INTEGER NOT NULL,
        effect_y5 INTEGER NOT NULL,
        related_map_name TEXT NOT NULL CHECK(length(related_map_name) <= 10),
        PRIMARY KEY (map_name, point_index),
        FOREIGN KEY (map_name) REFERENCES maps(map_name) ON DELETE CASCADE
    );

    -- Item events
    CREATE TABLE IF NOT EXISTS map_item_events (
        map_name TEXT NOT NULL,
        event_index INTEGER NOT NULL,
        item_name TEXT NOT NULL CHECK(length(item_name) <= 20),
        amount INTEGER NOT NULL,
        total_num INTEGER NOT NULL,
        event_month INTEGER NOT NULL,
        event_day INTEGER NOT NULL,
        event_type INTEGER NOT NULL DEFAULT 0,
        mob_list TEXT NOT NULL DEFAULT '',
        PRIMARY KEY (map_name, event_index),
        FOREIGN KEY (map_name) REFERENCES maps(map_name) ON DELETE CASCADE
    );

    -- Heldenian towers
    CREATE TABLE IF NOT EXISTS map_heldenian_towers (
        map_name TEXT NOT NULL,
        tower_index INTEGER NOT NULL,
        type_id INTEGER NOT NULL,
        side INTEGER NOT NULL,
        x INTEGER NOT NULL,
        y INTEGER NOT NULL,
        PRIMARY KEY (map_name, tower_index),
        FOREIGN KEY (map_name) REFERENCES maps(map_name) ON DELETE CASCADE
    );

    -- Heldenian gate doors
    CREATE TABLE IF NOT EXISTS map_heldenian_gate_doors (
        map_name TEXT NOT NULL,
        door_index INTEGER NOT NULL,
        direction INTEGER NOT NULL,
        x INTEGER NOT NULL,
        y INTEGER NOT NULL,
        PRIMARY KEY (map_name, door_index),
        FOREIGN KEY (map_name) REFERENCES maps(map_name) ON DELETE CASCADE
    );

    -- Static NPCs
    CREATE TABLE IF NOT EXISTS map_npcs (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        map_name TEXT NOT NULL,
        npc_name TEXT NOT NULL CHECK(length(npc_name) <= 20),
        move_type INTEGER NOT NULL,
        waypoint_list TEXT NOT NULL DEFAULT '',
        name_prefix TEXT NOT NULL DEFAULT '' CHECK(length(name_prefix) <= 1),
        FOREIGN KEY (map_name) REFERENCES maps(map_name) ON DELETE CASCADE
    );

    -- Apocalypse boss config
    CREATE TABLE IF NOT EXISTS map_apocalypse_boss (
        map_name TEXT PRIMARY KEY,
        npc_id INTEGER NOT NULL,
        rect_x1 INTEGER NOT NULL,
        rect_y1 INTEGER NOT NULL,
        rect_x2 INTEGER NOT NULL,
        rect_y2 INTEGER NOT NULL,
        FOREIGN KEY (map_name) REFERENCES maps(map_name) ON DELETE CASCADE
    );

    -- Dynamic gate config
    CREATE TABLE IF NOT EXISTS map_dynamic_gate (
        map_name TEXT PRIMARY KEY,
        gate_type INTEGER NOT NULL,
        rect_x1 INTEGER NOT NULL,
        rect_y1 INTEGER NOT NULL,
        rect_x2 INTEGER NOT NULL,
        rect_y2 INTEGER NOT NULL,
        dest_map TEXT NOT NULL CHECK(length(dest_map) <= 10),
        dest_x INTEGER NOT NULL,
        dest_y INTEGER NOT NULL,
        FOREIGN KEY (map_name) REFERENCES maps(map_name) ON DELETE CASCADE
    );

    -- Indexes
    CREATE INDEX IF NOT EXISTS idx_teleport_map ON map_teleport_locations(map_name);
    CREATE INDEX IF NOT EXISTS idx_initial_points_map ON map_initial_points(map_name);
    CREATE INDEX IF NOT EXISTS idx_waypoints_map ON map_waypoints(map_name);
    CREATE INDEX IF NOT EXISTS idx_no_attack_map ON map_no_attack_areas(map_name);
    CREATE INDEX IF NOT EXISTS idx_npc_avoid_map ON map_npc_avoid_rects(map_name);
    CREATE INDEX IF NOT EXISTS idx_spot_mob_map ON map_spot_mob_generators(map_name);
    CREATE INDEX IF NOT EXISTS idx_fish_map ON map_fish_points(map_name);
    CREATE INDEX IF NOT EXISTS idx_mineral_map ON map_mineral_points(map_name);
    CREATE INDEX IF NOT EXISTS idx_strategic_map ON map_strategic_points(map_name);
    CREATE INDEX IF NOT EXISTS idx_sphere_creation_map ON map_energy_sphere_creation(map_name);
    CREATE INDEX IF NOT EXISTS idx_sphere_goal_map ON map_energy_sphere_goal(map_name);
    CREATE INDEX IF NOT EXISTS idx_strike_map ON map_strike_points(map_name);
    CREATE INDEX IF NOT EXISTS idx_item_events_map ON map_item_events(map_name);
    CREATE INDEX IF NOT EXISTS idx_heldenian_towers_map ON map_heldenian_towers(map_name);
    CREATE INDEX IF NOT EXISTS idx_heldenian_doors_map ON map_heldenian_gate_doors(map_name);
    CREATE INDEX IF NOT EXISTS idx_npcs_map ON map_npcs(map_name);
    """

    cursor.executescript(schema_sql)
    conn.commit()


def insert_map_config(conn: sqlite3.Connection, config: MapConfig):
    """Insert a map configuration into the database"""
    cursor = conn.cursor()

    # Insert main map record
    cursor.execute("""
        INSERT INTO maps (
            map_name, location_name, maximum_object, level_limit, upper_level_limit,
            map_type, random_mob_generator_enabled, random_mob_generator_level,
            mineral_generator_enabled, mineral_generator_level, max_fish, max_mineral,
            fixed_day_mode, recall_impossible, apocalypse_map, apocalypse_mob_gen_type,
            citizen_limit, is_fight_zone, heldenian_map, heldenian_mode_map,
            mob_event_amount, energy_sphere_auto_creation, pk_mode
        ) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
    """, (
        config.map_name, config.location_name, config.maximum_object,
        config.level_limit, config.upper_level_limit, config.map_type,
        config.random_mob_generator_enabled, config.random_mob_generator_level,
        config.mineral_generator_enabled, config.mineral_generator_level,
        config.max_fish, config.max_mineral, config.fixed_day_mode,
        config.recall_impossible, config.apocalypse_map, config.apocalypse_mob_gen_type,
        config.citizen_limit, config.is_fight_zone, config.heldenian_map,
        config.heldenian_mode_map, config.mob_event_amount,
        config.energy_sphere_auto_creation, config.pk_mode
    ))

    # Insert teleport locations
    for tp in config.teleport_locations:
        cursor.execute("""
            INSERT INTO map_teleport_locations
            (map_name, teleport_index, src_x, src_y, dest_map_name, dest_x, dest_y, direction)
            VALUES (?, ?, ?, ?, ?, ?, ?, ?)
        """, (config.map_name, *tp))

    # Insert initial points
    for pt in config.initial_points:
        cursor.execute("""
            INSERT INTO map_initial_points (map_name, point_index, x, y)
            VALUES (?, ?, ?, ?)
        """, (config.map_name, *pt))

    # Insert waypoints
    for wp in config.waypoints:
        cursor.execute("""
            INSERT INTO map_waypoints (map_name, waypoint_index, x, y)
            VALUES (?, ?, ?, ?)
        """, (config.map_name, *wp))

    # Insert no-attack areas
    for area in config.no_attack_areas:
        cursor.execute("""
            INSERT INTO map_no_attack_areas
            (map_name, area_index, rect_left, rect_top, rect_right, rect_bottom)
            VALUES (?, ?, ?, ?, ?, ?)
        """, (config.map_name, *area))

    # Insert NPC avoid rects
    for rect in config.npc_avoid_rects:
        cursor.execute("""
            INSERT INTO map_npc_avoid_rects
            (map_name, rect_index, rect_left, rect_top, rect_right, rect_bottom)
            VALUES (?, ?, ?, ?, ?, ?)
        """, (config.map_name, *rect))

    # Insert spot mob generators
    for gen in config.spot_mob_generators:
        cursor.execute("""
            INSERT INTO map_spot_mob_generators
            (map_name, generator_index, generator_type, rect_left, rect_top, rect_right, rect_bottom, waypoints, mob_type, max_mobs)
            VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
        """, (config.map_name, *gen))

    # Insert fish points
    for pt in config.fish_points:
        cursor.execute("""
            INSERT INTO map_fish_points (map_name, point_index, x, y)
            VALUES (?, ?, ?, ?)
        """, (config.map_name, *pt))

    # Insert mineral points
    for pt in config.mineral_points:
        cursor.execute("""
            INSERT INTO map_mineral_points (map_name, point_index, x, y)
            VALUES (?, ?, ?, ?)
        """, (config.map_name, *pt))

    # Insert strategic points
    for pt in config.strategic_points:
        cursor.execute("""
            INSERT INTO map_strategic_points
            (map_name, point_index, side, point_value, x, y)
            VALUES (?, ?, ?, ?, ?, ?)
        """, (config.map_name, *pt))

    # Insert energy sphere creation points
    for pt in config.energy_sphere_creation:
        cursor.execute("""
            INSERT INTO map_energy_sphere_creation
            (map_name, point_index, sphere_type, x, y)
            VALUES (?, ?, ?, ?, ?)
        """, (config.map_name, *pt))

    # Insert energy sphere goal points
    for pt in config.energy_sphere_goal:
        cursor.execute("""
            INSERT INTO map_energy_sphere_goal
            (map_name, point_index, result, aresden_x, aresden_y, elvine_x, elvine_y)
            VALUES (?, ?, ?, ?, ?, ?, ?)
        """, (config.map_name, *pt))

    # Insert strike points
    for pt in config.strike_points:
        cursor.execute("""
            INSERT INTO map_strike_points
            (map_name, point_index, x, y, hp, effect_x1, effect_y1, effect_x2, effect_y2,
             effect_x3, effect_y3, effect_x4, effect_y4, effect_x5, effect_y5, related_map_name)
            VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
        """, (config.map_name, *pt))

    # Insert item events
    for evt in config.item_events:
        cursor.execute("""
            INSERT INTO map_item_events
            (map_name, event_index, item_name, amount, total_num, event_month, event_day, event_type, mob_list)
            VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)
        """, (config.map_name, *evt))

    # Insert heldenian towers
    for tower in config.heldenian_towers:
        cursor.execute("""
            INSERT INTO map_heldenian_towers
            (map_name, tower_index, type_id, side, x, y)
            VALUES (?, ?, ?, ?, ?, ?)
        """, (config.map_name, *tower))

    # Insert heldenian gate doors
    for door in config.heldenian_gate_doors:
        cursor.execute("""
            INSERT INTO map_heldenian_gate_doors
            (map_name, door_index, direction, x, y)
            VALUES (?, ?, ?, ?, ?)
        """, (config.map_name, *door))

    # Insert NPCs
    for npc in config.npcs:
        cursor.execute("""
            INSERT INTO map_npcs (map_name, npc_name, move_type, waypoint_list, name_prefix)
            VALUES (?, ?, ?, ?, ?)
        """, (config.map_name, *npc))

    # Insert apocalypse boss
    if config.apocalypse_boss:
        cursor.execute("""
            INSERT INTO map_apocalypse_boss
            (map_name, npc_id, rect_x1, rect_y1, rect_x2, rect_y2)
            VALUES (?, ?, ?, ?, ?, ?)
        """, (config.map_name, *config.apocalypse_boss))

    # Insert dynamic gate
    if config.dynamic_gate:
        cursor.execute("""
            INSERT INTO map_dynamic_gate
            (map_name, gate_type, rect_x1, rect_y1, rect_x2, rect_y2, dest_map, dest_x, dest_y)
            VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)
        """, (config.map_name, *config.dynamic_gate))


def main():
    print("=" * 60)
    print("Helbreath 3.82 Map Configuration Migration Tool")
    print("=" * 60)

    # Check source directory
    if not MAPDATA_DIR.exists():
        print(f"ERROR: MAPDATA directory not found: {MAPDATA_DIR}")
        sys.exit(1)

    # Find all map files (use set to avoid duplicates on case-insensitive filesystems)
    map_files_set = set()
    for f in MAPDATA_DIR.glob("*.txt"):
        map_files_set.add(f.resolve())
    for f in MAPDATA_DIR.glob("*.TXT"):
        map_files_set.add(f.resolve())
    map_files = list(map_files_set)
    print(f"Found {len(map_files)} map files in {MAPDATA_DIR}")

    # Remove existing database
    if OUTPUT_DB.exists():
        print(f"Removing existing database: {OUTPUT_DB}")
        OUTPUT_DB.unlink()

    # Create new database
    print(f"Creating new database: {OUTPUT_DB}")
    conn = sqlite3.connect(str(OUTPUT_DB))
    conn.execute("PRAGMA foreign_keys = ON")

    # Create schema
    print("Creating database schema...")
    create_schema(conn)

    # Process each map file
    success_count = 0
    error_count = 0
    stats = {
        'teleports': 0,
        'initial_points': 0,
        'waypoints': 0,
        'spot_generators': 0,
        'total_max_mobs': 0,
    }

    print("\nProcessing map files...")
    for map_file in sorted(map_files):
        print(f"  Processing: {map_file.name}")
        config = parse_map_file(map_file)

        if config:
            try:
                insert_map_config(conn, config)
                conn.commit()
                success_count += 1

                # Update stats
                stats['teleports'] += len(config.teleport_locations)
                stats['initial_points'] += len(config.initial_points)
                stats['waypoints'] += len(config.waypoints)
                stats['spot_generators'] += len(config.spot_mob_generators)
                for gen in config.spot_mob_generators:
                    stats['total_max_mobs'] += gen[8]  # max_mobs is at index 8

            except Exception as e:
                print(f"    ERROR inserting {map_file.name}: {e}")
                conn.rollback()
                error_count += 1
        else:
            error_count += 1

    conn.close()

    # Print summary
    print("\n" + "=" * 60)
    print("Migration Complete!")
    print("=" * 60)
    print(f"Maps processed successfully: {success_count}")
    print(f"Maps with errors: {error_count}")
    print(f"\nStatistics:")
    print(f"  Total teleport locations: {stats['teleports']}")
    print(f"  Total initial points: {stats['initial_points']}")
    print(f"  Total waypoints: {stats['waypoints']}")
    print(f"  Total spot mob generators: {stats['spot_generators']}")
    print(f"  Total max mobs from spots: {stats['total_max_mobs']}")
    print(f"\nOutput: {OUTPUT_DB}")
    print(f"Database size: {OUTPUT_DB.stat().st_size / 1024:.1f} KB")


if __name__ == "__main__":
    main()
