/*
 Navicat Premium Data Transfer

 Source Server         : GameConfigs
 Source Server Type    : SQLite
 Source Server Version : 3035005 (3.35.5)
 Source Schema         : main

 Target Server Type    : SQLite
 Target Server Version : 3035005 (3.35.5)
 File Encoding         : 65001

 Date: 08/01/2026 02:44:27
*/

PRAGMA foreign_keys = false;

-- ----------------------------
-- Table structure for admin_list
-- ----------------------------
DROP TABLE IF EXISTS "admin_list";
CREATE TABLE "admin_list" (
  "gm_name" TEXT,
  PRIMARY KEY ("gm_name")
);

-- ----------------------------
-- Records of admin_list
-- ----------------------------
INSERT INTO "admin_list" VALUES ('CrazyAdmin');

-- ----------------------------
-- Table structure for admin_settings
-- ----------------------------
DROP TABLE IF EXISTS "admin_settings";
CREATE TABLE "admin_settings" (
  "key" TEXT,
  "value" INTEGER NOT NULL,
  PRIMARY KEY ("key")
);

-- ----------------------------
-- Records of admin_settings
-- ----------------------------
INSERT INTO "admin_settings" VALUES ('Admin-Level-/kill', 3);
INSERT INTO "admin_settings" VALUES ('Admin-Level-/revive', 3);
INSERT INTO "admin_settings" VALUES ('Admin-Level-/closecon', 3);
INSERT INTO "admin_settings" VALUES ('Admin-Level-/checkrep', 1);
INSERT INTO "admin_settings" VALUES ('Admin-Level-/who', 0);
INSERT INTO "admin_settings" VALUES ('Admin-Level-/energysphere', 2);
INSERT INTO "admin_settings" VALUES ('Admin-Level-/shutdownthisserverrightnow', 3);
INSERT INTO "admin_settings" VALUES ('Admin-Level-/setobservermode', 3);
INSERT INTO "admin_settings" VALUES ('Admin-Level-/shutup', 2);
INSERT INTO "admin_settings" VALUES ('Admin-Level-/attack', 2);
INSERT INTO "admin_settings" VALUES ('Admin-Level-/summondemon', 3);
INSERT INTO "admin_settings" VALUES ('Admin-Level-/summondeath', 3);
INSERT INTO "admin_settings" VALUES ('Admin-Level-/reservefightzone', 2);
INSERT INTO "admin_settings" VALUES ('Admin-Level-/createfish', 2);
INSERT INTO "admin_settings" VALUES ('Admin-Level-/teleport', 2);
INSERT INTO "admin_settings" VALUES ('Admin-Level-/checkip', 2);
INSERT INTO "admin_settings" VALUES ('Admin-Level-/polymorph', 2);
INSERT INTO "admin_settings" VALUES ('Admin-Level-/setinvi', 2);
INSERT INTO "admin_settings" VALUES ('Admin-Level-/setzerk', 2);
INSERT INTO "admin_settings" VALUES ('Admin-Level-/setfreeze', 2);
INSERT INTO "admin_settings" VALUES ('Admin-Level-/gns', 2);
INSERT INTO "admin_settings" VALUES ('Admin-Level-/setattackmode', 2);
INSERT INTO "admin_settings" VALUES ('Admin-Level-/unsummonall', 3);
INSERT INTO "admin_settings" VALUES ('Admin-Level-/unsummondemon', 3);
INSERT INTO "admin_settings" VALUES ('Admin-Level-/summonnpc', 3);
INSERT INTO "admin_settings" VALUES ('Admin-Level-/summonall', 4);
INSERT INTO "admin_settings" VALUES ('Admin-Level-/summonplayer', 1);
INSERT INTO "admin_settings" VALUES ('Admin-Level-/disconnectall', 2);
INSERT INTO "admin_settings" VALUES ('Admin-Level-/enableadmincreateitem', 3);
INSERT INTO "admin_settings" VALUES ('Admin-Level-/createitem', 4);
INSERT INTO "admin_settings" VALUES ('Admin-Level-/storm', 3);
INSERT INTO "admin_settings" VALUES ('Admin-Level-/weather', 2);
INSERT INTO "admin_settings" VALUES ('Admin-Level-/setstatus', 2);
INSERT INTO "admin_settings" VALUES ('Admin-Level-/goto', 1);
INSERT INTO "admin_settings" VALUES ('Admin-Level-/monstercount', 1);
INSERT INTO "admin_settings" VALUES ('Admin-Level-/setforcerecalltime', 3);
INSERT INTO "admin_settings" VALUES ('Admin-Level-/unsummonboss', 3);
INSERT INTO "admin_settings" VALUES ('Admin-Level-/clearnpc', 3);
INSERT INTO "admin_settings" VALUES ('Admin-Level-/time', 2);
INSERT INTO "admin_settings" VALUES ('Admin-Level-/send', 2);
INSERT INTO "admin_settings" VALUES ('Admin-Level-/summonguild', 3);
INSERT INTO "admin_settings" VALUES ('Admin-Level-/checkstatus', 0);
INSERT INTO "admin_settings" VALUES ('Admin-Level-/clearmap', 0);

-- ----------------------------
-- Table structure for banned_list
-- ----------------------------
DROP TABLE IF EXISTS "banned_list";
CREATE TABLE "banned_list" (
  "ip_address" TEXT,
  PRIMARY KEY ("ip_address")
);

-- ----------------------------
-- Records of banned_list
-- ----------------------------
INSERT INTO "banned_list" VALUES ('192.118.1.1');

-- ----------------------------
-- Table structure for builditem_configs
-- ----------------------------
DROP TABLE IF EXISTS "builditem_configs";
CREATE TABLE "builditem_configs" (
  "build_id" INTEGER,
  "name" TEXT NOT NULL,
  "skill_limit" INTEGER NOT NULL,
  "material_id1" INTEGER NOT NULL,
  "material_count1" INTEGER NOT NULL,
  "material_value1" INTEGER NOT NULL,
  "material_id2" INTEGER NOT NULL,
  "material_count2" INTEGER NOT NULL,
  "material_value2" INTEGER NOT NULL,
  "material_id3" INTEGER NOT NULL,
  "material_count3" INTEGER NOT NULL,
  "material_value3" INTEGER NOT NULL,
  "material_id4" INTEGER NOT NULL,
  "material_count4" INTEGER NOT NULL,
  "material_value4" INTEGER NOT NULL,
  "material_id5" INTEGER NOT NULL,
  "material_count5" INTEGER NOT NULL,
  "material_value5" INTEGER NOT NULL,
  "material_id6" INTEGER NOT NULL,
  "material_count6" INTEGER NOT NULL,
  "material_value6" INTEGER NOT NULL,
  "average_value" INTEGER NOT NULL,
  "max_skill" INTEGER NOT NULL,
  "attribute" INTEGER NOT NULL,
  "item_id" INTEGER NOT NULL,
  PRIMARY KEY ("build_id")
);

-- ----------------------------
-- Records of builditem_configs
-- ----------------------------
INSERT INTO "builditem_configs" VALUES (0, 'SuperCoal', 20, 355, 1, 0, 355, 1, 0, 355, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 30, 0, 501);
INSERT INTO "builditem_configs" VALUES (1, 'UltraCoal', 80, 501, 1, 0, 501, 1, 0, 357, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 90, 0, 502);
INSERT INTO "builditem_configs" VALUES (2, 'IronIngot', 20, 357, 1, 0, 357, 1, 0, 357, 1, 0, 501, 1, 0, 0, 0, 0, 0, 0, 0, 0, 30, 0, 500);
INSERT INTO "builditem_configs" VALUES (3, 'MithralIngot', 85, 508, 1, 0, 508, 1, 0, 502, 1, 0, 501, 1, 0, 0, 0, 0, 0, 0, 0, 0, 95, 0, 506);
INSERT INTO "builditem_configs" VALUES (4, 'GoldIngot', 70, 354, 1, 0, 354, 1, 0, 354, 1, 0, 501, 1, 0, 0, 0, 0, 0, 0, 0, 0, 95, 0, 503);
INSERT INTO "builditem_configs" VALUES (5, 'SilverIngot', 40, 356, 1, 0, 356, 1, 0, 356, 1, 0, 501, 1, 0, 0, 0, 0, 0, 0, 0, 0, 95, 0, 504);
INSERT INTO "builditem_configs" VALUES (6, 'BlondeIngot', 40, 507, 1, 0, 507, 1, 0, 507, 1, 0, 501, 1, 0, 0, 0, 0, 0, 0, 0, 0, 95, 0, 505);
INSERT INTO "builditem_configs" VALUES (7, 'Dagger', 30, 500, 1, 2, 501, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 26, 40, 0, 1);
INSERT INTO "builditem_configs" VALUES (8, 'ShortSword', 40, 500, 1, 2, 501, 1, 2, 357, 1, 1, 355, 1, 0, 0, 0, 0, 0, 0, 0, 33, 50, 0, 8);
INSERT INTO "builditem_configs" VALUES (9, 'MainGauche', 50, 500, 1, 2, 501, 1, 2, 357, 1, 1, 355, 1, 0, 0, 0, 0, 0, 0, 0, 41, 60, 0, 12);
INSERT INTO "builditem_configs" VALUES (10, 'Gradius', 60, 500, 1, 2, 501, 1, 2, 357, 1, 1, 355, 1, 0, 0, 0, 0, 0, 0, 0, 48, 70, 0, 15);
INSERT INTO "builditem_configs" VALUES (11, 'LongSword', 40, 500, 1, 2, 500, 1, 2, 501, 1, 1, 355, 1, 0, 0, 0, 0, 0, 0, 0, 33, 50, 0, 17);
INSERT INTO "builditem_configs" VALUES (12, 'Sabre', 50, 500, 1, 2, 500, 1, 2, 501, 1, 1, 355, 1, 0, 0, 0, 0, 0, 0, 0, 41, 60, 0, 23);
INSERT INTO "builditem_configs" VALUES (13, 'Scimitar', 60, 500, 1, 2, 500, 1, 2, 501, 1, 1, 355, 1, 0, 0, 0, 0, 0, 0, 0, 48, 70, 0, 25);
INSERT INTO "builditem_configs" VALUES (14, 'Falchion', 70, 500, 1, 2, 500, 1, 2, 501, 1, 1, 355, 1, 0, 0, 0, 0, 0, 0, 0, 56, 80, 0, 28);
INSERT INTO "builditem_configs" VALUES (15, 'Esterk', 40, 500, 1, 2, 500, 1, 2, 501, 1, 1, 357, 1, 0, 0, 0, 0, 0, 0, 0, 33, 50, 0, 31);
INSERT INTO "builditem_configs" VALUES (16, 'Rapier', 50, 500, 1, 2, 500, 1, 2, 501, 1, 1, 357, 1, 0, 0, 0, 0, 0, 0, 0, 41, 60, 0, 34);
INSERT INTO "builditem_configs" VALUES (17, 'BroadSword', 50, 500, 1, 2, 500, 1, 2, 501, 1, 2, 501, 1, 1, 0, 0, 0, 0, 0, 0, 41, 60, 0, 38);
INSERT INTO "builditem_configs" VALUES (18, 'BastadSword', 60, 500, 1, 2, 500, 1, 2, 501, 1, 2, 501, 1, 1, 355, 1, 1, 357, 1, 0, 48, 70, 0, 42);
INSERT INTO "builditem_configs" VALUES (19, 'Claymore', 70, 500, 1, 2, 500, 1, 2, 501, 1, 2, 501, 1, 1, 501, 1, 1, 0, 0, 0, 56, 80, 0, 46);
INSERT INTO "builditem_configs" VALUES (20, 'GreatSword', 80, 500, 1, 2, 500, 1, 2, 502, 1, 2, 501, 1, 1, 501, 1, 1, 0, 0, 0, 63, 90, 0, 50);
INSERT INTO "builditem_configs" VALUES (21, 'Flameberge', 90, 500, 1, 2, 500, 1, 2, 502, 1, 2, 502, 1, 2, 501, 1, 1, 501, 1, 1, 71, 100, 0, 54);
INSERT INTO "builditem_configs" VALUES (22, 'GiantSword', 95, 506, 1, 2, 503, 1, 2, 503, 1, 2, 508, 1, 1, 195, 1, -1, 500, 1, 1, 75, 100, 0, 615);
INSERT INTO "builditem_configs" VALUES (23, 'BlackShadowSword', 99, 506, 1, 2, 506, 1, 2, 505, 1, 2, 505, 1, 2, 508, 1, 1, 195, 1, -1, 75, 100, 0, 844);
INSERT INTO "builditem_configs" VALUES (24, 'LightAxe', 30, 500, 1, 2, 500, 1, 2, 501, 1, 1, 355, 1, 0, 0, 0, 0, 0, 0, 0, 26, 40, 0, 59);
INSERT INTO "builditem_configs" VALUES (25, 'Tomahoc', 40, 500, 1, 2, 500, 1, 2, 501, 1, 1, 355, 1, 0, 0, 0, 0, 0, 0, 0, 33, 50, 0, 62);
INSERT INTO "builditem_configs" VALUES (26, 'SexonAxe', 50, 500, 1, 2, 500, 1, 2, 501, 1, 1, 355, 1, 0, 0, 0, 0, 0, 0, 0, 41, 60, 0, 65);
INSERT INTO "builditem_configs" VALUES (27, 'DoubleAxe', 60, 500, 1, 2, 500, 1, 2, 501, 1, 1, 501, 1, 1, 0, 0, 0, 0, 0, 0, 48, 70, 0, 68);
INSERT INTO "builditem_configs" VALUES (28, 'WarAxe', 70, 500, 1, 2, 500, 1, 2, 501, 1, 2, 501, 1, 1, 501, 1, 1, 0, 0, 0, 56, 80, 0, 71);
INSERT INTO "builditem_configs" VALUES (29, 'BattleAxe', 90, 500, 1, 2, 500, 1, 2, 502, 1, 2, 502, 1, 2, 501, 1, 1, 501, 1, 1, 66, 100, 0, 560);
INSERT INTO "builditem_configs" VALUES (30, 'Hammer', 90, 503, 1, 2, 500, 1, 2, 500, 1, 2, 500, 1, 2, 502, 1, 1, 502, 1, 1, 71, 100, 0, 760);
INSERT INTO "builditem_configs" VALUES (31, 'BattleHammer', 95, 506, 1, 2, 503, 1, 2, 503, 1, 2, 508, 1, 1, 502, 1, 1, 500, 1, 1, 72, 100, 0, 761);
INSERT INTO "builditem_configs" VALUES (32, 'BarbarianHammer', 99, 506, 1, 2, 506, 1, 2, 503, 1, 2, 351, 1, -2, 508, 1, 1, 502, 1, 1, 73, 100, 0, 843);
INSERT INTO "builditem_configs" VALUES (33, 'Hauberk(M)', 40, 504, 1, 2, 500, 1, 2, 500, 1, 2, 207, 1, -1, 0, 0, 0, 0, 0, 0, 33, 50, 0, 454);
INSERT INTO "builditem_configs" VALUES (34, 'ChainHose(M)', 50, 504, 1, 2, 500, 1, 2, 500, 1, 2, 501, 1, 1, 207, 1, -1, 0, 0, 0, 41, 60, 0, 461);
INSERT INTO "builditem_configs" VALUES (35, 'ScaleMail(M)', 60, 504, 1, 2, 500, 1, 2, 500, 1, 2, 500, 1, 2, 501, 1, 1, 207, 1, -1, 48, 70, 0, 457);
INSERT INTO "builditem_configs" VALUES (36, 'ChainMail(M)', 70, 504, 1, 2, 500, 1, 2, 500, 1, 2, 500, 1, 2, 501, 1, 1, 207, 1, -1, 56, 80, 0, 456);
INSERT INTO "builditem_configs" VALUES (37, 'PlateLeggings(M)', 80, 504, 1, 2, 500, 1, 2, 500, 1, 2, 500, 1, 2, 502, 1, 1, 198, 1, -1, 63, 90, 0, 462);
INSERT INTO "builditem_configs" VALUES (38, 'PlateMail(M)', 90, 504, 1, 2, 504, 1, 2, 500, 1, 2, 500, 1, 2, 502, 1, 1, 198, 1, -1, 71, 100, 0, 458);
INSERT INTO "builditem_configs" VALUES (39, 'WizardHauberk(M)', 95, 506, 1, 2, 504, 1, 2, 508, 1, 2, 502, 1, 1, 553, 1, -1, 0, 0, 0, 71, 100, 0, 681);
INSERT INTO "builditem_configs" VALUES (40, 'KnightHauberk(M)', 95, 506, 1, 2, 504, 1, 2, 508, 1, 2, 502, 1, 1, 553, 1, -1, 0, 0, 0, 80, 100, 0, 687);
INSERT INTO "builditem_configs" VALUES (41, 'KnightPlateLeg(M)', 95, 506, 1, 2, 504, 1, 2, 508, 1, 2, 502, 1, 1, 553, 1, -1, 0, 0, 0, 80, 100, 0, 677);
INSERT INTO "builditem_configs" VALUES (42, 'KnightPlateMail(M)', 99, 506, 1, 2, 504, 1, 2, 504, 1, 2, 508, 1, 1, 502, 1, 1, 553, 1, -1, 71, 100, 0, 675);
INSERT INTO "builditem_configs" VALUES (43, 'Helm(M)', 75, 504, 1, 2, 504, 1, 2, 500, 1, 2, 500, 1, 1, 200, 1, -1, 0, 0, 0, 60, 85, 0, 600);
INSERT INTO "builditem_configs" VALUES (44, 'FullHelm(M)', 80, 504, 1, 2, 504, 1, 2, 500, 1, 2, 502, 1, 1, 501, 1, 1, 200, 1, -1, 65, 90, 0, 601);
INSERT INTO "builditem_configs" VALUES (45, 'KnightFullHelm(M)', 95, 506, 1, 2, 504, 1, 2, 508, 1, 2, 502, 1, 1, 553, 1, -1, 0, 0, 0, 75, 100, 0, 679);
INSERT INTO "builditem_configs" VALUES (46, 'Wings-Helm(M)', 95, 506, 1, 2, 504, 1, 2, 504, 1, 2, 508, 1, 1, 502, 1, 1, 200, 1, -1, 75, 100, 0, 751);
INSERT INTO "builditem_configs" VALUES (47, 'Horned-Helm(M)', 99, 506, 1, 2, 504, 1, 2, 504, 1, 2, 508, 1, 1, 502, 1, 1, 200, 1, -1, 80, 100, 0, 750);
INSERT INTO "builditem_configs" VALUES (48, 'Hauberk(W)', 40, 504, 1, 2, 500, 1, 2, 500, 1, 2, 207, 1, -1, 0, 0, 1, 0, 0, 0, 33, 50, 0, 472);
INSERT INTO "builditem_configs" VALUES (49, 'ChainHose(W)', 50, 504, 1, 2, 500, 1, 2, 500, 1, 2, 501, 1, 1, 207, 1, -1, 0, 0, 0, 41, 60, 0, 482);
INSERT INTO "builditem_configs" VALUES (50, 'ScaleMail(W)', 60, 504, 1, 2, 500, 1, 2, 500, 1, 2, 500, 1, 2, 501, 1, 1, 207, 1, -1, 48, 70, 0, 477);
INSERT INTO "builditem_configs" VALUES (51, 'ChainMail(W)', 70, 504, 1, 2, 500, 1, 2, 500, 1, 2, 500, 1, 2, 501, 1, 1, 207, 1, -1, 56, 80, 0, 476);
INSERT INTO "builditem_configs" VALUES (52, 'PlateLeggings(W)', 80, 504, 1, 2, 500, 1, 2, 500, 1, 2, 500, 1, 2, 502, 1, 1, 198, 1, -1, 63, 90, 0, 483);
INSERT INTO "builditem_configs" VALUES (53, 'PlateMail(W)', 90, 504, 1, 2, 504, 1, 2, 500, 1, 2, 500, 1, 2, 502, 1, 1, 198, 1, -1, 71, 100, 0, 478);
INSERT INTO "builditem_configs" VALUES (54, 'WizardHauberk(W)', 95, 506, 1, 2, 504, 1, 2, 502, 1, 1, 553, 1, -1, 0, 0, 0, 0, 0, 0, 71, 100, 0, 682);
INSERT INTO "builditem_configs" VALUES (55, 'KnightHauberk(W)', 95, 506, 1, 2, 506, 1, 2, 502, 1, 1, 553, 1, -1, 0, 0, 0, 0, 0, 0, 75, 100, 0, 688);
INSERT INTO "builditem_configs" VALUES (56, 'KnightPlateLeg(W)', 95, 506, 1, 2, 506, 1, 2, 502, 1, 1, 553, 1, -1, 0, 0, 0, 0, 0, 0, 75, 100, 0, 678);
INSERT INTO "builditem_configs" VALUES (57, 'KnightPlateMail(W)', 99, 506, 1, 2, 504, 1, 2, 504, 1, 2, 508, 1, 1, 502, 1, 1, 553, 1, -1, 71, 100, 0, 676);
INSERT INTO "builditem_configs" VALUES (58, 'Helm(W)', 75, 504, 1, 2, 504, 1, 2, 500, 1, 2, 500, 1, 1, 200, 1, -1, 0, 0, 0, 56, 85, 0, 602);
INSERT INTO "builditem_configs" VALUES (59, 'FullHelm(W)', 80, 504, 1, 2, 504, 1, 2, 500, 1, 2, 502, 1, 1, 501, 1, 1, 200, 1, -1, 63, 90, 0, 603);
INSERT INTO "builditem_configs" VALUES (60, 'KnightFullHelm(W)', 95, 506, 1, 2, 504, 1, 2, 508, 1, 2, 502, 1, 1, 553, 1, -1, 0, 0, 0, 71, 100, 0, 680);
INSERT INTO "builditem_configs" VALUES (61, 'Wings-Helm(W)', 95, 506, 1, 2, 504, 1, 2, 504, 1, 2, 508, 1, 1, 502, 1, 1, 200, 1, -1, 71, 100, 0, 755);
INSERT INTO "builditem_configs" VALUES (62, 'Horned-Helm(W)', 99, 506, 1, 2, 504, 1, 2, 504, 1, 2, 508, 1, 1, 502, 1, 1, 200, 1, -1, 80, 100, 0, 754);
INSERT INTO "builditem_configs" VALUES (63, 'LongSword+1', 45, 505, 1, 2, 500, 1, 2, 500, 1, 2, 501, 1, 1, 355, 1, 0, 355, 1, 0, 43, 80, 0, 18);
INSERT INTO "builditem_configs" VALUES (64, 'Sabre+1', 55, 505, 1, 2, 500, 1, 2, 500, 1, 2, 501, 1, 1, 355, 1, 0, 355, 1, 0, 51, 85, 0, 24);
INSERT INTO "builditem_configs" VALUES (65, 'Scimitar+1', 65, 505, 1, 2, 500, 1, 2, 500, 1, 2, 501, 1, 1, 355, 1, 0, 355, 1, 0, 58, 90, 0, 26);
INSERT INTO "builditem_configs" VALUES (66, 'Falchion+1', 75, 505, 1, 2, 500, 1, 2, 500, 1, 2, 501, 1, 1, 355, 1, 0, 355, 1, 0, 66, 95, 0, 29);
INSERT INTO "builditem_configs" VALUES (67, 'Esterk+1', 45, 505, 1, 2, 500, 1, 2, 500, 1, 2, 501, 1, 1, 357, 1, 0, 355, 1, 0, 43, 65, 0, 32);
INSERT INTO "builditem_configs" VALUES (68, 'Rapier+1', 55, 505, 1, 2, 500, 1, 2, 500, 1, 2, 501, 1, 1, 357, 1, 0, 355, 1, 0, 51, 75, 0, 35);
INSERT INTO "builditem_configs" VALUES (69, 'BroadSword+1', 55, 505, 1, 2, 500, 1, 2, 500, 1, 2, 501, 1, 1, 501, 1, 1, 0, 0, 0, 51, 90, 0, 39);
INSERT INTO "builditem_configs" VALUES (70, 'BastadSword+1', 65, 505, 1, 2, 500, 1, 2, 500, 1, 2, 501, 1, 1, 501, 1, 1, 357, 1, 1, 58, 95, 0, 43);
INSERT INTO "builditem_configs" VALUES (71, 'Claymore+1', 75, 505, 1, 2, 500, 1, 2, 500, 1, 2, 501, 1, 2, 501, 1, 1, 501, 1, 1, 66, 96, 0, 47);
INSERT INTO "builditem_configs" VALUES (72, 'GreatSword+1', 84, 505, 1, 2, 500, 1, 2, 500, 1, 2, 502, 1, 2, 502, 1, 1, 502, 1, 1, 73, 97, 0, 51);
INSERT INTO "builditem_configs" VALUES (73, 'Flameberge+1', 93, 505, 1, 2, 500, 1, 2, 500, 1, 2, 500, 1, 2, 502, 1, 1, 502, 1, 1, 81, 100, 0, 55);
INSERT INTO "builditem_configs" VALUES (74, 'LightAxe+1', 40, 505, 1, 2, 500, 1, 2, 500, 1, 1, 355, 1, 0, 0, 0, 0, 0, 0, 0, 36, 60, 0, 60);
INSERT INTO "builditem_configs" VALUES (75, 'Tomahoc+1', 45, 505, 1, 2, 500, 1, 2, 500, 1, 1, 355, 1, 0, 0, 0, 0, 0, 0, 0, 43, 70, 0, 63);
INSERT INTO "builditem_configs" VALUES (76, 'SexonAxe+1', 55, 505, 1, 2, 500, 1, 2, 500, 1, 1, 355, 1, 0, 0, 0, 0, 0, 0, 0, 51, 80, 0, 66);
INSERT INTO "builditem_configs" VALUES (77, 'DoubleAxe+1', 65, 505, 1, 2, 500, 1, 2, 500, 1, 2, 501, 1, 1, 501, 1, 1, 0, 0, 0, 58, 90, 0, 69);
INSERT INTO "builditem_configs" VALUES (78, 'WarAxe+1', 80, 505, 1, 2, 500, 1, 2, 500, 1, 2, 501, 1, 1, 501, 1, 1, 501, 1, 0, 66, 94, 0, 72);
INSERT INTO "builditem_configs" VALUES (79, 'BattleAxe+1', 95, 505, 1, 2, 500, 1, 2, 500, 1, 2, 500, 1, 1, 502, 1, 1, 502, 1, 1, 75, 100, 0, 580);
INSERT INTO "builditem_configs" VALUES (80, 'LongSword+2', 55, 506, 1, 2, 503, 1, 2, 195, 1, -2, 500, 1, 1, 0, 0, 0, 0, 0, 0, 53, 80, 0, 19);
INSERT INTO "builditem_configs" VALUES (81, 'Sabre+2', 65, 506, 1, 2, 503, 1, 2, 195, 1, -2, 500, 1, 1, 502, 1, 0, 501, 1, 0, 61, 85, 0, 582);
INSERT INTO "builditem_configs" VALUES (82, 'Scimitar+2', 75, 506, 1, 2, 503, 1, 2, 195, 1, -2, 500, 1, 1, 502, 1, 0, 501, 1, 0, 68, 90, 0, 27);
INSERT INTO "builditem_configs" VALUES (83, 'Falchion+2', 85, 506, 1, 2, 503, 1, 2, 195, 1, -2, 500, 1, 1, 502, 1, 0, 501, 1, 0, 76, 95, 0, 30);
INSERT INTO "builditem_configs" VALUES (84, 'Esterk+2', 55, 506, 1, 2, 503, 1, 2, 195, 1, -2, 500, 1, 1, 502, 1, 0, 501, 1, 0, 53, 65, 0, 33);
INSERT INTO "builditem_configs" VALUES (85, 'Rapier+2', 65, 506, 1, 2, 503, 1, 2, 195, 1, -2, 500, 1, 1, 502, 1, 0, 501, 1, 0, 61, 75, 0, 36);
INSERT INTO "builditem_configs" VALUES (86, 'BroadSword+2', 65, 506, 1, 2, 503, 1, 2, 195, 1, -2, 500, 1, 1, 500, 1, 1, 0, 0, 0, 61, 80, 0, 40);
INSERT INTO "builditem_configs" VALUES (87, 'BastadSword+2', 75, 506, 1, 2, 503, 1, 2, 195, 1, -2, 500, 1, 1, 500, 1, 1, 0, 0, 0, 68, 85, 0, 44);
INSERT INTO "builditem_configs" VALUES (88, 'Claymore+2', 85, 506, 1, 2, 503, 1, 2, 195, 1, -2, 500, 1, 2, 500, 1, 1, 500, 1, 1, 76, 90, 0, 48);
INSERT INTO "builditem_configs" VALUES (89, 'GreatSword+2', 94, 506, 1, 2, 503, 1, 2, 195, 1, -2, 500, 1, 2, 500, 1, 1, 502, 1, 1, 83, 95, 0, 52);
INSERT INTO "builditem_configs" VALUES (90, 'Flameberge+2', 97, 506, 1, 2, 506, 1, 2, 503, 1, 2, 195, 1, -2, 500, 1, 1, 500, 1, 1, 85, 100, 0, 56);
INSERT INTO "builditem_configs" VALUES (91, 'LightAxe+2', 50, 506, 1, 2, 503, 1, 2, 195, 1, -1, 502, 1, 0, 0, 0, 0, 0, 0, 0, 36, 75, 0, 61);
INSERT INTO "builditem_configs" VALUES (92, 'Tomahoc+2', 55, 506, 1, 2, 503, 1, 2, 195, 1, -1, 500, 1, 0, 0, 0, 0, 0, 0, 0, 53, 80, 0, 64);
INSERT INTO "builditem_configs" VALUES (93, 'SexonAxe+2', 65, 506, 1, 2, 503, 1, 2, 195, 1, -1, 500, 1, 0, 0, 0, 0, 0, 0, 0, 61, 85, 0, 67);
INSERT INTO "builditem_configs" VALUES (94, 'DoubleAxe+2', 75, 506, 1, 2, 503, 1, 2, 195, 1, -2, 500, 1, 1, 500, 1, 1, 0, 0, 0, 68, 90, 0, 70);
INSERT INTO "builditem_configs" VALUES (95, 'WarAxe+2', 90, 506, 1, 2, 503, 1, 2, 195, 1, -2, 500, 1, 1, 500, 1, 1, 500, 1, 0, 76, 95, 0, 73);
INSERT INTO "builditem_configs" VALUES (96, 'BattleAxe+2', 99, 506, 1, 2, 506, 1, 2, 503, 1, 2, 508, 1, 1, 195, 1, -1, 500, 1, 1, 88, 100, 0, 581);

