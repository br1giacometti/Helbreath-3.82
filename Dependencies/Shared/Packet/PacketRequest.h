#pragma once

#include "PacketHeaders.h"

#include <cstdint>

namespace hb {
namespace net {
	HB_PACK_BEGIN
	struct HB_PACKED PacketRequestHeaderOnly {
		PacketHeader header;
	};

	struct HB_PACKED PacketRequestAngel {
		PacketHeader header;
		char name[20];
		int32_t angel_id;
	};

	struct HB_PACKED PacketRequestHeldenianScroll {
		PacketHeader header;
		char name[20];
		uint16_t item_id;
	};

	struct HB_PACKED PacketRequestName20 {
		PacketHeader header;
		char name[20];
	};

	struct HB_PACKED PacketRequestTeleportId {
		PacketHeader header;
		int32_t teleport_id;
	};

	struct HB_PACKED PacketRequestPanning {
		PacketHeader header;
		uint8_t dir;
	};

	struct HB_PACKED PacketRequestSetItemPos {
		PacketHeader header;
		uint8_t dir;
		int16_t x;
		int16_t y;
	};

	struct HB_PACKED PacketCommandCheckConnection {
		PacketHeader header;
		uint32_t time_ms;
	};

	struct HB_PACKED PacketRequestInitPlayer {
		PacketHeader header;
		char player[10];
		char account[10];
		char password[10];
		uint8_t is_observer;
		char server[20];
		uint8_t padding;
	};

	struct HB_PACKED PacketRequestLevelUpSettings {
		PacketHeader header;
		uint16_t str;
		uint16_t vit;
		uint16_t dex;
		uint16_t intel;
		uint16_t mag;
		uint16_t chr;
	};

	struct HB_PACKED PacketRequestSellItemListEntry {
		uint8_t index;
		int32_t amount;
	};

	struct HB_PACKED PacketRequestSellItemList {
		PacketHeader header;
		PacketRequestSellItemListEntry entries[12];
		uint8_t padding[4];
	};

	struct HB_PACKED PacketCommandChatMsgHeader {
		PacketHeader header;
		int16_t x;
		int16_t y;
		char name[10];
		uint8_t chat_type;
	};

	struct HB_PACKED PacketCommandCommonBase {
		PacketHeader header;
		int16_t x;
		int16_t y;
		uint8_t dir;
	};

	struct HB_PACKED PacketCommandCommonWithTime {
		PacketCommandCommonBase base;
		int32_t v1;
		int32_t v2;
		int32_t v3;
		uint32_t time_ms;
	};

	struct HB_PACKED PacketCommandCommonWithString {
		PacketCommandCommonBase base;
		int32_t v1;
		int32_t v2;
		int32_t v3;
		char text[30];
		int32_t v4;
	};

	struct HB_PACKED PacketCommandCommonItems {
		PacketCommandCommonBase base;
		uint8_t item_ids[6];
		uint8_t padding;
	};

	struct HB_PACKED PacketCommandCommonBuild {
		PacketCommandCommonBase base;
		char name[20];
		uint8_t item_ids[6];
	};

	struct HB_PACKED PacketRequestGuildAction {
		PacketHeader header;
		char player[10];
		char account[10];
		char password[10];
		char guild[20];
	};

	struct HB_PACKED PacketRequestRetrieveItem {
		PacketHeader header;
		uint8_t item_slot;
	};

	struct HB_PACKED PacketRequestNoticement {
		PacketHeader header;
		int32_t value;
	};

	struct HB_PACKED PacketRequestFightzoneReserve {
		PacketHeader header;
		int32_t fightzone;
	};

	struct HB_PACKED PacketRequestStateChange {
		PacketHeader header;
		uint8_t change1;
		uint8_t change2;
		uint8_t change3;
	};

	struct HB_PACKED PacketCommandMotionBase {
		PacketHeader header;
		int16_t x;
		int16_t y;
		uint8_t dir;
		int16_t dx;
		int16_t dy;
		int16_t type;
	};

	struct HB_PACKED PacketCommandMotionSimple {
		PacketCommandMotionBase base;
		uint32_t time_ms;
	};

	struct HB_PACKED PacketCommandMotionAttack {
		PacketCommandMotionBase base;
		uint16_t target_id;
		uint32_t time_ms;
	};
	HB_PACK_END
}
}
