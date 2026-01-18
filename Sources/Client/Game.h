// Game.h: interface for the CGame class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

// MODERNIZED: Prevent old winsock.h from loading (must be before windows.h)
#define _WINSOCKAPI_

#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <mmsystem.h>
#include <winbase.h>
#include <memory.h>
#include <string.h>
#include <process.h>
#include <direct.h>
#include <tlhelp32.h>
#include <fstream>
#include <iostream>
#include <iosfwd>
#include <vector>
#include <sstream>
using namespace std;

#include "GlobalDef.h"
#include "DXC_ddraw.h"
#include "InputManager.h"
#include "XSocket.h"
#include "Sprite.h"
#include "SpriteID.h"
#include "Misc.h"
#include "ChatMsg.h"
#include "Effect.h"
#include "MapData.h"
#include "ActionID.h"
#include "ActionID_Client.h"
#include "NetMessages.h"
#include "ClientMessages.h"
#include "MouseInterface.h"
#include "CharInfo.h"
#include "Item/Item.h"
#include "Magic.h"
#include "Skill.h"
#include "DynamicObjectID.h"
#include "GameMonitor.h"
#include "BuildItem.h"
#include "Curse.h"
#include "DialogBoxManager.h"
#include "EffectManager.h"
#include "NetworkMessageManager.h"

//v2.18
#define DEF_BTNSZX				74
#define DEF_BTNSZY				20
#define DEF_LBTNPOSX			30
#define DEF_RBTNPOSX			154
#define DEF_BTNPOSY				292

#define DEF_INDEX4_MSGID		0
#define DEF_INDEX2_MSGTYPE		4

#define DEF_SOCKETBLOCKLIMIT	300

#define DEF_MAXSPRITES			25000	// 20000 // Snoopy: Adjusted!
#define DEF_MAXTILES			1000	// 800 // Snoopy: Adjusted!
#define DEF_MAXEFFECTSPR		300
#define DEF_MAXSOUNDEFFECTS		200		// 110   //Snoopy: Adjusted!
#define DEF_MAXCHATMSGS			500
#define DEF_MAXWHISPERMSG		5
#define DEF_MAXCHATSCROLLMSGS	80
#define DEF_MAXEFFECTS			300	//600 <- original
#define DEF_CHATTIMEOUT_A		4000
#define DEF_CHATTIMEOUT_B		500
#define DEF_CHATTIMEOUT_C		2000
#define DEF_MAXITEMS			50
#define DEF_MAXBANKITEMS		1000 // Hard cap - actual soft limit received from server
#define DEF_MAXGUILDSMAN		32
#define DEF_MAXMENUITEMS		140  //v2.15  120 ->140
#define DEF_TEXTDLGMAXLINES		300 //v2.18 3000->300

#define DEF_MAXMAGICTYPE		100
#define DEF_MAXSKILLTYPE		60
#define DEF_MAXWHETHEROBJECTS	600
#define DEF_MAXBUILDITEMS		100
#define DEF_MAXGAMEMSGS			300
#define DEF_MAXGUILDNAMES		100
#define DEF_MAXSELLLIST			12

#define WM_USER_GAMESOCKETEVENT	WM_USER + 2000
#define WM_USER_LOGSOCKETEVENT	WM_USER + 2001

#define DEF_GAMEMODE_NULL					-2
#define DEF_GAMEMODE_ONQUIT					-1
#define DEF_GAMEMODE_ONMAINMENU				0
#define DEF_GAMEMODE_ONCONNECTING			1
#define DEF_GAMEMODE_ONLOADING				2
#define DEF_GAMEMODE_ONWAITINGINITDATA		3
#define DEF_GAMEMODE_ONMAINGAME				4
#define DEF_GAMEMODE_ONCONNECTIONLOST		5
#define DEF_GAMEMODE_ONMSG					6
#define DEF_GAMEMODE_ONCREATENEWACCOUNT		7
#define DEF_GAMEMODE_ONLOGIN				8
#define DEF_GAMEMODE_ONQUERYFORCELOGIN		9
#define DEF_GAMEMODE_ONSELECTCHARACTER		10
#define DEF_GAMEMODE_ONCREATENEWCHARACTER	11
#define DEF_GAMEMODE_ONWAITINGRESPONSE		12
#define DEF_GAMEMODE_ONQUERYDELETECHARACTER 13
#define DEF_GAMEMODE_ONLOGRESMSG			14
#define DEF_GAMEMODE_ONCHANGEPASSWORD		15
#define DEF_GAMEMODE_ONVERSIONNOTMATCH		17
#define DEF_GAMEMODE_ONINTRODUCTION			18
#define DEF_GAMEMODE_ONAGREEMENT			19
#define DEF_GAMEMODE_ONSELECTSERVER			20
#define DEF_GAMEMODE_ONINPUTKEYCODE			21

#define DEF_SERVERTYPE_GAME			1
#define DEF_SERVERTYPE_LOG			2

#define DEF_CURSORSTATUS_NULL		0
#define DEF_CURSORSTATUS_PRESSED	1
#define DEF_CURSORSTATUS_SELECTED	2
#define DEF_CURSORSTATUS_DRAGGING	3

#define DEF_SELECTEDOBJTYPE_DLGBOX	1
#define DEF_SELECTEDOBJTYPE_ITEM	2

