// EffectManager.h: Visual effects system manager
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include <cstdint>

// Forward declarations only - avoid including heavy headers
class CGame;
class CSprite;
class CEffect;

// Effect constants
#ifndef DEF_MAXEFFECTS
#define DEF_MAXEFFECTS 300
#endif

#ifndef DEF_MAXEFFECTSPR
#define DEF_MAXEFFECTSPR 300
#endif

class EffectManager
{
public:
	explicit EffectManager(CGame* pGame);
	~EffectManager();

	// Initialization
	void SetEffectSprites(CSprite** pEffectSpr);

	// Main API
	void AddEffect(short sType, int sX, int sY, int dX, int dY, char cStartFrame, int iV1 = 1);
	void Update();   // Updates effect frames, removes finished effects
	
	// Render methods (separate for correct draw order: lights before objects, effects after)
	void DrawEffects();     // Draw particle effects (call after DrawObjects)
	void DrawEffectLights(); // Draw lighting effects (call before DrawObjects)

	// Cleanup
	void ClearAllEffects();

private:
	// Private implementation methods (defined in separate .cpp files)
	void AddEffectImpl(short sType, int sX, int sY, int dX, int dY, char cStartFrame, int iV1 = 0);
	void UpdateEffectsImpl();
	void DrawEffectsImpl();
	void DrawEffectLightsImpl();

	CGame* m_pGame;
	CEffect* m_pEffectList[DEF_MAXEFFECTS];
	CSprite** m_pEffectSpr;  // Reference, not owned
};
