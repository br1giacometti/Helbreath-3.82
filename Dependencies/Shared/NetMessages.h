#pragma once

// NetMessages.h - Shared Network Protocol Definitions
//
// This file contains network message IDs and constants used by BOTH the
// Helbreath Client and Server for communication protocol.
//
// IMPORTANT: Any changes to message IDs or constants must be tested with
// both client and server to ensure compatibility.
//
// For client-only messages, see Sources/Client/ClientMessages.h
// For server-only messages, see Sources/Server/ServerMessages.h

// ============================================================================
// Basic Message Types
// ============================================================================

#define DEF_MSGTYPE_CONFIRM					0x0F14
#define DEF_MSGTYPE_REJECT					0x0F15

// ============================================================================
// Player Initialization Messages
// ============================================================================

#define MSGID_REQUEST_INITPLAYER			0x05040205  // Client → Server
#define MSGID_RESPONSE_INITPLAYER			0x05040206  // Server → Client

#define MSGID_REQUEST_INITDATA				0x05080404  // Client → Server
#define MSGID_RESPONSE_INITDATA				0x05080405  // Server → Client

// ============================================================================
// Motion and Action Messages
// ============================================================================

#define MSGID_COMMAND_MOTION				0x0FA314D5
#define MSGID_RESPONSE_MOTION				0x0FA314D6
#define MSGID_EVENT_MOTION					0x0FA314D7
#define MSGID_EVENT_LOG						0x0FA314D8

// CRITICAL: This ID is actively used for EVENT_COMMON
// Note: Server also uses this ID for MSGID_MAGICCONFIGURATIONCONTENTS (server-only)
#define MSGID_EVENT_COMMON					0x0FA314DB

#define MSGID_COMMAND_COMMON				0x0FA314DC

// ============================================================================
// Common Action Types (DEF_COMMONTYPE_*)
// Client sends action requests, Server processes them
// ============================================================================

#define DEF_COMMONTYPE_ITEMDROP					0x0A01
#define DEF_COMMONTYPE_EQUIPITEM				0x0A02
#define DEF_COMMONTYPE_REQ_LISTCONTENTS			0x0A03
#define DEF_COMMONTYPE_REQ_PURCHASEITEM			0x0A04
#define DEF_COMMONTYPE_GIVEITEMTOCHAR			0x0A05
#define DEF_COMMONTYPE_JOINGUILDAPPROVE			0x0A06
#define DEF_COMMONTYPE_JOINGUILDREJECT			0x0A07
#define DEF_COMMONTYPE_DISMISSGUILDAPPROVE		0x0A08
#define DEF_COMMONTYPE_DISMISSGUILDREJECT		0x0A09
#define DEF_COMMONTYPE_RELEASEITEM				0x0A0A
#define DEF_COMMONTYPE_TOGGLECOMBATMODE			0x0A0B
#define DEF_COMMONTYPE_SETITEM					0x0A0C
#define DEF_COMMONTYPE_MAGIC					0x0A0D
#define DEF_COMMONTYPE_REQ_STUDYMAGIC			0x0A0E
#define DEF_COMMONTYPE_REQ_TRAINSKILL			0x0A0F

#define DEF_COMMONTYPE_REQ_GETREWARDMONEY		0x0A10
#define DEF_COMMONTYPE_REQ_USEITEM				0x0A11
#define DEF_COMMONTYPE_REQ_USESKILL				0x0A12
#define DEF_COMMONTYPE_REQ_SELLITEM				0x0A13
#define DEF_COMMONTYPE_REQ_REPAIRITEM			0x0A14
#define DEF_COMMONTYPE_REQ_SELLITEMCONFIRM		0x0A15
#define DEF_COMMONTYPE_REQ_REPAIRITEMCONFIRM	0x0A16
#define DEF_COMMONTYPE_REQ_GETFISHTHISTIME		0x0A17
#define DEF_COMMONTYPE_TOGGLESAFEATTACKMODE		0x0A18
#define DEF_COMMONTYPE_REQ_CREATEPORTION		0x0A19  // Alchemy
#define DEF_COMMONTYPE_TALKTONPC				0x0A1A
#define DEF_COMMONTYPE_REQ_SETDOWNSKILLINDEX	0x0A1B
#define DEF_COMMONTYPE_REQ_GETOCCUPYFLAG		0x0A1C
#define DEF_COMMONTYPE_REQ_GETHEROMANTLE		0x0A1D
#define DEF_COMMONTYPE_EXCHANGEITEMTOCHAR		0x0A1E
#define DEF_COMMONTYPE_SETEXCHANGEITEM			0x0A1F

