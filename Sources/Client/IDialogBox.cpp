#include "IDialogBox.h"
#include "Game.h"

IDialogBox::IDialogBox(DialogBoxId::Type id, CGame* pGame)
	: m_pGame(pGame)
	, m_id(id)
{
}

DialogBoxInfo& IDialogBox::Info()
{
	return m_pGame->m_dialogBoxManager.Info(m_id);
}

const DialogBoxInfo& IDialogBox::Info() const
{
	return m_pGame->m_dialogBoxManager.Info(m_id);
}

bool IDialogBox::IsEnabled() const
{
	return m_pGame->m_dialogBoxManager.IsEnabled(m_id);
}

void IDialogBox::DrawNewDialogBox(char cType, int sX, int sY, int iFrame, bool bIsNoColorKey, bool bIsTrans)
{
	m_pGame->DrawNewDialogBox(cType, sX, sY, iFrame, bIsNoColorKey, bIsTrans);
}

void IDialogBox::PutString(int iX, int iY, char* pString, uint32_t color)
{
	m_pGame->PutString(iX, iY, pString, color);
}

void IDialogBox::PutString2(int iX, int iY, char* pString, short sR, short sG, short sB)
{
	m_pGame->PutString2(iX, iY, pString, sR, sG, sB);
}

void IDialogBox::PutAlignedString(int iX1, int iX2, int iY, char* pString, short sR, short sG, short sB)
{
	m_pGame->PutAlignedString(iX1, iX2, iY, pString, sR, sG, sB);
}

void IDialogBox::PlaySoundEffect(char cType, int iNum, int iDist, long lPan)
{
	m_pGame->PlaySound(cType, iNum, iDist, lPan);
}

void IDialogBox::AddEventList(char* pTxt, char cColor, bool bDupAllow)
{
	m_pGame->AddEventList(pTxt, cColor, bDupAllow);
}

bool IDialogBox::bSendCommand(uint32_t dwMsgID, uint16_t wCommand, char cDir, int iV1, int iV2, int iV3, char* pString, int iV4)
{
	return m_pGame->bSendCommand(dwMsgID, wCommand, cDir, iV1, iV2, iV3, pString, iV4);
}

void IDialogBox::SetDefaultRect(short sX, short sY, short sSizeX, short sSizeY)
{
	auto& info = Info();
	info.sX = sX;
	info.sY = sY;
	info.sSizeX = sSizeX;
	info.sSizeY = sSizeY;
}

void IDialogBox::EnableDialogBox(DialogBoxId::Type id, int cType, int sV1, int sV2, char* pString)
{
	m_pGame->m_dialogBoxManager.EnableDialogBox(id, cType, sV1, sV2, pString);
}

void IDialogBox::DisableDialogBox(DialogBoxId::Type id)
{
	m_pGame->m_dialogBoxManager.DisableDialogBox(id);
}

void IDialogBox::DisableThisDialog()
{
	m_pGame->m_dialogBoxManager.DisableDialogBox(m_id);
}