-- ----------------------------
-- Table structure for crafting_configs
-- ----------------------------
DROP TABLE IF EXISTS "crafting_configs";
CREATE TABLE "crafting_configs" (
  "crafting_id" INTEGER,
  "name" TEXT NOT NULL,
  "array0" INTEGER NOT NULL,
  "array1" INTEGER NOT NULL,
  "array2" INTEGER NOT NULL,
  "array3" INTEGER NOT NULL,
  "array4" INTEGER NOT NULL,
  "array5" INTEGER NOT NULL,
  "array6" INTEGER NOT NULL,
  "array7" INTEGER NOT NULL,
  "array8" INTEGER NOT NULL,
  "array9" INTEGER NOT NULL,
  "array10" INTEGER NOT NULL,
  "array11" INTEGER NOT NULL,
  "skill_limit" INTEGER NOT NULL,
  "difficulty" INTEGER NOT NULL,
  PRIMARY KEY ("crafting_id")
);

-- ----------------------------
-- Records of crafting_configs
-- ----------------------------
INSERT INTO "crafting_configs" VALUES (1, 'MagicNecklace(DF+15)', 657, 1, 356, 1, 354, 1, 311, 2, -1, 0, -1, 0, 10, 70);
INSERT INTO "crafting_configs" VALUES (2, 'MagicNecklace(DF+20)', 1086, 1, 657, 1, 356, 1, 354, 1, 311, 1, -1, 0, 20, 70);
INSERT INTO "crafting_configs" VALUES (3, 'MagicNecklace(DF+25)', 1087, 1, 657, 1, 358, 1, 356, 1, 354, 1, 311, 1, 30, 70);
INSERT INTO "crafting_configs" VALUES (4, 'MagicNecklace(DF+30)', 1088, 1, 657, 1, 358, 1, 356, 1, 354, 1, 311, 1, 40, 70);
INSERT INTO "crafting_configs" VALUES (5, 'MagicNecklace(DM+2)', 657, 1, 356, 1, 354, 1, 305, 2, -1, 0, -1, 0, 10, 70);
INSERT INTO "crafting_configs" VALUES (6, 'MagicNecklace(DM+3)', 1090, 1, 657, 1, 356, 1, 354, 1, 311, 1, -1, 0, 20, 70);
INSERT INTO "crafting_configs" VALUES (7, 'MagicNecklace(DM+4)', 1091, 1, 657, 1, 358, 1, 356, 1, 354, 1, 305, 1, 30, 70);
INSERT INTO "crafting_configs" VALUES (8, 'MagicNecklace(DM+5)', 1092, 1, 657, 1, 358, 1, 356, 1, 354, 1, 305, 1, 40, 70);
INSERT INTO "crafting_configs" VALUES (9, 'MagicNecklace(MS12)', 657, 1, 356, 1, 354, 1, 308, 2, -1, 0, -1, 0, 10, 70);
INSERT INTO "crafting_configs" VALUES (10, 'MagicNecklace(MS13)', 1094, 1, 657, 1, 356, 1, 354, 1, 311, 1, -1, 0, 20, 70);
INSERT INTO "crafting_configs" VALUES (11, 'MagicNecklace(MS14)', 1095, 1, 657, 1, 358, 1, 356, 1, 354, 1, 308, 1, 30, 70);
INSERT INTO "crafting_configs" VALUES (12, 'MagicNecklace(MS15)', 1096, 1, 657, 1, 358, 1, 356, 1, 354, 1, 308, 1, 40, 70);
INSERT INTO "crafting_configs" VALUES (13, 'MagicNecklace(RM15)', 657, 1, 356, 1, 354, 1, 300, 2, -1, 0, -1, 0, 10, 70);
INSERT INTO "crafting_configs" VALUES (14, 'MagicNecklace(RM20)', 1098, 1, 657, 1, 356, 1, 354, 1, 311, 1, -1, 0, 20, 70);
INSERT INTO "crafting_configs" VALUES (15, 'MagicNecklace(RM25)', 1099, 1, 657, 1, 358, 1, 356, 1, 354, 1, 300, 1, 30, 70);
INSERT INTO "crafting_configs" VALUES (16, 'MagicNecklace(RM30)', 1100, 1, 657, 1, 358, 1, 356, 1, 354, 1, 300, 1, 40, 70);
INSERT INTO "crafting_configs" VALUES (17, 'DiamondWare', 358, 1, 350, 2, -1, 0, -1, 0, -1, 0, -1, 0, 0, 70);
INSERT INTO "crafting_configs" VALUES (18, 'RubyWare', 358, 1, 351, 2, -1, 0, -1, 0, -1, 0, -1, 0, 0, 70);
INSERT INTO "crafting_configs" VALUES (19, 'SapphireWare', 358, 1, 352, 2, -1, 0, -1, 0, -1, 0, -1, 0, 0, 70);
INSERT INTO "crafting_configs" VALUES (20, 'EmeraldWare', 358, 1, 353, 2, -1, 0, -1, 0, -1, 0, -1, 0, 0, 70);
INSERT INTO "crafting_configs" VALUES (21, 'CrystalWare', 358, 3, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, 0, 70);
INSERT INTO "crafting_configs" VALUES (22, 'MaginDiamond', 1106, 1, 1102, 1, 1102, 1, 657, 1, -1, 0, -1, 0, 30, 70);
INSERT INTO "crafting_configs" VALUES (23, 'MaginRuby', 1106, 1, 1103, 1, 1103, 1, 657, 1, -1, 0, -1, 0, 30, 70);
INSERT INTO "crafting_configs" VALUES (24, 'MagicEmerald', 1106, 1, 1105, 1, 1105, 1, 657, 1, -1, 0, -1, 0, 30, 70);
INSERT INTO "crafting_configs" VALUES (25, 'MagicSapphire', 1106, 1, 1104, 1, 1104, 1, 657, 1, -1, 0, -1, 0, 30, 70);

-- ----------------------------
-- Table structure for crusade_structures
-- ----------------------------
DROP TABLE IF EXISTS "crusade_structures";
CREATE TABLE "crusade_structures" (
  "structure_id" INTEGER,
  "map_name" TEXT NOT NULL,
  "structure_type" INTEGER NOT NULL,
  "pos_x" INTEGER NOT NULL,
  "pos_y" INTEGER NOT NULL,
  PRIMARY KEY ("structure_id")
);

-- ----------------------------
-- Records of crusade_structures
-- ----------------------------
INSERT INTO "crusade_structures" VALUES (1, 'aresden', 40, 145, 128);
INSERT INTO "crusade_structures" VALUES (2, 'aresden', 40, 152, 124);
INSERT INTO "crusade_structures" VALUES (3, 'aresden', 40, 99, 183);
INSERT INTO "crusade_structures" VALUES (4, 'aresden', 40, 109, 186);
INSERT INTO "crusade_structures" VALUES (5, 'aresden', 40, 124, 168);
INSERT INTO "crusade_structures" VALUES (6, 'aresden', 40, 134, 165);
INSERT INTO "crusade_structures" VALUES (7, 'aresden', 40, 171, 197);
INSERT INTO "crusade_structures" VALUES (8, 'aresden', 40, 156, 203);
INSERT INTO "crusade_structures" VALUES (9, 'elvine', 40, 144, 131);
INSERT INTO "crusade_structures" VALUES (10, 'elvine', 40, 152, 126);
INSERT INTO "crusade_structures" VALUES (11, 'elvine', 40, 196, 128);
INSERT INTO "crusade_structures" VALUES (12, 'elvine', 40, 205, 130);
INSERT INTO "crusade_structures" VALUES (13, 'elvine', 40, 224, 153);
INSERT INTO "crusade_structures" VALUES (14, 'elvine', 40, 234, 149);
INSERT INTO "crusade_structures" VALUES (15, 'elvine', 40, 241, 110);
INSERT INTO "crusade_structures" VALUES (16, 'elvine', 40, 230, 115);
INSERT INTO "crusade_structures" VALUES (17, 'middleland', 42, 418, 147);
INSERT INTO "crusade_structures" VALUES (18, 'middleland', 42, 112, 174);
INSERT INTO "crusade_structures" VALUES (19, 'middleland', 42, 263, 305);
INSERT INTO "crusade_structures" VALUES (20, 'aresden', 41, 165, 109);
INSERT INTO "crusade_structures" VALUES (21, 'elvine', 41, 170, 120);

-- ----------------------------
-- Table structure for dup_item_ids
-- ----------------------------
DROP TABLE IF EXISTS "dup_item_ids";
CREATE TABLE "dup_item_ids" (
  "dup_id" INTEGER,
  "touch_effect_type" INTEGER NOT NULL,
  "touch_effect_value1" INTEGER NOT NULL,
  "touch_effect_value2" INTEGER NOT NULL,
  "touch_effect_value3" INTEGER NOT NULL,
  "price" INTEGER NOT NULL,
  PRIMARY KEY ("dup_id")
);

-- ----------------------------
-- Records of dup_item_ids
-- ----------------------------
INSERT INTO "dup_item_ids" VALUES (1, 2, 20241, 14678, 9989, 37856);
INSERT INTO "dup_item_ids" VALUES (2, 2, 18973, 31109, 29735, 34464);
INSERT INTO "dup_item_ids" VALUES (3, 2, 6354, 27849, -19762, 34464);
INSERT INTO "dup_item_ids" VALUES (4, 2, 30420, 30326, -11353, 37856);
INSERT INTO "dup_item_ids" VALUES (5, 2, 4293, 19708, -17063, 34464);
INSERT INTO "dup_item_ids" VALUES (6, 2, 826, 23094, -19632, 34464);
INSERT INTO "dup_item_ids" VALUES (7, 2, 12628, 10715, 26066, 34464);
INSERT INTO "dup_item_ids" VALUES (8, 2, 1654, 16036, -7281, 34464);
INSERT INTO "dup_item_ids" VALUES (9, 2, 15461, 13040, 1529, 37856);
INSERT INTO "dup_item_ids" VALUES (10, 2, 762, 25913, 26628, 34464);
INSERT INTO "dup_item_ids" VALUES (11, 2, 17984, 17783, -20213, 34464);
INSERT INTO "dup_item_ids" VALUES (12, 2, 1708, 12950, -7076, 34464);
INSERT INTO "dup_item_ids" VALUES (13, 2, 4244, 16688, -12527, 10000);

-- ----------------------------
-- Table structure for items
-- ----------------------------
DROP TABLE IF EXISTS "items";
CREATE TABLE "items" (
  "item_id" INTEGER,
  "name" TEXT NOT NULL,
  "item_type" INTEGER NOT NULL,
  "equip_pos" INTEGER NOT NULL,
  "item_effect_type" INTEGER NOT NULL,
  "item_effect_value1" INTEGER NOT NULL,
  "item_effect_value2" INTEGER NOT NULL,
  "item_effect_value3" INTEGER NOT NULL,
  "item_effect_value4" INTEGER NOT NULL,
  "item_effect_value5" INTEGER NOT NULL,
  "item_effect_value6" INTEGER NOT NULL,
  "max_lifespan" INTEGER NOT NULL,
  "special_effect" INTEGER NOT NULL,
  "sprite" INTEGER NOT NULL,
  "sprite_frame" INTEGER NOT NULL,
  "price" INTEGER NOT NULL,
  "is_for_sale" INTEGER NOT NULL,
  "weight" INTEGER NOT NULL,
  "appr_value" INTEGER NOT NULL,
  "speed" INTEGER NOT NULL,
  "level_limit" INTEGER NOT NULL,
  "gender_limit" INTEGER NOT NULL,
  "special_effect_value1" INTEGER NOT NULL,
  "special_effect_value2" INTEGER NOT NULL,
  "related_skill" INTEGER NOT NULL,
  "category" INTEGER NOT NULL,
  "item_color" INTEGER NOT NULL,
  PRIMARY KEY ("item_id")
);