#define DEF_COMMONTYPE_CONFIRMEXCHANGEITEM		0x0A20
#define DEF_COMMONTYPE_CANCELEXCHANGEITEM		0x0A21
#define DEF_COMMONTYPE_QUESTACCEPTED			0x0A22
#define DEF_COMMONTYPE_BUILDITEM				0x0A23  // Manufacturing
#define DEF_COMMONTYPE_GETMAGICABILITY			0x0A24

// NOTE: 0x0A25 has dual use depending on context
#define DEF_COMMONTYPE_CLEARGUILDNAME					0x0A25
#define DEF_COMMONTYPE_REQ_GETOCCUPYFIGHTZONETICKET		0x0A25  // Same ID

#define DEF_COMMONTYPE_CRAFTITEM						0x0A28  // Crafting

#define DEF_COMMONTYPE_REQUEST_ACCEPTJOINPARTY			0x0A30
#define DEF_COMMONTYPE_REQUEST_JOINPARTY				0x0A31
#define DEF_COMMONTYPE_RESPONSE_JOINPARTY				0x0A32

#define DEF_COMMONTYPE_REQUEST_ACTIVATESPECABLTY		0x0A40

#define DEF_COMMONTYPE_REQUEST_CANCELQUEST				0x0A50
#define DEF_COMMONTYPE_REQUEST_SELECTCRUSADEDUTY		0x0A51
#define DEF_COMMONTYPE_REQUEST_MAPSTATUS				0x0A52
#define DEF_COMMONTYPE_SETGUILDTELEPORTLOC				0x0A54
#define DEF_COMMONTYPE_GUILDTELEPORT					0x0A55
#define DEF_COMMONTYPE_SUMMONWARUNIT					0x0A56
#define DEF_COMMONTYPE_SETGUILDCONSTRUCTLOC				0x0A57
#define DEF_COMMONTYPE_UPGRADEITEM						0x0A58
#define DEF_COMMONTYPE_REQGUILDNAME						0x0A59

#define DEF_COMMONTYPE_REQUEST_HUNTMODE					0x0A60  // Client name
// Note: Server uses same ID for DEF_COMMONTYPE_REQ_CHANGEPLAYMODE
#define DEF_COMMONTYPE_REQ_CREATESLATE					0x0A61

// Mob kills notification
#define DEF_NOTIFY_MOBKILLS								0x0A68

// Enchantment system (definitions present, not actively used)
#define msg_shard										0x0A71  // Definition only
#define msg_fragment									0x0A72  // Definition only
#define DEF_COMMONTYPE_ENCHANTITEM						0x0A73  // Definition only
#define DEF_COMMONTYPE_UPGRADEENCHANT					0x0A74  // Definition only
#define DEF_COMMONTYPE_DISENCHANTITEM					0x0A75  // Definition only

// ============================================================================
// Notification Messages (MSGID_NOTIFY and DEF_NOTIFY_*)
// Server sends notifications to Client about game events
// ============================================================================

#define MSGID_NOTIFY							0x0FA314D0  // Main notification message ID

#define DEF_NOTIFY_ITEMOBTAINED					0x0B01
#define DEF_NOTIFY_QUERY_JOINGUILDREQPERMISSION	0x0B02
#define DEF_NOTIFY_QUERY_DISMISSGUILDREQPERMISSION	0x0B03
#define DEF_NOTIFY_WAITFORGUILDOPERATION			0x0B04
#define DEF_NOTIFY_CANNOTCARRYMOREITEM				0x0B05
#define DEF_NOTIFY_ITEMPURCHASED					0x0B06
#define DEF_NOTIFY_HP								0x0B07
#define DEF_NOTIFY_NOTENOUGHGOLD					0x0B08
#define DEF_NOTIFY_KILLED							0x0B09
#define DEF_NOTIFY_EXP								0x0B0A
#define DEF_NOTIFY_GUILDDISBANDED					0x0B0B
#define DEF_NOTIFY_CANNOTJOINMOREGUILDSMAN			0x0B0D
#define DEF_NOTIFY_NEWGUILDSMAN						0x0B0E
#define DEF_NOTIFY_DISMISSGUILDSMAN					0x0B0F