#define DEF_DOUBLECLICKTIME			300
#define DEF_DOUBLECLICKTOLERANCE	4
#define DEF_MAXPARTYMEMBERS			8
#define DEF_MAXCRUSADESTRUCTURES	300

// Overlay types for popup screens that render over base screens
enum class OverlayType {
	None = 0,
	Connecting,
	WaitingResponse,
	LogResMsg,
	QueryForceLogin,
	QueryDeleteCharacter
};

template <typename T, class = typename enable_if<!is_pointer<T>::value>::type >
static void Push(char*& cp, T value) {
	auto p = (T*)cp;
	*p = (T)value;
	cp += sizeof(T);
}

template <typename T, class = typename enable_if<!is_pointer<T>::value>::type >
static void Pop(char*& cp, T& v) {
	T* p = (T*)cp;
	v = *p;
	cp += sizeof(T);
}

static void Push(char*& dest, const char* src, uint32_t len) {
	memcpy(dest, src, len);
	dest += len;
}

static void Push(char*& dest, const char* src) {

	strcpy(dest, src);
	dest += strlen(src) + 1;
}

static void Push(char*& dest, const string& str) {
	strcpy(dest, str.c_str());
	dest += str.length() + 1;
}

static void Pop(char*& src, char* dest, uint32_t len) {
	memcpy(dest, src, len);
	src += len;
}
static void Pop(char*& src, char* dest) {

	uint32_t len = strlen(src) + 1;
	memcpy(dest, src, len);
	src += len;
}

static void Pop(char*& src, string& str) {
	str = src;
	src += str.length() + 1;
}



class CGame
{
public:
	// CLEROTH - AURAS
	void CheckActiveAura(short sX, short sY, uint32_t dwTime, short sOwnerType);
	void CheckActiveAura2(short sX, short sY, uint32_t dwTime, short sOwnerType);

	void NotifyMsg_CurLifeSpan(char* pData);

	// MJ Stats Change Related vars - Alastor
	char cStateChange1;
	char cStateChange2;
	char cStateChange3;

	struct {
		char cName[21], cDesc[11];
		int iCount;
		uint32_t dwType;
		uint32_t dwValue;
	} m_stShards[13][17];

	struct {
		char cName[21], cDesc[11];
		int iCount;
		uint32_t dwType;
		uint32_t dwValue;
	} m_stFragments[13][17];

	int m_iTeleportMapCount;
	void ResponseTeleportList(char * pData);
	void ResponseChargedTeleport(char * pData);

	void ItemEquipHandler(char cItemID);
	void ReleaseEquipHandler(char cEquipPos);

	void ReadSettings();
	void WriteSettings();

	int  iGetManaCost(int iMagicNo);
	void UseMagic(int iMagicNo);
	bool _bCheckMoveable( short sx, short sy );
	bool FindGuildName(char* pName, int* ipIndex);
	void bItemDrop_SkillDialog();
	void bItemDrop_IconPannel(short msX, short msY);
	void bItemDrop_Character();
	void bItemDrop_Inventory(short msX, short msY);
	void bItemDrop_ItemUpgrade();
	void bItemDrop_SellList(short msX, short msY);
	void bItemDrop_ExchangeDialog(short msX, short msY);
	void bItemDrop_Bank(short msX, short msY);
	void bItemDrop_ExternalScreen(char cItemID, short msX, short msY);
	void CreateScreenShot();
	void CrusadeWarResult(int iWinnerSide);
	void CrusadeContributionResult(int iWarContribution);
	void CannotConstruct(int iCode);
	void DrawTopMsg();
	void SetTopMsg(char * pString, unsigned char iLastSec);
	void DrawObjectFOE(int ix, int iy, int iFrame);
	void GrandMagicResult(char * pMapName, int iV1, int iV2, int iV3, int iV4, int iHP1, int iHP2, int iHP3, int iHP4) ;
	void MeteorStrikeComing(int iCode);
	void _Draw_OnLogin(char * pAccount, char * pPassword, int msX, int msY, int iFrame = 60000);
	void DrawNewDialogBox(char cType, int sX, int sY, int iFrame, bool bIsNoColorKey = false, bool bIsTrans = false);
	void AddMapStatusInfo(char * pData, bool bIsLastData);
	void _RequestMapStatus(char * pMapName, int iMode);
	int  GetCharKind(char *str, int index);
	void ReceiveString(char * pString);
	void EndInputString();
	void ClearInputString();
	void ShowReceivedString(bool bIsHide = false);
	bool GetText(HWND hWnd,UINT msg,WPARAM wparam, LPARAM lparam);
	void DrawDialogBoxs(short msX, short msY, short msZ, char cLB);
	void DisplayCommaNumber_G_cTxt(uint32_t iGold);// Name changed by Snoopy (easyer to understand...)

	// Slates - Alastor
	void bItemDrop_Slates();

	bool _bCheckDlgBoxClick(short msX, short msY);


