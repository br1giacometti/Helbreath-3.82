// EffectManager.cpp: Visual effects system implementation (Orchestrator)
//
//////////////////////////////////////////////////////////////////////

#include "EffectManager.h"
#include "Game.h"
#include "Sprite.h"
#include "Effect.h"
#include "GlobalDef.h"
#include "Misc.h"
#include "ConfigManager.h"

// External global from Game.cpp
extern int _iAttackerHeight[];

EffectManager::EffectManager(CGame* pGame)
	: m_pGame(pGame)
	, m_pEffectSpr(nullptr)
{
	for (int i = 0; i < DEF_MAXEFFECTS; i++)
		m_pEffectList[i] = nullptr;
}

// Listo
EffectManager::~EffectManager()
{
	ClearAllEffects();
}

// Listo
void EffectManager::SetEffectSprites(CSprite** pEffectSpr)
{
	m_pEffectSpr = pEffectSpr;
}

// Listo
void EffectManager::ClearAllEffects()
{
	for (int i = 0; i < DEF_MAXEFFECTS; i++)
	{
		if (m_pEffectList[i] != nullptr)
		{
			delete m_pEffectList[i];
			m_pEffectList[i] = nullptr;
		}
	}
}

// Public API: Orchestrator methods that delegate to private implementation methods
// Implementation methods are defined in separate .cpp files:
//   - Effect_Add.cpp
//   - Effect_Update.cpp
//   - Effect_Draw.cpp
//   - Effect_Lights.cpp

void EffectManager::AddEffect(EffectType sType, int sX, int sY, int dX, int dY, char cStartFrame, int iV1)
{
	AddEffectImpl(sType, sX, sY, dX, dY, cStartFrame, iV1);
}

void EffectManager::Update()
{
	UpdateEffectsImpl();
}

void EffectManager::DrawEffects()
{
	DrawEffectsImpl();
}

void EffectManager::DrawEffectLights()
{
	DrawEffectLightsImpl();
}