#define DEF_NOTIFY_MAGICSTUDYSUCCESS				0x0B10
#define DEF_NOTIFY_MAGICSTUDYFAIL					0x0B11
#define DEF_NOTIFY_SKILLTRAINSUCCESS				0x0B12
#define DEF_NOTIFY_MP								0x0B14
#define DEF_NOTIFY_SP								0x0B15
#define DEF_NOTIFY_LEVELUP							0x0B16
#define DEF_NOTIFY_ITEMLIFESPANEND					0x0B17
#define DEF_NOTIFY_LIMITEDLEVEL						0x0B18
#define DEF_NOTIFY_ITEMTOBANK						0x0B19
#define DEF_NOTIFY_PKPENALTY						0x0B1A
#define DEF_NOTIFY_PKCAPTURED						0x0B1B
#define DEF_NOTIFY_ENEMYKILLREWARD					0x0B1C
#define DEF_NOTIFY_GIVEITEMFIN_ERASEITEM			0x0B1D
#define DEF_NOTIFY_DROPITEMFIN_ERASEITEM			0x0B1F

#define DEF_NOTIFY_ITEMDEPLETED_ERASEITEM			0x0B20
#define DEF_NOTIFY_NEWDYNAMICOBJECT					0x0B21  // Server → Client
#define DEF_NOTIFY_DELDYNAMICOBJECT					0x0B22  // Server → Client
#define DEF_NOTIFY_SKILL							0x0B23
#define DEF_NOTIFY_SERVERCHANGE						0x0B24
#define DEF_NOTIFY_SETITEMCOUNT						0x0B25
#define DEF_NOTIFY_CANNOTITEMTOBANK					0x0B26
#define DEF_NOTIFY_MAGICEFFECTON					0x0B27
#define DEF_NOTIFY_MAGICEFFECTOFF					0x0B28
#define DEF_NOTIFY_TOTALUSERS						0x0B29
#define DEF_NOTIFY_SKILLUSINGEND					0x0B2A
#define DEF_NOTIFY_SHOWMAP							0x0B2B
#define DEF_NOTIFY_CANNOTSELLITEM					0x0B2C
#define DEF_NOTIFY_SELLITEMPRICE					0x0B2D
#define DEF_NOTIFY_CANNOTREPAIRITEM					0x0B2E
#define DEF_NOTIFY_REPAIRITEMPRICE					0x0B2F

#define DEF_NOTIFY_ITEMREPAIRED						0x0B30
#define DEF_NOTIFY_ITEMSOLD							0x0B31
#define DEF_NOTIFY_CHARISMA							0x0B32
#define DEF_NOTIFY_PLAYERONGAME						0x0B33
#define DEF_NOTIFY_PLAYERNOTONGAME					0x0B34
#define DEF_NOTIFY_WHISPERMODEON					0x0B35
#define DEF_NOTIFY_WHISPERMODEOFF					0x0B36
#define DEF_NOTIFY_PLAYERPROFILE					0x0B37
#define DEF_NOTIFY_TRAVELERLIMITEDLEVEL				0x0B38
#define DEF_NOTIFY_HUNGER							0x0B39

#define DEF_NOTIFY_TOBERECALLED						0x0B40
#define DEF_NOTIFY_TIMECHANGE						0x0B41
#define DEF_NOTIFY_PLAYERSHUTUP						0x0B42
#define DEF_NOTIFY_ADMINUSERLEVELLOW				0x0B43
#define DEF_NOTIFY_CANNOTRATING						0x0B44
#define DEF_NOTIFY_RATINGPLAYER						0x0B45
#define DEF_NOTIFY_NOTICEMSG						0x0B46
#define DEF_NOTIFY_EVENTFISHMODE					0x0B47
#define DEF_NOTIFY_FISHCHANCE						0x0B48
#define DEF_NOTIFY_FISHSUCCESS						0x0B4A
#define DEF_NOTIFY_FISHFAIL							0x0B4B
#define DEF_NOTIFY_FISHCANCELED						0x0B4C
#define DEF_NOTIFY_WHETHERCHANGE					0x0B4D
#define DEF_NOTIFY_SERVERSHUTDOWN					0x0B4E
#define DEF_NOTIFY_REWARDGOLD						0x0B4F