	void ResponsePanningHandler(char * pData);
	void _CalcSocketClosed();
	void UpdateScreen_OnSelectServer();
	void StartInputString(int sX, int sY, unsigned char iLen, char * pBuffer, bool bIsHide = false);
	void _SetIlusionEffect(int iOwnerH);
	int _iGetFOE(int iStatus);
	void NoticementHandler(char * pData);
	void GetItemName(short sItemId, uint32_t dwAttribute, char *pStr1, char *pStr2, char *pStr3);
	void GetItemName(class CItem * pItem, char * pStr1, char * pStr2, char * pStr3);
	short FindItemIdByName(const char* cItemName);
	void _InitOnCreateNewCharacter();
	void _LoadGameMsgTextContents();
	bool _bCheckCurrentBuildItemStatus();
	bool _bCheckBuildItemStatus();
	bool _bDecodeBuildItemContents();
	bool _bCheckBadWords(char * pMsg);
	void GetNpcName(short sType, char * pName);


#ifdef DEF_MAKE_ACCOUNT
	int m_iAgreeView;
	void _LoadAgreementTextContents(char cType);
	void UpdateScreen_OnAgreement();
	void UpdateScreen_OnCreateNewAccount();
#endif


	void UseShortCut( int num );
	void UpdateScreen();
	void DrawScreen();        // Dispatches to Draw_* methods based on game mode
	void RenderFrame();       // Clear backbuffer -> DrawScreen -> Flip (centralized)
	void UpdateScreen_OnMainMenu();
	void UpdateScreen_OnGame();
	void DrawScreen_OnGame();
	void UpdateScreen_OnConnecting();
	void UpdateScreen_OnWaitInitData();
	void MakeSprite( char* FileName, short sStart, short sCount, bool bAlphaEffect = true);
	void MakeTileSpr( char* FileName, short sStart, short sCount, bool bAlphaEffect = true);
	void MakeEffectSpr( char* FileName, short sStart, short sCount, bool bAlphaEffect = true);
	void UpdateScreen_OnLoading(bool bActive);
	void UpdateScreen_OnConnectionLost();
	void UpdateScreen_OnLogin();
	void UpdateScreen_OnMsg();
	void UpdateScreen_OnQuit();
	void UpdateScreen_OnQueryForceLogin();
	void UpdateScreen_OnQueryDeleteCharacter();
	void UpdateScreen_OnWaitingResponse();
	void UpdateScreen_OnCreateNewCharacter();
	void UpdateScreen_OnSelectCharacter();
	void UpdateScreen_OnLogResMsg();
	void UpdateScreen_OnSelectCharacter(short sX, short sY, short msX, short msY, bool bIgnoreFocus = false);
	void UpdateScreen_OnChangePassword();
	void UpdateScreen_OnLoading_Progress();
	void UpdateScreen_OnVersionNotMatch();

	// Separated Update/Draw methods (Phase 3 refactor)
	void UpdateScreen_Quit();
	void DrawScreen_Quit();
	void UpdateScreen_VersionNotMatch();
	void DrawScreen_VersionNotMatch();
	void UpdateScreen_ConnectionLost();
	void DrawScreen_ConnectionLost();
	void UpdateScreen_Msg();
	void DrawScreen_Msg();
	void UpdateScreen_WaitingResponse();
	void DrawScreen_WaitingResponse();
	void UpdateScreen_Connecting();
	void DrawScreen_Connecting();
	void UpdateScreen_QueryForceLogin();
	void DrawScreen_QueryForceLogin();
	void UpdateScreen_QueryDeleteCharacter();
	void DrawScreen_QueryDeleteCharacter();
	void UpdateScreen_MainMenu();
	void DrawScreen_MainMenu();
	void UpdateScreen_Login();
	void DrawScreen_Login();
	void UpdateScreen_SelectServer();
	void DrawScreen_SelectServer();
	void UpdateScreen_WaitInitData();
	void DrawScreen_WaitInitData();
	void UpdateScreen_LogResMsg();
	void DrawScreen_LogResMsg();
	void UpdateScreen_ChangePassword();
	void DrawScreen_ChangePassword();
	void UpdateScreen_CreateNewAccount();
	void DrawScreen_CreateNewAccount();
	void UpdateScreen_SelectCharacter();
	void DrawScreen_SelectCharacter();
	void UpdateScreen_CreateNewCharacter();
	void DrawScreen_CreateNewCharacter();
	void UpdateScreen_Loading();
	void DrawScreen_Loading();

	// Overlay system for popup screens that render over base screens
	void ShowOverlay(OverlayType type, char context, char message = 0);
	void HideOverlay();
	bool IsOverlayActive() const { return m_activeOverlay != OverlayType::None; }
	void UpdateOverlay();
	void DrawOverlay();

