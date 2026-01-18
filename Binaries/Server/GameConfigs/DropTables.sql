-- NPC body-part drops (tier 1 only). item_id=0 represents no-drop.
CREATE TABLE IF NOT EXISTS drop_tables (
  drop_table_id INTEGER PRIMARY KEY,
  name TEXT NOT NULL,
  description TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS drop_entries (
  drop_table_id INTEGER NOT NULL,
  tier INTEGER NOT NULL,
  item_id INTEGER NOT NULL,
  weight INTEGER NOT NULL,
  min_count INTEGER NOT NULL,
  max_count INTEGER NOT NULL,
  PRIMARY KEY (drop_table_id, tier, item_id)
);

ALTER TABLE npc_configs ADD COLUMN drop_table_id INTEGER NOT NULL DEFAULT 0;

DELETE FROM drop_entries;
DELETE FROM drop_tables;

INSERT INTO drop_tables(drop_table_id, name, description) VALUES(20010, 'body_Slime', 'Body-part drops for Slime');
INSERT INTO drop_tables(drop_table_id, name, description) VALUES(20011, 'body_Skeleton', 'Body-part drops for Skeleton');
INSERT INTO drop_tables(drop_table_id, name, description) VALUES(20012, 'body_Stone-Golem', 'Body-part drops for Stone-Golem');
INSERT INTO drop_tables(drop_table_id, name, description) VALUES(20013, 'body_Cyclops', 'Body-part drops for Cyclops');
INSERT INTO drop_tables(drop_table_id, name, description) VALUES(20014, 'body_Orc', 'Body-part drops for Orc');
INSERT INTO drop_tables(drop_table_id, name, description) VALUES(20016, 'body_Giant-Ant', 'Body-part drops for Giant-Ant');
INSERT INTO drop_tables(drop_table_id, name, description) VALUES(20017, 'body_Scorpion', 'Body-part drops for Scorpion');
INSERT INTO drop_tables(drop_table_id, name, description) VALUES(20018, 'body_Zombie', 'Body-part drops for Zombie');
INSERT INTO drop_tables(drop_table_id, name, description) VALUES(20022, 'body_Amphis', 'Body-part drops for Amphis');
INSERT INTO drop_tables(drop_table_id, name, description) VALUES(20023, 'body_Clay-Golem', 'Body-part drops for Clay-Golem');
INSERT INTO drop_tables(drop_table_id, name, description) VALUES(20027, 'body_Hellbound', 'Body-part drops for Hellbound');
INSERT INTO drop_tables(drop_table_id, name, description) VALUES(20028, 'body_Troll', 'Body-part drops for Troll');
INSERT INTO drop_tables(drop_table_id, name, description) VALUES(20029, 'body_Orge', 'Body-part drops for Orge');
INSERT INTO drop_tables(drop_table_id, name, description) VALUES(20030, 'body_Liche', 'Body-part drops for Liche');
INSERT INTO drop_tables(drop_table_id, name, description) VALUES(20031, 'body_Demon', 'Body-part drops for Demon');
INSERT INTO drop_tables(drop_table_id, name, description) VALUES(20032, 'body_Unicorn', 'Body-part drops for Unicorn');
INSERT INTO drop_tables(drop_table_id, name, description) VALUES(20033, 'body_WereWolf', 'Body-part drops for WereWolf');

INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20010, 1, 220, 400, 1, 1);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20010, 1, 0, 9600, 0, 0);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20011, 1, 219, 250, 1, 1);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20011, 1, 0, 9750, 0, 0);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20012, 1, 221, 167, 1, 1);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20012, 1, 0, 9833, 0, 0);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20013, 1, 194, 46, 1, 1);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20013, 1, 195, 42, 1, 1);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20013, 1, 196, 56, 1, 1);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20013, 1, 197, 76, 1, 1);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20013, 1, 198, 42, 1, 1);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20013, 1, 0, 9738, 0, 0);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20014, 1, 206, 227, 1, 1);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20014, 1, 207, 125, 1, 1);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20014, 1, 208, 119, 1, 1);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20014, 1, 0, 9529, 0, 0);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20016, 1, 192, 370, 1, 1);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20016, 1, 193, 333, 1, 1);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20016, 1, 0, 9297, 0, 0);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20017, 1, 215, 40, 1, 1);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20017, 1, 216, 100, 1, 1);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20017, 1, 217, 40, 1, 1);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20017, 1, 218, 50, 1, 1);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20017, 1, 0, 9770, 0, 0);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20022, 1, 188, 133, 1, 1);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20022, 1, 189, 125, 1, 1);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20022, 1, 190, 125, 1, 1);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20022, 1, 191, 118, 1, 1);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20022, 1, 0, 9499, 0, 0);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20023, 1, 205, 167, 1, 1);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20023, 1, 0, 9833, 0, 0);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20027, 1, 199, 36, 1, 1);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20027, 1, 200, 38, 1, 1);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20027, 1, 201, 38, 1, 1);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20027, 1, 202, 40, 1, 1);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20027, 1, 203, 40, 1, 1);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20027, 1, 204, 29, 1, 1);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20027, 1, 0, 9779, 0, 0);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20028, 1, 222, 57, 1, 1);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20028, 1, 223, 87, 1, 1);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20028, 1, 224, 80, 1, 1);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20028, 1, 225, 74, 1, 1);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20028, 1, 0, 9702, 0, 0);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20029, 1, 209, 71, 1, 1);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20029, 1, 210, 65, 1, 1);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20029, 1, 211, 57, 1, 1);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20029, 1, 212, 57, 1, 1);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20029, 1, 213, 51, 1, 1);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20029, 1, 214, 51, 1, 1);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20029, 1, 0, 9648, 0, 0);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20031, 1, 541, 5, 1, 1);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20031, 1, 542, 2, 1, 1);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20031, 1, 543, 10, 1, 1);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20031, 1, 540, 7, 1, 1);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20031, 1, 0, 9976, 0, 0);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20032, 1, 544, 1, 1, 1);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20032, 1, 545, 4, 1, 1);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20032, 1, 546, 20, 1, 1);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20032, 1, 547, 10, 1, 1);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20032, 1, 0, 9965, 0, 0);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20033, 1, 551, 42, 1, 1);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20033, 1, 548, 45, 1, 1);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20033, 1, 550, 50, 1, 1);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20033, 1, 553, 36, 1, 1);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20033, 1, 552, 45, 1, 1);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20033, 1, 554, 45, 1, 1);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20033, 1, 549, 33, 1, 1);
INSERT INTO drop_entries(drop_table_id, tier, item_id, weight, min_count, max_count) VALUES(20033, 1, 0, 9704, 0, 0);