#define DEF_NOTIFY_IPACCOUNTINFO					0x0B50
#define DEF_NOTIFY_SAFEATTACKMODE					0x0B51
#define DEF_NOTIFY_SUPERATTACKLEFT					0x0B52
#define DEF_NOTIFY_NOMATCHINGPORTION				0x0B53
#define DEF_NOTIFY_LOWPORTIONSKILL					0x0B54
#define DEF_NOTIFY_PORTIONFAIL						0x0B55
#define DEF_NOTIFY_PORTIONSUCCESS					0x0B56
#define DEF_NOTIFY_NPCTALK							0x0B57
#define DEF_NOTIFY_ADMINIFO							0x0B58
#define DEF_NOTIFY_DOWNSKILLINDEXSET				0x0B59
#define DEF_NOTIFY_ENEMYKILLS						0x0B5A
#define DEF_NOTIFY_ITEMPOSLIST						0x0B5B
#define DEF_NOTIFY_ITEMRELEASED						0x0B5C
#define DEF_NOTIFY_NOTFLAGSPOT						0x0B5D
#define DEF_NOTIFY_OPENEXCHANGEWINDOW				0x0B5E
#define DEF_NOTIFY_SETEXCHANGEITEM					0x0B5F

#define DEF_NOTIFY_CANCELEXCHANGEITEM				0x0B60
#define DEF_NOTIFY_EXCHANGEITEMCOMPLETE				0x0B61
#define DEF_NOTIFY_CANNOTGIVEITEM					0x0B62
#define DEF_NOTIFY_GIVEITEMFIN_COUNTCHANGED			0x0B63
#define DEF_NOTIFY_DROPITEMFIN_COUNTCHANGED			0x0B64
#define DEF_NOTIFY_ITEMCOLORCHANGE					0x0B65
#define DEF_NOTIFY_QUESTCONTENTS					0x0B66
#define DEF_NOTIFY_QUESTABORTED						0x0B67
#define DEF_NOTIFY_QUESTCOMPLETED					0x0B68
#define DEF_NOTIFY_QUESTREWARD						0x0B69

#define DEF_NOTIFY_BUILDITEMSUCCESS					0x0B70
#define DEF_NOTIFY_BUILDITEMFAIL					0x0B71
#define DEF_NOTIFY_OBSERVERMODE						0x0B72
#define DEF_NOTIFY_GLOBALATTACKMODE					0x0B73
#define DEF_NOTIFY_DAMAGEMOVE						0x0B74
#define DEF_NOTIFY_FORCEDISCONN						0x0B75
#define DEF_NOTIFY_FIGHTZONERESERVE					0x0B76
#define DEF_NOTIFY_NOGUILDMASTERLEVEL				0x0B77
#define DEF_NOTIFY_SUCCESSBANGUILDMAN				0x0B78
#define DEF_NOTIFY_CANNOTBANGUILDMAN				0x0B79

#define DEF_NOTIFY_RESPONSE_CREATENEWPARTY			0x0B80
#define DEF_NOTIFY_QUERY_JOINPARTY					0x0B81

#define DEF_NOTIFY_ENERGYSPHERECREATED				0x0B90
#define DEF_NOTIFY_ENERGYSPHEREGOALIN				0x0B91
#define DEF_NOTIFY_SPECIALABILITYENABLED			0x0B92
#define DEF_NOTIFY_SPECIALABILITYSTATUS				0x0B93
#define DEF_NOTIFY_CRUSADE							0x0B94
#define DEF_NOTIFY_LOCKEDMAP						0x0B95
#define DEF_NOTIFY_MAPSTATUSNEXT					0x0B97
#define DEF_NOTIFY_MAPSTATUSLAST					0x0B98
#define DEF_NOTIFY_METEORSTRIKECOMING				0x0B9B
#define DEF_NOTIFY_METEORSTRIKEHIT					0x0B9C
#define DEF_NOTIFY_GRANDMAGICRESULT					0x0B9D
#define DEF_NOTIFY_NOMORECRUSADESTRUCTURE			0x0B9E
#define DEF_NOTIFY_CONSTRUCTIONPOINT				0x0B9F