	void NpcTalkHandler(char * pData);
	int  _iGetWeaponSkillType();
	void SetCameraShakingEffect(short sDist, int iMul = 0);
	bool bDlgBoxPress_SkillDlg(short msX, short msY);
	bool bDlgBoxPress_Inventory(short msX, short msY);
	bool bDlgBoxPress_Character(short msX, short msY);
	void ClearSkillUsingStatus();
	bool bCheckItemOperationEnabled(char cItemID);
	void _DrawThunderEffect(int sX, int sY, int dX, int dY, int rX, int rY, char cType);
	void DrawLine2(int x0, int y0, int x1, int y1, int iR, int iG, int iB);
	void DrawLine(int x0, int y0, int x1, int y1, int iR, int iG, int iB);
	void SetWhetherStatus(bool bStart, char cType);
	void WhetherObjectFrameCounter();
	void DrawWhetherEffects();
	bool bCheckExID(char * pName);
	bool bCheckLocalChatCommand(char * pMsg);
	char GetOfficialMapName(char * pMapName, char * pName);
	uint32_t iGetLevelExp(int iLevel);
	int _iCalcTotalWeight();
	void DrawVersion();
	bool _bIsItemOnHand();
	void DynamicObjectHandler(char * pData);
	bool _bCheckItemByType(char cType);
	void _DrawBlackRect(int iSize);
	void DrawNpcName(   short sX, short sY, short sOwnerType, int iStatus);
	void DrawObjectName(short sX, short sY, char * pName, int iStatus);
	void PlaySound(char cType, int iNum, int iDist, long lPan = 0);  // Forwards to AudioManager
	void _RemoveChatMsgListByObjectID(int iObjectID);
	void _LoadTextDlgContents(int cType);
	int  _iLoadTextDlgContents2(int iType);
	void DrawChatMsgs(short sX, short sY, short dX, short dY);
	void RequestFullObjectData(uint16_t wObjectID);
	bool bInitSkillCfgList();
	bool bCheckImportantFile();
	void DlbBoxDoubleClick_Inventory(short msX, short msY);
	void DlbBoxDoubleClick_Character(short msX, short msY);
	void DlbBoxDoubleClick_GuideMap(short msX, short msY);
	bool _bCheckDlgBoxDoubleClick(short msX, short msY);
	void EraseItem(char cItemID);
	void RetrieveItemHandler(char * pData);
	void CivilRightAdmissionHandler(char * pData);
	void _Draw_CharacterBody(short sX, short sY, short sType);
	void ClearContents_OnSelectCharacter();
	void ClearContents_OnCreateNewAccount();
	void _Draw_UpdateScreen_OnCreateNewAccount();
	bool _bDraw_OnCreateNewCharacter(char * pName, short msX, short msY, int iPoint);
	bool _bGetIsStringIsNumber(char * pStr);
	bool bInitMagicCfgList();
	void _LoadShopMenuContents(char cType);
	void _RequestShopContents(int16_t npcType);
	void ResponseShopContentsHandler(char* pData);
	void PutChatScrollList(char * pMsg, char cType);
	void RequestTeleportAndWaitData();
	void PointCommandHandler(int indexX, int indexY, char cItemID = -1);
	void AddEventList(char * pTxt, char cColor = 0, bool bDupAllow = true);
	void ShowEventList(uint32_t dwTime);
	void SetItemCount(char * pItemName, uint32_t dwCount);
	void _ShiftGuildOperationList();
	void _PutGuildOperationList(char * pName, char cOpMode);
	void DisbandGuildResponseHandler(char * pData);
	void InitPlayerCharacteristics(char * pData);
	void CreateNewGuildResponseHandler(char * pData);
	void _GetHairColorRGB(int iColorType , int * pR, int * pG, int * pB);
	void InitGameSettings();
	void CommonEventHandler(char * pData);
	bool _bCheckDraggingItemRelease(short msX, short msY);
	void _SetItemOrder(char cWhere, char cItemID);
	int iGetTopDialogBoxIndex();
	void DisableDialogBox(int iBoxID);
	void EnableDialogBox(int iBoxID, int cType, int sV1, int sV2, char * pString = 0);
	void InitItemList(char * pData);
	int _iCheckDlgBoxFocus(short msX, short msY, char cButtonSide);
	void GetPlayerTurn();
	bool __fastcall DrawObject_OnDead(int indexX, int indexY, int sX, int sY, bool bTrans, uint32_t dwTime, int msX, int msY);
	bool __fastcall DrawObject_OnDying(int indexX, int indexY, int sX, int sY, bool bTrans, uint32_t dwTime, int msX, int msY);
	bool __fastcall DrawObject_OnMagic(int indexX, int indexY, int sX, int sY, bool bTrans, uint32_t dwTime, int msX, int msY);
	bool __fastcall DrawObject_OnAttack(int indexX, int indexY, int sX, int sY, bool bTrans, uint32_t dwTime, int msX, int msY);
	bool __fastcall DrawObject_OnAttackMove(int indexX, int indexY, int sX, int sY, bool bTrans, uint32_t dwTime, int msX, int msY);
	bool __fastcall DrawObject_OnStop(int indexX, int indexY, int sX, int sY, bool bTrans, uint32_t dwTime, int msX, int msY);
	bool __fastcall DrawObject_OnMove_ForMenu(int indexX, int indexY, int sX, int sY, bool bTrans, uint32_t dwTime, int msX, int msY);
	bool __fastcall DrawObject_OnMove(int indexX, int indexY, int sX, int sY, bool bTrans, uint32_t dwTime, int msX, int msY, bool frame_omision);
	bool __fastcall DrawObject_OnDamageMove(int indexX, int indexY, int sX, int sY, bool bTrans, uint32_t dwTime, int msX, int msY, bool frame_omision);
	bool __fastcall DrawObject_OnRun(int indexX, int indexY, int sX, int sY, bool bTrans, uint32_t dwTime, int msX, int msY, bool frame_omision);
	bool __fastcall DrawObject_OnDamage(int indexX, int indexY, int sX, int sY, bool bTrans, uint32_t dwTime, int msX, int msY);
	bool __fastcall DrawObject_OnGetItem(int indexX, int indexY, int sX, int sY, bool bTrans, uint32_t dwTime, int msX, int msY);
	bool bEffectFrameCounter();
	void ClearGuildNameList();
	void DrawBackground(short sDivX, short sModX, short sDivY, short sModY);
	void DrawChatMsgBox(short sX, short sY, int iChatIndex, bool bIsPreDC);
	void ReleaseTimeoverChatMsg();
	void ChatMsgHandler(char * pData);
	void ReleaseUnusedSprites();
	bool bReadIp();
	void OnKeyUp(WPARAM wParam);
	void ChangeGameMode(char cMode);
	void PutString(int iX, int iY, char * pString, COLORREF color);
	void PutString(int iX, int iY, char * pString, COLORREF color, bool bHide, char cBGtype, bool bIsPreDC = false);
	void PutString2(int iX, int iY, char * pString, short sR, short sG, short sB);
	void PutAlignedString(int iX1, int iX2, int iY, char * pString, short sR = 0, short sG = 0, short sB = 0);
	void PutString_SprFont(int iX, int iY, char * pStr, short sR, short sG, short sB);
	void PutString_SprFont2(int iX, int iY, char * pStr, short sR, short sG, short sB);
	void PutString_SprFont3(int iX, int iY, char * pStr, short sR, short sG, short sB, bool bTrans = false, int iType = 0);
	void PutString_SprNum(int iX, int iY, char * pStr, short sR, short sG, short sB);
	void LogRecvMsgHandler(char * pData);
	void LogResponseHandler(char * pData);
	void OnLogSocketEvent();  // MODERNIZED: Polls socket instead of handling window messages
	void OnTimer();
	void LogEventHandler(char * pData);
	void _ReadMapData(short sPivotX, short sPivotY, const char* pData);
	void MotionEventHandler(char * pData);
	void InitDataResponseHandler(char * pData);
	void InitPlayerResponseHandler(char * pData);
	void ConnectionEstablishHandler(char cWhere);
	void MotionResponseHandler(char * pData);
	void GameRecvMsgHandler(uint32_t dwMsgSize, char * pData);
	void DrawObjects(short sPivotX, short sPivotY, short sDivX, short sDivY, short sModX, short sModY, short msX, short msY);
	bool bSendCommand(uint32_t dwMsgID, uint16_t wCommand, char cDir, int iV1, int iV2, int iV3, char * pString, int iV4 = 0); // v1.4
	char cGetNextMoveDir(short sX, short sY, short dstX, short dstY, bool bMoveCheck = false, bool bMIM = false);
	void RestoreSprites();
	void CommandProcessor(short msX, short msY, short indexX, short indexY, char cLB, char cRB);
	void OnGameSocketEvent();  // MODERNIZED: Polls socket instead of handling window messages
	void CalcViewPoint();
	void OnKeyDown(WPARAM wParam);
	void RegisterHotkeys();
	void Hotkey_ToggleForceAttack();
	void Hotkey_CycleDetailLevel();
	void Hotkey_ToggleHelp();
	void Hotkey_ToggleDialogTransparency();
	void Hotkey_ToggleSystemMenu();
	void Hotkey_ToggleGuideMap();
	void Hotkey_EnableAdminCommand();
	void Hotkey_ToggleRunningMode();
	void Hotkey_ToggleSoundAndMusic();
	void Hotkey_WhisperTarget();
	void Hotkey_Simple_UseHealthPotion();
	void Hotkey_Simple_UseManaPotion();
	void Hotkey_Simple_LoadBackupChat();
	void Hotkey_Simple_UseMagicShortcut();
	void Hotkey_Simple_ToggleCharacterInfo();
	void Hotkey_Simple_ToggleInventory();
	void Hotkey_Simple_ToggleMagic();
	void Hotkey_Simple_ToggleSkill();
	void Hotkey_Simple_ToggleChatHistory();
	void Hotkey_Simple_ToggleSystemMenu();
	void Hotkey_Simple_UseShortcut1();
	void Hotkey_Simple_UseShortcut2();
	void Hotkey_Simple_UseShortcut3();
	void Hotkey_Simple_WhisperCycleUp();
	void Hotkey_Simple_WhisperCycleDown();
	void Hotkey_Simple_ArrowLeft();
	void Hotkey_Simple_ArrowRight();
	void Hotkey_Simple_Screenshot();
	void Hotkey_Simple_TabToggleCombat();
	void Hotkey_Simple_ToggleSafeAttack();
	void Hotkey_Simple_Escape();
	void Hotkey_Simple_SpecialAbility();
	void Hotkey_Simple_ZoomIn();
	void Hotkey_Simple_ZoomOut();
	void Quit();
	bool bInit(HWND hWnd, HINSTANCE hInst, char * pCmdLine);

