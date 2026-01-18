#pragma once
#include "CommonTypes.h"

// ServerMessages.h - Server-Only Network Messages
//
// This file contains network message definitions and constants used exclusively
// by the Helbreath Server. These include:
// - Server infrastructure messages (database, inter-server communication)
// - Configuration loading messages
// - Logging and monitoring messages
// - Gate Server Messages (GSM_*)
// - Internal tracking constants
//
// For shared protocol messages, see Dependencies/Shared/NetMessages.h

// ============================================================================
// Configuration Message ID Conflicts
// ============================================================================

// CRITICAL: This conflicts with MSGID_EVENT_COMMON (0x0FA314DB) which is SHARED
// Only the server loads magic configuration
#define MSGID_MAGICCONFIGURATIONCONTENTS			0x0FA314DB  // Conflicts with EVENT_COMMON

// ============================================================================
// Server-Only Common Action Types
// ============================================================================

#define DEF_COMMONTYPE_BANGUILD						0x0A26
#define DEF_COMMONTYPE_REQUEST_HELP					0x0A53

// NOTE: Same ID as DEF_COMMONTYPE_REQUEST_HUNTMODE (client name)
#define DEF_COMMONTYPE_REQ_CHANGEPLAYMODE			0x0A60

// ============================================================================
// Server-Only Notification Messages
// ============================================================================

#define DEF_NOTIFY_EVENTMSGSTRING					0x0B0C
#define DEF_NOTIFY_SKILLTRAINFAIL					0x0B13
#define DEF_NOTIFY_DEBUGMSG							0x0B49
#define DEF_NOTIFY_DUTYSELECTED						0x0B96
#define DEF_NOTIFY_HELP								0x0B99
#define DEF_NOTIFY_HELPFAILED						0x0B9A
#define DEF_NOTIFY_HELDENIANVICTORY					0x0BEB

// ============================================================================
// Repair All System (Server-Only Part)
// ============================================================================

#define DEF_COMMONTYPE_REQ_REPAIRALLDELETE			0x0F12

// ============================================================================
// Configuration Content Messages (Server Infrastructure)
// Server loads game configuration files and sends to clients
// ============================================================================

#define MSGID_NPCCONFIGURATIONCONTENTS				0x0FA314DA
#define MSGID_SKILLCONFIGURATIONCONTENTS			0x0FA314DC
#define MSGID_PORTIONCONFIGURATIONCONTENTS			0x0FA314DE
#define MSGID_QUESTCONFIGURATIONCONTENTS			0x0FA40001
#define MSGID_BUILDITEMCONFIGURATIONCONTENTS		0x0FA40002
#define MSGID_NOTICEMENTFILECONTENTS				0x0FA40004
#define MSGID_NPCITEMCONFIGCONTENTS					0x0FA40006

// ============================================================================
// Server Registration Messages
// Used for server-to-server communication
// ============================================================================

#define MSGID_REQUEST_REGISTERGAMESERVER			0x0512A3F4
#define MSGID_RESPONSE_REGISTERGAMESERVER			0x0512A3F5
#define MSGID_REQUEST_REGISTERDBSERVER				0x0512A3F6  // Definition
#define MSGID_RESPONSE_REGISTERDBSERVER				0x0512A3F7  // Definition

// ============================================================================
// Guild Update Messages (Inter-Server)
// ============================================================================

#define MSGID_REQUEST_UPDATEGUILDINFO_NEWGUILDSMAN	0x0FC9420C
#define MSGID_REQUEST_UPDATEGUILDINFO_DELGUILDSMAN	0x0FC9420D

// ============================================================================
// Player Data Messages (Server Infrastructure)
// Used for database communication
// ============================================================================

#define MSGID_REQUEST_PLAYERDATA					0x0C152210
#define MSGID_RESPONSE_PLAYERDATA					0x0C152211
#define MSGID_RESPONSE_SAVEPLAYERDATA_REPLY			0x0C152212
#define MSGID_REQUEST_SAVEPLAYERDATA				0x0DF3076F
#define MSGID_REQUEST_SAVEPLAYERDATA_REPLY			0x0DF30770
#define MSGID_REQUEST_SAVEPLAYERDATALOGOUT			0x0DF3074F
#define MSGID_REQUEST_NOSAVELOGOUT					0x0DF30750

// ============================================================================
// Guild Notifications (Inter-Server)
// ============================================================================

#define MSGID_GUILDNOTIFY							0x0DF30760
#define DEF_GUILDNOTIFY_NEWGUILDSMAN				0x1F00