#define DEF_NOTIFY_TCLOC							0x0BA0
#define DEF_NOTIFY_CANNOTCONSTRUCT					0x0BA1
#define DEF_NOTIFY_PARTY							0x0BA2
#define DEF_NOTIFY_ITEMATTRIBUTECHANGE				0x0BA3
#define DEF_NOTIFY_GIZONITEMUPGRADELEFT				0x0BA4
#define DEF_NOTIFY_GIZONEITEMCHANGE					0x0BA5
#define DEF_NOTIFY_REQGUILDNAMEANSWER				0x0BA6
#define DEF_NOTIFY_FORCERECALLTIME					0x0BA7
#define DEF_NOTIFY_ITEMUPGRADEFAIL					0x0BA8
#define DEF_NOTIFY_CHANGEPLAYMODE					0x0BA9
#define DEF_NOTIFY_SPAWNEVENT						0x0BAA

#define DEF_NOTIFY_NOMOREAGRICULTURE				0x0BB0
#define DEF_NOTIFY_AGRICULTURESKILLLIMIT			0x0BB1
#define DEF_NOTIFY_AGRICULTURENOAREA				0x0BB2
#define DEF_NOTIFY_SETTING_SUCCESS					0x0BB3
#define DEF_NOTIFY_SETTING_FAILED					0x0BB4
#define DEF_NOTIFY_STATECHANGE_SUCCESS				0x0BB5
#define DEF_NOTIFY_STATECHANGE_FAILED				0x0BB6

#define DEF_NOTIFY_SLATE_CREATESUCCESS				0x0BC1
#define DEF_NOTIFY_SLATE_CREATEFAIL					0x0BC2

#define DEF_NOTIFY_NORECALL							0x0BD1
#define DEF_NOTIFY_APOCGATESTARTMSG					0x0BD2
#define DEF_NOTIFY_APOCGATEENDMSG					0x0BD3
#define DEF_NOTIFY_APOCGATEOPEN						0x0BD4
#define DEF_NOTIFY_APOCGATECLOSE					0x0BD5
#define DEF_NOTIFY_ABADDONKILLED					0x0BD6
#define DEF_NOTIFY_APOCFORCERECALLPLAYERS			0x0BD7
#define DEF_NOTIFY_SLATE_INVINCIBLE					0x0BD8
#define DEF_NOTIFY_SLATE_MANA						0x0BD9

#define DEF_NOTIFY_SLATE_EXP						0x0BE0
#define DEF_NOTIFY_SLATE_STATUS						0x0BE1
#define DEF_NOTIFY_QUESTCOUNTER						0x0BE2
#define DEF_NOTIFY_MONSTERCOUNT						0x0BE3
// #define DEF_NOTIFY_0BE5							0x0BE5  // Undefined - Abaddon related
#define DEF_NOTIFY_HELDENIANTELEPORT				0x0BE6
#define DEF_NOTIFY_HELDENIANEND						0x0BE7
#define DEF_NOTIFY_0BE8								0x0BE8  // Definition only
#define DEF_NOTIFY_RESURRECTPLAYER					0x0BE9
#define DEF_NOTIFY_HELDENIANSTART					0x0BEA
#define DEF_NOTIFY_HELDENIANCOUNT					0x0BEC

// Reversed 3.60+ MSGIDs
#define DEF_NOTIFY_SLATE_BERSERK					0x0BED
#define DEF_NOTIFY_LOTERY_LOST						0x0BEE
// #define DEF_NOTIFY_0BEF							0x0BEF  // Undefined
#define DEF_NOTIFY_CRAFTING_SUCCESS					0x0BF0
#define DEF_NOTIFY_CRAFTING_FAIL					0x0BF1

#define DEF_NOTIFY_ANGELIC_STATS					0x0BF2
#define DEF_NOTIFY_CURLIFESPAN						0x0BF3

#define DEF_NOTIFY_ANGEL_FAILED						0x0BF4
#define DEF_NOTIFY_ANGEL_RECEIVED					0x0BF5

#define DEF_NOTIFY_SPELL_SKILL						0x0BF6

// ============================================================================
// Repair All System
// ============================================================================