	void ReserveFightzoneResponseHandler(char * pData);
	int _iGetAttackType();
	bool __bDecodeBuildItemContents(char * pBuffer);
	int _iGetBankItemCount();
	int _iGetTotalItemNum();
	LONG GetRegKey(HKEY key, LPCTSTR subkey, LPTSTR retdata);
	void GoHomepage();
	void StartBGM();  // Forwards to AudioManager based on current location

	//Snoopy: added function:
	bool bReadLoginConfigFile(char * cFn);
	int bHasHeroSet( short Appr3, short Appr4, char OwnerType);
	void ShowHeldenianVictory(short sSide);
	void ResponseHeldenianTeleportList(char *pData);
	void DKGlare(int iWeaponColor, int iWeaponIndex, int *iWeaponGlare);
	void DrawDruncncity();
	void Abaddon_corpse(int sX, int sY);
	void DrawAngel(int iSprite, short sX, short sY, char cFrame, uint32_t dwTime);


	//50Cent - Repair All
	void NotifyMsg_RepairAllPrices(char* pData);
	short totalItemRepair;
	int totalPrice;
	struct
	{
		char index;
		short price;
	} m_stRepairAll[DEF_MAXITEMS];


	bool _ItemDropHistory(char * ItemName);
	CGame();
	virtual ~CGame();

