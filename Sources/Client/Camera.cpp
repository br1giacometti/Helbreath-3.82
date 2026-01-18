#include "Camera.h"
#include <cstdlib>
#include <cmath>

Camera& Camera::Get()
{
	static Camera instance;
	return instance;
}

void Camera::Initialize()
{
	m_mode = CameraMode::FollowPlayer;
	m_attachedEntityId = 0;

	m_viewX = 0;
	m_viewY = 0;
	m_exactX = 0.0f;
	m_exactY = 0.0f;
	m_targetX = 0;
	m_targetY = 0;

	m_bSmoothFollow = false;
	m_followSpeed = 0.1f;

	// Default viewport (will be set properly by game init)
	m_viewWidth = 800;
	m_viewHeight = 600;
	m_tileWidth = 32;
	m_tileHeight = 32;
	m_viewWidthTiles = m_viewWidth / m_tileWidth + 2;
	m_viewHeightTiles = m_viewHeight / m_tileHeight + 2;

	m_bShaking = false;
	m_shakeDegree = 0;
	m_shakeDuration = 0.0f;
	m_shakeTimer = 0.0f;
	m_shakeOffsetX = 0;
	m_shakeOffsetY = 0;

	m_worldMinX = 0;
	m_worldMinY = 0;
	m_worldMaxX = 0;
	m_worldMaxY = 0;
	m_bClampToBounds = false;
}

void Camera::Shutdown()
{
	// Nothing to clean up
}

void Camera::SetViewportSize(int width, int height)
{
	m_viewWidth = width;
	m_viewHeight = height;
	m_viewWidthTiles = width / m_tileWidth + 2;
	m_viewHeightTiles = height / m_tileHeight + 2;
}

void Camera::SetTileSize(int tileWidth, int tileHeight)
{
	m_tileWidth = tileWidth;
	m_tileHeight = tileHeight;
	m_viewWidthTiles = m_viewWidth / m_tileWidth + 2;
	m_viewHeightTiles = m_viewHeight / m_tileHeight + 2;
}

void Camera::AttachToPlayer()
{
	m_mode = CameraMode::FollowPlayer;
	m_attachedEntityId = 0;
}

void Camera::AttachToEntity(uint32_t entityId)
{
	m_mode = CameraMode::FollowEntity;
	m_attachedEntityId = entityId;
}

void Camera::Detach()
{
	m_mode = CameraMode::FreeCamera;
}

void Camera::SetFixedPosition(int worldX, int worldY)
{
	m_mode = CameraMode::Fixed;
	m_viewX = worldX - m_viewWidthTiles / 2;
	m_viewY = worldY - m_viewHeightTiles / 2;
	m_exactX = static_cast<float>(m_viewX);
	m_exactY = static_cast<float>(m_viewY);
	ClampToBounds();
}

int Camera::GetViewX() const
{
	return m_viewX + m_shakeOffsetX;
}

int Camera::GetViewY() const
{
	return m_viewY + m_shakeOffsetY;
}

int Camera::GetCenterX() const
{
	return m_viewX + m_viewWidthTiles / 2;
}

int Camera::GetCenterY() const
{
	return m_viewY + m_viewHeightTiles / 2;
}

void Camera::GetViewPosition(int& x, int& y) const
{
	x = GetViewX();
	y = GetViewY();
}

void Camera::SetPosition(int tileX, int tileY)
{
	if (m_mode == CameraMode::FreeCamera || m_mode == CameraMode::Fixed)
	{
		m_viewX = tileX;
		m_viewY = tileY;
		m_exactX = static_cast<float>(m_viewX);
		m_exactY = static_cast<float>(m_viewY);
		ClampToBounds();
	}
}

void Camera::SetViewPosition(int tileX, int tileY)
{
	m_viewX = tileX;
	m_viewY = tileY;
	m_exactX = static_cast<float>(m_viewX);
	m_exactY = static_cast<float>(m_viewY);
	m_targetX = tileX;
	m_targetY = tileY;
}

void Camera::Move(int deltaTileX, int deltaTileY)
{
	if (m_mode == CameraMode::FreeCamera)
	{
		m_viewX += deltaTileX;
		m_viewY += deltaTileY;
		m_exactX = static_cast<float>(m_viewX);
		m_exactY = static_cast<float>(m_viewY);
		ClampToBounds();
	}
}

void Camera::SetSmoothFollow(bool enabled)
{
	m_bSmoothFollow = enabled;
}