-- ----------------------------
-- Records of items
-- ----------------------------
INSERT INTO "items" VALUES (1, 'Dagger', 1, 8, 1, 1, 5, 0, 1, 4, 0, 300, 0, 1, 0, 25, 1, 200, 1, 0, 0, 0, 0, -10, 7, 1, 0);
INSERT INTO "items" VALUES (2, 'Dagger(S.C)', 1, 8, 1, 1, 4, 0, 1, 3, 0, 800, 0, 1, 0, 55, 0, 200, 1, 0, 0, 0, 0, -10, 7, 1, 0);
INSERT INTO "items" VALUES (3, 'Dagger(Swd.breaker)', 1, 8, 1, 1, 4, 0, 1, 3, 0, 1, 0, 1, 0, 55, 0, 200, 1, 0, 0, 0, 0, -10, 7, 1, 0);
INSERT INTO "items" VALUES (4, 'Dagger+1', 1, 8, 1, 1, 5, 1, 1, 4, 1, 800, 0, 1, 0, 100, 1, 200, 1, 0, 10, 0, 0, -10, 7, 1, 0);
INSERT INTO "items" VALUES (6, 'KightDagger', 1, 8, 1, 1, 4, 0, 1, 3, 0, 800, 0, 1, 0, 35, 0, 200, 1, 0, 0, 0, 0, -10, 7, 1, 0);
INSERT INTO "items" VALUES (7, 'Dirk', 1, 8, 1, 1, 4, 0, 1, 3, 0, 800, 0, 1, 0, 35, 0, 200, 1, 0, 0, 0, 0, -10, 7, 1, 0);
INSERT INTO "items" VALUES (8, 'ShortSword', 1, 8, 1, 1, 6, 0, 1, 5, 0, 500, 0, 1, 1, 50, 1, 800, 2, 2, 0, 0, 0, -5, 7, 1, 0);
INSERT INTO "items" VALUES (9, 'ShortSword+1', 1, 8, 1, 1, 6, 1, 1, 5, 1, 800, 0, 1, 1, 200, 1, 800, 2, 2, 10, 0, 0, -5, 7, 1, 0);
INSERT INTO "items" VALUES (11, 'ShortSword(S.C)', 1, 8, 1, 1, 6, 0, 1, 5, 0, 800, 0, 1, 1, 100, 0, 800, 2, 2, 0, 0, 0, -5, 7, 1, 0);
INSERT INTO "items" VALUES (12, 'MainGauche', 1, 8, 1, 1, 7, 0, 1, 6, 0, 500, 0, 1, 1, 50, 1, 800, 2, 2, 0, 0, 0, -2, 7, 1, 0);
INSERT INTO "items" VALUES (13, 'MainGauche+1', 1, 8, 1, 1, 7, 1, 1, 6, 1, 800, 0, 1, 1, 200, 1, 800, 2, 2, 15, 0, 0, -2, 7, 1, 0);
INSERT INTO "items" VALUES (14, 'MainGauche(S.C)', 1, 8, 1, 1, 6, 0, 1, 4, 0, 800, 0, 1, 1, 100, 0, 800, 2, 2, 0, 0, 0, -2, 7, 1, 0);
INSERT INTO "items" VALUES (15, 'Gradius', 1, 8, 1, 1, 8, 0, 1, 7, 0, 500, 0, 1, 1, 90, 1, 800, 2, 2, 0, 0, 0, -2, 7, 1, 0);
INSERT INTO "items" VALUES (16, 'Gradius+1', 1, 8, 1, 1, 8, 1, 1, 7, 1, 800, 0, 1, 1, 350, 1, 800, 2, 2, 20, 0, 0, -2, 7, 1, 0);
INSERT INTO "items" VALUES (17, 'LongSword', 1, 8, 1, 1, 9, 0, 1, 10, 0, 800, 0, 1, 2, 180, 1, 1400, 3, 6, 0, 0, -1, 0, 8, 1, 0);
INSERT INTO "items" VALUES (18, 'LongSword+1', 1, 8, 1, 1, 9, 1, 1, 10, 1, 1400, 0, 1, 2, 650, 1, 1400, 3, 6, 25, 0, -1, 0, 8, 1, 0);
INSERT INTO "items" VALUES (19, 'LongSword+2', 1, 8, 1, 1, 9, 2, 1, 10, 2, 1400, 0, 1, 2, 2600, 0, 1600, 3, 6, 50, 0, -1, 0, 8, 1, 0);
INSERT INTO "items" VALUES (20, 'Excaliber', 1, 8, 1, 2, 10, 4, 2, 12, 4, 8000, 0, 1, 19, 31000, 0, 4000, 5, 0, 0, 0, -1, 0, 8, 1, 0);
INSERT INTO "items" VALUES (22, 'LongSword(S.C)', 1, 8, 1, 1, 8, 0, 1, 12, 0, 1400, 0, 1, 2, 250, 0, 1400, 3, 6, 0, 0, -1, 0, 8, 1, 0);
INSERT INTO "items" VALUES (23, 'Sabre', 1, 8, 1, 1, 8, 0, 1, 9, 0, 800, 0, 1, 3, 150, 1, 1200, 4, 5, 0, 0, -1, 0, 8, 1, 0);
INSERT INTO "items" VALUES (24, 'Sabre+1', 1, 8, 1, 1, 8, 1, 1, 9, 1, 1000, 0, 1, 3, 600, 1, 1200, 4, 5, 20, 0, -1, 0, 8, 1, 0);
INSERT INTO "items" VALUES (25, 'Scimitar', 1, 8, 1, 1, 10, 0, 1, 12, 0, 800, 0, 1, 4, 200, 1, 1800, 6, 6, 0, 0, -1, 3, 8, 1, 0);
INSERT INTO "items" VALUES (26, 'Scimitar+1', 1, 8, 1, 1, 10, 1, 1, 12, 1, 1000, 0, 1, 4, 800, 1, 1800, 6, 6, 30, 0, -1, 3, 8, 1, 0);
INSERT INTO "items" VALUES (27, 'Scimitar+2', 1, 8, 1, 1, 10, 2, 1, 12, 2, 1000, 0, 1, 4, 3200, 0, 2000, 6, 6, 70, 0, -1, 3, 8, 1, 0);
INSERT INTO "items" VALUES (28, 'Falchion', 1, 8, 1, 1, 12, 0, 2, 7, 0, 800, 0, 1, 5, 250, 1, 2200, 6, 6, 0, 0, -2, 2, 8, 1, 0);
INSERT INTO "items" VALUES (29, 'Falchion+1', 1, 8, 1, 1, 12, 1, 2, 7, 1, 1400, 0, 1, 5, 1000, 1, 2200, 6, 6, 35, 0, -2, 2, 8, 1, 0);
INSERT INTO "items" VALUES (30, 'Falchion+2', 1, 8, 1, 1, 12, 2, 2, 7, 2, 1400, 0, 1, 5, 4000, 0, 2200, 6, 6, 70, 0, -2, 2, 8, 1, 0);
INSERT INTO "items" VALUES (31, 'Esterk', 1, 8, 1, 1, 8, 0, 1, 12, 0, 800, 0, 1, 6, 400, 1, 1200, 7, 4, 0, 0, 0, 0, 9, 1, 0);
INSERT INTO "items" VALUES (32, 'Esterk+1', 1, 8, 1, 1, 8, 1, 1, 12, 1, 1400, 0, 1, 6, 800, 1, 1200, 7, 4, 20, 0, 0, 0, 9, 1, 0);
INSERT INTO "items" VALUES (33, 'Esterk+2', 1, 8, 1, 1, 8, 2, 1, 12, 2, 1400, 0, 1, 6, 3200, 0, 1200, 7, 4, 70, 0, 0, 0, 9, 1, 0);
INSERT INTO "items" VALUES (34, 'Rapier', 1, 8, 1, 1, 7, 0, 1, 10, 0, 800, 0, 1, 6, 300, 1, 1100, 7, 3, 0, 0, 0, 0, 9, 1, 0);
INSERT INTO "items" VALUES (35, 'Rapier+1', 1, 8, 1, 1, 7, 1, 1, 10, 1, 1000, 0, 1, 6, 1300, 1, 1100, 7, 3, 30, 0, 0, 0, 9, 1, 0);
INSERT INTO "items" VALUES (36, 'Rapier+2', 1, 8, 1, 1, 7, 2, 1, 10, 2, 1000, 0, 1, 6, 5200, 0, 1100, 7, 3, 70, 0, 0, 0, 9, 1, 0);
INSERT INTO "items" VALUES (37, 'TemplerSword', 1, 8, 1, 1, 8, 0, 1, 12, 0, 1000, 0, 1, 6, 1000, 0, 1200, 7, 5, 0, 0, -1, 1, 8, 1, 0);
INSERT INTO "items" VALUES (38, 'BroadSword', 1, 9, 1, 2, 7, 0, 2, 8, 0, 800, 0, 1, 7, 250, 1, 2800, 8, 6, 0, 0, -3, 2, 8, 1, 0);
INSERT INTO "items" VALUES (39, 'BroadSword+1', 1, 9, 1, 2, 7, 1, 2, 8, 1, 1400, 0, 1, 7, 1100, 1, 2800, 8, 6, 30, 0, -3, 2, 8, 1, 0);
INSERT INTO "items" VALUES (40, 'BroadSword+2', 1, 9, 1, 2, 7, 2, 2, 8, 2, 1400, 0, 1, 7, 4400, 0, 2800, 8, 6, 70, 0, -3, 2, 8, 1, 0);
INSERT INTO "items" VALUES (41, 'BroadSword(S.C)', 1, 9, 1, 2, 7, 0, 2, 8, 0, 1400, 0, 1, 7, 400, 0, 2800, 8, 6, 0, 0, -3, 2, 8, 1, 0);
INSERT INTO "items" VALUES (42, 'BastadSword', 1, 9, 1, 2, 8, 0, 2, 9, 0, 800, 0, 1, 8, 300, 1, 3300, 9, 6, 0, 0, -4, 3, 8, 1, 0);
INSERT INTO "items" VALUES (43, 'BastadSword+1', 1, 9, 1, 2, 8, 1, 2, 9, 1, 1400, 0, 1, 8, 1200, 1, 3300, 9, 6, 35, 0, -4, 3, 8, 1, 0);
INSERT INTO "items" VALUES (44, 'BastadSword+2', 1, 9, 1, 2, 8, 2, 2, 9, 2, 1400, 0, 1, 8, 4800, 0, 3300, 9, 6, 70, 0, -4, 3, 8, 1, 0);
INSERT INTO "items" VALUES (45, 'BastadSword(S.C)', 1, 9, 1, 2, 5, 0, 2, 9, 0, 1400, 0, 1, 8, 450, 0, 3300, 9, 6, 0, 0, -4, 3, 8, 1, 0);
INSERT INTO "items" VALUES (46, 'Claymore', 1, 9, 1, 2, 9, 0, 2, 10, 0, 1000, 0, 1, 9, 400, 1, 4000, 10, 7, 0, 0, -5, 4, 8, 1, 0);
INSERT INTO "items" VALUES (47, 'Claymore+1', 1, 9, 1, 2, 9, 1, 2, 10, 1, 1400, 0, 1, 9, 1800, 1, 4000, 10, 7, 40, 0, -5, 4, 8, 1, 0);
INSERT INTO "items" VALUES (48, 'Claymore+2', 1, 9, 1, 2, 9, 2, 2, 10, 2, 1400, 0, 1, 9, 7200, 0, 4000, 10, 7, 70, 0, -5, 4, 8, 1, 0);
INSERT INTO "items" VALUES (49, 'Claymore(S.C)', 1, 9, 1, 2, 9, 0, 2, 10, 0, 1400, 0, 1, 9, 600, 0, 4000, 10, 7, 0, 0, -5, 4, 8, 1, 0);
INSERT INTO "items" VALUES (50, 'GreatSword', 1, 9, 1, 2, 10, 0, 2, 11, 0, 1000, 0, 1, 10, 500, 1, 5200, 11, 8, 0, 0, -8, 5, 8, 1, 0);
INSERT INTO "items" VALUES (51, 'GreatSword+1', 1, 9, 1, 2, 10, 1, 2, 11, 1, 1400, 0, 1, 10, 2300, 1, 5200, 11, 8, 50, 0, -8, 5, 8, 1, 0);
INSERT INTO "items" VALUES (52, 'GreatSword+2', 1, 9, 1, 2, 10, 2, 2, 11, 2, 1400, 0, 1, 10, 9200, 0, 5200, 11, 8, 70, 0, -8, 5, 8, 1, 0);
INSERT INTO "items" VALUES (53, 'GreatSword(S.C)', 1, 9, 1, 2, 10, 0, 2, 11, 0, 1400, 0, 1, 10, 700, 0, 5200, 11, 8, 0, 0, -8, 5, 8, 1, 0);
INSERT INTO "items" VALUES (54, 'Flameberge', 1, 9, 1, 2, 11, 0, 2, 12, 0, 1000, 0, 1, 11, 700, 1, 6000, 12, 10, 0, 0, -15, 10, 8, 1, 0);
INSERT INTO "items" VALUES (55, 'Flameberge+1', 1, 9, 1, 2, 11, 1, 2, 12, 1, 1400, 0, 1, 11, 3300, 1, 6000, 12, 10, 60, 0, -15, 10, 8, 1, 0);
INSERT INTO "items" VALUES (56, 'Flameberge+2', 1, 9, 1, 2, 11, 2, 2, 12, 2, 1400, 0, 1, 11, 13200, 0, 6000, 12, 10, 70, 0, -15, 10, 8, 1, 0);
INSERT INTO "items" VALUES (57, 'Flameberge(S.C)', 1, 9, 1, 2, 11, 0, 2, 12, 0, 1400, 0, 1, 11, 1000, 0, 6000, 12, 10, 0, 0, -15, 10, 8, 1, 0);
INSERT INTO "items" VALUES (59, 'LightAxe', 1, 8, 1, 1, 6, 0, 1, 7, 0, 500, 0, 15, 2, 100, 1, 1400, 22, 3, 0, 0, 0, 0, 10, 1, 0);
INSERT INTO "items" VALUES (60, 'LightAxe+1', 1, 8, 1, 1, 6, 1, 1, 7, 1, 500, 0, 15, 2, 350, 1, 1400, 22, 3, 10, 0, 0, 0, 10, 1, 0);
INSERT INTO "items" VALUES (61, 'LightAxe+2', 1, 8, 1, 1, 6, 2, 1, 7, 2, 500, 0, 15, 2, 1400, 0, 1400, 22, 3, 70, 0, 0, 0, 10, 1, 0);
INSERT INTO "items" VALUES (62, 'Tomahoc', 1, 8, 1, 2, 3, 0, 2, 4, 0, 500, 0, 15, 2, 180, 1, 1700, 22, 4, 0, 0, 0, 0, 10, 1, 0);
INSERT INTO "items" VALUES (63, 'Tomahoc+1', 1, 8, 1, 2, 3, 1, 2, 4, 1, 500, 0, 15, 2, 700, 1, 1700, 22, 4, 20, 0, 0, 0, 10, 1, 0);
INSERT INTO "items" VALUES (64, 'Tomahoc+2', 1, 8, 1, 2, 3, 2, 2, 4, 2, 500, 0, 15, 2, 2800, 0, 1700, 22, 4, 70, 0, 0, 0, 10, 1, 0);
INSERT INTO "items" VALUES (65, 'SexonAxe', 1, 8, 1, 2, 4, 0, 2, 5, 0, 700, 0, 15, 3, 200, 1, 2000, 23, 4, 0, 0, 0, 0, 10, 1, 0);
INSERT INTO "items" VALUES (66, 'SexonAxe+1', 1, 8, 1, 2, 4, 1, 2, 5, 1, 700, 0, 15, 3, 800, 1, 2000, 23, 4, 30, 0, 0, 0, 10, 1, 0);
INSERT INTO "items" VALUES (67, 'SexonAxe+2', 1, 8, 1, 2, 4, 2, 2, 5, 2, 700, 0, 15, 3, 3200, 0, 2000, 23, 4, 70, 0, 0, 0, 10, 1, 0);
INSERT INTO "items" VALUES (68, 'DoubleAxe', 1, 8, 1, 3, 3, 0, 3, 3, 0, 800, 0, 15, 0, 560, 1, 3300, 20, 5, 0, 0, 0, 0, 10, 1, 0);
INSERT INTO "items" VALUES (69, 'DoubleAxe+1', 1, 8, 1, 3, 3, 1, 3, 3, 1, 800, 0, 15, 0, 1200, 1, 3300, 20, 5, 40, 0, 0, 0, 10, 1, 0);
INSERT INTO "items" VALUES (70, 'DoubleAxe+2', 1, 8, 1, 3, 3, 2, 3, 3, 2, 800, 0, 15, 0, 4800, 0, 3300, 20, 5, 70, 0, 0, 0, 10, 1, 0);
INSERT INTO "items" VALUES (71, 'WarAxe', 1, 8, 1, 3, 5, 0, 3, 6, 0, 1000, 0, 15, 1, 700, 1, 4400, 21, 8, 0, 0, 0, 0, 10, 1, 0);
INSERT INTO "items" VALUES (72, 'WarAxe+1', 1, 8, 1, 3, 5, 1, 3, 6, 1, 1000, 0, 15, 1, 2000, 1, 4400, 21, 8, 60, 0, 0, 0, 10, 1, 0);
INSERT INTO "items" VALUES (73, 'WarAxe+2', 1, 8, 1, 3, 5, 2, 3, 6, 2, 1000, 0, 15, 1, 8000, 0, 4400, 21, 8, 70, 0, 0, 0, 10, 1, 0);
INSERT INTO "items" VALUES (74, '4BladeGoldenAxe', 1, 8, 1, 3, 6, 0, 3, 6, 0, 2000, 0, 15, 4, 52000, 0, 2000, 24, 6, 60, 0, 0, 0, 10, 1, 0);
INSERT INTO "items" VALUES (75, 'ShortBow', 1, 9, 3, 1, 6, 0, 1, 6, 0, 500, 0, 2, 0, 100, 1, 800, 40, 4, 0, 0, 5, 0, 6, 3, 0);
INSERT INTO "items" VALUES (76, 'LongBow', 1, 9, 3, 1, 7, 0, 1, 7, 0, 800, 0, 2, 1, 200, 1, 1200, 41, 5, 0, 0, 0, 5, 6, 3, 0);
INSERT INTO "items" VALUES (77, 'Arrow', 6, 0, 0, 1, 4, 0, 1, 4, 0, 1, 0, 6, 10, 1, 1, 10, 1, 3, 0, 0, 0, 0, 0, 4, 0);
INSERT INTO "items" VALUES (78, 'PoisonArrow', 6, 0, 0, 1, 8, 0, 1, 8, 0, 1, 0, 6, 10, 5, 0, 10, 1, 5, 0, 0, 0, 0, 0, 4, 0);
INSERT INTO "items" VALUES (79, 'WoodShield', 1, 7, 2, 8, 1, 1, 1, 1, 1, 300, 0, 3, 0, 100, 1, 800, 1, 0, 0, 0, 0, 0, 11, 5, 0);
INSERT INTO "items" VALUES (80, 'LeatherShield', 1, 7, 2, 10, 1, 1, 1, 1, 1, 300, 0, 3, 1, 150, 1, 1000, 2, 0, 0, 0, 0, 0, 11, 5, 0);
INSERT INTO "items" VALUES (81, 'TargeShield', 1, 7, 2, 13, 1, 1, 1, 1, 1, 500, 0, 3, 2, 250, 1, 1800, 3, 0, 0, 0, 0, 0, 11, 5, 0);
INSERT INTO "items" VALUES (82, 'ScootermShield', 1, 7, 2, 16, 1, 1, 1, 1, 1, 500, 0, 3, 3, 300, 1, 2000, 4, 0, 0, 0, 0, 0, 11, 5, 0);
INSERT INTO "items" VALUES (83, 'BlondeShield', 1, 7, 2, 18, 1, 1, 1, 1, 1, 500, 0, 3, 4, 450, 1, 2000, 5, 0, 0, 0, 0, 0, 11, 5, 0);
INSERT INTO "items" VALUES (84, 'IronShield', 1, 7, 2, 22, 1, 1, 1, 1, 1, 500, 0, 3, 5, 700, 1, 2500, 6, 0, 0, 0, -2, 0, 11, 5, 0);
INSERT INTO "items" VALUES (85, 'LagiShield', 1, 7, 2, 26, 1, 1, 1, 1, 1, 800, 0, 3, 6, 1300, 1, 3000, 7, 0, 0, 0, -4, 0, 11, 5, 0);
INSERT INTO "items" VALUES (86, 'KnightShield', 1, 7, 2, 30, 1, 1, 1, 1, 1, 800, 0, 3, 7, 1500, 1, 3200, 8, 0, 0, 0, -8, -5, 11, 5, 0);
INSERT INTO "items" VALUES (87, 'TowerShield', 1, 7, 2, 35, 1, 1, 1, 1, 1, 800, 0, 3, 8, 1800, 1, 4000, 9, 0, 0, 0, -10, -10, 11, 5, 0);
INSERT INTO "items" VALUES (88, 'GuildAdmissionTicket', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 9, 5, 1, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (89, 'GuildSecessionTicket', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 9, 5, 1, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (90, 'Gold', 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 1, 1, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (91, 'RedPotion', 7, 0, 4, 2, 12, 10, 0, 0, 0, 1, 0, 6, 1, 10, 1, 30, -1, 0, 0, 0, 0, 0, -1, 21, 0);
INSERT INTO "items" VALUES (92, 'BigRedPotion', 7, 0, 4, 3, 8, 40, 0, 0, 0, 1, 0, 6, 2, 65, 1, 100, -1, 0, 0, 0, 0, 0, -1, 21, 0);
INSERT INTO "items" VALUES (93, 'BluePotion', 7, 0, 5, 2, 12, 10, 0, 0, 0, 1, 0, 6, 3, 10, 1, 30, -1, 0, 0, 0, 0, 0, -1, 21, 0);
INSERT INTO "items" VALUES (94, 'BigBluePotion', 7, 0, 5, 4, 8, 50, 0, 0, 0, 1, 0, 6, 4, 65, 1, 100, -1, 0, 0, 0, 0, 0, -1, 21, 0);
INSERT INTO "items" VALUES (95, 'GreenPotion', 7, 0, 6, 2, 12, 10, 0, 0, 0, 1, 0, 6, 5, 10, 1, 30, -1, 0, 0, 0, 0, 0, -1, 21, 0);
INSERT INTO "items" VALUES (96, 'BigGreenPotion', 7, 0, 6, 4, 8, 50, 0, 0, 0, 1, 0, 6, 6, 65, 1, 100, -1, 0, 0, 0, 0, 0, -1, 21, 0);
INSERT INTO "items" VALUES (97, 'DilutionPotion', 3, 0, 9, 23, 20, 0, 0, 0, 0, 1, 0, 6, 5, 200, 1, 30, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (98, 'Baguette', 7, 0, 7, 2, 8, 10, 0, 0, 0, 1, 0, 6, 8, 5, 1, 17, -1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (99, 'Meat', 7, 0, 7, 4, 8, 10, 0, 0, 0, 1, 0, 6, 7, 10, 1, 52, -1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (100, 'Fish', 7, 0, 7, 4, 8, 10, 0, 0, 0, 1, 0, 6, 11, 30, 1, 30, -1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (101, 'RedFish', 7, 0, 7, 8, 4, 60, 0, 0, 0, 1, 0, 6, 14, 400, 0, 100, -1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (102, 'GreenFish', 7, 0, 7, 8, 4, 40, 0, 0, 0, 1, 0, 6, 15, 200, 0, 100, -1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (103, 'YellowFish', 7, 0, 7, 8, 4, 30, 0, 0, 0, 1, 0, 6, 16, 100, 0, 100, -1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (104, 'Map', 9, 0, 10, 1, 0, 0, 0, 0, 0, 35, 0, 6, 9, 30, 1, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (105, 'FishingRod', 8, 0, 0, 1, 8, 0, 0, 0, 0, 200, 0, 14, 0, 100, 1, 300, -1, 0, 0, 0, 0, 0, 1, 43, 0);
INSERT INTO "items" VALUES (106, 'PretendCorpseManual', 3, 0, 9, 19, 20, 0, 0, 0, 0, 0, 0, 6, 92, 100, 1, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (107, 'ArcheryManual', 3, 0, 9, 6, 20, 0, 0, 0, 0, 0, 0, 6, 92, 100, 1, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (108, 'ShieldManual', 3, 0, 9, 11, 20, 0, 0, 0, 0, 0, 0, 6, 92, 100, 1, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (109, 'LongSwordManual', 3, 0, 9, 8, 20, 0, 0, 0, 0, 0, 0, 6, 92, 100, 1, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (110, 'FencingManual', 3, 0, 9, 9, 20, 0, 0, 0, 0, 0, 0, 6, 92, 100, 1, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (111, 'FishingManual', 3, 0, 9, 1, 20, 0, 0, 0, 0, 0, 0, 6, 92, 100, 1, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (112, 'AxeManual', 3, 0, 9, 10, 20, 0, 0, 0, 0, 0, 0, 6, 92, 100, 1, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (113, 'MagicResistManual', 3, 0, 9, 3, 20, 0, 0, 0, 0, 0, 0, 6, 92, 500, 1, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (114, 'RecallScroll', 3, 0, 11, 1, 0, 0, 0, 0, 0, 1, 0, 6, 9, 120, 1, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (115, 'InvisibilityScroll', 3, 0, 11, 2, 0, 0, 0, 0, 0, 1, 0, 6, 9, 560, 1, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (116, 'DetectInviScroll', 3, 0, 11, 3, 0, 0, 0, 0, 0, 1, 0, 6, 9, 330, 1, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (117, 'BleedingIslandTicket', 3, 0, 11, 4, 1, 0, 0, 0, 0, 1, 0, 6, 9, 100, 1, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (188, 'SnakeMeat', 7, 0, 7, 4, 8, 20, 0, 0, 0, 1, 0, 6, 17, 57, 0, 45, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (189, 'SnakeSkin', 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 18, 175, 0, 20, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (190, 'SnakeTeeth', 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 19, 55, 0, 5, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (191, 'SnakeTongue', 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 20, 50, 0, 3, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (192, 'AntLeg', 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 21, 32, 0, 17, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (193, 'AntFeeler', 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 22, 34, 0, 10, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (194, 'CyclopsEye', 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 23, 170, 0, 330, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (195, 'CyclopsHandEdge', 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 24, 270, 0, 4000, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (196, 'CyclopsHeart', 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 25, 160, 0, 1230, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (197, 'CyclopsMeat', 7, 0, 7, 4, 8, 30, 0, 0, 0, 1, 0, 6, 26, 90, 0, 500, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (198, 'CyclopsLeather', 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 27, 600, 0, 350, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (199, 'HelboundHeart', 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 28, 90, 0, 820, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (200, 'HelboundLeather', 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 29, 320, 0, 200, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (201, 'HelboundTail', 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 30, 70, 0, 250, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (202, 'HelboundTeeth', 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 31, 70, 0, 130, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (203, 'HelboundClaw', 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 32, 70, 0, 280, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (204, 'HelboundTongue', 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 33, 75, 0, 150, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (205, 'LumpofClay', 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 34, 95, 0, 230, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (206, 'OrcMeat', 7, 0, 7, 2, 4, 5, 0, 0, 0, 1, 0, 6, 35, 50, 0, 100, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (207, 'OrcLeather', 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 36, 193, 0, 100, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (208, 'OrcTeeth', 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 37, 56, 0, 50, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (209, 'OgreHair', 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 38, 230, 0, 250, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (210, 'OgreHeart', 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 39, 340, 0, 1580, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (211, 'OgreMeat', 7, 0, 7, 4, 8, 50, 0, 0, 0, 1, 0, 6, 40, 200, 0, 710, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (212, 'OgreLeather', 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 41, 840, 0, 650, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (213, 'OgreTeeth', 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 42, 215, 0, 230, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (214, 'OgreClaw', 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 43, 215, 0, 370, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (215, 'ScorpionPincers', 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 44, 50, 0, 1200, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (216, 'ScorpionMeat', 7, 0, 7, 4, 8, 25, 0, 0, 0, 1, 0, 6, 45, 55, 0, 450, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (217, 'ScorpionSting', 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 46, 55, 0, 1000, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (218, 'ScorpionSkin', 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 47, 90, 0, 380, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (219, 'SkeletonBones', 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 48, 50, 0, 1300, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (220, 'SlimeJelly', 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 49, 10, 0, 100, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (221, 'StoneGolemPiece', 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 50, 50, 0, 500, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (222, 'TrollHeart', 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 51, 145, 0, 1050, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (223, 'TrollMeat', 7, 0, 7, 8, 4, 50, 0, 0, 0, 1, 0, 6, 52, 180, 0, 500, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (224, 'TrollLeather', 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 53, 335, 0, 450, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (225, 'TrollClaw', 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 54, 70, 0, 290, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (226, 'AlchemyManual', 3, 0, 9, 12, 20, 0, 0, 0, 0, 0, 0, 6, 92, 100, 1, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (227, 'AlchemyBowl', 10, 0, 0, 1, 0, 0, 0, 0, 0, 300, 0, 6, 55, 1000, 1, 700, -1, 0, 0, 0, 0, 0, -1, 21, 0);
INSERT INTO "items" VALUES (230, 'MiningManual', 3, 0, 9, 0, 20, 0, 0, 0, 0, 0, 0, 6, 92, 100, 1, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (231, 'PickAxe', 1, 8, 1, 2, 4, 0, 2, 4, 0, 1000, 0, 15, 5, 500, 1, 1000, 25, 10, 0, 0, 0, 0, 0, 1, 0);
INSERT INTO "items" VALUES (232, 'Hoe', 1, 8, 1, 2, 4, 0, 2, 4, 0, 800, 0, 15, 9, 300, 1, 1000, 27, 5, 0, 0, 0, 0, -1, 1, 0);
INSERT INTO "items" VALUES (235, 'ManufacturingManual', 3, 0, 9, 13, 20, 0, 0, 0, 0, 0, 0, 6, 92, 100, 1, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (236, 'ManufacturingHammer', 10, 0, 0, 1, 0, 0, 0, 0, 0, 300, 0, 6, 113, 1500, 1, 2000, -1, 0, 0, 0, 0, 0, -1, 21, 0);
INSERT INTO "items" VALUES (237, 'HammerAttackManual', 3, 0, 9, 14, 20, 0, 0, 0, 0, 0, 0, 6, 92, 100, 1, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (245, 'AresdenFlag(Master)', 11, 0, 16, 1, 1, 0, 0, 0, 0, 1, 0, 6, 56, 100, 0, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (246, 'ElvineFlag(Master)', 11, 0, 16, 2, 1, 0, 0, 0, 0, 1, 0, 6, 57, 100, 0, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (247, 'AresdenFlag', 11, 0, 16, 1, 0, 0, 0, 0, 0, 1, 0, 6, 56, 100, 0, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (248, 'ElvineFlag', 11, 0, 16, 2, 0, 0, 0, 0, 0, 1, 0, 6, 57, 100, 0, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (250, 'WandAttackManual', 3, 0, 9, 21, 20, 0, 0, 0, 0, 0, 0, 6, 92, 100, 1, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (256, 'MagicWand(MS20)', 1, 8, 13, 2, 4, 0, 20, 0, 0, 3600, 0, 17, 1, 5000, 1, 1000, 36, 3, 50, 0, 0, 0, 21, 8, 0);
INSERT INTO "items" VALUES (257, 'MagicWand(MS10)', 1, 8, 13, 2, 4, 0, 10, 0, 0, 2400, 0, 17, 1, 2500, 1, 1000, 36, 3, 40, 0, 0, 0, 21, 8, 0);
INSERT INTO "items" VALUES (258, 'MagicWand(MS0)', 1, 8, 13, 2, 4, 0, 0, 0, 0, 1200, 0, 17, 1, 1000, 1, 1000, 36, 3, 30, 0, 0, 0, 21, 8, 0);
INSERT INTO "items" VALUES (259, 'MagicWand(M.Shield)', 1, 8, 20, 2, 4, 0, 0, 0, 0, 5000, 30, 17, 1, 8200, 0, 1000, 36, 3, 0, 0, 0, 0, 21, 8, 0);
INSERT INTO "items" VALUES (270, 'HairColorPotion', 7, 0, 12, 1, 0, 0, 0, 0, 0, 1, 0, 6, 5, 300, 0, 100, -1, 0, 0, 0, 0, 0, -1, 21, 0);
INSERT INTO "items" VALUES (271, 'HairStylePotion', 7, 0, 12, 2, 0, 0, 0, 0, 0, 1, 0, 6, 5, 400, 0, 100, -1, 0, 0, 0, 0, 0, -1, 21, 0);
INSERT INTO "items" VALUES (272, 'SkinColorPotion', 7, 0, 12, 3, 0, 0, 0, 0, 0, 1, 0, 6, 5, 500, 0, 100, -1, 0, 0, 0, 0, 0, -1, 21, 0);
INSERT INTO "items" VALUES (273, 'InvisibilityPotion', 7, 0, 11, 2, 0, 0, 0, 0, 0, 1, 0, 6, 5, 700, 0, 100, -1, 0, 0, 0, 0, 0, -1, 21, 0);
INSERT INTO "items" VALUES (274, 'SexChangePotion', 7, 0, 12, 4, 0, 0, 0, 0, 0, 1, 0, 6, 5, 4000, 0, 100, -1, 0, 0, 0, 0, 0, -1, 21, 0);
INSERT INTO "items" VALUES (275, 'OgrePotion', 7, 0, 11, 5, 8, 0, 0, 0, 0, 1, 0, 6, 5, 5000, 0, 100, -1, 0, 0, 0, 0, 0, -1, 21, 0);
INSERT INTO "items" VALUES (276, 'UnderWearPotion', 7, 0, 12, 5, 0, 0, 0, 0, 0, 1, 0, 6, 5, 4000, 0, 100, -1, 0, 0, 0, 0, 0, -1, 21, 0);
INSERT INTO "items" VALUES (290, 'Flameberge+3(LLF)', 1, 9, 1, 2, 11, 3, 2, 12, 3, 8000, 0, 1, 11, 21000, 0, 6000, 12, 10, 0, 0, -15, 10, 8, 1, 0);
INSERT INTO "items" VALUES (291, 'MagicWand(MS30-LLF)', 1, 8, 13, 2, 4, 0, 30, 0, 0, 4800, 0, 17, 0, 10000, 0, 1000, 35, 3, 0, 0, 0, 0, 21, 8, 0);
INSERT INTO "items" VALUES (292, 'GoldenAxe(LLF)', 1, 8, 1, 2, 8, 0, 2, 8, 0, 2000, 0, 15, 4, 32000, 0, 2000, 24, 6, 0, 0, 0, 0, 10, 1, 0);
INSERT INTO "items" VALUES (300, 'MagicNecklace(RM10)', 1, 6, 14, 1, 10, 0, 0, 0, 0, 300, 0, 16, 4, 2250, 0, 400, -1, 0, 30, 0, 0, -10, -1, 46, 0);
INSERT INTO "items" VALUES (305, 'MagicNecklace(DM+1)', 1, 6, 14, 3, 1, 0, 0, 0, 0, 300, 0, 16, 5, 39800, 0, 400, -1, 0, 65, 0, 0, -10, -1, 46, 0);
INSERT INTO "items" VALUES (308, 'MagicNecklace(MS10)', 1, 6, 14, 2, 10, 0, 0, 0, 0, 300, 0, 16, 7, 7000, 0, 400, -1, 0, 50, 0, 0, -10, -1, 46, 0);
INSERT INTO "items" VALUES (311, 'MagicNecklace(DF+10)', 1, 6, 14, 4, 10, 0, 0, 0, 0, 300, 0, 16, 6, 19000, 0, 400, -1, 0, 50, 0, 0, -10, -1, 46, 0);
INSERT INTO "items" VALUES (315, 'GoldNecklace', 1, 6, 0, 0, 0, 0, 0, 0, 0, 300, 0, 16, 8, 1000, 1, 300, -1, 0, 0, 0, 0, -10, -1, 46, 0);
INSERT INTO "items" VALUES (316, 'SilverNecklace', 1, 6, 0, 0, 0, 0, 0, 0, 0, 300, 0, 16, 9, 500, 1, 300, -1, 0, 0, 0, 0, -10, -1, 46, 0);
INSERT INTO "items" VALUES (331, 'GoldRing', 1, 10, 0, 0, 0, 0, 0, 0, 0, 300, 0, 16, 14, 700, 1, 200, -1, 0, 0, 0, 0, -10, -1, 46, 0);
INSERT INTO "items" VALUES (332, 'SilverRing', 1, 10, 0, 0, 0, 0, 0, 0, 0, 300, 0, 16, 15, 350, 1, 200, -1, 0, 0, 0, 0, -10, -1, 46, 0);
INSERT INTO "items" VALUES (333, 'PlatinumRing', 1, 10, 0, 0, 0, 0, 0, 0, 0, 300, 0, 16, 15, 750, 0, 200, -1, 0, 0, 0, 0, -10, -1, 46, 0);
INSERT INTO "items" VALUES (334, 'LuckyGoldRing', 1, 10, 14, 5, 0, 0, 0, 0, 0, 300, 0, 16, 13, 2750, 0, 200, -1, 0, 0, 0, 0, -10, -1, 46, 0);
INSERT INTO "items" VALUES (335, 'EmeraldRing', 1, 10, 15, 0, 0, 0, 0, 0, 0, 9000, 0, 16, 10, 2500, 0, 200, -1, 0, 0, 0, 0, -10, -1, 46, 0);
INSERT INTO "items" VALUES (336, 'SapphireRing', 1, 10, 0, 0, 0, 0, 0, 0, 0, 5000, 0, 16, 11, 2450, 0, 200, -1, 0, 0, 0, 0, -10, -1, 46, 0);
INSERT INTO "items" VALUES (337, 'RubyRing', 1, 10, 15, 0, 0, 0, 0, 0, 0, 5000, 0, 16, 12, 1800, 0, 200, -1, 0, 0, 0, 0, -10, -1, 46, 0);
INSERT INTO "items" VALUES (338, 'MemorialRing', 1, 10, 0, 0, 0, 0, 0, 0, 0, 300, 0, 16, 12, 1000, 0, 200, -1, 0, 0, 0, 0, -10, -1, 46, 0);
INSERT INTO "items" VALUES (350, 'Diamond', 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 16, 42, 3000, 0, 200, 1, 0, 0, 0, 0, 0, -1, 46, 0);
INSERT INTO "items" VALUES (351, 'Ruby', 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 16, 43, 2000, 0, 200, 1, 0, 0, 0, 0, 0, -1, 46, 0);
INSERT INTO "items" VALUES (352, 'Sapphire', 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 16, 44, 2000, 0, 200, 1, 0, 0, 0, 0, 0, -1, 46, 0);
INSERT INTO "items" VALUES (353, 'Emerald', 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 16, 45, 2000, 0, 200, 1, 0, 0, 0, 0, 0, -1, 46, 0);
INSERT INTO "items" VALUES (354, 'GoldNugget', 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 16, 21, 300, 0, 300, 1, 0, 0, 0, 0, 0, -1, 46, 0);
INSERT INTO "items" VALUES (355, 'Coal', 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 16, 22, 50, 0, 180, 1, 0, 0, 0, 0, 0, -1, 46, 0);
INSERT INTO "items" VALUES (356, 'SilverNugget', 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 16, 23, 200, 0, 220, 1, 0, 0, 0, 0, 0, -1, 46, 0);
INSERT INTO "items" VALUES (357, 'IronOre', 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 16, 24, 100, 0, 250, 1, 0, 0, 0, 0, 0, -1, 46, 0);
INSERT INTO "items" VALUES (358, 'Crystal', 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 16, 46, 300, 0, 200, 1, 0, 0, 0, 0, 0, -1, 46, 0);
INSERT INTO "items" VALUES (360, 'Dye(Indigo)', 11, 0, 17, 1, 0, 0, 0, 0, 0, 1, 0, 6, 58, 100, 1, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (361, 'Dye(Crimson-Red)', 11, 0, 17, 2, 0, 0, 0, 0, 0, 1, 0, 6, 58, 100, 0, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (362, 'Dye(Brown)', 11, 0, 17, 3, 0, 0, 0, 0, 0, 1, 0, 6, 58, 100, 0, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (363, 'Dye(Gold)', 11, 0, 17, 4, 0, 0, 0, 0, 0, 1, 0, 6, 58, 100, 0, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (364, 'Dye(Green)', 11, 0, 17, 5, 0, 0, 0, 0, 0, 1, 0, 6, 62, 100, 1, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (365, 'Dye(Gray)', 11, 0, 17, 6, 0, 0, 0, 0, 0, 1, 0, 6, 63, 100, 1, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (366, 'Dye(Aqua)', 11, 0, 17, 7, 0, 0, 0, 0, 0, 1, 0, 6, 58, 100, 1, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (367, 'Dye(Pink)', 11, 0, 17, 8, 0, 0, 0, 0, 0, 1, 0, 6, 58, 100, 0, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (368, 'Dye(Violet)', 11, 0, 17, 9, 0, 0, 0, 0, 0, 1, 0, 6, 66, 100, 1, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (369, 'Dye(Blue)', 11, 0, 17, 10, 0, 0, 0, 0, 0, 1, 0, 6, 67, 100, 1, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (370, 'Dye(Tan)', 11, 0, 17, 11, 0, 0, 0, 0, 0, 1, 0, 6, 68, 100, 1, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (371, 'Dye(Khaki)', 11, 0, 17, 12, 0, 0, 0, 0, 0, 1, 0, 6, 69, 100, 1, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (372, 'Dye(Yellow)', 11, 0, 17, 13, 0, 0, 0, 0, 0, 1, 0, 6, 70, 100, 1, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (373, 'Dye(Red)', 11, 0, 17, 14, 0, 0, 0, 0, 0, 1, 0, 6, 71, 100, 1, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (374, 'Dye(Black)', 11, 0, 17, 15, 0, 0, 0, 0, 0, 1, 0, 6, 58, 100, 0, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (375, 'DecolorationPotion', 11, 0, 17, 0, 0, 0, 0, 0, 0, 1, 0, 6, 58, 100, 1, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (380, 'IceStormManual', 3, 0, 18, 55, 0, 0, 0, 0, 0, 0, 0, 6, 91, 100, 0, 1, -1, 0, 0, 0, 0, 0, -1, 42, 1);
INSERT INTO "items" VALUES (381, 'MassFireStrikeManual', 3, 0, 18, 61, 0, 0, 0, 0, 0, 0, 0, 6, 91, 100, 0, 1, -1, 0, 0, 0, 0, 0, -1, 42, 2);
INSERT INTO "items" VALUES (382, 'BloodyShockW.Manual', 3, 0, 18, 70, 0, 0, 0, 0, 0, 0, 0, 6, 91, 100, 0, 1, -1, 0, 0, 0, 0, 0, -1, 42, 2);
INSERT INTO "items" VALUES (385, 'HandAttackManual', 3, 0, 9, 5, 20, 0, 0, 0, 0, 0, 0, 6, 92, 100, 1, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (386, 'ShortSwordManual', 3, 0, 9, 7, 20, 0, 0, 0, 0, 0, 0, 6, 92, 100, 1, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (390, 'PowerGreenPotion', 7, 0, 22, 300, 0, 0, 0, 0, 0, 1, 0, 6, 5, 600, 0, 30, -1, 0, 0, 0, 0, 0, -1, 21, 0);
INSERT INTO "items" VALUES (391, 'SuperGreenPotion', 7, 0, 22, 600, 0, 0, 0, 0, 0, 1, 0, 6, 5, 1200, 0, 30, -1, 0, 0, 0, 0, 0, -1, 21, 0);
INSERT INTO "items" VALUES (400, 'AresdenHeroCape', 1, 12, 2, 2, 1, 1, 1, 1, 1, 300, 0, 20, 0, 2000, 0, 200, 1, 0, 0, 0, 0, 0, -1, 13, 0);
INSERT INTO "items" VALUES (401, 'ElvineHeroCape', 1, 12, 2, 2, 1, 1, 1, 1, 1, 300, 0, 20, 1, 2000, 0, 200, 2, 0, 0, 0, 0, 0, -1, 13, 0);
INSERT INTO "items" VALUES (402, 'Cape', 1, 12, 2, 2, 1, 1, 1, 1, 1, 300, 0, 20, 2, 1000, 1, 200, 3, 0, 0, 0, 0, 0, -1, 12, 0);
INSERT INTO "items" VALUES (403, 'aHeroHelm(M)', 1, 1, 2, 18, 24, 0, 0, 0, 0, 2500, 0, 21, 7, 16000, 0, 10000, 10, 0, 0, 1, -7, -7, -1, 6, 0);
INSERT INTO "items" VALUES (404, 'aHeroHelm(W)', 1, 1, 2, 18, 24, 0, 0, 0, 0, 2500, 0, 21, 7, 16000, 0, 10000, 10, 0, 0, 2, -7, -7, -1, 6, 0);
INSERT INTO "items" VALUES (405, 'eHeroHelm(M)', 1, 1, 2, 18, 24, 0, 0, 0, 0, 2500, 0, 21, 6, 16000, 0, 10000, 9, 0, 0, 1, -7, -7, -1, 6, 0);
INSERT INTO "items" VALUES (406, 'eHeroHelm(W)', 1, 1, 2, 18, 24, 0, 0, 0, 0, 2500, 0, 21, 6, 16000, 0, 10000, 9, 0, 0, 2, -7, -7, -1, 6, 0);
INSERT INTO "items" VALUES (407, 'aHeroCap(M)', 1, 1, 2, 12, 15, 0, 0, 0, 0, 1500, 0, 21, 9, 12000, 0, 1500, 12, 0, 0, 1, -7, -7, -1, 6, 0);
INSERT INTO "items" VALUES (408, 'aHeroCap(W)', 1, 1, 2, 12, 15, 0, 0, 0, 0, 1500, 0, 21, 9, 12000, 0, 1500, 12, 0, 0, 2, -7, -7, -1, 6, 0);
INSERT INTO "items" VALUES (409, 'eHeroCap(M)', 1, 1, 2, 12, 15, 0, 0, 0, 0, 1500, 0, 21, 8, 12000, 0, 1500, 11, 0, 0, 1, -7, -7, -1, 6, 0);
INSERT INTO "items" VALUES (410, 'eHeroCap(W)', 1, 1, 2, 12, 15, 0, 0, 0, 0, 1500, 0, 21, 8, 12000, 0, 1500, 11, 0, 0, 2, -7, -7, -1, 6, 0);
INSERT INTO "items" VALUES (411, 'aHeroArmor(M)', 1, 2, 2, 45, 48, 0, 0, 0, 0, 5000, 0, 9, 8, 40000, 0, 10000, 9, 0, 0, 1, -5, -5, 0, 6, 0);
INSERT INTO "items" VALUES (412, 'aHeroArmor(W)', 1, 2, 2, 45, 48, 0, 0, 0, 0, 5000, 0, 13, 9, 40000, 0, 10000, 10, 0, 0, 2, -5, -5, 0, 6, 0);
INSERT INTO "items" VALUES (413, 'eHeroArmor(M)', 1, 2, 2, 45, 48, 0, 0, 0, 0, 5000, 0, 9, 7, 40000, 0, 10000, 8, 0, 0, 1, -5, -5, 0, 6, 0);
INSERT INTO "items" VALUES (414, 'eHeroArmor(W)', 1, 2, 2, 45, 48, 0, 0, 0, 0, 5000, 0, 13, 8, 40000, 0, 10000, 9, 0, 0, 2, -5, -5, 0, 6, 0);
INSERT INTO "items" VALUES (415, 'aHeroRobe(M)', 1, 2, 2, 20, 20, 0, 0, 0, 0, 4000, 0, 9, 10, 30000, 0, 1500, 11, 0, 0, 1, 0, 0, 0, 13, 0);
INSERT INTO "items" VALUES (416, 'aHeroRobe(W)', 1, 2, 2, 20, 20, 0, 0, 0, 0, 4000, 0, 13, 11, 30000, 0, 1500, 12, 0, 0, 2, 0, 0, 0, 13, 0);
INSERT INTO "items" VALUES (417, 'eHeroRobe(M)', 1, 2, 2, 20, 20, 0, 0, 0, 0, 4000, 0, 9, 9, 30000, 0, 1500, 10, 0, 0, 1, 0, 0, 0, 13, 0);
INSERT INTO "items" VALUES (418, 'eHeroRobe(W)', 1, 2, 2, 20, 20, 0, 0, 0, 0, 4000, 0, 13, 10, 30000, 0, 1500, 11, 0, 0, 2, 0, 0, 0, 13, 0);
INSERT INTO "items" VALUES (419, 'aHeroHauberk(M)', 1, 3, 2, 15, 15, 0, 0, 0, 0, 2000, 0, 7, 3, 14000, 0, 1500, 4, 0, 0, 1, -3, -3, 0, 6, 0);
INSERT INTO "items" VALUES (420, 'aHeroHauberk(W)', 1, 3, 2, 15, 15, 0, 0, 0, 0, 2000, 0, 11, 4, 14000, 0, 1500, 5, 0, 0, 2, -3, -3, 0, 6, 0);
INSERT INTO "items" VALUES (421, 'eHeroHauberk(M)', 1, 3, 2, 15, 15, 0, 0, 0, 0, 2000, 0, 7, 2, 14000, 0, 1500, 3, 0, 0, 1, -3, -3, 0, 6, 0);
INSERT INTO "items" VALUES (422, 'eHeroHauberk(W)', 1, 3, 2, 15, 15, 0, 0, 0, 0, 2000, 0, 11, 3, 14000, 0, 1500, 4, 0, 0, 2, -3, -3, 0, 6, 0);
INSERT INTO "items" VALUES (423, 'aHeroLeggings(M)', 1, 4, 2, 18, 25, 1, 1, 1, 1, 3000, 0, 8, 5, 22000, 0, 1500, 6, 0, 0, 1, -6, -6, 0, 6, 0);
INSERT INTO "items" VALUES (424, 'aHeroLeggings(W)', 1, 4, 2, 18, 25, 1, 1, 1, 1, 3000, 0, 12, 6, 22000, 0, 1500, 7, 0, 0, 2, -6, -6, 0, 6, 0);
INSERT INTO "items" VALUES (425, 'eHeroLeggings(M)', 1, 4, 2, 18, 25, 1, 1, 1, 1, 3000, 0, 8, 4, 22000, 0, 1500, 5, 0, 0, 1, -6, -6, 0, 6, 0);
INSERT INTO "items" VALUES (426, 'eHeroLeggings(W)', 1, 4, 2, 18, 25, 1, 1, 1, 1, 3000, 0, 12, 5, 22000, 0, 1500, 6, 0, 0, 2, -6, -6, 0, 6, 0);
INSERT INTO "items" VALUES (427, 'AresdenHeroCape+1', 1, 12, 2, 2, 1, 1, 1, 1, 1, 300, 0, 20, 3, 2000, 0, 200, 4, 0, 0, 0, 0, 0, -1, 13, 0);
INSERT INTO "items" VALUES (428, 'ElvineHeroCape+1', 1, 12, 2, 2, 1, 1, 1, 1, 1, 300, 0, 20, 4, 2000, 0, 200, 5, 0, 0, 0, 0, 0, -1, 13, 0);
INSERT INTO "items" VALUES (429, 'Cape+1', 1, 12, 2, 2, 1, 1, 1, 1, 1, 300, 0, 20, 5, 1000, 1, 200, 6, 0, 0, 0, 0, 0, -1, 12, 0);
INSERT INTO "items" VALUES (450, 'Shoes', 1, 5, 2, 1, 1, 1, 1, 1, 1, 300, 0, 5, 0, 20, 1, 200, 1, 0, 0, 0, 0, 0, 0, 12, 0);
INSERT INTO "items" VALUES (451, 'LongBoots', 1, 5, 2, 1, 1, 1, 1, 1, 1, 300, 0, 5, 1, 100, 1, 500, 2, 0, 0, 0, 0, 0, 0, 12, 0);
INSERT INTO "items" VALUES (453, 'Shirt(M)', 1, 3, 2, 1, 1, 1, 1, 1, 1, 300, 0, 7, 0, 20, 1, 100, 1, 0, 0, 1, 0, 0, 0, 11, 0);
INSERT INTO "items" VALUES (454, 'Hauberk(M)', 1, 3, 2, 8, 10, 0, 0, 0, 0, 300, 0, 7, 1, 400, 1, 1200, 2, 0, 0, 1, -3, -3, 0, 6, 0);
INSERT INTO "items" VALUES (455, 'LeatherArmor(M)', 1, 2, 2, 10, 10, 0, 0, 0, 0, 400, 0, 9, 0, 500, 1, 1500, 1, 0, 0, 1, -5, -5, 0, 6, 0);
INSERT INTO "items" VALUES (456, 'ChainMail(M)', 1, 2, 2, 30, 32, 0, 0, 0, 0, 1000, 0, 9, 1, 1200, 1, 3000, 2, 0, 0, 1, -12, -12, 0, 6, 0);
INSERT INTO "items" VALUES (457, 'ScaleMail(M)', 1, 2, 2, 20, 20, 0, 0, 0, 0, 600, 0, 9, 2, 900, 1, 2000, 3, 0, 0, 1, -8, -8, 0, 6, 0);
INSERT INTO "items" VALUES (458, 'PlateMail(M)', 1, 2, 2, 37, 40, 0, 0, 0, 0, 3000, 0, 9, 3, 4500, 1, 10000, 4, 0, 0, 1, -10, -10, 0, 6, 0);
INSERT INTO "items" VALUES (459, 'Trousers(M)', 1, 4, 2, 1, 1, 1, 1, 1, 1, 300, 0, 8, 0, 80, 1, 100, 1, 0, 0, 1, 0, 0, 0, 11, 0);
INSERT INTO "items" VALUES (460, 'KneeTrousers(M)', 1, 4, 2, 1, 1, 1, 1, 1, 1, 300, 0, 8, 1, 20, 1, 100, 2, 0, 0, 1, 0, 0, 0, 11, 0);
INSERT INTO "items" VALUES (461, 'ChainHose(M)', 1, 4, 2, 6, 10, 1, 1, 1, 1, 500, 0, 8, 2, 400, 1, 1000, 3, 0, 0, 1, -3, -3, 0, 6, 0);
INSERT INTO "items" VALUES (462, 'PlateLeggings(M)', 1, 4, 2, 12, 20, 1, 1, 1, 1, 1000, 0, 8, 3, 1000, 1, 2000, 4, 0, 0, 1, -6, -6, 0, 6, 0);
INSERT INTO "items" VALUES (470, 'Chemise(W)', 1, 3, 2, 1, 1, 1, 1, 1, 1, 300, 0, 11, 0, 200, 1, 100, 1, 0, 0, 2, 0, 0, 0, 11, 0);
INSERT INTO "items" VALUES (471, 'Shirt(W)', 1, 3, 2, 1, 1, 1, 1, 1, 1, 300, 0, 11, 1, 20, 1, 100, 2, 0, 0, 2, 0, 0, 0, 11, 0);
INSERT INTO "items" VALUES (472, 'Hauberk(W)', 1, 3, 2, 8, 10, 0, 0, 0, 0, 300, 0, 11, 2, 400, 1, 1200, 3, 0, 0, 2, -3, -3, 0, 6, 0);
INSERT INTO "items" VALUES (473, 'Bodice(W)', 1, 2, 2, 1, 1, 1, 1, 1, 1, 400, 0, 13, 0, 150, 1, 200, 1, 0, 0, 2, -1, -1, 0, 11, 0);
INSERT INTO "items" VALUES (474, 'LongBodice(W)', 1, 2, 2, 1, 1, 1, 1, 1, 1, 400, 0, 13, 1, 180, 1, 200, 2, 0, 0, 2, -1, -1, 0, 11, 0);
INSERT INTO "items" VALUES (475, 'LeatherArmor(W)', 1, 2, 2, 10, 10, 0, 0, 0, 0, 400, 0, 13, 2, 500, 1, 1500, 3, 0, 0, 2, -5, -5, 0, 6, 0);
INSERT INTO "items" VALUES (476, 'ChainMail(W)', 1, 2, 2, 30, 32, 0, 0, 0, 0, 1000, 0, 13, 3, 1200, 1, 3000, 4, 0, 0, 2, -12, -12, 0, 6, 0);
INSERT INTO "items" VALUES (477, 'ScaleMail(W)', 1, 2, 2, 20, 20, 0, 0, 0, 0, 600, 0, 13, 4, 900, 1, 2000, 5, 0, 0, 2, -8, -8, 0, 6, 0);
INSERT INTO "items" VALUES (478, 'PlateMail(W)', 1, 2, 2, 37, 40, 0, 0, 0, 0, 3000, 0, 13, 5, 4500, 1, 10000, 6, 0, 0, 2, -10, -10, 0, 6, 0);
INSERT INTO "items" VALUES (479, 'Skirt(W)', 1, 4, 2, 1, 1, 1, 1, 1, 1, 300, 0, 12, 0, 200, 1, 100, 1, 0, 0, 2, 0, 0, 0, 11, 0);
INSERT INTO "items" VALUES (480, 'Trousers(W)', 1, 4, 2, 1, 1, 1, 1, 1, 1, 300, 0, 12, 1, 80, 1, 100, 2, 0, 0, 2, 0, 0, 0, 11, 0);
INSERT INTO "items" VALUES (481, 'KneeTrousers(W)', 1, 4, 2, 1, 1, 1, 1, 1, 1, 300, 0, 12, 2, 20, 1, 100, 3, 0, 0, 2, 0, 0, 0, 11, 0);
INSERT INTO "items" VALUES (482, 'ChainHose(W)', 1, 4, 2, 6, 10, 1, 1, 1, 1, 500, 0, 12, 3, 400, 1, 1000, 4, 0, 0, 2, -3, -3, 0, 6, 0);
INSERT INTO "items" VALUES (483, 'PlateLeggings(W)', 1, 4, 2, 12, 20, 1, 1, 1, 1, 1000, 0, 12, 4, 1000, 1, 2000, 5, 0, 0, 2, -6, -6, 0, 6, 0);
INSERT INTO "items" VALUES (484, 'Tunic(M)', 1, 2, 2, 3, 1, 1, 1, 1, 1, 300, 0, 9, 4, 350, 1, 500, 5, 0, 0, 1, 0, 0, 0, 11, 0);
INSERT INTO "items" VALUES (490, 'BloodSword', 1, 9, 19, 4, 7, 1, 4, 7, 1, 8000, 5, 1, 7, 31000, 0, 13100, 8, 11, 0, 0, 0, 0, 8, 1, 9);
INSERT INTO "items" VALUES (491, 'BloodAxe', 1, 8, 19, 3, 6, 2, 3, 6, 2, 5000, 5, 15, 1, 25000, 0, 6100, 21, 8, 0, 0, 0, 0, 10, 1, 9);
INSERT INTO "items" VALUES (492, 'BloodRapier', 1, 8, 19, 2, 5, 2, 2, 5, 2, 5000, 5, 1, 6, 25000, 0, 1100, 7, 3, 0, 0, 0, 0, 9, 1, 9);
INSERT INTO "items" VALUES (500, 'IronIngot', 12, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 76, 500, 0, 500, 1, 0, 0, 0, 0, 0, -1, 46, 0);
INSERT INTO "items" VALUES (501, 'SuperCoal', 12, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 88, 200, 0, 500, 1, 0, 0, 0, 0, 0, -1, 46, 0);
INSERT INTO "items" VALUES (502, 'UltraCoal', 12, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 88, 500, 0, 500, 1, 0, 0, 0, 0, 0, -1, 46, 0);
INSERT INTO "items" VALUES (503, 'GoldIngot', 12, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 74, 3000, 0, 500, 1, 0, 0, 0, 0, 0, -1, 46, 0);
INSERT INTO "items" VALUES (504, 'SilverIngot', 12, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 75, 2000, 0, 500, 1, 0, 0, 0, 0, 0, -1, 46, 0);
INSERT INTO "items" VALUES (505, 'BlondeIngot', 12, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 77, 1000, 0, 500, 1, 0, 0, 0, 0, 0, -1, 46, 0);
INSERT INTO "items" VALUES (506, 'MithralIngot', 12, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 78, 6000, 0, 800, 1, 0, 0, 0, 0, 0, -1, 46, 0);
INSERT INTO "items" VALUES (507, 'BlondeStone', 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 79, 160, 0, 180, 1, 0, 0, 0, 0, 0, -1, 46, 0);
INSERT INTO "items" VALUES (508, 'Mithral', 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 80, 50, 0, 180, 1, 0, 0, 0, 0, 0, -1, 46, 0);
INSERT INTO "items" VALUES (511, 'ArenaTicket', 3, 0, 11, 4, 11, 0, 0, 0, 0, 1, 0, 6, 89, 100, 0, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (513, 'ArenaTicket(2)', 3, 0, 11, 4, 12, 0, 0, 0, 0, 1, 0, 6, 89, 100, 0, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (515, 'ArenaTicket(3)', 3, 0, 11, 4, 13, 0, 0, 0, 0, 1, 0, 6, 89, 100, 0, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (517, 'ArenaTicket(4)', 3, 0, 11, 4, 14, 0, 0, 0, 0, 1, 0, 6, 89, 100, 0, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (520, 'Bouquette', 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 81, 1000, 1, 180, 1, 0, 0, 0, 0, 0, -1, 46, 0);
INSERT INTO "items" VALUES (521, 'FlowerBasket', 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 82, 1500, 1, 180, 1, 0, 0, 0, 0, 0, -1, 46, 0);
INSERT INTO "items" VALUES (522, 'Flowerpot', 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 83, 500, 1, 180, 1, 0, 0, 0, 0, 0, -1, 46, 0);
INSERT INTO "items" VALUES (530, 'ArenaTicket(5)', 3, 0, 11, 4, 15, 0, 0, 0, 0, 1, 0, 6, 89, 10, 0, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (531, 'ArenaTicket(6)', 3, 0, 11, 4, 16, 0, 0, 0, 0, 1, 0, 6, 89, 10, 0, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (532, 'ArenaTicket(7)', 3, 0, 11, 4, 17, 0, 0, 0, 0, 1, 0, 6, 89, 10, 0, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (533, 'ArenaTicket(8)', 3, 0, 11, 4, 18, 0, 0, 0, 0, 1, 0, 6, 89, 10, 0, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (534, 'ArenaTicket(9)', 3, 0, 11, 4, 19, 0, 0, 0, 0, 1, 0, 6, 89, 10, 0, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (540, 'DemonEye', 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 93, 3000, 0, 530, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (541, 'DemonHeart', 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 94, 5000, 0, 1500, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (542, 'DemonMeat', 7, 0, 7, 4, 8, 50, 0, 0, 0, 1, 0, 6, 95, 2000, 0, 1200, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (543, 'DemonLeather', 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 96, 6000, 0, 900, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (544, 'UnicornHeart', 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 97, 5000, 0, 230, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (545, 'UnicornHorn', 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 98, 50000, 0, 250, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (546, 'UnicornMeat', 7, 0, 7, 4, 8, 50, 0, 0, 0, 1, 0, 6, 99, 2000, 0, 500, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (547, 'UnicornLeather', 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 100, 6000, 0, 650, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (548, 'WerewolfHeart', 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 101, 210, 0, 350, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (549, 'WerewolfNail', 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 102, 140, 0, 290, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (550, 'WerewolfMeat', 7, 0, 7, 8, 4, 50, 0, 0, 0, 1, 0, 6, 103, 250, 0, 500, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (551, 'WerewolfTail', 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 104, 300, 0, 550, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (552, 'WerewolfTeeth', 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 105, 140, 0, 290, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (553, 'WerewolfLeather', 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 106, 820, 0, 450, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (554, 'WerewolfClaw', 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 107, 140, 0, 290, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (560, 'BattleAxe', 1, 9, 1, 3, 8, 0, 3, 9, 0, 1500, 0, 15, 6, 3500, 1, 9000, 26, 13, 0, 0, 0, 0, 10, 1, 0);
INSERT INTO "items" VALUES (570, 'RedCarp', 7, 0, 7, 8, 4, 30, 0, 0, 0, 1, 0, 6, 14, 1200, 0, 100, -1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (571, 'GreenCarp', 7, 0, 7, 8, 4, 40, 0, 0, 0, 1, 0, 6, 15, 1500, 0, 100, -1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (572, 'GoldCarp', 7, 0, 7, 8, 4, 60, 0, 0, 0, 1, 0, 6, 16, 3000, 0, 100, -1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (573, 'CrucianCarp', 7, 0, 7, 8, 4, 0, 0, 0, 0, 1, 0, 6, 12, 200, 0, 30, -1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (574, 'BlueSeaBream', 7, 0, 7, 8, 4, 50, 0, 0, 0, 1, 0, 6, 84, 2000, 0, 80, -1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (575, 'Salmon', 7, 0, 7, 8, 4, 10, 0, 0, 0, 1, 0, 6, 85, 800, 0, 50, -1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (576, 'RedSeaBream', 7, 0, 7, 8, 4, 50, 0, 0, 0, 1, 0, 6, 86, 2000, 0, 80, -1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (577, 'GrayMullet', 7, 0, 7, 8, 4, 5, 0, 0, 0, 1, 0, 6, 87, 500, 0, 50, -1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (580, 'BattleAxe+1', 1, 9, 1, 3, 8, 1, 3, 9, 1, 2000, 0, 15, 6, 6000, 1, 9000, 26, 13, 110, 0, 0, 0, 10, 1, 0);
INSERT INTO "items" VALUES (581, 'BattleAxe+2', 1, 9, 1, 3, 8, 2, 3, 9, 2, 4000, 0, 15, 6, 48000, 0, 9000, 26, 13, 0, 0, 0, 0, 10, 1, 0);
INSERT INTO "items" VALUES (582, 'Sabre+2', 1, 8, 1, 1, 8, 2, 1, 8, 2, 1000, 0, 1, 3, 2400, 0, 1200, 4, 5, 20, 0, -1, 0, 8, 1, 0);
INSERT INTO "items" VALUES (590, 'Robe(M)', 1, 2, 2, 12, 1, 0, 14, 100, 0, 3000, 0, 9, 5, 2000, 1, 1000, 6, 0, 0, 1, 0, 0, 0, 11, 0);
INSERT INTO "items" VALUES (591, 'Robe(W)', 1, 2, 2, 12, 1, 0, 14, 100, 0, 3000, 0, 13, 6, 2000, 1, 1000, 7, 0, 0, 2, 0, 0, 0, 11, 0);
INSERT INTO "items" VALUES (600, 'Helm(M)', 1, 1, 2, 5, 10, 0, 0, 0, 0, 1500, 0, 21, 0, 800, 1, 5200, 4, 0, 0, 1, -4, -4, -1, 6, 0);
INSERT INTO "items" VALUES (601, 'FullHelm(M)', 1, 1, 2, 10, 20, 0, 0, 0, 0, 2000, 0, 21, 1, 1500, 1, 8500, 1, 0, 0, 1, -7, -7, -1, 6, 0);
INSERT INTO "items" VALUES (602, 'Helm(W)', 1, 1, 2, 5, 10, 0, 0, 0, 0, 1500, 0, 21, 0, 800, 1, 5200, 4, 0, 0, 2, -4, -4, -1, 6, 0);
INSERT INTO "items" VALUES (603, 'FullHelm(W)', 1, 1, 2, 10, 20, 0, 0, 0, 0, 2000, 0, 21, 1, 1500, 1, 8500, 1, 0, 0, 2, -7, -7, -1, 6, 0);
INSERT INTO "items" VALUES (610, 'XelimaBlade', 1, 9, 24, 2, 11, 2, 2, 12, 2, 8000, 1, 1, 13, 31000, 0, 12000, 11, 11, 0, 0, 60, 0, 8, 1, 0);
INSERT INTO "items" VALUES (611, 'XelimaAxe', 1, 9, 24, 3, 8, 1, 3, 9, 1, 5000, 1, 1, 12, 31000, 0, 12000, 26, 13, 0, 0, 60, 0, 10, 1, 0);
INSERT INTO "items" VALUES (612, 'XelimaRapier', 1, 8, 24, 2, 6, 1, 2, 6, 1, 5000, 1, 1, 14, 25000, 0, 1100, 7, 3, 0, 0, 60, 0, 9, 1, 0);
INSERT INTO "items" VALUES (613, 'SwordofMedusa', 1, 9, 24, 2, 11, 2, 2, 12, 2, 7000, 3, 1, 16, 31000, 0, 10000, 11, 10, 0, 0, 60, 0, 8, 1, 0);
INSERT INTO "items" VALUES (614, 'SwordofIceElemental', 1, 9, 24, 2, 11, 2, 2, 12, 2, 7000, 2, 1, 15, 31000, 0, 10000, 11, 10, 0, 0, 60, 0, 8, 1, 0);
INSERT INTO "items" VALUES (615, 'GiantSword', 1, 9, 1, 2, 11, 3, 2, 12, 3, 1500, 0, 1, 18, 8000, 1, 13000, 13, 12, 100, 0, 0, 0, 8, 1, 0);
INSERT INTO "items" VALUES (616, 'DemonSlayer', 1, 9, 1, 4, 7, 2, 4, 8, 2, 5000, 0, 1, 17, 25000, 0, 12000, 13, 12, 0, 0, 0, 0, 8, 1, 9);
INSERT INTO "items" VALUES (617, 'CompositeBow', 1, 9, 3, 1, 6, 0, 1, 6, 0, 1200, 0, 2, 2, 3000, 1, 4000, 41, 5, 70, 0, 0, 0, 6, 3, 0);
INSERT INTO "items" VALUES (618, 'DarkElfBow', 1, 9, 3, 2, 7, 0, 2, 7, 0, 2500, 0, 2, 3, 8000, 0, 8000, 40, 4, 0, 0, 0, 0, 6, 3, 0);
INSERT INTO "items" VALUES (620, 'MerienShield', 1, 7, 25, 50, 1, 1, 1, 1, 1, 1600, 52, 3, 9, 45000, 0, 4000, 9, 0, 0, 0, 60, 0, 11, 5, 0);
INSERT INTO "items" VALUES (621, 'MerienPlateMailM', 1, 2, 25, 60, 45, 0, 0, 0, 0, 5000, 50, 9, 3, 45000, 0, 10000, 4, 0, 0, 1, 60, 0, 0, 6, 5);
INSERT INTO "items" VALUES (622, 'MerienPlateMailW', 1, 2, 25, 60, 45, 0, 0, 0, 0, 5000, 50, 13, 5, 45000, 0, 10000, 6, 0, 0, 2, 60, 0, 0, 6, 5);
INSERT INTO "items" VALUES (623, 'GM-Shield', 1, 7, 25, 50, 1, 1, 1, 1, 1, 1600, 53, 3, 7, 1000, 0, 1000, 8, 0, 0, 0, 60, 0, 11, 5, 0);
INSERT INTO "items" VALUES (630, 'RingoftheXelima', 1, 10, 14, 3, 7, 0, 0, 0, 0, 300, 0, 16, 25, 10000, 0, 500, -1, 0, 0, 0, 0, 0, -1, 46, 0);
INSERT INTO "items" VALUES (631, 'RingoftheAbaddon', 1, 10, 14, 3, 10, 0, 0, 0, 0, 300, 0, 16, 26, 19000, 0, 500, -1, 0, 0, 0, 0, 0, -1, 46, 0);
INSERT INTO "items" VALUES (632, 'RingofOgrepower', 1, 10, 14, 3, 2, 0, 0, 0, 0, 300, 0, 16, 29, 10000, 0, 500, -1, 0, 0, 0, 0, 0, -1, 46, 0);
INSERT INTO "items" VALUES (633, 'RingofDemonpower', 1, 10, 14, 3, 4, 0, 0, 0, 0, 300, 0, 16, 28, 10000, 0, 500, -1, 0, 0, 0, 0, 0, -1, 46, 0);
INSERT INTO "items" VALUES (634, 'RingofWizard', 1, 10, 14, 6, 1, 0, 0, 0, 0, 300, 0, 16, 30, 10000, 0, 500, -1, 0, 0, 0, 0, 0, -1, 46, 0);
INSERT INTO "items" VALUES (635, 'RingofMage', 1, 10, 14, 6, 2, 0, 0, 0, 0, 300, 0, 16, 31, 10000, 0, 500, -1, 0, 0, 0, 0, 0, -1, 46, 0);
INSERT INTO "items" VALUES (636, 'RingofGrandMage', 1, 10, 14, 6, 3, 0, 0, 0, 0, 300, 0, 16, 32, 10000, 0, 500, -1, 0, 0, 0, 0, 0, -1, 46, 0);
INSERT INTO "items" VALUES (637, 'KnecklaceOfLightPro', 1, 6, 14, 7, 25, 0, 0, 0, 0, 300, 0, 16, 33, 20000, 0, 1000, -1, 0, 0, 0, 0, 0, -1, 46, 0);
INSERT INTO "items" VALUES (638, 'KnecklaceOfFirePro', 1, 6, 14, 9, 25, 0, 0, 0, 0, 300, 0, 16, 34, 20000, 0, 1000, -1, 0, 0, 0, 0, 0, -1, 46, 0);
INSERT INTO "items" VALUES (639, 'KnecklaceOfPoisonPro', 1, 6, 14, 11, 50, 0, 0, 0, 0, 300, 0, 16, 35, 20000, 0, 1000, -1, 0, 0, 0, 0, 0, -1, 46, 0);
INSERT INTO "items" VALUES (640, 'KnecklaceOfSufferent', 1, 6, 14, 11, 110, 0, 0, 0, 0, 300, 0, 16, 36, 20000, 0, 1000, -1, 0, 0, 0, 0, 0, -1, 46, 0);
INSERT INTO "items" VALUES (641, 'KnecklaceOfMedusa', 1, 6, 14, 11, 500, 0, 0, 0, 0, 300, 0, 16, 36, 20000, 0, 1000, -1, 0, 0, 0, 0, 0, -1, 46, 5);
INSERT INTO "items" VALUES (642, 'KnecklaceOfIcePro', 1, 6, 14, 10, 25, 0, 0, 0, 0, 300, 0, 16, 37, 20000, 0, 1000, -1, 0, 0, 0, 0, 0, -1, 46, 0);
INSERT INTO "items" VALUES (643, 'KnecklaceOfIceEle', 1, 6, 14, 10, 50, 0, 0, 0, 0, 300, 0, 16, 38, 20000, 0, 1000, -1, 0, 0, 0, 0, 0, -1, 46, 0);
INSERT INTO "items" VALUES (644, 'KnecklaceOfAirEle', 1, 6, 14, 7, 50, 0, 0, 0, 0, 300, 0, 16, 40, 20000, 0, 1000, -1, 0, 0, 0, 0, 0, -1, 46, 0);
INSERT INTO "items" VALUES (645, 'KnecklaceOfEfreet', 1, 6, 14, 9, 50, 0, 0, 0, 0, 300, 0, 16, 41, 20000, 0, 1000, -1, 0, 0, 0, 0, 0, -1, 46, 0);
INSERT INTO "items" VALUES (646, 'NecklaceOfBeholder', 1, 6, 14, 9, 50, 0, 0, 0, 0, 300, 0, 16, 47, 20000, 0, 1000, -1, 0, 0, 0, 0, 0, -1, 46, 0);
INSERT INTO "items" VALUES (647, 'NecklaceOfStoneGol', 1, 6, 14, 4, 25, 0, 0, 0, 0, 300, 0, 16, 48, 20000, 0, 1000, -1, 0, 0, 0, 0, 0, -1, 46, 0);
INSERT INTO "items" VALUES (648, 'NecklaceOfLiche', 1, 6, 14, 2, 15, 0, 0, 0, 0, 300, 0, 16, 51, 10000, 0, 600, -1, 0, 0, 0, 0, -10, -1, 46, 0);
INSERT INTO "items" VALUES (650, 'ZemstoneofSacrifice', 0, 0, 26, 0, 0, 0, 0, 0, 0, 3, 0, 16, 39, 5000, 0, 5000, -1, 0, 0, 0, 0, 0, -1, 0, 0);
INSERT INTO "items" VALUES (651, 'GreenBall', 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 6, 123, 5000, 0, 4000, -1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (652, 'RedBall', 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 6, 124, 5000, 0, 4000, -1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (653, 'YellowBall', 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 6, 125, 5000, 0, 4000, -1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (654, 'BlueBall', 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 6, 126, 5000, 0, 4000, -1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (655, 'PearlBall', 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 6, 127, 5000, 0, 4000, -1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (656, 'StoneOfXelima', 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 6, 128, 10000, 0, 4000, -1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (657, 'StoneOfMerien', 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 6, 129, 10000, 0, 4000, -1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (658, 'AresdenMinePotion', 7, 0, 4, 2, 12, 10, 0, 0, 0, 1, 0, 6, 1, 10, 1, 30, -1, 0, 0, 0, 0, 0, -1, 21, 0);
INSERT INTO "items" VALUES (659, 'ElvineMinePotion', 7, 0, 4, 2, 12, 10, 0, 0, 0, 1, 0, 6, 1, 10, 1, 30, -1, 0, 0, 0, 0, 0, -1, 21, 0);
INSERT INTO "items" VALUES (660, 'UnfreezePotion', 7, 0, 28, 2, 12, 10, 0, 0, 0, 1, 0, 6, 130, 200, 0, 50, -1, 0, 0, 0, 0, 0, -1, 21, 0);
INSERT INTO "items" VALUES (671, 'KnightRapier', 1, 8, 1, 1, 7, 2, 1, 7, 2, 1100, 0, 1, 6, 3200, 1, 1200, 7, 3, 95, 0, 0, 0, 9, 1, 11);
INSERT INTO "items" VALUES (672, 'KnightGreatSword', 1, 9, 1, 2, 8, 2, 2, 10, 2, 1200, 0, 1, 10, 3500, 1, 5200, 11, 8, 85, 0, -8, 5, 8, 1, 11);
INSERT INTO "items" VALUES (673, 'KnightFlameberge', 1, 9, 1, 2, 10, 2, 2, 12, 2, 1200, 0, 1, 11, 3700, 1, 6000, 12, 10, 95, 0, -15, 10, 8, 1, 11);
INSERT INTO "items" VALUES (674, 'KnightWarAxe', 1, 8, 1, 2, 6, 2, 2, 8, 2, 1200, 0, 15, 1, 3000, 1, 4400, 21, 8, 85, 0, 0, 0, 10, 1, 11);
INSERT INTO "items" VALUES (675, 'KnightPlateMail(M)', 1, 2, 2, 40, 42, 0, 0, 0, 0, 3500, 0, 9, 3, 6000, 1, 10000, 4, 0, 85, 1, -10, -10, 0, 6, 11);
INSERT INTO "items" VALUES (676, 'KnightPlateMail(W)', 1, 2, 2, 40, 42, 0, 0, 0, 0, 3500, 0, 13, 5, 6000, 1, 10000, 6, 0, 85, 2, -10, -10, 0, 6, 11);
INSERT INTO "items" VALUES (677, 'KnightPlateLeg(M)', 1, 4, 2, 15, 22, 1, 1, 1, 1, 1100, 0, 8, 3, 3000, 1, 2000, 4, 0, 80, 1, -6, -6, 0, 6, 11);
INSERT INTO "items" VALUES (678, 'KnightPlateLeg(W)', 1, 4, 2, 15, 22, 1, 1, 1, 1, 1100, 0, 12, 4, 3000, 1, 2000, 5, 0, 80, 2, -6, -6, 0, 6, 11);
INSERT INTO "items" VALUES (679, 'KnightFullHelm(M)', 1, 1, 2, 12, 22, 0, 0, 0, 0, 2000, 0, 21, 1, 3500, 1, 8500, 1, 0, 80, 1, -7, -7, -1, 6, 11);
INSERT INTO "items" VALUES (680, 'KnightFullHelm(W)', 1, 1, 2, 12, 22, 0, 0, 0, 0, 2000, 0, 21, 1, 3500, 1, 8500, 1, 0, 80, 2, -7, -7, -1, 6, 11);
INSERT INTO "items" VALUES (681, 'WizardHauberk(M)', 1, 3, 2, 12, 12, 0, 14, 100, 0, 1000, 0, 7, 1, 2400, 1, 1200, 2, 0, 90, 1, -3, -3, 0, 6, 11);
INSERT INTO "items" VALUES (682, 'WizardHauberk(W)', 1, 3, 2, 12, 12, 0, 14, 100, 0, 1000, 0, 11, 2, 2400, 1, 1200, 3, 0, 90, 2, -3, -3, 0, 6, 11);
INSERT INTO "items" VALUES (683, 'WizMagicWand(MS20)', 1, 8, 13, 1, 6, 0, 20, 0, 0, 3600, 10, 17, 1, 6000, 1, 1000, 36, 3, 95, 0, 0, 0, 21, 8, 4);
INSERT INTO "items" VALUES (684, 'WizMagicWand(MS10)', 1, 8, 13, 1, 6, 0, 10, 0, 0, 3600, 10, 17, 1, 5500, 1, 1000, 36, 3, 90, 0, 0, 0, 21, 8, 4);
INSERT INTO "items" VALUES (685, 'WizardRobe(M)', 1, 2, 2, 12, 1, 0, 14, 100, 0, 3000, 0, 9, 5, 3000, 1, 1000, 6, 0, 80, 1, 0, 0, 0, 13, 11);
INSERT INTO "items" VALUES (686, 'WizardRobe(W)', 1, 2, 2, 12, 1, 0, 14, 100, 0, 3000, 0, 13, 6, 3000, 1, 1000, 7, 0, 80, 2, 0, 0, 0, 13, 11);
INSERT INTO "items" VALUES (687, 'KnightHauberk(M)', 1, 3, 2, 12, 12, 0, 11, 100, 0, 1000, 0, 7, 1, 2400, 1, 1200, 2, 0, 70, 1, -3, -3, 0, 6, 11);
INSERT INTO "items" VALUES (688, 'KnightHauberk(W)', 1, 3, 2, 12, 12, 0, 11, 100, 0, 1000, 0, 11, 2, 2400, 1, 1200, 3, 0, 70, 2, -3, -3, 0, 6, 11);
INSERT INTO "items" VALUES (700, 'SangAhHauberk', 1, 3, 2, 18, 18, 0, 0, 0, 0, 30000, 0, 7, 1, 2400, 0, 1200, 2, 0, 0, 1, -3, -3, 0, 6, 6);
INSERT INTO "items" VALUES (701, 'SangAhFullHel', 1, 1, 2, 17, 27, 0, 0, 0, 0, 30000, 0, 21, 1, 3500, 0, 8500, 1, 0, 0, 1, -7, -7, -1, 6, 6);
INSERT INTO "items" VALUES (702, 'SangAhLeggings', 1, 4, 2, 21, 28, 1, 1, 1, 1, 30000, 0, 8, 3, 3000, 0, 2000, 4, 0, 0, 1, -6, -6, 0, 6, 6);
INSERT INTO "items" VALUES (703, 'SangAhFlameberge', 1, 9, 1, 4, 7, 0, 4, 7, 0, 50000, 0, 1, 11, 3700, 0, 6000, 12, 10, 0, 0, -15, 10, 8, 1, 6);
INSERT INTO "items" VALUES (704, 'SangAhPlateMail', 1, 2, 2, 53, 55, 0, 0, 0, 0, 30000, 0, 9, 3, 1000, 0, 10000, 4, 0, 0, 1, -10, -10, 0, 6, 6);
INSERT INTO "items" VALUES (705, 'SangAhJewel', 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 16, 42, 5000, 0, 200, 1, 0, 0, 0, 0, 0, -1, 46, 0);
INSERT INTO "items" VALUES (706, 'DarkKnightHauberk', 1, 3, 2, 18, 18, 0, 0, 0, 0, 30000, 0, 7, 1, 2400, 0, 1200, 2, 0, 0, 1, -3, -3, 0, 6, 6);
INSERT INTO "items" VALUES (707, 'DarkKnightFullHelm', 1, 1, 2, 17, 27, 0, 0, 0, 0, 30000, 0, 21, 1, 3500, 0, 8500, 1, 0, 0, 1, -7, -7, -1, 6, 6);
INSERT INTO "items" VALUES (708, 'DarkKnightLeggings', 1, 4, 2, 21, 28, 1, 1, 1, 1, 30000, 0, 8, 3, 3000, 0, 2000, 4, 0, 0, 1, -6, -6, 0, 6, 6);
INSERT INTO "items" VALUES (709, 'DarkKnightFlameberge', 1, 9, 1, 4, 7, 0, 4, 7, 0, 30000, 0, 1, 11, 3700, 0, 6000, 12, 10, 0, 0, -15, 10, 8, 1, 6);
INSERT INTO "items" VALUES (710, 'DarkKnightPlateMail', 1, 2, 2, 53, 55, 0, 0, 0, 0, 30000, 0, 9, 3, 6000, 0, 10000, 4, 0, 0, 1, -10, -10, 0, 6, 6);
INSERT INTO "items" VALUES (711, 'DarkMageHauberk', 1, 3, 2, 18, 18, 0, 0, 0, 0, 30000, 0, 7, 1, 2400, 0, 1200, 2, 0, 0, 1, -3, -3, 0, 6, 6);
INSERT INTO "items" VALUES (712, 'DarkMageChainMail', 1, 2, 2, 36, 38, 0, 0, 0, 0, 30000, 0, 9, 1, 1200, 0, 3000, 2, 0, 0, 1, -12, -12, 0, 6, 6);
INSERT INTO "items" VALUES (713, 'DarkMageLeggings', 1, 4, 2, 21, 28, 1, 1, 1, 1, 30000, 0, 8, 3, 3000, 0, 2000, 4, 0, 0, 1, -6, -6, 0, 6, 6);
INSERT INTO "items" VALUES (714, 'DarkMageMagicStaff', 1, 8, 13, 1, 6, 0, 25, 0, 0, 30000, 10, 17, 1, 6000, 0, 1000, 36, 3, 0, 0, 0, 0, 21, 8, 6);
INSERT INTO "items" VALUES (715, 'DarkMageRobe', 1, 2, 2, 22, 20, 0, 14, 100, 0, 30000, 0, 9, 5, 2000, 0, 1000, 6, 0, 0, 1, 0, 0, 0, 11, 6);
INSERT INTO "items" VALUES (716, 'DarkMageLedderArmor', 1, 2, 2, 24, 22, 0, 0, 0, 0, 30000, 0, 9, 0, 2000, 0, 1500, 1, 0, 0, 1, -5, -5, 0, 6, 6);
INSERT INTO "items" VALUES (717, 'DarkKnightRapier', 1, 8, 1, 1, 7, 0, 1, 7, 0, 30000, 0, 1, 6, 3000, 0, 1100, 7, 3, 0, 0, 0, 0, 9, 1, 6);
INSERT INTO "items" VALUES (718, 'DarkKnightGreatSword', 1, 9, 1, 2, 8, 0, 2, 10, 0, 30000, 0, 1, 10, 3000, 0, 5200, 11, 8, 0, 0, -8, 5, 8, 1, 6);
INSERT INTO "items" VALUES (719, 'DarkMageScaleMail', 1, 2, 2, 32, 30, 0, 0, 0, 0, 30000, 0, 9, 2, 1000, 0, 2000, 3, 0, 0, 1, -8, -8, 0, 6, 6);
INSERT INTO "items" VALUES (720, 'Songpyon', 7, 0, 22, 900, 0, 0, 0, 0, 0, 1, 0, 6, 115, 2400, 0, 20, -1, 0, 0, 0, 0, 0, -1, 21, 0);
INSERT INTO "items" VALUES (721, 'Ginseng', 7, 0, 28, 2, 12, 10, 0, 0, 0, 1, 0, 6, 114, 600, 0, 50, -1, 0, 0, 0, 0, 0, -1, 21, 0);
INSERT INTO "items" VALUES (722, 'BeefRibSet', 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 116, 50000, 0, 5000, -1, 0, 0, 0, 0, 0, -1, 0, 0);
INSERT INTO "items" VALUES (723, 'Wine', 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 117, 25000, 0, 250, -1, 0, 0, 0, 0, 0, -1, 0, 0);
INSERT INTO "items" VALUES (724, 'DarkKnightHauberkW', 1, 3, 2, 18, 18, 0, 0, 0, 0, 30000, 0, 11, 2, 2400, 0, 1200, 3, 0, 0, 2, -3, -3, 0, 6, 6);
INSERT INTO "items" VALUES (725, 'DarkKnightFullHelmW', 1, 1, 2, 17, 27, 0, 0, 0, 0, 30000, 0, 21, 1, 3500, 0, 8500, 1, 0, 0, 2, -7, -7, -1, 6, 6);
INSERT INTO "items" VALUES (726, 'DarkKnightLeggingsW', 1, 4, 2, 21, 28, 1, 1, 1, 1, 30000, 0, 12, 4, 3000, 0, 2000, 5, 0, 0, 2, -6, -6, 0, 6, 6);
INSERT INTO "items" VALUES (727, 'DarkKnightFlamebergW', 1, 9, 1, 4, 7, 0, 4, 7, 0, 30000, 0, 1, 11, 3700, 0, 6000, 12, 10, 0, 0, -15, 10, 8, 1, 6);
INSERT INTO "items" VALUES (728, 'DarkKnightPlateMailW', 1, 2, 2, 53, 55, 0, 0, 0, 0, 30000, 0, 13, 5, 6000, 0, 10000, 6, 0, 0, 2, -10, -10, 0, 6, 6);
INSERT INTO "items" VALUES (729, 'DarkMageHauberkW', 1, 3, 2, 18, 18, 0, 0, 0, 0, 30000, 0, 11, 2, 2400, 0, 1200, 3, 0, 0, 2, -3, -3, 0, 6, 6);
INSERT INTO "items" VALUES (730, 'DarkMageChainMailW', 1, 2, 2, 36, 38, 0, 0, 0, 0, 30000, 0, 13, 3, 1200, 0, 3000, 4, 0, 0, 2, -12, -12, 0, 6, 6);
INSERT INTO "items" VALUES (731, 'DarkMageLeggingsW', 1, 4, 2, 21, 28, 1, 1, 1, 1, 30000, 0, 12, 4, 3000, 0, 2000, 5, 0, 0, 2, -6, -6, 0, 6, 6);
INSERT INTO "items" VALUES (732, 'DarkMageMagicStaffW', 1, 8, 13, 1, 6, 0, 25, 0, 0, 30000, 10, 17, 1, 6000, 0, 1000, 36, 3, 0, 0, 0, 0, 21, 8, 6);
INSERT INTO "items" VALUES (733, 'DarkMageRobeW', 1, 2, 2, 22, 20, 0, 14, 100, 0, 30000, 0, 13, 6, 2000, 0, 1000, 7, 0, 0, 2, 0, 0, 0, 11, 6);
INSERT INTO "items" VALUES (734, 'RingofArcmage', 1, 10, 14, 6, 4, 0, 0, 0, 0, 300, 0, 16, 49, 10000, 0, 500, -1, 0, 0, 0, 0, 0, -1, 46, 0);
INSERT INTO "items" VALUES (735, 'RingofDragonpower', 1, 10, 14, 3, 5, 0, 0, 0, 0, 300, 0, 16, 50, 10000, 0, 500, -1, 0, 0, 0, 0, 0, -1, 46, 0);
INSERT INTO "items" VALUES (736, 'SangAhGiantSword', 1, 9, 1, 2, 10, 2, 2, 12, 2, 50000, 0, 1, 18, 3700, 0, 6000, 13, 10, 120, 0, -15, 10, 8, 1, 6);
INSERT INTO "items" VALUES (737, 'DarkKnightGiantSword', 1, 9, 1, 2, 10, 2, 2, 12, 2, 30000, 0, 1, 18, 3700, 0, 6000, 13, 10, 120, 0, -15, 10, 8, 1, 6);
INSERT INTO "items" VALUES (738, 'DarkMageMagicWand', 1, 8, 13, 1, 6, 0, 28, 0, 0, 30000, 10, 17, 0, 6000, 0, 1000, 35, 3, 120, 0, 0, 0, 21, 8, 6);
INSERT INTO "items" VALUES (740, '5000GoldPocket', 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 118, 10000, 0, 500, -1, 0, 0, 0, 0, 0, -1, 21, 0);
INSERT INTO "items" VALUES (741, '10000GoldPocket', 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 119, 20000, 0, 1000, -1, 0, 0, 0, 0, 0, -1, 21, 0);
INSERT INTO "items" VALUES (742, '50000GoldPocket', 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 120, 100000, 0, 2000, -1, 0, 0, 0, 0, 0, -1, 21, 0);
INSERT INTO "items" VALUES (743, '100000GoldPocket', 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 121, 200000, 0, 3000, -1, 0, 0, 0, 0, 0, -1, 21, 0);
INSERT INTO "items" VALUES (744, '1000000GoldPocket', 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 122, 2000000, 0, 4000, -1, 0, 0, 0, 0, 0, -1, 21, 0);
INSERT INTO "items" VALUES (745, 'BlackKnightTemple', 1, 9, 1, 2, 10, 2, 2, 12, 2, 30000, 0, 1, 20, 3700, 0, 6000, 14, 10, 120, 0, -15, 10, 8, 1, 6);
INSERT INTO "items" VALUES (746, 'BlackMageTemple', 1, 8, 13, 1, 6, 0, 28, 0, 0, 30000, 10, 17, 2, 6000, 0, 1000, 37, 3, 120, 0, 0, 0, 21, 8, 6);
INSERT INTO "items" VALUES (750, 'Horned-Helm(M)', 1, 1, 2, 17, 24, 0, 0, 0, 0, 3500, 0, 21, 2, 4000, 1, 16000, 5, 0, 120, 1, -7, -7, -1, 6, 0);
INSERT INTO "items" VALUES (751, 'Wings-Helm(M)', 1, 1, 2, 15, 22, 0, 0, 0, 0, 2500, 0, 21, 3, 5000, 1, 13000, 6, 0, 100, 1, -7, -7, -1, 6, 0);
INSERT INTO "items" VALUES (752, 'Wizard-Cap(M)', 1, 1, 2, 5, 10, 0, 14, 110, 0, 500, 0, 21, 4, 1500, 1, 1500, 7, 0, 90, 1, -7, -7, -1, 6, 0);
INSERT INTO "items" VALUES (753, 'Wizard-Hat(M)', 1, 1, 2, 10, 15, 0, 14, 130, 0, 800, 0, 21, 5, 3000, 1, 1500, 8, 0, 120, 1, -7, -7, -1, 6, 0);
INSERT INTO "items" VALUES (754, 'Horned-Helm(W)', 1, 1, 2, 17, 24, 0, 0, 0, 0, 3500, 0, 21, 2, 4000, 1, 16000, 5, 0, 120, 2, -7, -7, -1, 6, 0);
INSERT INTO "items" VALUES (755, 'Wings-Helm(W)', 1, 1, 2, 15, 22, 0, 0, 0, 0, 2500, 0, 21, 3, 5000, 1, 13000, 6, 0, 100, 2, -7, -7, -1, 6, 0);
INSERT INTO "items" VALUES (756, 'Wizard-Cap(W)', 1, 1, 2, 5, 10, 0, 14, 110, 0, 500, 0, 21, 4, 1500, 1, 1500, 7, 0, 90, 2, -7, -7, -1, 6, 0);
INSERT INTO "items" VALUES (757, 'Wizard-Hat(W)', 1, 1, 2, 10, 15, 0, 14, 130, 0, 800, 0, 21, 5, 3000, 1, 1500, 8, 0, 120, 2, -7, -7, -1, 6, 0);
INSERT INTO "items" VALUES (760, 'Hammer', 1, 9, 1, 3, 7, 0, 3, 9, 0, 2000, 0, 15, 7, 6000, 1, 9000, 30, 12, 0, 0, 0, 0, 14, 1, 0);
INSERT INTO "items" VALUES (761, 'BattleHammer', 1, 9, 1, 3, 7, 2, 3, 9, 2, 4000, 0, 15, 8, 9000, 1, 12000, 31, 14, 110, 0, 0, 0, 14, 1, 0);
INSERT INTO "items" VALUES (762, 'GiantBattleHammer', 1, 9, 1, 3, 9, 3, 3, 10, 3, 6000, 0, 15, 8, 15000, 0, 14000, 31, 14, 110, 0, 0, 0, 14, 1, 9);
INSERT INTO "items" VALUES (765, 'ThirdMemorialRing', 1, 10, 4, 0, 0, 0, 10, 0, 0, 300, 0, 16, 11, 1000, 0, 200, -1, 0, 0, 0, 0, -10, -1, 46, 0);
INSERT INTO "items" VALUES (770, 'SantaCostume(M)', 1, 13, 14, 10, 25, 0, 0, 0, 0, 1500, 0, 9, 6, 18000, 0, 1000, 7, 0, 0, 1, 0, 0, 0, 15, 0);
INSERT INTO "items" VALUES (771, 'SantaCostume(W)', 1, 13, 14, 10, 25, 0, 0, 0, 0, 1500, 0, 13, 7, 18000, 0, 1000, 8, 0, 0, 2, 0, 0, 0, 15, 0);
INSERT INTO "items" VALUES (780, 'RedCandy', 7, 0, 4, 3, 8, 200, 0, 0, 0, 1, 0, 6, 131, 2000, 0, 100, -1, 0, 0, 0, 0, 0, -1, 21, 0);
INSERT INTO "items" VALUES (781, 'BlueCandy', 7, 0, 5, 4, 8, 200, 0, 0, 0, 1, 0, 6, 132, 2000, 0, 100, -1, 0, 0, 0, 0, 0, -1, 21, 0);
INSERT INTO "items" VALUES (782, 'GreenCandy', 7, 0, 6, 4, 8, 200, 0, 0, 0, 1, 0, 6, 133, 2000, 0, 100, -1, 0, 0, 0, 0, 0, -1, 21, 0);
INSERT INTO "items" VALUES (800, 'FarmingManual', 3, 0, 9, 2, 20, 0, 0, 0, 0, 0, 0, 6, 92, 100, 1, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (801, 'SeedBag(WaterMelon)', 11, 0, 30, 1, 20, 0, 0, 0, 0, 1, 0, 6, 137, 100, 1, 100, -1, 0, 0, 0, 0, 0, -1, 21, 0);
INSERT INTO "items" VALUES (802, 'SeedBag(Pumpkin)', 11, 0, 30, 2, 20, 0, 0, 0, 0, 1, 0, 6, 137, 100, 1, 100, -1, 0, 0, 0, 0, 0, -1, 21, 0);
INSERT INTO "items" VALUES (803, 'SeedBag(Garlic)', 11, 0, 30, 3, 30, 0, 0, 0, 0, 1, 0, 6, 137, 150, 1, 100, -1, 0, 0, 0, 0, 0, -1, 21, 0);
INSERT INTO "items" VALUES (804, 'SeedBag(Barley)', 11, 0, 30, 4, 30, 0, 0, 0, 0, 1, 0, 6, 137, 150, 1, 100, -1, 0, 0, 0, 0, 0, -1, 21, 0);
INSERT INTO "items" VALUES (805, 'SeedBag(Carrot)', 11, 0, 30, 5, 40, 0, 0, 0, 0, 1, 0, 6, 137, 200, 1, 100, -1, 0, 0, 0, 0, 0, -1, 21, 0);
INSERT INTO "items" VALUES (806, 'SeedBag(Radish)', 11, 0, 30, 6, 40, 0, 0, 0, 0, 1, 0, 6, 137, 200, 1, 100, -1, 0, 0, 0, 0, 0, -1, 21, 0);
INSERT INTO "items" VALUES (807, 'SeedBag(Corn)', 11, 0, 30, 7, 50, 0, 0, 0, 0, 1, 0, 6, 137, 250, 1, 100, -1, 0, 0, 0, 0, 0, -1, 21, 0);
INSERT INTO "items" VALUES (808, 'SeedBag(CBellflower)', 11, 0, 30, 8, 50, 0, 0, 0, 0, 1, 0, 6, 137, 250, 1, 100, -1, 0, 0, 0, 0, 0, -1, 21, 0);
INSERT INTO "items" VALUES (809, 'SeedBag(Melone)', 11, 0, 30, 9, 60, 0, 0, 0, 0, 1, 0, 6, 137, 300, 1, 100, -1, 0, 0, 0, 0, 0, -1, 21, 0);
INSERT INTO "items" VALUES (810, 'SeedBag(Tommato)', 11, 0, 30, 10, 60, 0, 0, 0, 0, 1, 0, 6, 137, 300, 1, 100, -1, 0, 0, 0, 0, 0, -1, 21, 0);
INSERT INTO "items" VALUES (811, 'SeedBag(Grapes)', 11, 0, 30, 11, 70, 0, 0, 0, 0, 1, 0, 6, 137, 350, 1, 100, -1, 0, 0, 0, 0, 0, -1, 21, 0);
INSERT INTO "items" VALUES (812, 'SeedBag(BlueGrapes)', 11, 0, 30, 12, 70, 0, 0, 0, 0, 1, 0, 6, 137, 350, 1, 100, -1, 0, 0, 0, 0, 0, -1, 21, 0);
INSERT INTO "items" VALUES (813, 'SeedBag(Mushroom)', 11, 0, 30, 13, 80, 0, 0, 0, 0, 1, 0, 6, 137, 400, 1, 100, -1, 0, 0, 0, 0, 0, -1, 21, 0);
INSERT INTO "items" VALUES (814, 'SeedBag(Ginseng)', 11, 0, 30, 14, 90, 0, 0, 0, 0, 1, 0, 6, 137, 450, 1, 100, -1, 0, 0, 0, 0, 0, -1, 21, 0);
INSERT INTO "items" VALUES (820, 'WaterMelon', 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 138, 120, 0, 100, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (821, 'Pumpkin', 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 139, 120, 0, 100, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (822, 'Garlic', 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 140, 180, 0, 100, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (823, 'Barley', 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 141, 180, 0, 100, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (824, 'Carrot', 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 142, 200, 0, 100, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (825, 'Radish', 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 143, 200, 0, 100, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (826, 'Corn', 7, 0, 7, 4, 8, 10, 0, 0, 0, 1, 0, 6, 144, 240, 0, 100, -1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (827, 'ChineseBellflower', 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 145, 240, 0, 100, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (828, 'Melone', 7, 0, 7, 5, 7, 12, 0, 0, 0, 1, 0, 6, 146, 300, 0, 100, -1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (829, 'Tommato', 7, 0, 7, 5, 7, 10, 0, 0, 0, 1, 0, 6, 147, 300, 0, 100, -1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (830, 'Grapes', 7, 0, 7, 5, 8, 10, 0, 0, 0, 1, 0, 6, 148, 360, 0, 100, -1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (831, 'BlueGrapes', 7, 0, 7, 5, 8, 10, 0, 0, 0, 1, 0, 6, 149, 360, 0, 100, -1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (832, 'Mushroom', 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 150, 400, 0, 100, 1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (840, 'SuperRedPotion', 7, 0, 4, 3, 8, 130, 0, 0, 0, 1, 0, 6, 134, 2000, 0, 100, -1, 0, 0, 0, 0, 0, -1, 21, 0);
INSERT INTO "items" VALUES (841, 'SuperBluePotion', 7, 0, 5, 3, 8, 130, 0, 0, 0, 1, 0, 6, 135, 2000, 0, 100, -1, 0, 0, 0, 0, 0, -1, 21, 0);
INSERT INTO "items" VALUES (842, 'SuperGreenPotion', 7, 0, 6, 4, 8, 130, 0, 0, 0, 1, 0, 6, 136, 2000, 0, 100, -1, 0, 0, 0, 0, 0, -1, 21, 0);
INSERT INTO "items" VALUES (843, 'BarbarianHammer', 1, 9, 1, 3, 9, 2, 3, 10, 2, 4500, 0, 15, 10, 15000, 1, 20000, 32, 15, 110, 0, 0, 0, 14, 1, 0);
INSERT INTO "items" VALUES (844, 'BlackShadowSword', 1, 9, 1, 2, 12, 3, 2, 12, 3, 2800, 0, 1, 25, 10000, 1, 15000, 33, 14, 120, 0, 0, 0, 8, 1, 0);
INSERT INTO "items" VALUES (845, 'StormBringer', 1, 9, 1, 3, 10, 0, 3, 11, 0, 3000, 0, 1, 26, 12000, 0, 11000, 15, 11, 0, 0, 0, 0, 8, 1, 0);
INSERT INTO "items" VALUES (846, 'The_Devastator', 1, 9, 1, 4, 8, 1, 4, 9, 1, 3000, 0, 1, 21, 18000, 0, 20000, 19, 15, 0, 0, 0, 0, 8, 1, 0);
INSERT INTO "items" VALUES (847, 'DarkExecutor', 1, 9, 1, 2, 12, 3, 2, 13, 3, 4000, 0, 1, 24, 14000, 0, 14000, 16, 13, 0, 0, 0, 0, 8, 1, 0);
INSERT INTO "items" VALUES (848, 'LightingBlade', 1, 9, 1, 2, 12, 3, 2, 13, 3, 4000, 0, 1, 22, 14000, 0, 14000, 29, 13, 0, 0, 0, 0, 8, 1, 0);
INSERT INTO "items" VALUES (849, 'KlonessBlade', 1, 9, 1, 2, 12, 2, 2, 13, 2, 8000, 0, 1, 23, 12000, 0, 12000, 17, 12, 0, 0, 0, 0, 8, 1, 0);
INSERT INTO "items" VALUES (850, 'KlonessAxe', 1, 9, 1, 3, 9, 1, 3, 10, 1, 5000, 0, 15, 11, 8000, 0, 15000, 28, 14, 0, 0, 0, 0, 8, 1, 0);
INSERT INTO "items" VALUES (851, 'KlonessEsterk', 1, 8, 1, 2, 6, 2, 2, 7, 2, 5000, 0, 1, 27, 6000, 0, 5000, 18, 5, 0, 0, 0, 0, 8, 1, 0);
INSERT INTO "items" VALUES (852, 'CancelManual', 3, 0, 18, 76, 0, 0, 0, 0, 0, 0, 0, 6, 91, 100, 0, 1, -1, 0, 0, 0, 0, 0, -1, 42, 1);
INSERT INTO "items" VALUES (853, 'E.S.W.Manual', 3, 0, 18, 96, 0, 0, 0, 0, 0, 0, 0, 6, 91, 100, 0, 1, -1, 0, 0, 0, 0, 0, -1, 42, 1);
INSERT INTO "items" VALUES (857, 'I.M.CManual', 3, 0, 18, 83, 0, 0, 0, 0, 0, 0, 0, 6, 91, 100, 0, 1, -1, 0, 0, 0, 0, 0, -1, 42, 1);
INSERT INTO "items" VALUES (858, 'NecklaceOfMerien', 1, 6, 14, 4, 50, 0, 0, 0, 0, 300, 0, 16, 54, 20000, 0, 1000, -1, 0, 0, 0, 0, 0, -1, 46, 0);
INSERT INTO "items" VALUES (859, 'NecklaceOfKloness', 1, 6, 14, 4, 0, 0, 0, 0, 0, 300, 0, 16, 52, 20000, 0, 1000, -1, 0, 0, 0, 0, 0, -1, 46, 0);
INSERT INTO "items" VALUES (860, 'NecklaceOfXelima', 1, 6, 14, 12, 100, 0, 0, 0, 0, 300, 0, 16, 53, 20000, 0, 1000, -1, 0, 0, 0, 0, 0, -1, 46, 5);
INSERT INTO "items" VALUES (861, 'BerserkWand(MS.20)', 1, 8, 13, 1, 6, 0, 20, 0, 0, 5000, 0, 17, 4, 12000, 0, 1000, 34, 3, 100, 0, 0, 0, 21, 8, 0);
INSERT INTO "items" VALUES (862, 'BerserkWand(MS.10)', 1, 8, 13, 1, 6, 0, 10, 0, 0, 5000, 0, 17, 4, 12000, 0, 1000, 34, 3, 100, 0, 0, 0, 21, 8, 0);
INSERT INTO "items" VALUES (863, 'KlonessWand(MS.20)', 1, 8, 13, 1, 6, 0, 20, 0, 0, 5000, 0, 17, 5, 14000, 0, 1000, 39, 3, 120, 0, 0, 0, 21, 8, 0);
INSERT INTO "items" VALUES (864, 'KlonessWand(MS.10)', 1, 8, 13, 1, 6, 0, 10, 0, 0, 5000, 0, 17, 5, 14000, 0, 1000, 39, 3, 120, 0, 0, 0, 21, 8, 0);
INSERT INTO "items" VALUES (865, 'ResurWand(MS.20)', 1, 8, 13, 1, 6, 0, 20, 0, 0, 5000, 0, 17, 3, 10000, 0, 1000, 38, 3, 100, 0, 0, 0, 21, 8, 0);
INSERT INTO "items" VALUES (866, 'ResurWand(MS.10)', 1, 8, 13, 1, 6, 0, 10, 0, 0, 5000, 0, 17, 3, 10000, 0, 1000, 38, 3, 100, 0, 0, 0, 21, 8, 0);
INSERT INTO "items" VALUES (867, 'AcientTablet', 3, 0, 31, 7, 0, 0, 0, 0, 0, 1, 0, 6, 155, 1, 0, 50, -1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (868, 'AcientTablet(LU)', 10, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 151, 1, 0, 50, -1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (869, 'AcientTablet(LD)', 10, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 152, 1, 0, 50, -1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (870, 'AcientTablet(RU)', 10, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 153, 1, 0, 50, -1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (871, 'AcientTablet(RD)', 10, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 6, 154, 1, 0, 50, -1, 0, 0, 0, 0, 0, -1, 31, 0);
INSERT INTO "items" VALUES (873, 'Fire-Bow', 1, 9, 3, 2, 5, 0, 2, 5, 0, 1000, 0, 2, 5, 6000, 1, 7000, 43, 6, 70, 0, 0, 0, 6, 3, 0);
INSERT INTO "items" VALUES (874, 'Direction-Bow', 1, 9, 3, 2, 6, 0, 2, 6, 0, 1200, 0, 2, 4, 7000, 1, 10000, 42, 8, 70, 0, 0, 0, 6, 3, 0);
INSERT INTO "items" VALUES (875, 'SummonScroll(SOR)', 3, 0, 11, 5, 9, 0, 0, 0, 0, 1, 9, 6, 9, 300, 0, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (876, 'SummonScroll(ATK)', 3, 0, 11, 5, 10, 0, 0, 0, 0, 1, 9, 6, 9, 300, 0, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (877, 'SummonScroll(ELF)', 3, 0, 11, 5, 11, 0, 0, 0, 0, 1, 9, 6, 9, 300, 0, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (878, 'SummonScroll(DSK)', 3, 0, 11, 5, 12, 0, 0, 0, 0, 1, 9, 6, 9, 300, 0, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (879, 'SummonScroll(HBT)', 3, 0, 11, 5, 13, 0, 0, 0, 0, 1, 9, 6, 9, 300, 0, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (880, 'SummonScroll(BAR)', 3, 0, 11, 5, 14, 0, 0, 0, 0, 1, 9, 6, 9, 300, 0, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (881, 'ArmorDye(Indigo)', 11, 0, 32, 1, 0, 0, 0, 0, 0, 1, 0, 6, 58, 100, 0, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (882, 'ArmorDye(CrimsonRed)', 11, 0, 32, 4, 0, 0, 0, 0, 0, 1, 0, 6, 61, 100, 0, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (883, 'ArmorDye(Gold)', 11, 0, 32, 3, 0, 0, 0, 0, 0, 1, 0, 6, 60, 100, 0, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (884, 'ArmorDye(Aqua)', 11, 0, 32, 7, 0, 0, 0, 0, 0, 1, 0, 6, 54, 100, 0, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (885, 'ArmorDye(Pink)', 11, 0, 32, 8, 0, 0, 0, 0, 0, 1, 0, 6, 65, 100, 0, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (886, 'ArmorDye(Violet)', 11, 0, 32, 9, 0, 0, 0, 0, 0, 1, 0, 6, 66, 100, 0, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (887, 'ArmorDye(Blue)', 11, 0, 32, 10, 0, 0, 0, 0, 0, 1, 0, 6, 67, 100, 0, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (888, 'ArmorDye(Khaki)', 11, 0, 32, 12, 0, 0, 0, 0, 0, 1, 0, 6, 69, 100, 0, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (889, 'ArmorDye(Yellow)', 11, 0, 32, 13, 0, 0, 0, 0, 0, 1, 0, 6, 70, 100, 0, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (890, 'ArmorDye(Red)', 11, 0, 32, 14, 0, 0, 0, 0, 0, 1, 0, 6, 71, 100, 0, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (1081, 'MaginDiamond', 1, 11, 14, 14, 0, 0, 0, 0, 0, 300, 0, 22, 6, 8000, 0, 200, -1, 0, 0, 0, 0, -10, -1, 46, 9);
INSERT INTO "items" VALUES (1082, 'MaginRuby', 1, 11, 14, 13, 0, 0, 0, 0, 0, 300, 0, 22, 8, 5000, 0, 200, -1, 0, 0, 0, 0, -10, -1, 46, 9);
INSERT INTO "items" VALUES (1083, 'MagicEmerald', 1, 11, 14, 15, 0, 0, 0, 0, 0, 300, 0, 22, 7, 5000, 0, 200, -1, 0, 0, 0, 0, -10, -1, 46, 9);
INSERT INTO "items" VALUES (1084, 'MagicSapphire', 1, 11, 14, 30, 0, 0, 0, 0, 0, 300, 0, 22, 9, 5000, 0, 200, -1, 0, 0, 0, 0, -10, -1, 46, 9);
INSERT INTO "items" VALUES (1085, 'LuckyPrizeTicket', 3, 0, 23, 1, 0, 0, 0, 0, 0, 1, 9, 6, 9, 50000, 1, 1, -1, 0, 0, 0, 0, 0, -1, 42, 0);
INSERT INTO "items" VALUES (1086, 'MagicNecklace(DF+15)', 1, 6, 14, 4, 15, 0, 0, 0, 0, 300, 0, 16, 6, 19000, 0, 400, -1, 0, 50, 0, 0, -10, -1, 46, 0);
INSERT INTO "items" VALUES (1087, 'MagicNecklace(DF+20)', 1, 6, 14, 4, 20, 0, 0, 0, 0, 300, 0, 16, 6, 19000, 0, 400, -1, 0, 50, 0, 0, -10, -1, 46, 0);
INSERT INTO "items" VALUES (1088, 'MagicNecklace(DF+25)', 1, 6, 14, 4, 25, 0, 0, 0, 0, 300, 0, 16, 6, 19000, 0, 400, -1, 0, 50, 0, 0, -10, -1, 46, 0);
INSERT INTO "items" VALUES (1089, 'MagicNecklace(DF+30)', 1, 6, 14, 4, 30, 0, 0, 0, 0, 300, 0, 16, 6, 19000, 0, 400, -1, 0, 50, 0, 0, -10, -1, 46, 0);
INSERT INTO "items" VALUES (1090, 'MagicNecklace(DM+2)', 1, 6, 14, 3, 2, 0, 0, 0, 0, 300, 0, 16, 5, 39800, 0, 400, -1, 0, 65, 0, 0, -10, -1, 46, 0);
INSERT INTO "items" VALUES (1091, 'MagicNecklace(DM+3)', 1, 6, 14, 3, 3, 0, 0, 0, 0, 300, 0, 16, 5, 39800, 0, 400, -1, 0, 65, 0, 0, -10, -1, 46, 0);
INSERT INTO "items" VALUES (1092, 'MagicNecklace(DM+4)', 1, 6, 14, 3, 4, 0, 0, 0, 0, 300, 0, 16, 5, 39800, 0, 400, -1, 0, 65, 0, 0, -10, -1, 46, 0);
INSERT INTO "items" VALUES (1093, 'MagicNecklace(DM+5)', 1, 6, 14, 3, 5, 0, 0, 0, 0, 300, 0, 16, 5, 39800, 0, 400, -1, 0, 65, 0, 0, -10, -1, 46, 0);
INSERT INTO "items" VALUES (1094, 'MagicNecklace(MS12)', 1, 6, 14, 2, 12, 0, 0, 0, 0, 300, 0, 16, 7, 7000, 0, 400, -1, 0, 50, 0, 0, -10, -1, 46, 0);
INSERT INTO "items" VALUES (1095, 'MagicNecklace(MS14)', 1, 6, 14, 2, 14, 0, 0, 0, 0, 300, 0, 16, 7, 7000, 0, 400, -1, 0, 50, 0, 0, -10, -1, 46, 0);
INSERT INTO "items" VALUES (1096, 'MagicNecklace(MS16)', 1, 6, 14, 2, 16, 0, 0, 0, 0, 300, 0, 16, 7, 7000, 0, 400, -1, 0, 50, 0, 0, -10, -1, 46, 0);
INSERT INTO "items" VALUES (1097, 'MagicNecklace(MS18)', 1, 6, 14, 2, 18, 0, 0, 0, 0, 300, 0, 16, 7, 7000, 0, 400, -1, 0, 50, 0, 0, -10, -1, 46, 0);
INSERT INTO "items" VALUES (1098, 'MagicNecklace(RM15)', 1, 6, 14, 1, 15, 0, 0, 0, 0, 300, 0, 16, 4, 2250, 0, 400, -1, 0, 30, 0, 0, -10, -1, 46, 0);
INSERT INTO "items" VALUES (1099, 'MagicNecklace(RM20)', 1, 6, 14, 1, 20, 0, 0, 0, 0, 300, 0, 16, 4, 2250, 0, 400, -1, 0, 30, 0, 0, -10, -1, 46, 0);
INSERT INTO "items" VALUES (1100, 'MagicNecklace(RM25)', 1, 6, 14, 1, 25, 0, 0, 0, 0, 300, 0, 16, 4, 2250, 0, 400, -1, 0, 30, 0, 0, -10, -1, 46, 0);
INSERT INTO "items" VALUES (1101, 'MagicNecklace(RM30)', 1, 6, 14, 1, 30, 0, 0, 0, 0, 300, 0, 16, 4, 2250, 0, 400, -1, 0, 30, 0, 0, -10, -1, 46, 0);
INSERT INTO "items" VALUES (1102, 'DiamondWare', 12, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 22, 1, 5000, 0, 200, 1, 0, 0, 30, 0, 0, -1, 46, 0);
INSERT INTO "items" VALUES (1103, 'RubyWare', 12, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 22, 3, 3000, 0, 200, 1, 0, 0, 30, 0, 0, -1, 46, 0);
INSERT INTO "items" VALUES (1104, 'SapphireWare', 12, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 22, 4, 3000, 0, 200, 1, 0, 0, 30, 0, 0, -1, 46, 0);
INSERT INTO "items" VALUES (1105, 'EmeraldWare', 12, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 22, 2, 3000, 0, 200, 1, 0, 0, 30, 0, 0, -1, 46, 0);
INSERT INTO "items" VALUES (1106, 'CrystalWare', 12, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 22, 5, 500, 0, 200, 1, 0, 0, 30, 0, 0, -1, 46, 0);
INSERT INTO "items" VALUES (1107, 'CraftingVessel', 10, 0, 0, 1, 0, 0, 0, 0, 0, 300, 0, 22, 0, 1000, 0, 700, -1, 0, 0, 0, 0, 0, -1, 21, 0);
INSERT INTO "items" VALUES (1108, 'AngelicPandent(STR)', 1, 11, 14, 16, 0, 0, 0, 0, 0, 300, 0, 22, 11, 3000, 0, 200, -1, 0, 0, 0, 60, -10, -1, 46, 6);
INSERT INTO "items" VALUES (1109, 'AngelicPandent(DEX)', 1, 11, 14, 17, 0, 0, 0, 0, 0, 300, 0, 22, 10, 3000, 0, 200, -1, 0, 0, 0, 60, -10, -1, 46, 6);
INSERT INTO "items" VALUES (1110, 'AngelicPandent(INT)', 1, 11, 14, 18, 0, 0, 0, 0, 0, 300, 0, 22, 12, 3000, 0, 200, -1, 0, 0, 0, 60, -10, -1, 46, 6);
INSERT INTO "items" VALUES (1111, 'AngelicPandent(MAG)', 1, 11, 14, 19, 0, 0, 0, 0, 0, 300, 0, 22, 13, 3000, 0, 200, -1, 0, 0, 0, 60, -10, -1, 46, 6);

-- ----------------------------
-- Table structure for magic_configs
-- ----------------------------
DROP TABLE IF EXISTS "magic_configs";
CREATE TABLE "magic_configs" (
  "magic_id" INTEGER,
  "name" TEXT NOT NULL,
  "magic_type" INTEGER NOT NULL,
  "delay_time" INTEGER NOT NULL,
  "last_time" INTEGER NOT NULL,
  "value1" INTEGER NOT NULL,
  "value2" INTEGER NOT NULL,
  "value3" INTEGER NOT NULL,
  "value4" INTEGER NOT NULL,
  "value5" INTEGER NOT NULL,
  "value6" INTEGER NOT NULL,
  "value7" INTEGER NOT NULL,
  "value8" INTEGER NOT NULL,
  "value9" INTEGER NOT NULL,
  "value10" INTEGER NOT NULL,
  "value11" INTEGER NOT NULL,
  "value12" INTEGER NOT NULL,
  "int_limit" INTEGER NOT NULL,
  "gold_cost" INTEGER NOT NULL,
  "category" INTEGER NOT NULL,
  "attribute" INTEGER NOT NULL,
  PRIMARY KEY ("magic_id")
);

-- ----------------------------
-- Records of magic_configs
-- ----------------------------
INSERT INTO "magic_configs" VALUES (0, 'Magic-Missile', 1, 0, 0, 8, 1, 1, 1, 8, 0, 0, 0, 0, 0, 0, 0, 18, 100, 1, 2);
INSERT INTO "magic_configs" VALUES (1, 'Heal', 2, 0, 0, 15, 1, 1, 2, 6, 10, 0, 0, 0, 0, 0, 0, 20, 100, 0, 4);
INSERT INTO "magic_configs" VALUES (2, 'Create-Food', 10, 0, 0, 18, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 18, 100, 0, 0);
INSERT INTO "magic_configs" VALUES (10, 'Energy-Bolt', 3, 0, 0, 15, 2, 2, 2, 4, 1, 2, 4, 1, 0, 0, 0, 24, 200, 1, 2);
INSERT INTO "magic_configs" VALUES (11, 'Staminar-Drain', 5, 0, 0, 14, 3, 3, 4, 6, 10, 2, 6, 5, 0, 0, 0, 22, 200, 1, 0);
INSERT INTO "magic_configs" VALUES (12, 'Recall', 8, 0, 0, 15, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 20, 120, 0, 0);
INSERT INTO "magic_configs" VALUES (13, 'Defense-Shield', 11, 0, 60, 19, 1, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 26, 200, 2, 0);
INSERT INTO "magic_configs" VALUES (14, 'Celebrating-Light', 5, 0, 0, 20, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 25, 400, 0, 0);
INSERT INTO "magic_configs" VALUES (20, 'Fire-Ball', 3, 0, 0, 27, 2, 2, 2, 6, 2, 2, 6, 2, 0, 0, 0, 26, 500, 1, 3);
INSERT INTO "magic_configs" VALUES (21, 'Great-Heal', 2, 0, 0, 28, 1, 1, 4, 10, 20, 0, 0, 0, 0, 0, 0, 28, 500, 0, 0);
INSERT INTO "magic_configs" VALUES (23, 'Staminar-Recovery', 7, 0, 0, 20, 3, 3, 4, 8, 8, 2, 6, 5, 0, 0, 0, 20, 300, 0, 0);
INSERT INTO "magic_configs" VALUES (24, 'Protection-From-Arrow', 11, 0, 60, 22, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 20, 300, 2, 0);
INSERT INTO "magic_configs" VALUES (25, 'Hold-Person', 12, 0, 30, 24, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 26, 500, 1, 0);
INSERT INTO "magic_configs" VALUES (26, 'Possession', 15, 0, 0, 25, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 26, 500, 1, 0);
INSERT INTO "magic_configs" VALUES (27, 'Poison', 17, 0, 0, 28, 1, 1, 1, 15, 0, 0, 0, 0, 0, 0, 0, 29, 700, 1, 1);
INSERT INTO "magic_configs" VALUES (28, 'Great-Staminar-Recov.', 7, 0, 0, 45, 3, 3, 4, 16, 16, 2, 12, 10, 0, 0, 0, 30, 800, 0, 0);
INSERT INTO "magic_configs" VALUES (30, 'Fire-Strike', 3, 0, 0, 36, 2, 2, 2, 8, 3, 2, 8, 3, 0, 0, 0, 34, 1000, 1, 3);
INSERT INTO "magic_configs" VALUES (31, 'Summon-Creature', 9, 0, 0, 35, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 38, 1000, 1, 1);
INSERT INTO "magic_configs" VALUES (32, 'Invisibility', 13, 0, 60, 31, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 30, 800, 1, 0);
INSERT INTO "magic_configs" VALUES (33, 'Protection-From-Magic', 11, 0, 60, 35, 1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 32, 850, 2, 0);
INSERT INTO "magic_configs" VALUES (34, 'Detect-Invisibility', 13, 0, 0, 33, 1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 30, 700, 0, 0);
INSERT INTO "magic_configs" VALUES (35, 'Paralyze', 12, 0, 50, 35, 1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 36, 1000, 1, 0);
INSERT INTO "magic_configs" VALUES (36, 'Cure', 17, 0, 0, 32, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 35, 700, 0, 1);
INSERT INTO "magic_configs" VALUES (37, 'Lightning-Arrow', 1, 0, 0, 32, 1, 1, 4, 5, 10, 0, 0, 0, 0, 0, 0, 38, 1100, 1, 2);
INSERT INTO "magic_configs" VALUES (38, 'Tremor', 22, 0, 0, 34, 2, 2, 3, 4, 3, 3, 4, 3, 0, 0, 0, 33, 1000, 1, 1);
INSERT INTO "magic_configs" VALUES (40, 'Fire-Wall', 14, 0, 30, 42, 1, 1, 2, 8, 0, 2, 8, 0, 1, 1, 2, 45, 1200, 1, 3);
INSERT INTO "magic_configs" VALUES (41, 'Fire-Field', 14, 0, 30, 48, 1, 1, 2, 8, 0, 2, 8, 0, 1, 2, 1, 48, 1400, 1, 3);
INSERT INTO "magic_configs" VALUES (42, 'Confuse-Language', 16, 0, 120, 40, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 42, 1300, 1, 0);
INSERT INTO "magic_configs" VALUES (43, 'Lightning', 1, 0, 0, 44, 1, 1, 4, 7, 12, 0, 0, 0, 0, 0, 0, 47, 1700, 1, 2);
INSERT INTO "magic_configs" VALUES (44, 'Great-Defense-Shield', 11, 0, 40, 45, 1, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 46, 1500, 2, 0);
INSERT INTO "magic_configs" VALUES (45, 'Chill-Wind', 23, 0, 0, 48, 2, 2, 2, 8, 3, 2, 8, 3, 5, 0, 0, 50, 2000, 1, 4);
INSERT INTO "magic_configs" VALUES (46, 'Poison-Cloud', 14, 0, 30, 48, 1, 1, 0, 15, 0, 0, 0, 0, 10, 2, 1, 49, 1800, 1, 1);
INSERT INTO "magic_configs" VALUES (47, 'Triple-Energy-Bolt', 3, 0, 0, 40, 2, 2, 2, 4, 2, 3, 8, 3, 0, 0, 0, 45, 1700, 1, 2);
INSERT INTO "magic_configs" VALUES (50, 'Berserk', 18, 0, 40, 57, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 59, 2200, 1, 0);
INSERT INTO "magic_configs" VALUES (51, 'Lightning-Bolt', 19, 0, 0, 58, 2, 2, 4, 5, 18, 4, 2, 6, 0, 0, 0, 58, 2500, 1, 2);
INSERT INTO "magic_configs" VALUES (53, 'Mass-Poison', 17, 0, 0, 54, 1, 1, 1, 40, 0, 0, 0, 0, 0, 0, 0, 52, 2100, 1, 1);
INSERT INTO "magic_configs" VALUES (54, 'Spike-Field', 14, 0, 30, 56, 1, 1, 2, 8, 0, 2, 8, 0, 9, 2, 2, 56, 2300, 1, 1);
INSERT INTO "magic_configs" VALUES (55, 'Ice-Storm', 14, 0, 30, 58, 1, 1, 4, 0, 0, 0, 0, 0, 8, 1, 0, 59, -1, 1, 4);
INSERT INTO "magic_configs" VALUES (56, 'Mass-Lightning-Arrow', 1, 0, 0, 55, 1, 1, 5, 6, 20, 0, 0, 0, 0, 0, 0, 53, 3000, 1, 2);
INSERT INTO "magic_configs" VALUES (57, 'Ice-Strike', 23, 0, 0, 59, 2, 2, 5, 6, 12, 0, 0, 0, 4, 0, 0, 60, 4200, 1, 4);
INSERT INTO "magic_configs" VALUES (60, 'Energy-Strike', 21, 0, 0, 65, 2, 2, 0, 0, 0, 7, 6, 17, 0, 0, 0, 67, 5000, 1, 2);
INSERT INTO "magic_configs" VALUES (61, 'Mass-Fire-Strike', 3, 0, 0, 80, 2, 3, 5, 6, 12, 7, 10, 18, 0, 0, 0, 85, -1, 1, 3);
INSERT INTO "magic_configs" VALUES (62, 'Confusion', 16, 0, 20, 78, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 75, 7500, 1, 0);
INSERT INTO "magic_configs" VALUES (63, 'Mass-Chill-Wind', 23, 0, 0, 90, 2, 2, 3, 8, 6, 3, 8, 6, 10, 0, 0, 93, 9800, 1, 4);
INSERT INTO "magic_configs" VALUES (64, 'Earthworm-Strike', 25, 0, 0, 80, 2, 2, 7, 6, 17, 7, 6, 17, 0, 0, 0, 97, 12000, 1, 1);
INSERT INTO "magic_configs" VALUES (65, 'Absolute-Magic-Protect.', 11, 0, 60, 90, 1, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 112, 13500, 2, 0);
INSERT INTO "magic_configs" VALUES (66, 'Armor-Break', 28, 0, 0, 90, 1, 1, 7, 6, 17, 7, 6, 17, 15, 0, 0, 97, 20000, 1, 1);
INSERT INTO "magic_configs" VALUES (67, 'Scan', 33, 0, 0, 50, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 70, 7500, 1, 1);
INSERT INTO "magic_configs" VALUES (70, 'Bloody-Shock-Wave', 19, 0, 0, 120, 2, 2, 5, 8, 20, 5, 4, 9, 0, 0, 0, 105, -1, 1, 2);
INSERT INTO "magic_configs" VALUES (71, 'Mass-Confusion', 16, 0, 60, 125, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 130, 15000, 1, 0);
INSERT INTO "magic_configs" VALUES (72, 'Mass-Ice-Strike', 23, 0, 0, 120, 2, 2, 7, 8, 25, 0, 0, 0, 7, 0, 0, 133, 21000, 1, 4);
INSERT INTO "magic_configs" VALUES (73, 'Cloud-Kill', 14, 0, 30, 130, 1, 1, 0, 40, 0, 0, 0, 0, 10, 2, 2, 120, 20000, 1, 1);
INSERT INTO "magic_configs" VALUES (74, 'Lightning-Strike', 21, 0, 0, 90, 2, 2, 0, 0, 0, 7, 7, 20, 0, 0, 0, 123, 35000, 1, 2);
INSERT INTO "magic_configs" VALUES (76, 'Cancellation', 29, 0, 30, 120, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 135, -200, 1, 0);
INSERT INTO "magic_configs" VALUES (77, 'Illusion-Movement', 21, 0, 0, 130, 2, 2, 0, 0, 0, 7, 7, 20, 0, 0, 0, 160, 27000, 1, 2);
INSERT INTO "magic_configs" VALUES (78, 'Haste', 45, 0, 5, 60, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 150, -1, 1, 0);
INSERT INTO "magic_configs" VALUES (80, 'Illusion', 16, 0, 20, 143, 2, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 150, 27000, 1, 0);
INSERT INTO "magic_configs" VALUES (81, 'Meteor-Strike', 21, 0, 0, 120, 2, 2, 6, 8, 12, 7, 12, 18, 0, 0, 0, 169, 40000, 1, 3);
INSERT INTO "magic_configs" VALUES (82, 'Mass-Magic-Missile', 21, 0, 0, 160, 3, 3, 0, 0, 0, 7, 7, 30, 0, 0, 0, 185, 45000, 1, 2);
INSERT INTO "magic_configs" VALUES (83, 'Inhibition-Casting', 31, 0, 0, 180, 1, 1, 8, 20, 30, 4, 10, 30, 0, 0, 0, 180, -1, 0, 0);
INSERT INTO "magic_configs" VALUES (90, 'Mass-Illusion', 16, 0, 60, 200, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 180, 35000, 1, 0);
INSERT INTO "magic_configs" VALUES (91, 'Blizzard', 26, 0, 20, 170, 3, 3, 5, 1, 20, 7, 8, 16, 2, 0, 0, 195, 43000, 1, 4);
INSERT INTO "magic_configs" VALUES (94, 'Resurrection', 32, 600, 0, 200, 2, 2, 3, 0, 0, 7, 7, 20, 0, 0, 0, 0, -1, 1, 2);
INSERT INTO "magic_configs" VALUES (95, 'Mass-Illusion-Movement', 21, 0, 0, 200, 2, 2, 0, 0, 0, 7, 7, 20, 0, 0, 0, 200, 27000, 1, 2);
INSERT INTO "magic_configs" VALUES (96, 'Earth-Shock-Wave', 30, 0, 0, 180, 2, 2, 5, 1, 20, 7, 8, 16, 0, 0, 0, 200, -1, 1, 1);

-- ----------------------------
-- Table structure for maps
-- ----------------------------
DROP TABLE IF EXISTS "maps";
CREATE TABLE "maps" (
  "map_index" INTEGER,
  "map_name" TEXT NOT NULL,
  PRIMARY KEY ("map_index")
);

-- ----------------------------
-- Records of maps
-- ----------------------------
INSERT INTO "maps" VALUES (0, 'default');
INSERT INTO "maps" VALUES (1, 'inferniaB');
INSERT INTO "maps" VALUES (2, 'inferniaA');
INSERT INTO "maps" VALUES (3, 'maze');
INSERT INTO "maps" VALUES (4, 'druncncity');
INSERT INTO "maps" VALUES (5, 'procella');
INSERT INTO "maps" VALUES (6, 'abaddon');
INSERT INTO "maps" VALUES (7, 'aresden');
INSERT INTO "maps" VALUES (8, 'arefarm');
INSERT INTO "maps" VALUES (9, 'aresdend1');
INSERT INTO "maps" VALUES (10, 'arebrk11');
INSERT INTO "maps" VALUES (11, 'arebrk12');
INSERT INTO "maps" VALUES (12, 'arebrk21');
INSERT INTO "maps" VALUES (13, 'arebrk22');
INSERT INTO "maps" VALUES (14, 'wrhus_1');
INSERT INTO "maps" VALUES (15, 'cityhall_1');
INSERT INTO "maps" VALUES (16, 'arewrhus');
INSERT INTO "maps" VALUES (17, 'resurr1');
INSERT INTO "maps" VALUES (18, 'gshop_1');
INSERT INTO "maps" VALUES (19, 'arejail');
INSERT INTO "maps" VALUES (20, 'cath_1');
INSERT INTO "maps" VALUES (21, 'wzdtwr_1');
INSERT INTO "maps" VALUES (22, 'gshop_1f');
INSERT INTO "maps" VALUES (23, 'wrhus_1f');
INSERT INTO "maps" VALUES (24, 'bsmith_1f');
INSERT INTO "maps" VALUES (25, 'bsmith_1');
INSERT INTO "maps" VALUES (26, 'gldhall_1');
INSERT INTO "maps" VALUES (27, 'CmdHall_1');
INSERT INTO "maps" VALUES (28, 'dglv2');
INSERT INTO "maps" VALUES (29, 'dglv3');
INSERT INTO "maps" VALUES (30, 'dglv4');
INSERT INTO "maps" VALUES (31, 'elvine');
INSERT INTO "maps" VALUES (32, 'elvfarm');
INSERT INTO "maps" VALUES (33, 'elvbrk11');
INSERT INTO "maps" VALUES (34, 'elvbrk12');
INSERT INTO "maps" VALUES (35, 'elvbrk21');
INSERT INTO "maps" VALUES (36, 'elvbrk22');
INSERT INTO "maps" VALUES (37, 'elvined1');
INSERT INTO "maps" VALUES (38, 'elvjail');
INSERT INTO "maps" VALUES (39, 'elvwrhus');
INSERT INTO "maps" VALUES (40, 'gldhall_2');
INSERT INTO "maps" VALUES (41, 'gshop_2');
INSERT INTO "maps" VALUES (42, 'gshop_2f');
INSERT INTO "maps" VALUES (43, 'resurr2');
INSERT INTO "maps" VALUES (44, 'wrhus_2');
INSERT INTO "maps" VALUES (45, 'wrhus_2f');
INSERT INTO "maps" VALUES (46, 'wzdtwr_2');
INSERT INTO "maps" VALUES (47, 'bsmith_2');
INSERT INTO "maps" VALUES (48, 'bsmith_2f');
INSERT INTO "maps" VALUES (49, 'cath_2');
INSERT INTO "maps" VALUES (50, 'cityhall_2');
INSERT INTO "maps" VALUES (51, 'CmdHall_2');
INSERT INTO "maps" VALUES (52, 'BtField');
INSERT INTO "maps" VALUES (53, 'GodH');
INSERT INTO "maps" VALUES (54, 'HRampart');
INSERT INTO "maps" VALUES (55, 'areuni');
INSERT INTO "maps" VALUES (56, 'elvuni');
INSERT INTO "maps" VALUES (57, 'huntzone1');
INSERT INTO "maps" VALUES (58, 'huntzone2');
INSERT INTO "maps" VALUES (59, 'huntzone3');
INSERT INTO "maps" VALUES (60, 'huntzone4');
INSERT INTO "maps" VALUES (61, 'middleland');
INSERT INTO "maps" VALUES (62, '2ndmiddle');
INSERT INTO "maps" VALUES (63, 'middled1n');
INSERT INTO "maps" VALUES (64, 'middled1x');
INSERT INTO "maps" VALUES (65, 'bisle');
INSERT INTO "maps" VALUES (66, 'fightzone1');
INSERT INTO "maps" VALUES (67, 'fightzone2');
INSERT INTO "maps" VALUES (68, 'fightzone3');
INSERT INTO "maps" VALUES (69, 'fightzone4');
INSERT INTO "maps" VALUES (70, 'fightzone5');
INSERT INTO "maps" VALUES (71, 'fightzone6');
INSERT INTO "maps" VALUES (72, 'fightzone7');
INSERT INTO "maps" VALUES (73, 'fightzone8');
INSERT INTO "maps" VALUES (74, 'fightzone9');
INSERT INTO "maps" VALUES (75, 'toh1');
INSERT INTO "maps" VALUES (76, 'toh2');
INSERT INTO "maps" VALUES (77, 'toh3');

-- ----------------------------
-- Table structure for meta
-- ----------------------------
DROP TABLE IF EXISTS "meta";
CREATE TABLE "meta" (
  "key" TEXT,
  "value" TEXT NOT NULL,
  PRIMARY KEY ("key")
);

-- ----------------------------
-- Records of meta
-- ----------------------------
INSERT INTO "meta" VALUES ('schema_version', '2');

-- ----------------------------
-- Table structure for npc_configs
-- ----------------------------
DROP TABLE IF EXISTS "npc_configs";
CREATE TABLE "npc_configs" (
  "npc_id" INTEGER,
  "name" TEXT NOT NULL,
  "npc_type" INTEGER NOT NULL,
  "hit_dice" INTEGER NOT NULL,
  "defense_ratio" INTEGER NOT NULL,
  "hit_ratio" INTEGER NOT NULL,
  "min_bravery" INTEGER NOT NULL,
  "exp_min" INTEGER NOT NULL,
  "exp_max" INTEGER NOT NULL,
  "gold_min" INTEGER NOT NULL,
  "gold_max" INTEGER NOT NULL,
  "attack_dice_throw" INTEGER NOT NULL,
  "attack_dice_range" INTEGER NOT NULL,
  "npc_size" INTEGER NOT NULL,
  "side" INTEGER NOT NULL,
  "action_limit" INTEGER NOT NULL,
  "action_time" INTEGER NOT NULL,
  "resist_magic" INTEGER NOT NULL,
  "magic_level" INTEGER NOT NULL,
  "day_of_week_limit" INTEGER NOT NULL,
  "chat_msg_presence" INTEGER NOT NULL,
  "target_search_range" INTEGER NOT NULL,
  "regen_time" INTEGER NOT NULL,
  "attribute" INTEGER NOT NULL,
  "abs_damage" INTEGER NOT NULL,
  "max_mana" INTEGER NOT NULL,
  "magic_hit_ratio" INTEGER NOT NULL,
  "attack_range" INTEGER NOT NULL,
  PRIMARY KEY ("npc_id")
);

-- ----------------------------
-- Records of npc_configs
-- ----------------------------
INSERT INTO "npc_configs" VALUES (0, 'Slime', 10, 2, 10, 30, 1, 120, 220, 11, 32, 1, 4, 0, 10, 0, 2100, 5, 0, 10, 0, 2, 5000, 1, 0, 0, 0, 1);
INSERT INTO "npc_configs" VALUES (1, 'Rabbit', 55, 4, 10, 35, 2, 150, 260, 12, 33, 1, 5, 0, 0, 0, 1500, 5, 0, 10, 0, 2, 5000, 1, 0, 0, 0, 1);
INSERT INTO "npc_configs" VALUES (2, 'Cat', 56, 4, 20, 45, 3, 200, 260, 12, 33, 2, 4, 0, 0, 0, 1500, 20, 0, 10, 0, 5, 5000, 1, 0, 0, 0, 1);
INSERT INTO "npc_configs" VALUES (3, 'Giant-Ant', 16, 3, 15, 40, 2, 300, 350, 13, 34, 2, 3, 0, 10, 0, 1200, 10, 0, 10, 0, 2, 5000, 1, 0, 0, 0, 1);
INSERT INTO "npc_configs" VALUES (4, 'Amphis', 22, 4, 30, 50, 1, 300, 400, 13, 35, 2, 4, 0, 10, 0, 1000, 20, 0, 10, 0, 3, 5000, 1, 0, 0, 0, 1);
INSERT INTO "npc_configs" VALUES (5, 'Orc', 14, 4, 35, 70, 2, 560, 700, 16, 39, 3, 3, 0, 10, 0, 1200, 25, 0, 10, 0, 5, 5000, 1, 0, 0, 0, 1);
INSERT INTO "npc_configs" VALUES (6, 'Dummy', 34, 10, 15, 300, 100, 500, 1000, 17, 41, 0, 0, 1, 10, 3, 2100, 5, 0, 10, 0, 7, 3000, 2, 0, 0, 0, 1);
INSERT INTO "npc_configs" VALUES (7, 'Attack-Dummy', 34, 10, 15, 300, 100, 750, 1500, 21, 46, 0, 0, 1, 10, 0, 2100, 5, 0, 10, 0, 7, 3000, 2, 0, 0, 0, 1);
INSERT INTO "npc_configs" VALUES (8, 'Zombie', 18, 10, 40, 90, 100, 1200, 1500, 23, 50, 4, 4, 0, 10, 0, 1500, 30, 0, 10, 0, 6, 5000, 1, 0, 0, 0, 1);
INSERT INTO "npc_configs" VALUES (9, 'Scorpion', 17, 6, 35, 80, 3, 1300, 1600, 24, 51, 5, 3, 0, 10, 0, 1200, 30, 0, 10, 0, 4, 5000, 1, 0, 0, 0, 1);
INSERT INTO "npc_configs" VALUES (10, 'Skeleton', 11, 8, 40, 100, 100, 1500, 1600, 25, 53, 5, 4, 0, 10, 0, 800, 40, 0, 10, 0, 5, 5000, 1, 0, 0, 0, 2);
INSERT INTO "npc_configs" VALUES (11, 'Orc-Mage', 14, 12, 35, 100, 3, 1200, 1260, 22, 48, 4, 3, 0, 10, 0, 1500, 45, 3, 10, 0, 6, 5000, 1, 0, 150, 10, 1);
INSERT INTO "npc_configs" VALUES (12, 'Clay-Golem', 23, 30, 100, 150, 100, 3900, 5000, 54, 96, 7, 4, 1, 10, 0, 1200, 50, 0, 10, 0, 5, 10000, 1, 0, 0, 0, 1);
INSERT INTO "npc_configs" VALUES (13, 'Stone-Golem', 12, 25, 110, 150, 100, 2500, 5000, 47, 86, 7, 4, 1, 10, 0, 1200, 50, 0, 10, 0, 5, 10000, 1, 0, 0, 0, 1);
INSERT INTO "npc_configs" VALUES (14, 'Hellbound', 27, 35, 90, 170, 4, 5000, 5500, 62, 108, 7, 5, 0, 10, 0, 900, 60, 5, 10, 0, 7, 10000, 3, 0, 250, 20, 1);
INSERT INTO "npc_configs" VALUES (15, 'Giant-Frog', 57, 35, 90, 170, 4, 4516, 6555, 65, 113, 7, 5, 0, 10, 0, 900, 60, 0, 10, 0, 7, 10000, 1, 0, 0, 20, 2);
INSERT INTO "npc_configs" VALUES (16, 'Rudolph', 61, 40, 100, 180, 10, 4526, 4912, 57, 100, 7, 5, 0, 10, 0, 1000, 60, 5, 10, 0, 5, 10000, 3, 0, 0, 0, 1);
INSERT INTO "npc_configs" VALUES (17, 'Troll', 28, 55, 85, 200, 100, 3220, 3500, 43, 80, 8, 5, 1, 10, 0, 700, 60, 0, 10, 0, 7, 10000, 1, 0, 0, 0, 1);
INSERT INTO "npc_configs" VALUES (18, 'Cyclops', 13, 60, 100, 180, 805, 6511, 8710, 86, 144, 8, 6, 1, 10, 0, 1200, 65, 5, 10, 0, 7, 10000, 3, 0, 450, 50, 3);
INSERT INTO "npc_configs" VALUES (19, 'Ice-Golem', 65, 60, 100, 180, 100, 6244, 7560, 79, 133, 8, 6, 1, 10, 0, 1200, 65, 11, 10, 0, 7, 10000, 4, 30, 0, 200, 1);
INSERT INTO "npc_configs" VALUES (20, 'Beholder', 53, 100, 100, 450, 100, 9050, 9800, 104, 171, 8, 8, 1, 10, 0, 800, 70, 0, 10, 0, 7, 10000, 2, 30, 0, 200, 4);
INSERT INTO "npc_configs" VALUES (21, 'Cannibal-Plant', 60, 105, 80, 230, 100, 6522, 7543, 80, 135, 8, 8, 1, 10, 0, 800, 70, 5, 10, 0, 7, 10000, 1, 0, 550, 65, 2);
INSERT INTO "npc_configs" VALUES (22, 'Orge', 29, 115, 150, 230, 100, 7212, 8312, 87, 146, 8, 7, 1, 10, 0, 700, 70, 0, 10, 0, 7, 10000, 2, 0, 0, 0, 3);
INSERT INTO "npc_configs" VALUES (23, 'Mountain-Giant', 58, 100, 250, 230, 100, 19872, 19883, 208, 328, 8, 7, 1, 10, 0, 700, 75, 0, 10, 0, 7, 10000, 1, 20, 0, 0, 2);
INSERT INTO "npc_configs" VALUES (24, 'DireBoar', 62, 130, 80, 230, 100, 6441, 7212, 78, 132, 8, 8, 0, 10, 0, 800, 70, 0, 10, 0, 7, 10000, 1, 0, 0, 0, 1);
INSERT INTO "npc_configs" VALUES (25, 'Tentocle', 80, 80, 150, 180, 100, 6005, 6200, 71, 121, 7, 6, 2, 10, 0, 400, 65, 6, 10, 0, 5, 10000, 1, 0, 500, 80, 3);
INSERT INTO "npc_configs" VALUES (26, 'Giant-Crayfish', 74, 70, 150, 200, 100, 9655, 10651, 111, 182, 7, 7, 1, 10, 0, 400, 60, 0, 10, 0, 5, 10000, 4, 0, 0, 0, 2);
INSERT INTO "npc_configs" VALUES (27, 'Giant-Plant', 76, 100, 120, 200, 100, 8321, 9321, 98, 162, 8, 6, 1, 10, 0, 700, 70, 0, 10, 0, 5, 10000, 1, 0, 0, 0, 2);
INSERT INTO "npc_configs" VALUES (28, 'Liche', 30, 130, 300, 230, 100, 8982, 9543, 102, 168, 8, 6, 1, 10, 0, 700, 75, 6, 10, 0, 7, 10000, 4, 10, 1000, 80, 5);
INSERT INTO "npc_configs" VALUES (29, 'Stalker', 48, 130, 200, 300, 100, 25321, 25902, 266, 414, 8, 9, 1, 10, 0, 600, 80, 0, 10, 0, 7, 10000, 1, 20, 0, 0, 4);
INSERT INTO "npc_configs" VALUES (30, 'WereWolf', 33, 140, 180, 300, 100, 15221, 19326, 182, 289, 8, 8, 1, 10, 0, 700, 80, 0, 10, 0, 7, 10000, 1, 20, 0, 0, 1);
INSERT INTO "npc_configs" VALUES (31, 'Dark-Elf', 54, 140, 200, 450, 100, 4521, 4834, 56, 100, 8, 4, 1, 10, 0, 700, 60, 0, 10, 0, 8, 10000, 1, 50, 0, 0, 8);
INSERT INTO "npc_configs" VALUES (32, 'Frost', 63, 130, 300, 230, 100, 4211, 6542, 63, 110, 8, 6, 1, 10, 0, 700, 75, 10, 10, 0, 7, 10000, 4, 10, 700, 80, 3);
INSERT INTO "npc_configs" VALUES (33, 'Claw-Turtle', 72, 120, 200, 280, 100, 56212, 56899, 575, 878, 8, 9, 1, 10, 0, 500, 80, 0, 10, 0, 5, 10000, 4, 0, 0, 0, 2);
INSERT INTO "npc_configs" VALUES (34, 'Barlog', 70, 500, 400, 500, 100, 26541, 27981, 282, 438, 9, 10, 1, 10, 0, 500, 90, 7, 10, 0, 5, 10000, 3, 10, 2000, 80, 3);
INSERT INTO "npc_configs" VALUES (35, 'Ettin', 59, 180, 350, 350, 100, 35561, 39564, 385, 593, 8, 9, 1, 10, 0, 700, 90, 0, 10, 0, 7, 10000, 2, 65, 0, 0, 3);
INSERT INTO "npc_configs" VALUES (36, 'Demon', 31, 340, 450, 500, 100, 122000, 161200, 1426, 2154, 10, 10, 1, 10, 0, 700, 100, 7, 10, 0, 7, 60000, 3, 75, 2000, 250, 4);
INSERT INTO "npc_configs" VALUES (37, 'Unicorn', 32, 340, 450, 500, 100, 25611, 25666, 266, 414, 10, 10, 1, 0, 0, 700, 100, 8, 10, 0, 7, 60000, 2, 75, 2000, 250, 4);
INSERT INTO "npc_configs" VALUES (38, 'Gagoyle', 52, 400, 450, 500, 100, 162130, 166540, 1653, 2495, 13, 10, 1, 10, 0, 700, 70, 7, 10, 0, 7, 60000, 3, 80, 2000, 250, 5);
INSERT INTO "npc_configs" VALUES (39, 'Centaurus', 71, 350, 450, 500, 100, 452321, 351321, 4028, 6057, 12, 11, 1, 10, 0, 500, 100, 8, 10, 0, 5, 10000, 1, 0, 2000, 80, 3);
INSERT INTO "npc_configs" VALUES (40, 'Giant-Lizard', 75, 450, 400, 400, 100, 56894, 65411, 621, 947, 10, 10, 1, 10, 0, 600, 90, 8, 10, 0, 5, 10000, 4, 0, 700, 80, 2);
INSERT INTO "npc_configs" VALUES (41, 'MasterMage-Orc', 77, 250, 300, 300, 100, 56431, 65412, 619, 943, 8, 7, 1, 10, 0, 500, 100, 7, 10, 0, 5, 10000, 3, 0, 1500, 80, 3);
INSERT INTO "npc_configs" VALUES (42, 'Minotaurs', 78, 340, 500, 500, 100, 60212, 65421, 638, 972, 13, 11, 1, 10, 0, 500, 60, 0, 10, 0, 5, 10000, 1, 0, 0, 0, 2);
INSERT INTO "npc_configs" VALUES (43, 'Nizie', 79, 280, 300, 300, 100, 65132, 65421, 662, 1009, 10, 10, 1, 10, 0, 500, 90, 10, 10, 0, 5, 10000, 4, 0, 2000, 80, 3);
INSERT INTO "npc_configs" VALUES (44, 'Hellclaw', 49, 1000, 450, 1000, 100, 190050, 198121, 1950, 2941, 15, 14, 1, 10, 0, 600, 100, 7, 10, 0, 7, 60000, 3, 50, 0, 0, 5);
INSERT INTO "npc_configs" VALUES (45, 'Tigerworm', 50, 2000, 550, 1200, 100, 152121, 192132, 1731, 2611, 18, 17, 1, 10, 0, 600, 100, 9, 10, 0, 7, 60000, 3, 70, 16000, 250, 6);
INSERT INTO "npc_configs" VALUES (46, 'Wyvern', 66, 2500, 1000, 1300, 100, 198945, 199995, 2004, 3022, 20, 18, 1, 10, 0, 600, 100, 12, 10, 0, 8, 60000, 4, 80, 16000, 250, 7);
INSERT INTO "npc_configs" VALUES (47, 'Fire-Wyvern', 73, 3000, 1000, 1300, 100, 251210, 263211, 2582, 3888, -10, 18, 1, 10, 0, 600, 100, 7, 10, 0, 8, 60000, 3, 80, 16000, 250, 7);
INSERT INTO "npc_configs" VALUES (48, 'Abaddon', 81, 15000, 1500, 1600, 100, 8494654, 9845165, 91709, 137578, 20, 20, 1, 10, 0, 500, 100, 13, 10, 0, 8, 60000, 2, 90, 20000, 300, 7);
INSERT INTO "npc_configs" VALUES (49, 'Crops', 64, 2000, 10, 10, 30, 0, 0, 0, 0, 0, 0, 0, 10, 5, 60000, 5, 0, 10, 0, 7, 3000, 2, 50, 0, 200, 1);
INSERT INTO "npc_configs" VALUES (50, 'Energy-Sphere', 35, 10, 10, 10, 100, 0, 0, 0, 0, 0, 0, 1, 10, 4, 60000, 5, 0, 10, 0, 7, 3000, 2, 0, 0, 0, 1);
INSERT INTO "npc_configs" VALUES (51, 'gate-a', 91, 2000, 800, 100, 100, 0, 0, 0, 0, 0, 0, 1, 1, 8, 1600, 100, 0, 10, 0, 1, 3000, 2, 0, 0, 0, 1);
INSERT INTO "npc_configs" VALUES (52, 'gate-e', 91, 2000, 800, 100, 100, 0, 0, 0, 0, 0, 0, 1, 2, 8, 1600, 100, 0, 10, 0, 1, 3000, 2, 0, 0, 0, 1);
INSERT INTO "npc_configs" VALUES (53, 'McGaffin', 67, 3000, 1000, 2000, 5, 0, 0, 0, 0, 1, 1, 0, 0, 6, 15000, 0, 0, 10, 1, 0, 10000, 0, 0, 0, 0, 4);
INSERT INTO "npc_configs" VALUES (54, 'Perry', 68, 3000, 1000, 2000, 5, 0, 0, 0, 0, 1, 1, 0, 0, 6, 5000, 0, 0, 10, 1, 0, 10000, 0, 0, 0, 0, 4);
INSERT INTO "npc_configs" VALUES (55, 'Devlin', 69, 3000, 1000, 2000, 5, 0, 0, 0, 0, 1, 1, 0, 0, 6, 30000, 0, 0, 10, 1, 0, 10000, 0, 0, 0, 0, 4);
INSERT INTO "npc_configs" VALUES (56, 'ShopKeeper-W', 15, 10, 10, 20, 5, 0, 0, 0, 0, 1, 1, 0, 0, 2, 15000, 0, 0, 10, 1, 0, 10000, 0, 0, 0, 0, 1);
INSERT INTO "npc_configs" VALUES (57, 'Gandlf', 19, 10, 10, 20, 5, 0, 0, 0, 0, 1, 1, 0, 0, 2, 5000, 0, 0, 10, 1, 0, 10000, 0, 0, 0, 0, 1);
INSERT INTO "npc_configs" VALUES (58, 'Howard', 20, 10, 10, 20, 5, 0, 0, 0, 0, 1, 1, 0, 0, 2, 30000, 0, 0, 10, 1, 0, 10000, 0, 0, 0, 0, 1);
INSERT INTO "npc_configs" VALUES (59, 'Guard-Aresden', 21, 115, 150, 230, 3, 0, 0, 0, 0, 3, 8, 0, 1, 0, 1000, 100, -10, 10, 1, 8, 10000, 2, 0, 1000, 130, 5);
INSERT INTO "npc_configs" VALUES (60, 'Guard-Elvine', 21, 115, 150, 230, 3, 0, 0, 0, 0, 3, 8, 0, 2, 0, 1000, 100, -10, 10, 1, 8, 10000, 2, 0, 1000, 130, 5);
INSERT INTO "npc_configs" VALUES (61, 'Guard-Neutral', 21, 115, 150, 230, 3, 0, 0, 0, 0, 3, 8, 0, 0, 0, 1000, 100, -10, 10, 1, 8, 10000, 2, 0, 1000, 130, 5);
INSERT INTO "npc_configs" VALUES (62, 'Tom', 24, 10, 10, 20, 1, 0, 0, 0, 0, 1, 1, 0, 0, 2, 5000, 0, 0, 10, 1, 0, 10000, 0, 0, 0, 0, 1);
INSERT INTO "npc_configs" VALUES (63, 'William', 25, 10, 10, 20, 1, 0, 0, 0, 0, 1, 1, 0, 0, 2, 5000, 0, 0, 10, 1, 0, 10000, 0, 0, 0, 0, 1);
INSERT INTO "npc_configs" VALUES (64, 'Kennedy', 26, 10, 10, 20, 1, 0, 0, 0, 0, 1, 1, 0, 0, 2, 5000, 0, 0, 10, 1, 0, 10000, 0, 0, 0, 0, 1);
INSERT INTO "npc_configs" VALUES (65, 'Gail', 90, 10, 10, 20, 1, 0, 0, 0, 0, 1, 1, 0, 0, 2, 5000, 0, 0, 10, 1, 0, 10000, 0, 0, 0, 0, 1);
INSERT INTO "npc_configs" VALUES (66, 'AGT-Aresden', 36, 500, 50, 500, 80, 2222, 2223, 500, 1500, 5, 8, 1, 1, 5, 600, 30, 0, 10, 0, 8, 3000, 2, 0, 0, 0, 8);
INSERT INTO "npc_configs" VALUES (67, 'AGT-Elvine', 36, 500, 50, 500, 80, 2222, 2223, 500, 1500, 5, 8, 1, 2, 5, 600, 30, 0, 10, 0, 8, 3000, 2, 0, 0, 0, 8);
INSERT INTO "npc_configs" VALUES (68, 'CGT-Aresden', 37, 500, 50, 500, 90, 2222, 2223, 750, 1250, 10, 14, 1, 1, 5, 1800, 30, 0, 10, 0, 8, 3000, 2, 0, 0, 0, 8);
INSERT INTO "npc_configs" VALUES (69, 'CGT-Elvine', 37, 500, 50, 500, 90, 2222, 2223, 750, 1250, 10, 14, 1, 2, 5, 1800, 30, 0, 10, 0, 8, 3000, 2, 0, 0, 0, 8);
INSERT INTO "npc_configs" VALUES (70, 'MS-Aresden', 38, 500, 50, 500, 40, 2222, 2223, 250, 1000, 0, 0, 1, 1, 5, 800, 30, 0, 10, 0, 8, 3000, 2, 0, 0, 0, 8);
INSERT INTO "npc_configs" VALUES (71, 'MS-Elvine', 38, 500, 50, 500, 40, 2222, 2223, 250, 1000, 0, 0, 1, 2, 5, 800, 30, 0, 10, 0, 8, 3000, 2, 0, 0, 0, 8);
INSERT INTO "npc_configs" VALUES (72, 'DT-Aresden', 39, 500, 50, 500, 50, 2222, 2226, 200, 800, 0, 0, 1, 1, 5, 800, 30, 0, 10, 0, 8, 3000, 2, 0, 0, 0, 8);
INSERT INTO "npc_configs" VALUES (73, 'DT-Elvine', 39, 500, 50, 500, 50, 2222, 2222, 200, 800, 0, 0, 1, 2, 5, 800, 30, 0, 10, 0, 8, 3000, 2, 0, 0, 0, 8);
INSERT INTO "npc_configs" VALUES (74, 'ESG-Aresden', 40, 500, 50, 500, 60, 2222, 2222, 500, 1000, 0, 0, 1, 1, 5, 800, 30, 0, 10, 0, 8, 3000, 2, 0, 0, 0, 8);
INSERT INTO "npc_configs" VALUES (75, 'ESG-Elvine', 40, 500, 50, 500, 60, 2222, 2222, 500, 1000, 0, 0, 1, 2, 5, 800, 30, 0, 10, 0, 8, 3000, 2, 0, 0, 0, 8);
INSERT INTO "npc_configs" VALUES (76, 'GMG-Aresden', 41, 50000, 5000, 500, 500, 2222, 2222, 500, 3000, 0, 0, 1, 1, 5, 800, 30, 0, 10, 0, 8, 3000, 2, 0, 1, 0, 8);
INSERT INTO "npc_configs" VALUES (77, 'GMG-Elvine', 41, 50000, 5000, 500, 500, 2222, 2222, 500, 3000, 0, 0, 1, 2, 5, 800, 30, 0, 10, 0, 8, 3000, 2, 0, 1, 0, 8);
INSERT INTO "npc_configs" VALUES (78, 'ManaStone', 42, 50000, 5000, 500, 500, 2222, 2222, 0, 0, 0, 0, 1, 0, 5, 500, 30, 0, 10, 0, 8, 3000, 2, 0, 0, 0, 8);
INSERT INTO "npc_configs" VALUES (79, 'LWB-Aresden', 43, 250, 450, 500, 20, 2222, 2222, 200, 1000, 10, 5, 1, 1, 0, 700, 100, 7, 10, 0, 7, 60000, 3, 50, 0, 0, 8);
INSERT INTO "npc_configs" VALUES (80, 'LWB-Elvine', 43, 250, 450, 500, 20, 2222, 2222, 200, 1000, 10, 5, 1, 2, 0, 700, 100, 7, 10, 0, 7, 60000, 3, 50, 0, 0, 8);
INSERT INTO "npc_configs" VALUES (81, 'GHK', 44, 350, 450, 500, 20, 2222, 2322, 300, 1500, 10, 9, 1, 2, 0, 700, 100, 7, 10, 0, 7, 60000, 3, 50, 0, 0, 4);
INSERT INTO "npc_configs" VALUES (82, 'GHKABS', 45, 800, 450, 1000, 100, 2222, 2222, 500, 2000, 13, 12, 1, 2, 0, 600, 100, 7, 10, 0, 7, 60000, 3, 50, 0, 0, 5);
INSERT INTO "npc_configs" VALUES (83, 'TK', 46, 350, 450, 500, 20, 2222, 2222, 300, 1500, 10, 9, 1, 1, 0, 700, 100, 7, 10, 0, 7, 60000, 3, 50, 0, 0, 4);
INSERT INTO "npc_configs" VALUES (84, 'BG', 47, 800, 450, 1000, 100, 2222, 2222, 500, 2000, 13, 12, 1, 1, 0, 600, 100, 7, 10, 0, 7, 60000, 3, 50, 0, 0, 5);
INSERT INTO "npc_configs" VALUES (85, 'XB-Aresden', 1, 85, 150, 200, 4, 2222, 2222, 100, 300, 8, 5, 1, 1, 0, 600, 70, 0, 10, 0, 7, 10000, 2, 0, 0, 0, 3);
INSERT INTO "npc_configs" VALUES (86, 'XB-Elvine', 1, 85, 150, 200, 4, 2222, 2222, 100, 300, 8, 5, 1, 2, 0, 600, 70, 0, 10, 0, 7, 10000, 2, 0, 0, 0, 3);
INSERT INTO "npc_configs" VALUES (87, 'XW-Aresden', 2, 85, 150, 200, 4, 2222, 2222, 100, 300, 8, 5, 1, 1, 0, 600, 70, 0, 10, 0, 7, 10000, 2, 0, 0, 0, 3);
INSERT INTO "npc_configs" VALUES (88, 'XW-Elvine', 2, 85, 150, 200, 4, 2222, 2222, 100, 300, 8, 5, 1, 2, 0, 600, 70, 0, 10, 0, 7, 10000, 2, 0, 0, 0, 3);
INSERT INTO "npc_configs" VALUES (89, 'XY-Aresden', 3, 85, 150, 200, 4, 2222, 2222, 100, 300, 8, 5, 1, 1, 0, 600, 70, 0, 10, 0, 7, 10000, 2, 0, 0, 0, 3);
INSERT INTO "npc_configs" VALUES (90, 'XY-Elvine', 3, 85, 150, 200, 4, 2222, 2222, 100, 300, 8, 5, 1, 2, 0, 600, 70, 0, 10, 0, 7, 10000, 2, 0, 0, 0, 3);
INSERT INTO "npc_configs" VALUES (91, 'YB-Aresden', 4, 85, 150, 200, 4, 2222, 2222, 100, 300, 8, 5, 1, 1, 0, 600, 70, 0, 10, 0, 7, 10000, 2, 0, 0, 0, 3);
INSERT INTO "npc_configs" VALUES (92, 'YB-Elvine', 4, 85, 150, 200, 4, 2222, 2222, 100, 300, 8, 5, 1, 2, 0, 600, 70, 0, 10, 0, 7, 10000, 2, 0, 0, 0, 3);
INSERT INTO "npc_configs" VALUES (93, 'YW-Aresden', 5, 85, 150, 200, 4, 2222, 2222, 100, 300, 8, 5, 1, 1, 0, 600, 70, 0, 10, 0, 7, 10000, 2, 0, 0, 0, 3);
INSERT INTO "npc_configs" VALUES (94, 'YW-Elvine', 5, 85, 150, 200, 4, 2222, 2222, 100, 300, 8, 5, 1, 2, 0, 600, 70, 0, 10, 0, 7, 10000, 2, 0, 0, 0, 3);
INSERT INTO "npc_configs" VALUES (95, 'YY-Aresden', 6, 85, 150, 200, 4, 2222, 2222, 100, 300, 8, 5, 1, 1, 0, 600, 70, 0, 10, 0, 7, 10000, 2, 0, 0, 0, 3);
INSERT INTO "npc_configs" VALUES (96, 'YY-Elvine', 6, 85, 150, 200, 4, 2222, 2222, 100, 300, 8, 5, 1, 2, 0, 600, 70, 0, 10, 0, 7, 10000, 2, 0, 0, 0, 3);
INSERT INTO "npc_configs" VALUES (97, 'CP-Aresden', 51, 500, 50, 500, 100, 2222, 2222, 500, 1000, 10, 14, 1, 1, 0, 1600, 100, 0, 10, 0, 9, 10000, 1, 0, 0, 0, 9);
INSERT INTO "npc_configs" VALUES (98, 'CP-Elvine', 51, 500, 50, 500, 100, 2222, 2222, 500, 1000, 10, 14, 1, 2, 0, 1600, 50, 0, 10, 0, 9, 10000, 1, 0, 0, 0, 9);
INSERT INTO "npc_configs" VALUES (99, 'Sor-Aresden', 82, 300, 450, 1000, 100, 2222, 2222, 750, 1250, 11, 10, 1, 1, 0, 700, 100, 7, 10, 0, 7, 60000, 3, 50, 19000, 9, 6);
INSERT INTO "npc_configs" VALUES (100, 'Sor-Elvine', 82, 300, 450, 1000, 100, 2222, 2222, 750, 1250, 11, 10, 1, 2, 0, 700, 100, 7, 10, 0, 7, 60000, 3, 50, 19000, 9, 6);
INSERT INTO "npc_configs" VALUES (101, 'ATK-Aresden', 83, 800, 500, 1000, 100, 2222, 2222, 1000, 1500, 13, 12, 1, 1, 0, 1000, 100, 0, 10, 0, 7, 60000, 3, 50, 0, 0, 3);
INSERT INTO "npc_configs" VALUES (102, 'ATK-Evline', 83, 800, 500, 1000, 100, 2222, 2222, 1000, 1500, 13, 12, 1, 2, 0, 1000, 100, 0, 10, 0, 7, 60000, 3, 50, 0, 0, 3);
INSERT INTO "npc_configs" VALUES (103, 'Elf-Aresden', 84, 250, 450, 500, 100, 2222, 2222, 500, 1000, 10, 6, 1, 1, 0, 700, 100, 0, 10, 0, 8, 60000, 3, 50, 0, 0, 8);
INSERT INTO "npc_configs" VALUES (104, 'Elf-Elvine', 84, 250, 450, 500, 100, 2222, 2222, 500, 1000, 10, 6, 1, 2, 0, 700, 100, 0, 10, 0, 8, 60000, 3, 50, 0, 0, 8);
INSERT INTO "npc_configs" VALUES (105, 'DSK-Aresden', 85, 500, 400, 600, 100, 2222, 2222, 700, 1250, 10, 9, 1, 1, 0, 500, 100, 0, 10, 0, 6, 60000, 3, 50, 0, 0, 4);
INSERT INTO "npc_configs" VALUES (106, 'DSK-Elvine', 85, 500, 400, 600, 100, 2222, 2222, 700, 1250, 10, 9, 1, 2, 0, 500, 100, 0, 10, 0, 6, 60000, 3, 50, 0, 0, 4);
INSERT INTO "npc_configs" VALUES (107, 'HBT-Aresden', 86, 500, 150, 500, 100, 2222, 2222, 550, 1100, 10, 14, 1, 1, 0, 1600, 100, 0, 10, 0, 9, 60000, 3, 50, 0, 0, 9);
INSERT INTO "npc_configs" VALUES (108, 'HBT-Elvine', 86, 500, 150, 500, 100, 2222, 2222, 550, 1100, 10, 14, 1, 2, 0, 1600, 100, 0, 10, 0, 9, 60000, 3, 50, 0, 0, 9);
INSERT INTO "npc_configs" VALUES (109, 'CT-Aresden', 87, 800, 200, 500, 100, 2222, 2222, 550, 1200, 8, 8, 1, 1, 5, 700, 30, 0, 10, 0, 8, 3000, 2, 0, 0, 0, 9);
INSERT INTO "npc_configs" VALUES (110, 'CT-Elvine', 87, 800, 200, 500, 100, 2222, 2222, 550, 1200, 8, 8, 1, 2, 5, 700, 30, 0, 10, 0, 8, 3000, 2, 0, 0, 0, 9);
INSERT INTO "npc_configs" VALUES (111, 'Bar-Aresden', 88, 350, 500, 1000, 100, 2222, 2222, 800, 1700, 15, 12, 1, 1, 0, 1400, 100, 0, 10, 0, 7, 60000, 3, 50, 0, 0, 2);
INSERT INTO "npc_configs" VALUES (112, 'Bar-Elvine', 88, 350, 500, 1000, 100, 2222, 2222, 800, 1700, 15, 12, 1, 2, 0, 1400, 100, 0, 10, 0, 7, 60000, 3, 50, 0, 0, 2);
INSERT INTO "npc_configs" VALUES (113, 'AGC-Aresden', 89, 1000, 200, 500, 100, 2222, 2222, 550, 1100, 14, 10, 1, 1, 5, 1600, 30, 0, 10, 0, 8, 3000, 2, 0, 0, 0, 9);
INSERT INTO "npc_configs" VALUES (114, 'AGC-Elvine', 89, 1000, 200, 500, 100, 2222, 2222, 550, 1100, 14, 10, 1, 2, 5, 1600, 30, 0, 10, 0, 8, 3000, 2, 0, 0, 0, 9);

-- ----------------------------
-- Table structure for potion_configs
-- ----------------------------
DROP TABLE IF EXISTS "potion_configs";
CREATE TABLE "potion_configs" (
  "potion_id" INTEGER,
  "name" TEXT NOT NULL,
  "array0" INTEGER NOT NULL,
  "array1" INTEGER NOT NULL,
  "array2" INTEGER NOT NULL,
  "array3" INTEGER NOT NULL,
  "array4" INTEGER NOT NULL,
  "array5" INTEGER NOT NULL,
  "array6" INTEGER NOT NULL,
  "array7" INTEGER NOT NULL,
  "array8" INTEGER NOT NULL,
  "array9" INTEGER NOT NULL,
  "array10" INTEGER NOT NULL,
  "array11" INTEGER NOT NULL,
  "skill_limit" INTEGER NOT NULL,
  "difficulty" INTEGER NOT NULL,
  PRIMARY KEY ("potion_id")
);

-- ----------------------------
-- Records of potion_configs
-- ----------------------------
INSERT INTO "potion_configs" VALUES (1, 'RedPotion', 220, 1, 192, 1, 191, 1, -1, 0, -1, 0, -1, 0, 20, 10);
INSERT INTO "potion_configs" VALUES (2, 'BluePotion', 220, 1, 193, 1, 189, 1, -1, 0, -1, 0, -1, 0, 20, 10);
INSERT INTO "potion_configs" VALUES (3, 'GreenPotion', 220, 1, 215, 1, 188, 1, -1, 0, -1, 0, -1, 0, 20, 10);
INSERT INTO "potion_configs" VALUES (4, 'DilutionPotion', 220, 1, 217, 1, 208, 1, 190, 2, -1, 0, -1, 0, 30, 20);
INSERT INTO "potion_configs" VALUES (5, 'BigRedPotion', 223, 1, 220, 3, 192, 1, 191, 1, -1, 0, -1, 0, 40, 20);
INSERT INTO "potion_configs" VALUES (6, 'BigBluePotion', 220, 3, 197, 1, 193, 1, 189, 1, -1, 0, -1, 0, 40, 20);
INSERT INTO "potion_configs" VALUES (7, 'BigGreenPotion', 220, 2, 215, 1, 189, 1, 188, 1, 188, 1, -1, 0, 40, 20);
INSERT INTO "potion_configs" VALUES (8, 'InvisibilityPotion', 220, 1, 219, 1, 208, 1, 206, 1, -1, 0, -1, 0, 50, 30);
INSERT INTO "potion_configs" VALUES (9, 'HairColorPotion', 220, 1, 216, 1, 205, 1, 188, 1, -1, 0, -1, 0, 60, 40);
INSERT INTO "potion_configs" VALUES (10, 'HairStylePotion', 221, 1, 220, 1, 204, 1, 188, 1, -1, 0, -1, 0, 70, 40);
INSERT INTO "potion_configs" VALUES (11, 'SkinColorPotion', 220, 1, 205, 1, 201, 1, 190, 1, -1, 0, -1, 0, 90, 60);
INSERT INTO "potion_configs" VALUES (12, 'SexChangePotion', 225, 1, 220, 1, 219, 1, 210, 1, 205, 1, 194, 1, 95, 70);
INSERT INTO "potion_configs" VALUES (13, 'OgrePotion', 222, 1, 214, 1, 212, 1, 211, 1, 210, 1, 209, 1, 100, 80);
INSERT INTO "potion_configs" VALUES (14, 'PowerGreenPotion', 554, 1, 222, 1, 220, 1, 199, 1, 196, 1, -1, 0, 95, 80);
INSERT INTO "potion_configs" VALUES (15, 'UnderWearPotion', 575, 1, 220, 1, 218, 1, 217, 1, 215, 1, 203, 1, 60, 50);
INSERT INTO "potion_configs" VALUES (16, 'UnfreezePotion', 548, 1, 220, 1, 217, 1, 207, 1, 198, 1, -1, 0, 90, 60);
INSERT INTO "potion_configs" VALUES (17, 'SuperRedPotion', 823, 1, 222, 1, 220, 1, 193, 1, -1, 0, -1, 0, 75, 50);
INSERT INTO "potion_configs" VALUES (18, 'SuperBluePotion', 820, 1, 220, 1, 206, 1, 196, 1, -1, 0, -1, 0, 75, 50);
INSERT INTO "potion_configs" VALUES (19, 'SuperGreenPotion', 821, 1, 220, 1, 199, 1, 192, 1, -1, 0, -1, 0, 70, 40);

-- ----------------------------
-- Table structure for program_config
-- ----------------------------
DROP TABLE IF EXISTS "program_config";
CREATE TABLE "program_config" (
  "key" TEXT,
  "value" TEXT NOT NULL,
  PRIMARY KEY ("key")
);

-- ----------------------------
-- Records of program_config
-- ----------------------------
INSERT INTO "program_config" VALUES ('game-server-name', 'Apocalypse');
INSERT INTO "program_config" VALUES ('game-server-port', '9907');
INSERT INTO "program_config" VALUES ('log-server-address', '127.0.0.1');
INSERT INTO "program_config" VALUES ('internal-log-server-port', '2500');
INSERT INTO "program_config" VALUES ('gate-server-address', '127.0.0.1');
INSERT INTO "program_config" VALUES ('gate-server-port', '6502');
INSERT INTO "program_config" VALUES ('game-server-internal-address', '127.0.0.1');
INSERT INTO "program_config" VALUES ('game-server-external-address', '127.0.0.1');
INSERT INTO "program_config" VALUES ('game-server-address', '127.0.0.1');
INSERT INTO "program_config" VALUES ('game-server-mode', 'lan');

-- ----------------------------
-- Table structure for quest_configs
-- ----------------------------
DROP TABLE IF EXISTS "quest_configs";
CREATE TABLE "quest_configs" (
  "quest_index" INTEGER,
  "side" INTEGER NOT NULL,
  "quest_type" INTEGER NOT NULL,
  "target_type" INTEGER NOT NULL,
  "max_count" INTEGER NOT NULL,
  "quest_from" INTEGER NOT NULL,
  "min_level" INTEGER NOT NULL,
  "max_level" INTEGER NOT NULL,
  "required_skill_num" INTEGER NOT NULL,
  "required_skill_level" INTEGER NOT NULL,
  "time_limit" INTEGER NOT NULL,
  "assign_type" INTEGER NOT NULL,
  "reward_type1" INTEGER NOT NULL,
  "reward_amount1" INTEGER NOT NULL,
  "reward_type2" INTEGER NOT NULL,
  "reward_amount2" INTEGER NOT NULL,
  "reward_type3" INTEGER NOT NULL,
  "reward_amount3" INTEGER NOT NULL,
  "contribution" INTEGER NOT NULL,
  "contribution_limit" INTEGER NOT NULL,
  "response_mode" INTEGER NOT NULL,
  "target_name" TEXT NOT NULL,
  "target_x" INTEGER NOT NULL,
  "target_y" INTEGER NOT NULL,
  "target_range" INTEGER NOT NULL,
  "quest_id" INTEGER NOT NULL,
  "req_contribution" INTEGER NOT NULL,
  PRIMARY KEY ("quest_index")
);

-- ----------------------------
-- Records of quest_configs
-- ----------------------------
INSERT INTO "quest_configs" VALUES (1, 1, 1, 56, 20, 4, 11, 20, -1, -1, -1, -1, -1, 100, 90, 200, 90, 100, 2, 20, 1, 'arefarm', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (2, 2, 1, 56, 20, 4, 11, 20, -1, -1, -1, -1, -1, 100, 90, 200, 90, 100, 2, 20, 1, 'elvfarm', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (3, 1, 1, 10, 30, 4, 11, 20, -1, -1, -1, -1, -1, 100, 90, 200, 90, 100, 2, 20, 1, 'arefarm', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (4, 2, 1, 10, 30, 4, 11, 20, -1, -1, -1, -1, -1, 100, 90, 200, 90, 100, 2, 20, 1, 'elvfarm', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (5, 1, 1, 16, 15, 4, 11, 20, -1, -1, -1, -1, -1, 100, 90, 200, 90, 100, 2, 20, 1, 'arefarm', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (6, 2, 1, 16, 15, 4, 11, 20, -1, -1, -1, -1, -1, 100, 90, 200, 90, 100, 2, 20, 1, 'elvfarm', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (7, 1, 1, 17, 25, 4, 20, 40, -1, -1, -1, -1, -1, 500, 90, 500, 90, 400, 3, 40, 1, 'arefarm', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (8, 2, 1, 17, 25, 4, 20, 40, -1, -1, -1, -1, -1, 500, 90, 500, 90, 400, 3, 40, 1, 'elvfarm', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (9, 1, 1, 22, 30, 4, 20, 40, -1, -1, -1, -1, -1, 500, 90, 500, 90, 400, 3, 40, 1, 'arefarm', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (10, 2, 1, 22, 30, 4, 20, 40, -1, -1, -1, -1, -1, 500, 90, 500, 90, 400, 3, 40, 1, 'elvfarm', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (11, 1, 1, 14, 30, 4, 20, 40, -1, -1, -1, -1, -1, 500, 90, 500, 90, 400, 3, 40, 1, 'arefarm', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (12, 2, 1, 14, 30, 4, 20, 40, -1, -1, -1, -1, -1, 500, 90, 500, 90, 400, 3, 40, 1, 'elvfarm', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (13, 1, 1, 14, 35, 4, 40, 50, -1, -1, -1, -1, -1, 1000, 90, 1000, 90, 800, 4, 80, 1, 'aresden', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (14, 2, 1, 14, 35, 4, 40, 50, -1, -1, -1, -1, -1, 1000, 90, 1000, 90, 800, 4, 80, 1, 'elvine', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (15, 1, 1, 17, 30, 4, 40, 50, -1, -1, -1, -1, -1, 1000, 90, 1000, 90, 800, 4, 80, 1, 'aresden', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (16, 2, 1, 17, 30, 4, 40, 50, -1, -1, -1, -1, -1, 1000, 90, 1000, 90, 800, 4, 80, 1, 'elvine', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (17, 1, 1, 11, 25, 4, 40, 50, -1, -1, -1, -1, -1, 1000, 90, 1000, 90, 800, 4, 80, 1, 'huntzone2', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (18, 2, 1, 11, 25, 4, 40, 50, -1, -1, -1, -1, -1, 1000, 90, 1000, 90, 800, 4, 80, 1, 'huntzone1', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (19, 1, 1, 11, 30, 4, 50, 70, -1, -1, -1, -1, -1, 2000, 90, 3000, 90, 2500, 5, 120, 1, 'middled1n', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (20, 2, 1, 11, 30, 4, 50, 70, -1, -1, -1, -1, -1, 2000, 90, 3000, 90, 2500, 5, 121, 1, 'middled1n', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (21, 1, 1, 12, 20, 4, 50, 70, -1, -1, -1, -1, -1, 2000, 90, 3000, 90, 2500, 5, 122, 1, 'huntzone2', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (22, 2, 1, 12, 20, 4, 50, 70, -1, -1, -1, -1, -1, 2000, 90, 3000, 90, 2500, 5, 123, 1, 'huntzone1', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (23, 1, 1, 61, 25, 4, 70, 80, -1, -1, -1, -1, -1, 3000, 90, 4000, 90, 3000, 6, 124, 1, 'huntzone2', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (24, 2, 1, 61, 25, 4, 70, 80, -1, -1, -1, -1, -1, 3000, 90, 4000, 90, 3000, 6, 125, 1, 'huntzone1', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (25, 1, 1, 28, 15, 4, 80, 90, -1, -1, -1, -1, -1, 4000, 90, 5000, 90, 4000, 7, 160, 1, 'areuni', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (26, 2, 1, 28, 15, 4, 80, 90, -1, -1, -1, -1, -1, 4000, 90, 5000, 90, 4000, 7, 160, 1, 'elvuni', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (27, 1, 1, 23, 30, 4, 80, 90, -1, -1, -1, -1, -1, 4000, 90, 5000, 90, 4000, 7, 160, 1, 'middled1n', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (28, 2, 1, 23, 30, 4, 80, 90, -1, -1, -1, -1, -1, 4000, 90, 5000, 90, 4000, 7, 160, 1, 'middled1n', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (29, 1, 7, 0, 0, 4, 50, 300, -1, -1, -1, -1, -2, 1, -2, 1, -2, 1, 1, 500, 1, 'elvine', 166, 136, 3, 723, 70);
INSERT INTO "quest_configs" VALUES (30, 2, 7, 0, 0, 4, 50, 300, -1, -1, -1, -1, -2, 1, -2, 1, -2, 1, 1, 500, 1, 'aresden', 244, 136, 3, 723, 70);
INSERT INTO "quest_configs" VALUES (31, 1, 7, 0, 0, 4, 50, 300, -1, -1, -1, -1, -2, 1, -2, 1, -2, 1, 1, 500, 1, 'elvine', 200, 193, 3, 723, 80);
INSERT INTO "quest_configs" VALUES (32, 2, 7, 0, 0, 4, 50, 300, -1, -1, -1, -1, -2, 1, -2, 1, -2, 1, 1, 500, 1, 'aresden', 218, 180, 3, 723, 80);
INSERT INTO "quest_configs" VALUES (33, 1, 7, 0, 0, 4, 50, 300, -1, -1, -1, -1, -2, 1, -2, 1, -2, 1, 1, 500, 1, 'elvine', 202, 108, 3, 723, 90);
INSERT INTO "quest_configs" VALUES (34, 2, 7, 0, 0, 4, 50, 300, -1, -1, -1, -1, -2, 1, -2, 1, -2, 1, 1, 500, 1, 'aresden', 179, 97, 3, 723, 90);
INSERT INTO "quest_configs" VALUES (41, 1, 10, 0, 0, 4, 31, 120, -1, -1, -1, 1, 0, 0, 0, 0, 0, 0, 1, 1000, 1, 'huntzone1', -1, -1, 3, 614, 0);
INSERT INTO "quest_configs" VALUES (42, 2, 10, 0, 0, 4, 31, 120, -1, -1, -1, 1, 0, 0, 0, 0, 0, 0, 1, 1000, 1, 'huntzone2', -1, -1, 3, 614, 0);
INSERT INTO "quest_configs" VALUES (43, 1, 1, 57, 20, 4, 90, 100, -1, -1, -1, -1, -1, 5000, 90, 7000, 90, 5500, 7, 210, 1, 'middled1n', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (44, 2, 1, 57, 20, 4, 90, 100, -1, -1, -1, -1, -1, 5000, 90, 7000, 90, 5500, 7, 210, 1, 'middled1n', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (45, 1, 1, 28, 20, 4, 90, 100, -1, -1, -1, -1, -1, 5000, 90, 7000, 90, 5500, 7, 210, 1, 'areuni', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (46, 2, 1, 28, 20, 4, 90, 100, -1, -1, -1, -1, -1, 5000, 90, 7000, 90, 5500, 7, 210, 1, 'elvuni', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (47, 1, 1, 13, 20, 4, 100, 110, -1, -1, -1, -1, -1, 5500, 90, 8000, 90, 6000, 8, 260, 1, '2ndmiddle', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (48, 2, 1, 13, 20, 4, 100, 110, -1, -1, -1, -1, -1, 5500, 90, 8000, 90, 6000, 8, 260, 1, '2ndmiddle', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (49, 1, 1, 28, 25, 4, 100, 110, -1, -1, -1, -1, -1, 5500, 90, 8000, 90, 6000, 8, 260, 1, 'areuni', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (50, 2, 1, 28, 25, 4, 100, 110, -1, -1, -1, -1, -1, 5500, 90, 8000, 90, 6000, 8, 260, 1, 'elvuni', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (51, 1, 1, 13, 25, 4, 110, 120, -1, -1, -1, -1, -1, 6000, 90, 10000, 90, 8500, 8, 300, 1, '2ndmiddle', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (52, 2, 1, 13, 25, 4, 110, 120, -1, -1, -1, -1, -1, 6000, 90, 10000, 90, 8500, 8, 300, 1, '2ndmiddle', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (53, 1, 1, 60, 15, 4, 110, 120, -1, -1, -1, -1, -1, 6000, 90, 10000, 90, 8500, 8, 300, 1, 'areuni', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (54, 2, 1, 60, 15, 4, 110, 120, -1, -1, -1, -1, -1, 6000, 90, 10000, 90, 8500, 8, 300, 1, 'elvuni', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (55, 1, 1, 29, 15, 4, 120, 130, -1, -1, -1, -1, -1, 6500, 90, 12000, 90, 9000, 9, 350, 1, 'huntzone4', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (56, 2, 1, 29, 15, 4, 120, 130, -1, -1, -1, -1, -1, 6500, 90, 12000, 90, 9000, 9, 350, 1, 'huntzone3', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (57, 1, 1, 28, 30, 4, 120, 130, -1, -1, -1, -1, -1, 6500, 90, 12000, 90, 9000, 9, 350, 1, 'huntzone4', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (58, 2, 1, 28, 30, 4, 120, 130, -1, -1, -1, -1, -1, 6500, 90, 12000, 90, 9000, 9, 350, 1, 'huntzone3', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (59, 1, 1, 58, 20, 4, 130, 140, -1, -1, -1, -1, -1, 7000, 90, 13000, 90, 10000, 10, 400, 1, 'huntzone4', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (60, 2, 1, 58, 20, 4, 130, 140, -1, -1, -1, -1, -1, 7000, 90, 13000, 90, 10000, 10, 400, 1, 'huntzone3', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (61, 1, 1, 29, 15, 4, 130, 140, -1, -1, -1, -1, -1, 7000, 90, 13000, 90, 10000, 10, 400, 1, 'dglv3', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (62, 2, 1, 29, 15, 4, 130, 140, -1, -1, -1, -1, -1, 7000, 90, 13000, 90, 10000, 10, 400, 1, 'dglv3', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (63, 1, 1, 29, 20, 4, 140, 150, -1, -1, -1, -1, -1, 8000, 90, 15000, 90, 12000, 11, 450, 1, 'toh1', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (64, 2, 1, 29, 20, 4, 140, 150, -1, -1, -1, -1, -1, 8000, 90, 15000, 90, 12000, 11, 450, 1, 'toh1', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (65, 1, 1, 30, 15, 4, 140, 150, -1, -1, -1, -1, -1, 8000, 90, 15000, 90, 12000, 12, 450, 1, 'dglv3', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (66, 2, 1, 30, 15, 4, 140, 150, -1, -1, -1, -1, -1, 8000, 90, 15000, 90, 12000, 12, 450, 1, 'dglv3', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (67, 1, 1, 33, 18, 4, 140, 150, -1, -1, -1, -1, -1, 8000, 90, 15000, 90, 12000, 11, 450, 1, 'huntzone4', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (68, 2, 1, 33, 18, 4, 140, 150, -1, -1, -1, -1, -1, 8000, 90, 15000, 90, 12000, 11, 450, 1, 'huntzone3', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (69, 1, 1, 48, 20, 4, 140, 150, -1, -1, -1, -1, -1, 8000, 90, 15000, 90, 12000, 10, 450, 1, 'middleland', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (70, 2, 1, 48, 20, 4, 140, 150, -1, -1, -1, -1, -1, 8000, 90, 15000, 90, 12000, 10, 450, 1, 'middleland', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (71, 1, 1, 62, 20, 4, 150, 160, -1, -1, -1, -1, -1, 9000, 90, 16000, 90, 13000, 13, 520, 1, 'icebound', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (72, 2, 1, 62, 20, 4, 150, 160, -1, -1, -1, -1, -1, 9000, 90, 16000, 90, 13000, 13, 520, 1, 'icebound', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (73, 1, 1, 54, 30, 4, 150, 160, -1, -1, -1, -1, -1, 9000, 90, 16000, 90, 13000, 10, 520, 1, 'toh1', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (74, 2, 1, 54, 30, 4, 150, 160, -1, -1, -1, -1, -1, 9000, 90, 16000, 90, 13000, 10, 520, 1, 'toh1', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (75, 1, 1, 31, 10, 4, 160, 170, -1, -1, -1, -1, -1, 10000, 90, 17000, 90, 13500, 11, 600, 1, 'dglv4', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (76, 2, 1, 31, 10, 4, 160, 170, -1, -1, -1, -1, -1, 10000, 90, 17000, 90, 13500, 11, 600, 1, 'dglv4', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (77, 1, 1, 59, 15, 4, 160, 170, -1, -1, -1, -1, -1, 10000, 90, 17000, 90, 13500, 12, 600, 1, 'huntzone4', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (78, 2, 1, 59, 15, 4, 160, 170, -1, -1, -1, -1, -1, 10000, 90, 17000, 90, 13500, 12, 600, 1, 'huntzone3', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (79, 1, 1, 63, 18, 4, 160, 170, -1, -1, -1, -1, -1, 10000, 90, 17000, 90, 13500, 11, 600, 1, 'icebound', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (80, 2, 1, 63, 18, 4, 160, 170, -1, -1, -1, -1, -1, 10000, 90, 17000, 90, 13500, 11, 600, 1, 'icebound', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (81, 1, 1, 30, 22, 4, 170, 180, -1, -1, -1, -1, -1, 12000, 90, 18000, 90, 14000, 12, 700, 1, 'dglv4', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (82, 2, 1, 30, 22, 4, 170, 180, -1, -1, -1, -1, -1, 12000, 90, 18000, 90, 14000, 12, 700, 1, 'dglv4', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (83, 1, 1, 31, 15, 4, 170, 180, -1, -1, -1, -1, -1, 12000, 90, 18000, 90, 14000, 14, 700, 1, 'dglv4', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (84, 2, 1, 31, 15, 4, 170, 180, -1, -1, -1, -1, -1, 12000, 90, 18000, 90, 14000, 14, 700, 1, 'dglv4', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (85, 1, 1, 52, 13, 4, 170, 180, -1, -1, -1, -1, -1, 12000, 90, 18000, 90, 14000, 15, 700, 1, 'toh3', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (86, 2, 1, 52, 13, 4, 170, 180, -1, -1, -1, -1, -1, 12000, 90, 18000, 90, 14000, 15, 700, 1, 'toh3', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (87, 1, 1, 59, 20, 4, 170, 180, -1, -1, -1, -1, -1, 12000, 90, 18000, 90, 14000, 12, 700, 1, 'huntzone4', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (88, 2, 1, 59, 20, 4, 170, 180, -1, -1, -1, -1, -1, 12000, 90, 18000, 90, 14000, 12, 700, 1, 'huntzone3', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (89, 1, 1, 63, 22, 4, 170, 180, -1, -1, -1, -1, -1, 12000, 90, 18000, 90, 14000, 12, 700, 1, 'icebound', 0, 0, 0, 354, 0);
INSERT INTO "quest_configs" VALUES (90, 2, 1, 63, 22, 4, 170, 180, -1, -1, -1, -1, -1, 12000, 90, 18000, 90, 14000, 12, 700, 1, 'icebound', 0, 0, 0, 354, 0);

-- ----------------------------
-- Table structure for schedule_apocalypse_end
-- ----------------------------
DROP TABLE IF EXISTS "schedule_apocalypse_end";
CREATE TABLE "schedule_apocalypse_end" (
  "schedule_id" INTEGER,
  "day" INTEGER NOT NULL,
  "hour" INTEGER NOT NULL,
  "minute" INTEGER NOT NULL,
  PRIMARY KEY ("schedule_id")
);

-- ----------------------------
-- Records of schedule_apocalypse_end
-- ----------------------------
INSERT INTO "schedule_apocalypse_end" VALUES (2, 6, 23, 1);

-- ----------------------------
-- Table structure for schedule_apocalypse_start
-- ----------------------------
DROP TABLE IF EXISTS "schedule_apocalypse_start";
CREATE TABLE "schedule_apocalypse_start" (
  "schedule_id" INTEGER,
  "day" INTEGER NOT NULL,
  "hour" INTEGER NOT NULL,
  "minute" INTEGER NOT NULL,
  PRIMARY KEY ("schedule_id")
);

-- ----------------------------
-- Records of schedule_apocalypse_start
-- ----------------------------
INSERT INTO "schedule_apocalypse_start" VALUES (1, 6, 1, 1);

-- ----------------------------
-- Table structure for schedule_crusade
-- ----------------------------
DROP TABLE IF EXISTS "schedule_crusade";
CREATE TABLE "schedule_crusade" (
  "schedule_id" INTEGER,
  "day" INTEGER NOT NULL,
  "hour" INTEGER NOT NULL,
  "minute" INTEGER NOT NULL,
  PRIMARY KEY ("schedule_id")
);

-- ----------------------------
-- Records of schedule_crusade
-- ----------------------------
INSERT INTO "schedule_crusade" VALUES (0, 1, 1, 1);

-- ----------------------------
-- Table structure for schedule_heldenian
-- ----------------------------
DROP TABLE IF EXISTS "schedule_heldenian";
CREATE TABLE "schedule_heldenian" (
  "schedule_id" INTEGER,
  "day" INTEGER NOT NULL,
  "start_hour" INTEGER NOT NULL,
  "start_minute" INTEGER NOT NULL,
  "end_hour" INTEGER NOT NULL,
  "end_minute" INTEGER NOT NULL,
  PRIMARY KEY ("schedule_id")
);

-- ----------------------------
-- Records of schedule_heldenian
-- ----------------------------

-- ----------------------------
-- Table structure for settings
-- ----------------------------
DROP TABLE IF EXISTS "settings";
CREATE TABLE "settings" (
  "key" TEXT,
  "value" TEXT NOT NULL,
  PRIMARY KEY ("key")
);

-- ----------------------------
-- Records of settings
-- ----------------------------
INSERT INTO "settings" VALUES ('primary-drop-rate', '1');
INSERT INTO "settings" VALUES ('secondary-drop-rate', '1');
INSERT INTO "settings" VALUES ('enemy-kill-mode', 'deathmatch');
INSERT INTO "settings" VALUES ('enemy-kill-adjust', '1');
INSERT INTO "settings" VALUES ('admin-security', 'off');
INSERT INTO "settings" VALUES ('monday-raid-time', '3');
INSERT INTO "settings" VALUES ('tuesday-raid-time', '3');
INSERT INTO "settings" VALUES ('wednesday-raid-time', '3');
INSERT INTO "settings" VALUES ('thursday-raid-time', '3');
INSERT INTO "settings" VALUES ('friday-raid-time', '30');
INSERT INTO "settings" VALUES ('saturday-raid-time', '45');
INSERT INTO "settings" VALUES ('sunday-raid-time', '60');
INSERT INTO "settings" VALUES ('log-chat-settings', 'all');
INSERT INTO "settings" VALUES ('summonguild-cost', '0');
INSERT INTO "settings" VALUES ('slate-success-rate', '25');
INSERT INTO "settings" VALUES ('character-stat-limit', '200');
INSERT INTO "settings" VALUES ('character-skill-limit', '2500');
INSERT INTO "settings" VALUES ('rep-drop-modifier', '5');
INSERT INTO "settings" VALUES ('admin-security-code', '1234393');
INSERT INTO "settings" VALUES ('max-player-level', '376');

-- ----------------------------
-- Table structure for skill_configs
-- ----------------------------
DROP TABLE IF EXISTS "skill_configs";
CREATE TABLE "skill_configs" (
  "skill_id" INTEGER,
  "name" TEXT NOT NULL,
  "skill_type" INTEGER NOT NULL,
  "value1" INTEGER NOT NULL,
  "value2" INTEGER NOT NULL,
  "value3" INTEGER NOT NULL,
  "value4" INTEGER NOT NULL,
  "value5" INTEGER NOT NULL,
  "value6" INTEGER NOT NULL,
  PRIMARY KEY ("skill_id")
);

-- ----------------------------
-- Records of skill_configs
-- ----------------------------
INSERT INTO "skill_configs" VALUES (0, 'Mining', 1, 1, 6, 0, 0, 0, 0);
INSERT INTO "skill_configs" VALUES (1, 'Fishing', 1, 2, 6, 0, 0, 0, 0);
INSERT INTO "skill_configs" VALUES (2, 'Farming', 1, 3, 6, 0, 0, 0, 0);
INSERT INTO "skill_configs" VALUES (3, 'Magic-Resistance', 0, 0, 0, 0, 0, 0, 0);
INSERT INTO "skill_configs" VALUES (4, 'Magic', 0, 0, 0, 0, 0, 0, 0);
INSERT INTO "skill_configs" VALUES (5, 'Hand-Attack', 0, 0, 0, 0, 0, 0, 0);
INSERT INTO "skill_configs" VALUES (6, 'Archery', 0, 0, 0, 0, 0, 0, 0);
INSERT INTO "skill_configs" VALUES (7, 'Short-Sword', 0, 0, 0, 0, 0, 0, 0);
INSERT INTO "skill_configs" VALUES (8, 'Long-Sword', 0, 0, 0, 0, 0, 0, 0);
INSERT INTO "skill_configs" VALUES (9, 'Fencing', 0, 0, 0, 0, 0, 0, 0);
INSERT INTO "skill_configs" VALUES (10, 'Axe-Attack', 0, 0, 0, 0, 0, 0, 0);
INSERT INTO "skill_configs" VALUES (11, 'Shield', 0, 0, 0, 0, 0, 0, 0);
INSERT INTO "skill_configs" VALUES (12, 'Alchemy', 1, 0, 0, 0, 0, 0, 0);
INSERT INTO "skill_configs" VALUES (13, 'Manufacturing', 1, 2, 0, 0, 0, 0, 0);
INSERT INTO "skill_configs" VALUES (14, 'Hammer', 0, 0, 0, 0, 0, 0, 0);
INSERT INTO "skill_configs" VALUES (15, '????', 1, 1, 0, 0, 0, 0, 0);
INSERT INTO "skill_configs" VALUES (16, '????', 1, 1, 0, 0, 0, 0, 0);
INSERT INTO "skill_configs" VALUES (17, '????', 1, 0, 0, 0, 0, 0, 0);
INSERT INTO "skill_configs" VALUES (18, 'Crafting', 1, 1, 0, 0, 0, 0, 0);
INSERT INTO "skill_configs" VALUES (19, 'Pretend-Corpse', 2, 1, 0, 0, 0, 0, 0);
INSERT INTO "skill_configs" VALUES (20, 'Enchanting', 1, 1, 0, 0, 0, 0, 0);
INSERT INTO "skill_configs" VALUES (21, 'Staff-Attack', 0, 0, 0, 0, 0, 0, 0);
INSERT INTO "skill_configs" VALUES (22, '????', 1, 2, 0, 0, 0, 0, 0);
INSERT INTO "skill_configs" VALUES (23, 'Poison-Resistance', 1, 0, 0, 0, 0, 0, 0);

PRAGMA foreign_keys = true;