	struct {
		short sX;
		short sY;
		short sCursorFrame;
		char  cPrevStatus;
		char  cSelectedObjectType;
		short sSelectedObjectID;
		short sPrevX, sPrevY, sDistX, sDistY;
		uint32_t dwSelectClickTime;
		short sClickX, sClickY;
	} m_stMCursor;

	DialogBoxManager m_dialogBoxManager;
//Snoopy=>>>>>>>>>>>>>>>>>>>>>
	struct {
		int   sV1, sV2, sV3, sV4, sV5, sV6, sV7, sItemID;
		uint32_t dwV1;
		char  cStr1[32], cStr2[32];
	} m_stDialogBoxExchangeInfo[8];
//Snoopy end<<<<<<<<<<<<<<<<<<
	struct {
		int iIndex;
		int iAmount;
	} m_stSellItemList[DEF_MAXSELLLIST];

	struct {
		char cName[22];
		char cOpMode;
	} m_stGuildOpList[100];

	struct {
		uint32_t dwTime;
		char  cColor;
		char  cTxt[96];
	} m_stEventHistory[6];

	struct {
		uint32_t dwTime;
		char  cColor;
		char  cTxt[96];
	} m_stEventHistory2[6];

	struct {
		short sX, sY, sBX;
		char cStep;
	} m_stWhetherObject[DEF_MAXWHETHEROBJECTS];

	struct {
		bool bIsQuestCompleted;
		short sWho, sQuestType, sContribution, sTargetType, sTargetCount, sX, sY, sRange;
		short sCurrentCount; // by Snoopy
		char cTargetName[22];
	} m_stQuest;

	struct {
		char cStatus;
		char cName[12];
	} m_stPartyMember[DEF_MAXPARTYMEMBERS];

	struct {
		short sX, sY;
		char cType;
		char cSide;
	} m_stCrusadeStructureInfo[DEF_MAXCRUSADESTRUCTURES];

	struct {
		char cName[12];
	} m_stPartyMemberNameList[DEF_MAXPARTYMEMBERS+1];

	// v2.171 2002-6-14
	struct {
		uint32_t dwRefTime;
		int iGuildRank;
		char cCharName[12];
		char cGuildName[24];
	} m_stGuildName[DEF_MAXGUILDNAMES];

	struct {
		int iIndex;
		char mapname[12];
		int iX;
		int iY;
		int iCost;
	} m_stTeleportList[20];

	class DXC_ddraw  m_DDraw;
	class CSprite  * m_pSprite[DEF_MAXSPRITES];
	class CSprite  * m_pTileSpr[DEF_MAXTILES];
	class CSprite  * m_pEffectSpr[DEF_MAXEFFECTSPR];
	class CMapData * m_pMapData;
	class XSocket * m_pGSock;
	class XSocket * m_pLSock;
	class CMsg    * m_pChatMsgList[DEF_MAXCHATMSGS];
	class CMsg    * m_pChatScrollList[DEF_MAXCHATSCROLLMSGS];
	class CMsg    * m_pWhisperMsg[DEF_MAXWHISPERMSG];
	EffectManager* m_pEffectManager;
	NetworkMessageManager* m_pNetworkMessageManager;
	class CItem   * m_pItemList[DEF_MAXITEMS];
	class CItem   * m_pBankList[DEF_MAXBANKITEMS];
	class CMagic * m_pMagicCfgList[DEF_MAXMAGICTYPE];
	class CSkill * m_pSkillCfgList[DEF_MAXSKILLTYPE];
	class CMsg * m_pMsgTextList[DEF_TEXTDLGMAXLINES];
	class CMsg * m_pMsgTextList2[DEF_TEXTDLGMAXLINES];
	class CMsg * m_pAgreeMsgTextList[DEF_TEXTDLGMAXLINES];
	class CMsg * m_pExID;
	class CBuildItem * m_pBuildItemList[DEF_MAXBUILDITEMS];
	class CBuildItem * m_pDispBuildItemList[DEF_MAXBUILDITEMS];


	class CGameMonitor * m_pCGameMonitor;
	class CItem * m_pItemForSaleList[DEF_MAXMENUITEMS];
	int16_t m_sPendingShopType;  // Shop type awaiting response from server (0 = none)
	class CCharInfo * m_pCharList[4];
	class CMsg * m_pGameMsgList[DEF_MAXGAMEMSGS];
	class CCurse m_curse;

	char * m_pInputBuffer;

	uint32_t G_dwGlobalTime;
	uint32_t m_dwCommandTime; //v2.15 SpeedHack
	uint32_t m_dwConnectMode;
	uint32_t m_dwTime;
	uint32_t m_dwCurTime;
	uint32_t m_dwCheckConnTime, m_dwCheckSprTime, m_dwCheckChatTime;
	uint32_t m_dwCheckConnectionTime;
	uint32_t m_dwDialogCloseTime;
	int  m_dwLogOutCountTime;//was DWORD
	uint32_t m_dwRestartCountTime;
	uint32_t m_dwWOFtime; //v1.4
	uint32_t m_dwObserverCamTime;
	uint32_t m_dwDamagedTime;
	uint32_t m_dwSpecialAbilitySettingTime;
	uint32_t m_dwCommanderCommandRequestedTime;
	uint32_t m_dwTopMsgTime;
	uint32_t m_dwEnvEffectTime;