// ============================================================================
// Server Teleport Messages
// NOTE: ID conflicts with Client teleport messages
// ============================================================================

#define MSGID_REQUEST_CITYHALLTELEPORT				0x0EA03202  // Conflicts with Client TELEPORT_LIST
#define MSGID_REQUEST_HELDENIANTELEPORT				0x0EA03206  // Conflicts with Client TP_LIST
#define MSGID_REQUEST_HELDENIAN_WINNER				0x3D001240

// ============================================================================
// Game Server Status Messages
// ============================================================================

#define MSGID_GAMESERVERALIVE						0x12A01002
#define MSGID_ADMINUSER								0x12A01003
#define MSGID_GAMESERVERDOWN						0x12A01004
#define MSGID_TOTALGAMESERVERCLIENTS				0x12A01005
#define MSGID_ENTERGAMECONFIRM						0x12A01006

// ============================================================================
// Account and Server Management Messages
// ============================================================================

#define DEF_MSGID_ANNOUNCEACCOUNT					0x13000000  // Definition
#define MSGID_ACCOUNTINFOCHANGE						0x13000001  // Definition
#define MSGID_IPINFOCHANGE							0x13000002  // Definition
#define MSGID_GAMESERVERSHUTDOWNED					0x14000000
#define MSGID_ANNOUNCEACCOUNTNEWPASSWORD			0x14000010  // Definition

#define MSGID_REQUEST_IPIDSTATUS					0x14E91200  // Definition
#define MSGID_RESPONSE_IPIDSTATUS					0x14E91201  // Definition
#define MSGID_REQUEST_ACCOUNTCONNSTATUS				0x14E91202  // Definition
#define MSGID_RESPONSE_ACCOUNTCONNSTATUS			0x14E91203  // Definition
#define MSGID_REQUEST_CLEARACCOUNTCONNSTATUS		0x14E91204  // Definition
#define MSGID_RESPONSE_CLEARACCOUNTCONNSTATUS		0x14E91205  // Definition

#define MSGID_REQUEST_FORCEDISCONECTACCOUNT			0x15000000
#define MSGID_REQUEST_NOCOUNTINGSAVELOGOUT			0x15000001  // Definition

// ============================================================================
// Occupy Flag Data (Territory Control)
// ============================================================================

#define MSGID_OCCUPYFLAGDATA						0x167C0A30  // Definition
#define MSGID_REQUEST_SAVEARESDENOCCUPYFLAGDATA		0x167C0A31  // Definition
#define MSGID_REQUEST_SAVEELVINEOCCUPYFLAGDATA		0x167C0A32  // Definition
#define MSGID_ARESDENOCCUPYFLAGSAVEFILECONTENTS		0x17081034
#define MSGID_ELVINEOCCUPYFLAGSAVEFILECONTENTS		0x17081035

// ============================================================================
// Bad Word Manager and Logging
// ============================================================================

#define MSGID_BWM_INIT								0x19CC0F82  // Bad Word Manager
#define MSGID_BWM_COMMAND_SHUTUP					0x19CC0F84

#define MSGID_SENDSERVERSHUTDOWNMSG					0x20000000
#define MSGID_ITEMLOG								0x210A914D
#define MSGID_GAMEMASTERLOG							0x210A914E
#define MSGID_GAMEITEMLOG							0x210A914F

// ============================================================================
// World Server Messages
// ============================================================================

#define MSGID_REGISTER_WORLDSERVER					0x23AA210E  // Definition
#define MSGID_REGISTER_WORLDSERVERSOCKET			0x23AA210F  // Definition
#define MSGID_REGISTER_WORLDSERVER_GAMESERVER		0x23AB211F  // Definition

#define MSGID_REQUEST_CHARINFOLIST					0x23AB2200  // Definition
#define MSGID_RESPONSE_CHARINFOLIST					0x23AB2201  // Definition

#define MSGID_REQUEST_REMOVEGAMESERVER				0x2400000A  // Definition
#define MSGID_REQUEST_CLEARACCOUNTSTATUS			0x24021EE0  // Definition

#define MSGID_REQUEST_SETACCOUNTINITSTATUS			0x25000198
#define MSGID_REQUEST_SETACCOUNTWAITSTATUS			0x25000199

#define MSGID_REQUEST_CHECKACCOUNTPASSWORD			0x2654203A
#define MSGID_WORLDSERVERACTIVATED					0x27049D0C  // Definition

#define MSGID_RESPONSE_REGISTER_WORLDSERVERSOCKET	0x280120A0  // Definition

// ============================================================================
// IP/Account Time and Block Management
// ============================================================================