void Camera::SetFollowSpeed(float speed)
{
	if (speed < 0.01f) speed = 0.01f;
	if (speed > 1.0f) speed = 1.0f;
	m_followSpeed = speed;
}

void Camera::Shake(int intensity, float duration)
{
	m_bShaking = true;
	m_shakeDegree = intensity;
	m_shakeDuration = duration;
	m_shakeTimer = 0.0f;
}

void Camera::StopShake()
{
	m_bShaking = false;
	m_shakeDegree = 0;
	m_shakeOffsetX = 0;
	m_shakeOffsetY = 0;
}

void Camera::WorldToScreen(int worldX, int worldY, int& screenX, int& screenY) const
{
	screenX = (worldX - GetViewX()) * m_tileWidth;
	screenY = (worldY - GetViewY()) * m_tileHeight;
}

void Camera::ScreenToWorld(int screenX, int screenY, int& worldX, int& worldY) const
{
	worldX = GetViewX() + screenX / m_tileWidth;
	worldY = GetViewY() + screenY / m_tileHeight;
}

bool Camera::IsWorldPosVisible(int worldX, int worldY) const
{
	int left, top, right, bottom;
	GetVisibleTileBounds(left, top, right, bottom);

	return worldX >= left && worldX <= right &&
		worldY >= top && worldY <= bottom;
}

bool Camera::IsTileVisible(int tileX, int tileY) const
{
	return IsWorldPosVisible(tileX, tileY);
}

void Camera::GetVisibleTileBounds(int& left, int& top, int& right, int& bottom) const
{
	left = GetViewX();
	top = GetViewY();
	right = left + m_viewWidthTiles;
	bottom = top + m_viewHeightTiles;
}

void Camera::SetWorldBounds(int minX, int minY, int maxX, int maxY)
{
	m_worldMinX = minX;
	m_worldMinY = minY;
	m_worldMaxX = maxX;
	m_worldMaxY = maxY;
	m_bClampToBounds = true;
	ClampToBounds();
}

void Camera::ClearWorldBounds()
{
	m_bClampToBounds = false;
}

void Camera::Update(double deltaTime)
{
	UpdateFollow(deltaTime);
	UpdateShake(deltaTime);
}

void Camera::UpdateFollow(double deltaTime)
{
	// For now, camera following is handled externally by CGame
	// This will be used when we fully integrate EntityManager/PlayerManager

	if (m_mode == CameraMode::FreeCamera || m_mode == CameraMode::Fixed)
	{
		return;
	}

	// If smooth follow is enabled and we have a target
	if (m_bSmoothFollow && (m_targetX != m_viewX || m_targetY != m_viewY))
	{
		float t = 1.0f - powf(1.0f - m_followSpeed, static_cast<float>(deltaTime) * 60.0f);
		m_exactX += (m_targetX - m_exactX) * t;
		m_exactY += (m_targetY - m_exactY) * t;
		m_viewX = static_cast<int>(m_exactX);
		m_viewY = static_cast<int>(m_exactY);
		ClampToBounds();
	}
}

void Camera::UpdateShake(double deltaTime)
{
	if (!m_bShaking) return;

	m_shakeTimer += static_cast<float>(deltaTime);

	if (m_shakeTimer >= m_shakeDuration)
	{
		StopShake();
		return;
	}

	// Decrease intensity over time
	float remaining = 1.0f - (m_shakeTimer / m_shakeDuration);
	int currentIntensity = static_cast<int>(m_shakeDegree * remaining);

	m_shakeOffsetX = GenerateShakeOffset(currentIntensity);
	m_shakeOffsetY = GenerateShakeOffset(currentIntensity);
}

void Camera::ClampToBounds()
{
	if (!m_bClampToBounds) return;

	if (m_viewX < m_worldMinX) m_viewX = m_worldMinX;
	if (m_viewY < m_worldMinY) m_viewY = m_worldMinY;

	int maxViewX = m_worldMaxX - m_viewWidthTiles;
	int maxViewY = m_worldMaxY - m_viewHeightTiles;

	if (m_viewX > maxViewX) m_viewX = maxViewX;
	if (m_viewY > maxViewY) m_viewY = maxViewY;

	m_exactX = static_cast<float>(m_viewX);
	m_exactY = static_cast<float>(m_viewY);
}

int Camera::GenerateShakeOffset(int intensity) const
{
	if (intensity <= 0) return 0;
	return (rand() % (intensity * 2 + 1)) - intensity;
}
