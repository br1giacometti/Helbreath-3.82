#pragma once

#include <cstdint>

enum class CameraMode
{
	FollowPlayer,       // Normal gameplay
	FollowEntity,       // Spectating/cutscene
	FreeCamera,         // Debug/cinematic
	Fixed               // Static position
};

class Camera
{
public:
	static Camera& Get();

	// Lifecycle
	void Initialize();
	void Shutdown();

	// Viewport setup
	void SetViewportSize(int width, int height);
	void SetTileSize(int tileWidth, int tileHeight);

	// Following target
	void AttachToPlayer();
	void AttachToEntity(uint32_t entityId);
	void Detach();
	void SetFixedPosition(int worldX, int worldY);

	CameraMode GetMode() const { return m_mode; }
	uint32_t GetAttachedEntityId() const { return m_attachedEntityId; }
	bool IsAttachedToPlayer() const { return m_mode == CameraMode::FollowPlayer; }

	// Position (in tiles)
	int GetViewX() const;
	int GetViewY() const;
	int GetCenterX() const;
	int GetCenterY() const;
	void GetViewPosition(int& x, int& y) const;

	// For free camera mode
	void SetPosition(int tileX, int tileY);
	void Move(int deltaTileX, int deltaTileY);

	// Smooth following
	void SetSmoothFollow(bool enabled);
	void SetFollowSpeed(float speed);
	bool IsSmoothFollow() const { return m_bSmoothFollow; }

	// Screen effects
	void Shake(int intensity, float duration);
	void StopShake();
	bool IsShaking() const { return m_bShaking; }
	int GetShakeOffsetX() const { return m_shakeOffsetX; }
	int GetShakeOffsetY() const { return m_shakeOffsetY; }
	int GetShakeDegree() const { return m_shakeDegree; }

	// Coordinate conversion
	void WorldToScreen(int worldX, int worldY, int& screenX, int& screenY) const;
	void ScreenToWorld(int screenX, int screenY, int& worldX, int& worldY) const;

	// Visibility testing
	bool IsWorldPosVisible(int worldX, int worldY) const;
	bool IsTileVisible(int tileX, int tileY) const;
	void GetVisibleTileBounds(int& left, int& top, int& right, int& bottom) const;

	// Viewport dimensions
	int GetViewWidth() const { return m_viewWidth; }
	int GetViewHeight() const { return m_viewHeight; }
	int GetViewWidthTiles() const { return m_viewWidthTiles; }
	int GetViewHeightTiles() const { return m_viewHeightTiles; }
	int GetTileWidth() const { return m_tileWidth; }
	int GetTileHeight() const { return m_tileHeight; }

	// World bounds clamping
	void SetWorldBounds(int minX, int minY, int maxX, int maxY);
	void ClearWorldBounds();

	// Per-frame update
	void Update(double deltaTime);

	// Direct position setting (for external control during transition)
	void SetViewPosition(int tileX, int tileY);

private:
	Camera() = default;
	~Camera() = default;
	Camera(const Camera&) = delete;
	Camera& operator=(const Camera&) = delete;

	void UpdateFollow(double deltaTime);
	void UpdateShake(double deltaTime);
	void ClampToBounds();
	int GenerateShakeOffset(int intensity) const;

	// Mode and target
	CameraMode m_mode;
	uint32_t m_attachedEntityId;

	// Position (in tiles)
	int m_viewX, m_viewY;               // Current view position (top-left)
	float m_exactX, m_exactY;           // Smooth position
	int m_targetX, m_targetY;           // Target position for smooth follow

	// Smooth follow
	bool m_bSmoothFollow;
	float m_followSpeed;

	// Viewport
	int m_viewWidth, m_viewHeight;      // In pixels
	int m_viewWidthTiles, m_viewHeightTiles;
	int m_tileWidth, m_tileHeight;

	// Shake effect
	bool m_bShaking;
	int m_shakeDegree;
	float m_shakeDuration;
	float m_shakeTimer;
	int m_shakeOffsetX, m_shakeOffsetY;

	// World bounds (optional clamping)
	int m_worldMinX, m_worldMinY;
	int m_worldMaxX, m_worldMaxY;
	bool m_bClampToBounds;
};