#define MSGID_REQUEST_BLOCKACCOUNT					0x2900AD10  // Definition
#define MSGID_IPTIMECHANGE							0x2900AD20  // Definition
#define MSGID_ACCOUNTTIMECHANGE						0x2900AD22  // Definition
#define MSGID_REQUEST_IPTIME						0x2900AD30  // Definition - Conflicts with SELLITEMLIST
#define MSGID_RESPONSE_IPTIME						0x2900AD31  // Definition

// ============================================================================
// Server Reboot and Monitor Messages
// ============================================================================

#define MSGID_REQUEST_ALL_SERVER_REBOOT				0x3AE8270A  // Definition
#define MSGID_REQUEST_EXEC_1DOTBAT					0x3AE8370A  // Definition
#define MSGID_REQUEST_EXEC_2DOTBAT					0x3AE8470A  // Definition
#define MSGID_MONITORALIVE							0x3AE8570A  // Definition

#define MSGID_COLLECTEDMANA							0x3AE90000
#define MSGID_METEORSTRIKE							0x3AE90001  // Definition

#define MSGID_SERVERSTOCKMSG						0x3AE90013

// ============================================================================
// Party Operation Messages
// ============================================================================

#define MSGID_PARTYOPERATION						0x3C00123A

#define DEF_PARTYSTATUS_PROCESSING					1
#define DEF_PARTYSTATUS_NULL						0
#define DEF_PARTYSTATUS_CONFIRM						2

// ============================================================================
// Gate Server Messages (GSM_*) - Inter-Server Communication
// All gate server messages are server-only for coordinating multiple game servers
// ============================================================================

#define GSM_REQUEST_FINDCHARACTER					0x01
#define GSM_RESPONSE_FINDCHARACTER					0x02
#define GSM_GRANDMAGICRESULT						0x03
#define GSM_GRANDMAGICLAUNCH						0x04
#define GSM_COLLECTEDMANA							0x05
#define GSM_BEGINCRUSADE							0x06
#define GSM_ENDCRUSADE								0x07
#define GSM_MIDDLEMAPSTATUS							0x08
#define GSM_SETGUILDTELEPORTLOC						0x09
#define GSM_CONSTRUCTIONPOINT						0x0A
#define GSM_SETGUILDCONSTRUCTLOC					0x0B
#define GSM_CHATMSG									0x0C
#define GSM_WHISFERMSG								0x0D
#define GSM_DISCONNECT								0x0E
#define GSM_REQUEST_SUMMONPLAYER					0x0F
#define GSM_REQUEST_SHUTUPPLAYER					0x10
#define GSM_RESPONSE_SHUTUPPLAYER					0x11
#define GSM_REQUEST_SETFORCERECALLTIME				0x12
#define GSM_BEGINAPOCALYPSE							0x13
#define GSM_ENDAPOCALYPSE							0x14
#define GSM_REQUEST_SUMMONGUILD						0x15
#define GSM_REQUEST_SUMMONALL						0x16
#define GSM_ENDHELDENIAN							0x17
#define GSM_UPDATECONFIGS							0x18
#define GSM_STARTHELDENIAN							0x19

// ============================================================================
// Crusade Logging
// ============================================================================

#define DEF_CRUSADELOG_ENDCRUSADE					1
#define DEF_CRUSADELOG_STARTCRUSADE					2
#define DEF_CRUSADELOG_SELECTDUTY					3
#define DEF_CRUSADELOG_GETEXP						4
#define MSGID_GAMECRUSADELOG						0x210A914F  // Conflicts with GAMEITEMLOG

// ============================================================================
// NPC Item Drops
// ============================================================================

#define DEF_ITEMSPREAD_RANDOM						1
#define DEF_ITEMSPREAD_FIXED						2
#define MAX_NPCITEMDROP								25

// ============================================================================
// Item Upgrade and Logs
// ============================================================================

#define DEF_ITEMLOG_UPGRADESUCCESS					30
#define DEF_ITEMLOG_UPGRADEFAIL						29

// ============================================================================
// Slate System (Server-Only Part)
// ============================================================================

#define DEF_NOTIFY_SLATECLEAR						99

// ============================================================================
// PK (Player Kill) Logging Constants
// Used only by server for internal PK tracking
// ============================================================================

#define DEF_PKLOG_REDUCECRIMINAL					1
#define DEF_PKLOG_BYPLAYER							2
#define DEF_PKLOG_BYPK								3
#define DEF_PKLOG_BYENERMY							4
#define DEF_PKLOG_BYNPC								5
#define DEF_PKLOG_BYOTHER							6