	//v2.2
	uint32_t m_dwMonsterEventTime;
	short m_sMonsterID;
	short m_sEventX, m_sEventY;


	//v2.183 Hunter Mode;
	bool m_bHunter;
	bool m_bAresden;
	bool m_bCitizen;
	//v2.183 Hunter Mode;

	bool m_bIsProgramActive;
	bool m_bCommandAvailable;
	bool m_bIsItemEquipped[DEF_MAXITEMS];
	bool m_bIsItemDisabled[DEF_MAXITEMS];
	bool m_bIsGetPointingMode;
	bool m_bIsCombatMode;
	bool m_bIsSafeAttackMode;
	bool m_bSkillUsingStatus;
	bool m_bItemUsingStatus;
	bool m_bIsWhetherEffect;
	bool m_bSuperAttackMode;	//
	bool m_bIsObserverMode, m_bIsObserverCommanded;
	bool m_bIsPoisoned;
	bool m_bIsFirstConn;
	bool m_bIsConfusion;
	bool m_bIsRedrawPDBGS;
	bool m_bDrawFlagDir;
	bool m_bIsCrusadeMode;
	bool m_bIsSpecialAbilityEnabled;
	bool m_bInputStatus;
	bool m_bIsSpecial;

	bool m_bIsF1HelpWindowEnabled;
	bool m_bIsTeleportRequested;
	bool m_bIsPrevMoveBlocked;
	bool m_bIsHideLocalCursor;

	bool m_bForceDisconn;
	bool m_bForceAttack;
	bool m_bParalyze;

	short m_sFrameCount;
	short m_sFPS;
	uint32_t m_dwFPStime;
	int m_iLatencyMs;
	uint32_t m_dwLastNetMsgId;
	uint32_t m_dwLastNetMsgTime;
	uint32_t m_dwLastNetMsgSize;
	uint32_t m_dwLastNetRecvTime;
	uint32_t m_dwLastNpcEventTime;

	int m_iFightzoneNumber;
	int m_iFightzoneNumberTemp;
	int m_iPlayerApprColor; // v1.4
	int m_iHP;//was int			// Hit Point
	int m_iMP;//was int			// Mana Point
	int m_iSP;//was int			// Staminar Point
	int m_iAC;						// Armour Class
	int m_iTHAC0;					// To Hit Armour Class 0
	int m_iHungerStatus;

	uint32_t m_iExp;
	int m_iLevel, m_iStr, m_iInt, m_iVit, m_iDex, m_iMag, m_iCharisma, m_iContribution;
	// Snoopy: Added Angels
	int m_iAngelicStr, m_iAngelicInt, m_iAngelicDex, m_iAngelicMag;

	int m_iEnemyKillCount;
	int m_iPKCount;
	int m_iRewardGold;
	int m_iGuildRank, m_iTotalGuildsMan;
	int m_iPointCommandType;
	int m_iTotalChar;
//	int m_iAccountStatus;
	short m_sMagicShortCut;
	int m_iLU_Point;
	int m_iCameraShakingDegree;
	int m_iSuperAttackLeft;
	int m_iAccntYear, m_iAccntMonth, m_iAccntDay;
	int m_iIpYear, m_iIpMonth, m_iIpDay;
	int m_iDownSkillIndex;

	int m_iIlusionOwnerH;
	int m_iApprColor_IE;
	int m_iInputX, m_iInputY;
	int m_iPDBGSdivX, m_iPDBGSdivY;			   // Pre-Draw Background Surface
	short m_sRecentShortCut;
	short m_sShortCut[6]; // Snoopy: 6 shortcuts
	int	m_iSpecialAbilityTimeLeftSec;
	int m_iDrawFlag;
	bool m_bSkipFrame;  // Set by UpdateScreen_OnGame when iUpdateRet == 0 to skip flip

	// Frame state shared between Update and Draw phases
	short m_sFrameMouseX, m_sFrameMouseY, m_sFrameMouseZ;
	char m_cFrameMouseLB, m_cFrameMouseRB;

	int m_iSpecialAbilityType;
	int m_iTimeLeftSecAccount, m_iTimeLeftSecIP;
	int m_iCrusadeDuty;
	int m_iLogServerPort, m_iGameServerPort;
	int m_iRating; //Rating

	int m_iPrevMoveX, m_iPrevMoveY;
	int m_iBlockYear, m_iBlockMonth, m_iBlockDay;
	unsigned char m_iTopMsgLastSec;
	int m_iConstructionPoint;
	int m_iWarContribution;
	int m_iConstructLocX, m_iConstructLocY;
	int m_iNetLagCount;
	int m_iTeleportLocX, m_iTeleportLocY;
	int m_iTotalPartyMember;
	int m_iPartyStatus;
	int m_iGizonItemUpgradeLeft;
	//int m_iFeedBackCardIndex; // removed by Snoopy

	short m_sItemEquipmentStatus[DEF_MAXITEMEQUIPPOS];
	short m_sPlayerX, m_sPlayerY;
	short m_sPlayerObjectID;
	short m_sPlayerType;
	short m_sPlayerAppr1, m_sPlayerAppr2, m_sPlayerAppr3, m_sPlayerAppr4;
	int m_iPlayerStatus;
	short m_sMCX, m_sMCY;
	short m_sCommX, m_sCommY;
	int   m_iCastingMagicType;
	short m_sDamageMove, m_sDamageMoveAmount;
	short m_sAppr1_IE, m_sAppr2_IE, m_sAppr3_IE, m_sAppr4_IE;
	int m_iStatus_IE;
	short m_sViewDstX, m_sViewDstY;
	short m_sViewPointX, m_sViewPointY;
	short m_sVDL_X, m_sVDL_Y;