#define DEF_COMMONTYPE_REQ_REPAIRALL				0x0F10
#define DEF_NOTIFY_REPAIRALLPRICES					0x0F11
#define DEF_COMMONTYPE_REQ_REPAIRALLCONFIRM			0x0F13

// ============================================================================
// HP Bar System
// ============================================================================

#define DEF_COMMONTYPE_REQ_GETNPCHP					0x1F12
#define DEF_SEND_NPCHP								0x1F13

// ============================================================================
// Configuration Content Messages
// ============================================================================

#define MSGID_ITEMCONFIGURATIONCONTENTS				0x0FA314D9
// Note: MSGID_MAGICCONFIGURATIONCONTENTS is server-only
#define MSGID_PLAYERITEMLISTCONTENTS				0x0FA314DD
#define MSGID_PLAYERCHARACTERCONTENTS				0x0FA40000

// ============================================================================
// Connection and Chat Messages
// ============================================================================

#define MSGID_COMMAND_CHECKCONNECTION				0x03203203
#define MSGID_COMMAND_CHATMSG						0x03203204

// ============================================================================
// Login and Account Management
// ============================================================================

#define MSGID_REQUEST_LOGIN							0x0FC94201  // Client → Server
#define MSGID_REQUEST_CREATENEWACCOUNT				0x0FC94202  // Client → Server
#define MSGID_RESPONSE_LOG							0x0FC94203  // Server → Client
#define MSGID_REQUEST_CREATENEWCHARACTER			0x0FC94204  // Client → Server
#define MSGID_REQUEST_ENTERGAME						0x0FC94205  // Client → Server
#define MSGID_RESPONSE_ENTERGAME					0x0FC94206  // Server → Client
#define MSGID_REQUEST_DELETECHARACTER				0x0FC94207  // Client → Server
#define MSGID_REQUEST_CREATENEWGUILD				0x0FC94208  // Client → Server
#define MSGID_RESPONSE_CREATENEWGUILD				0x0FC94209  // Server → Client
#define MSGID_REQUEST_DISBANDGUILD					0x0FC9420A  // Client → Server
#define MSGID_RESPONSE_DISBANDGUILD					0x0FC9420B  // Server → Client

#define MSGID_REQUEST_CIVILRIGHT					0x0FC9420E  // Client → Server
#define MSGID_RESPONSE_CIVILRIGHT					0x0FC9420F  // Server → Client

#define MSGID_REQUEST_CHANGEPASSWORD				0x0FC94210  // Client → Server
#define MSGID_RESPONSE_CHANGEPASSWORD				0x0FC94211  // Server → Client (definition)

#define MSGID_REQUEST_INPUTKEYCODE					0x0FC94212  // Client → Server
#define MSGID_RESPONSE_INPUTKEYCODE					0x0FC94213  // Server → Client (definition)

// Resurrection
#define DEF_REQUEST_RESURRECTPLAYER_YES				0x0FC94214
#define DEF_REQUEST_RESURRECTPLAYER_NO				0x0FC94215  // Definition

// Angel Request (Reversed by Snoopy)
#define DEF_REQUEST_ANGEL							0x0FC9421E

// ============================================================================
// Log Server Response Types (DEF_LOGRESMSGTYPE_*)
// Server sends login/account responses to client
// ============================================================================

