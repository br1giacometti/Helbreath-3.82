#pragma once

#include "PacketCommon.h"
#include "PacketHeaders.h"
#include <cstdint>

namespace hb {
namespace net {

//------------------------------------------------------------------------
// Shop System Packets
//
// Flow:
// 1. Client opens shop NPC → sends PacketShopRequest with NPC type
// 2. Server looks up shop for NPC type → sends PacketShopResponse with item IDs
// 3. Client populates shop UI from m_pItemConfigList using received IDs
// 4. Client purchases item → sends item ID (not name) to server
//------------------------------------------------------------------------

// Message IDs for shop system
constexpr uint32_t CYCLIC_MSGID_REQUEST_SHOP_CONTENTS  = 0x0FA31500;
constexpr uint32_t CYCLIC_MSGID_RESPONSE_SHOP_CONTENTS = 0x0FA31501;

//------------------------------------------------------------------------
// Shop Request Packet (Client → Server)
// Sent when player opens a shop NPC
//------------------------------------------------------------------------

HB_PACK_BEGIN
struct HB_PACKED PacketShopRequest
{
	PacketHeader header;       // msg_id = MSGID_REQUEST_SHOP_CONTENTS
	int16_t      npcType;      // NPC type (15=ShopKeeper, 24=Blacksmith, etc.)
};
HB_PACK_END

//------------------------------------------------------------------------
// Shop Response Header (Server → Client)
// Followed by array of int16_t item IDs
//------------------------------------------------------------------------

HB_PACK_BEGIN
struct HB_PACKED PacketShopResponseHeader
{
	PacketHeader header;       // msg_id = MSGID_RESPONSE_SHOP_CONTENTS
	int16_t      npcType;      // Echo back the NPC type
	int16_t      shopId;       // Shop ID (for reference)
	uint16_t     itemCount;    // Number of item IDs following this header
	// Followed by: int16_t itemIds[itemCount]
};
HB_PACK_END

//------------------------------------------------------------------------
// Purchase Request - uses existing MSGID_COMMAND_COMMON with DEF_COMMONTYPE_REQ_PURCHASEITEM
// but now sends item ID instead of item name
//
// Parameters:
//   iV1 = quantity
//   iV2 = item ID (NEW - primary lookup method)
//   pString = item name (deprecated, kept for logging only)
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// Helper: Maximum items per shop
//------------------------------------------------------------------------

constexpr uint16_t MAX_SHOP_ITEMS = 200;

} // namespace net
} // namespace hb

// Legacy macro definitions for compatibility
#define MSGID_REQUEST_SHOP_CONTENTS    hb::net::CYCLIC_MSGID_REQUEST_SHOP_CONTENTS
#define MSGID_RESPONSE_SHOP_CONTENTS   hb::net::CYCLIC_MSGID_RESPONSE_SHOP_CONTENTS