	uint16_t m_wCommObjectID;
	uint16_t m_wLastAttackTargetID;
	uint16_t m_wEnterGameType;
	uint16_t m_wR[16], m_wG[16], m_wB[16];
	uint16_t m_wWR[16], m_wWG[16], m_wWB[16];

	unsigned char m_cInputMaxLen;
	char m_cEdit[4];
	char G_cTxt[128];
	char m_cGameModeCount;
	char m_cBGMmapName[12];
	char m_cItemOrder[DEF_MAXITEMS];
	char m_cAmountString[12];
	char m_cLogOutCount;
	char m_cRestartCount;
	char m_cGameMode;

	// Overlay system state
	OverlayType m_activeOverlay = OverlayType::None;
	char m_cOverlayContext;      // Which background screen (replaces m_cMsg[0] for overlay)
	char m_cOverlayMessage;      // Message code (replaces m_cMsg[1] for overlay)
	uint32_t m_dwOverlayStartTime;  // When overlay was shown

	char m_cWhisperIndex;
	char m_cAccountName[12];
	char m_cAccountPassword[12];
	char m_cAccountAge[12];
	char m_cNewPassword[12];
	char m_cNewPassConfirm[12];
	char m_cAccountCountry[18];
	char m_cAccountSSN[32];
	char m_cEmailAddr[52];
	char m_cAccountQuiz[46];// Quiz
	char m_cAccountAnswer[22];
	char m_cPlayerName[12];
	char m_cPlayerDir;
	char m_cMsg[200];
	char m_cLocation[12];
	char m_cCurLocation[12];
   	char m_cGuildName[22];
	char m_cMCName[12];
	char m_cMapName[12];
	char m_cMapMessage[32];
	char m_cMapIndex;
	char m_cPlayerTurn;
	char m_cCommand;
	char m_cCurFocus, m_cMaxFocus;
	char m_cEnterCheck, m_cTabCheck, m_cLeftArrowCheck;
	char m_cArrowPressed;
	char m_cLogServerAddr[16];
	char m_cChatMsg[64];
	char m_cBackupChatMsg[64];
	char m_cGender, m_cSkinCol, m_cHairStyle, m_cHairCol, m_cUnderCol;
	char m_ccStr, m_ccVit, m_ccDex, m_ccInt, m_ccMag, m_ccChr;
	uint16_t m_cLU_Str, m_cLU_Vit, m_cLU_Dex, m_cLU_Int, m_cLU_Mag, m_cLU_Char;

	char m_cMagicMastery[DEF_MAXMAGICTYPE];
	unsigned char m_cSkillMastery[DEF_MAXSKILLTYPE]; // v1.4
	char m_cWorldServerName[32];
	char m_cMenuDir, m_cMenuDirCnt, m_cMenuFrame;
	char m_cWhetherEffectType;
	char m_cWhetherStatus;
	char m_cIlusionOwnerType;
	char m_cName_IE[12];
	char m_sViewDX, m_sViewDY;
	char m_cCommandCount;
	char m_cLoading;
	char m_cDiscount;

	char m_cStatusMapName[12];
	char m_cTopMsg[64];
	char m_cTeleportMapName[12];
	char m_cConstructMapName[12];
	char m_cGameServerName[22]; //  Gateway

	class CItem* m_pItemConfigList[5000];
	bool _bDecodeItemConfigFileContents(char* pData, uint32_t dwMsgSize);

	int iNpcHP, iNpcMaxHP;

	char m_cItemDrop[25][25];

	RECT m_rcPlayerRect, m_rcBodyRect;
	HWND m_hWnd;

	HANDLE m_hPakFile;

	bool m_bWhisper;
	bool m_bShout;

	bool m_bItemDrop;
    int  m_iItemDropCnt;

	// Snoopy: Apocalypse Gate
	char m_cGateMapName[12];
	int  m_iGatePositX, m_iGatePositY;
	int m_iHeldenianAresdenLeftTower;
	int m_iHeldenianElvineLeftTower;
	int m_iHeldenianAresdenFlags;
	int m_iHeldenianElvineFlags;
	bool m_bIllusionMVT;
	int m_iGameServerMode;
	bool m_bIsXmas;
	bool m_bUsingSlate;

	bool _tmp_bSpriteOmit;

	//Snoopy: Avatar
	bool m_bIsAvatarMode;
	bool m_bIsAvatarMessenger;

	//Snoopy: Crafting
	//bool _bDecodeCraftItemContents();
	//bool __bDecodeCraftItemContents(char *pBuffer);
	//bool _bCheckCraftItemStatus();
	//bool _bCheckCurrentCraftItemStatus();

	class CBuildItem * m_pCraftItemList[DEF_MAXBUILDITEMS];
	class CBuildItem * m_pDispCraftItemList[DEF_MAXBUILDITEMS];
	int   m_iContributionPrice;

	char m_cTakeHeroItemName[100]; //Drajwer - hero item str

	short iMaxStats;
	int iMaxLevel;
	int iMaxBankItems;
};