UPDATE npc_configs SET drop_table_id=20010 WHERE name='Slime';
UPDATE npc_configs SET drop_table_id=20011 WHERE name='Skeleton';
UPDATE npc_configs SET drop_table_id=20012 WHERE name='Stone-Golem';
UPDATE npc_configs SET drop_table_id=20013 WHERE name='Cyclops';
UPDATE npc_configs SET drop_table_id=20014 WHERE name='Orc';
UPDATE npc_configs SET drop_table_id=20016 WHERE name='Giant-Ant';
UPDATE npc_configs SET drop_table_id=20017 WHERE name='Scorpion';
UPDATE npc_configs SET drop_table_id=20018 WHERE name='Zombie';
UPDATE npc_configs SET drop_table_id=20022 WHERE name='Amphis';
UPDATE npc_configs SET drop_table_id=20023 WHERE name='Clay-Golem';
UPDATE npc_configs SET drop_table_id=20027 WHERE name='Hellbound';
UPDATE npc_configs SET drop_table_id=20028 WHERE name='Troll';
UPDATE npc_configs SET drop_table_id=20029 WHERE name='Orge';
UPDATE npc_configs SET drop_table_id=20030 WHERE name='Liche';
UPDATE npc_configs SET drop_table_id=20031 WHERE name='Demon';
UPDATE npc_configs SET drop_table_id=20032 WHERE name='Unicorn';
UPDATE npc_configs SET drop_table_id=20033 WHERE name='WereWolf';