#define DEF_LOGRESMSGTYPE_CONFIRM					0x0F14
#define DEF_LOGRESMSGTYPE_REJECT					0x0F15
#define DEF_LOGRESMSGTYPE_PASSWORDMISMATCH			0x0F16
#define DEF_LOGRESMSGTYPE_NOTEXISTINGACCOUNT		0x0F17
#define DEF_LOGRESMSGTYPE_NEWACCOUNTCREATED			0x0F18
#define DEF_LOGRESMSGTYPE_NEWACCOUNTFAILED			0x0F19
#define DEF_LOGRESMSGTYPE_ALREADYEXISTINGACCOUNT	0x0F1A
#define DEF_LOGRESMSGTYPE_NOTEXISTINGCHARACTER		0x0F1B
#define DEF_LOGRESMSGTYPE_NEWCHARACTERCREATED		0x0F1C
#define DEF_LOGRESMSGTYPE_NEWCHARACTERFAILED		0x0F1D
#define DEF_LOGRESMSGTYPE_ALREADYEXISTINGCHARACTER	0x0F1E
#define DEF_LOGRESMSGTYPE_CHARACTERDELETED			0x0F1F
#define DEF_LOGRESMSGTYPE_NOTENOUGHPOINT			0x0F30
#define DEF_LOGRESMSGTYPE_ACCOUNTLOCKED				0x0F31
#define DEF_LOGRESMSGTYPE_SERVICENOTAVAILABLE		0x0F32
#define DEF_LOGRESMSGTYPE_PASSWORDCHANGESUCCESS		0x0A00
#define DEF_LOGRESMSGTYPE_PASSWORDCHANGEFAIL		0x0A01
#define DEF_LOGRESMSGTYPE_NOTEXISTINGWORLDSERVER	0x0A02
#define DEF_LOGRESMSGTYPE_INPUTKEYCODE				0x0A03
#define DEF_LOGRESMSGTYPE_REALACCOUNT				0x0A04  // Client only
#define DEF_LOGRESMSGTYPE_FORCECHANGEPASSWORD		0x0A05
#define DEF_LOGRESMSGTYPE_INVALIDKOREANSSN			0x0A06
#define DEF_LOGRESMSGTYPE_LESSTHENFIFTEEN			0x0A07

// ============================================================================
// Enter Game Message Types
// ============================================================================

#define DEF_ENTERGAMEMSGTYPE_NEW					0x0F1C
#define DEF_ENTERGAMEMSGTYPE_NOENTER_FORCEDISCONN	0x0F1D
#define DEF_ENTERGAMEMSGTYPE_CHANGINGSERVER			0x0F1E
#define DEF_ENTERGAMEMSGTYPE_NEW_TOWLSBUTMLS		0x0F1F
#define DEF_ENTERGAMERESTYPE_PLAYING				0x0F20
#define DEF_ENTERGAMERESTYPE_REJECT					0x0F21
#define DEF_ENTERGAMERESTYPE_CONFIRM				0x0F22
#define DEF_ENTERGAMERESTYPE_FORCEDISCONN			0x0F23

// ============================================================================
// Item Messages
// ============================================================================

#define MSGID_REQUEST_RETRIEVEITEM					0x0DF30751
#define MSGID_RESPONSE_RETRIEVEITEM					0x0DF30752

#define MSGID_REQUEST_FULLOBJECTDATA				0x0DF40000

// ============================================================================
// Teleport Messages
// ============================================================================

#define MSGID_REQUEST_TELEPORT						0x0EA03201

// Note: Client and Server have different teleport message IDs
// See ClientMessages.h and ServerMessages.h for platform-specific messages

// Heldenian scroll purchase (Added by Snoopy)
#define MSGID_REQUEST_HELDENIAN_SCROLL				0x3D001244

// ============================================================================
// Level Up and Dynamic Objects
// ============================================================================

#define MSGID_LEVELUPSETTINGS						0x11A01000
#define MSGID_DYNAMICOBJECT							0x12A01001

// Fight Zone Reserve
#define MSGID_REQUEST_FIGHTZONE_RESERVE				0x12A01007
#define MSGID_RESPONSE_FIGHTZONE_RESERVE			0x12A01008

// ============================================================================
// Item Position
// ============================================================================

#define MSGID_REQUEST_SETITEMPOS					0x180ACE0A

// ============================================================================
// Notice Messages
// ============================================================================

#define MSGID_REQUEST_NOTICEMENT					0x220B2F00
#define MSGID_RESPONSE_NOTICEMENT					0x220B2F01

// ============================================================================
// Panning and Restart Messages
// ============================================================================

#define MSGID_REQUEST_PANNING						0x27B314D0
#define MSGID_RESPONSE_PANNING						0x27B314D1

#define MSGID_REQUEST_RESTART						0x28010EEE

// ============================================================================
// Item Sell List
// ============================================================================

// NOTE: This conflicts with server-only MSGID_REQUEST_IPTIME
#define MSGID_REQUEST_SELLITEMLIST					0x2900AD30

// ============================================================================
// MJ Stats Change
// ============================================================================

#define MSGID_STATECHANGEPOINT						0x11A01001

#define DEF_STR										0x01
#define DEF_DEX										0x02
#define DEF_INT										0x03
#define DEF_VIT										0x04
#define DEF_MAG										0x05
#define DEF_CHR										0x06
