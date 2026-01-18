#pragma once

// ClientMessages.h - Client-Only Network Messages
//
// This file contains network message definitions used exclusively by the
// Helbreath Client. These messages are not used by the Server.
//
// For shared protocol messages, see Dependencies/Shared/NetMessages.h

// ============================================================================
// Client Teleport Messages
// NOTE: Some of these IDs conflict with Server teleport message IDs
// ============================================================================

// Client teleport list messages
#define MSGID_REQUEST_TELEPORT_LIST					0x0EA03202  // Conflicts with Server CITYHALLTELEPORT
#define MSGID_RESPONSE_TELEPORT_LIST				0x0EA03203
#define MSGID_REQUEST_CHARGED_TELEPORT				0x0EA03204
#define MSGID_RESPONSE_CHARGED_TELEPORT				0x0EA03205

// Heldenian teleport messages
#define MSGID_REQUEST_HELDENIAN_TP_LIST				0x0EA03206  // Conflicts with Server HELDENIANTELEPORT
#define MSGID_RESPONSE_HELDENIAN_TP_LIST			0x0EA03207
#define MSGID_REQUEST_HELDENIAN_TP					0x0EA03208

// ============================================================================
// Gateway Messages
// ============================================================================

#define MSGID_GATEWAY_CURRENTCONN					0x3B000000  // Definition only, not actively used
#define MSGID_GETMINIMUMLOADGATEWAY					0x3B1890EA
