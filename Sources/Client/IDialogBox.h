#pragma once

#include "DialogBoxInfo.h"
#include "DialogBoxIDs.h"
#include <cstdint>

class CGame;
class DialogBoxManager;

class IDialogBox
{
public:
	IDialogBox(DialogBoxId::Type id, CGame* pGame);
	virtual ~IDialogBox() = default;

	// Core virtual methods - must be implemented by derived classes
	virtual void OnDraw(short msX, short msY, short msZ, char cLB) = 0;
	virtual bool OnClick(short msX, short msY) = 0;

	// Optional virtual methods - override as needed
	virtual void OnUpdate() {}  // Called once per frame for enabled dialogs
	virtual bool OnDoubleClick(short msX, short msY) { return false; }
	virtual void OnEnable(int cType, int sV1, int sV2, char* pString) {}
	virtual void OnDisable() {}

	// Accessors
	DialogBoxId::Type GetId() const { return m_id; }
	DialogBoxInfo& Info();
	const DialogBoxInfo& Info() const;
	bool IsEnabled() const;

protected:
	// Helper methods - delegate to CGame
	void DrawNewDialogBox(char cType, int sX, int sY, int iFrame, bool bIsNoColorKey = false, bool bIsTrans = false);
	void PutString(int iX, int iY, char* pString, uint32_t color);
	void PutString2(int iX, int iY, char* pString, short sR, short sG, short sB);
	void PutAlignedString(int iX1, int iX2, int iY, char* pString, short sR = 0, short sG = 0, short sB = 0);
	void PlaySoundEffect(char cType, int iNum, int iDist, long lPan = 0);
	void AddEventList(char* pTxt, char cColor = 0, bool bDupAllow = true);
	bool bSendCommand(uint32_t dwMsgID, uint16_t wCommand, char cDir, int iV1, int iV2, int iV3, char* pString, int iV4 = 0);
	void SetDefaultRect(short sX, short sY, short sSizeX, short sSizeY);

	// Dialog management helpers
	void EnableDialogBox(DialogBoxId::Type id, int cType = 0, int sV1 = 0, int sV2 = 0, char* pString = nullptr);
	void DisableDialogBox(DialogBoxId::Type id);
	void DisableThisDialog();

	// Direct access to game - use m_pGame->member for all game state
	CGame* m_pGame;
	DialogBoxId::Type m_id;
};
