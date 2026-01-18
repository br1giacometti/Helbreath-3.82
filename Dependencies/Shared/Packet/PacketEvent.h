#pragma once

#include "PacketHeaders.h"

#include <cstdint>

namespace hb {
namespace net {
	HB_PACK_BEGIN
	struct HB_PACKED PacketEventCommonBase {
		PacketHeader header;
		std::int16_t x;
		std::int16_t y;
		std::int16_t v1;
		std::int16_t v2;
		std::int16_t v3;
	};

	struct HB_PACKED PacketEventCommonItem {
		PacketEventCommonBase base;
		std::uint32_t v4;
	};

	struct HB_PACKED PacketEventCommonMagic {
		PacketEventCommonBase base;
		std::int16_t v4;
	};

	struct HB_PACKED PacketEventLogBase {
		PacketHeader header;
		std::uint16_t object_id;
		std::int16_t x;
		std::int16_t y;
		std::int16_t type;
		std::uint8_t dir;
	};

	struct HB_PACKED PacketEventLogPlayer {
		PacketEventLogBase base;
		char name[10];
		std::int16_t appr1;
		std::int16_t appr2;
		std::int16_t appr3;
		std::int16_t appr4;
		std::int32_t appr_color;
		std::int32_t status;
	};

	struct HB_PACKED PacketEventLogNpc {
		PacketEventLogBase base;
		char name[5];
		std::int16_t appr2;
		std::int32_t status;
	};

	struct HB_PACKED PacketEventMotionPlayer {
		PacketHeader header;
		std::uint16_t object_id;
		std::int16_t x;
		std::int16_t y;
		std::int16_t type;
		std::uint8_t dir;
		char name[10];
		std::int16_t appr1;
		std::int16_t appr2;
		std::int16_t appr3;
		std::int16_t appr4;
		std::int32_t appr_color;
		std::int32_t status;
		std::uint8_t loc;
		std::uint8_t reserved;
	};

	struct HB_PACKED PacketEventMotionBaseId {
		PacketHeader header;
		std::uint16_t object_id;
	};

	struct HB_PACKED PacketEventMotionNpc {
		PacketHeader header;
		std::uint16_t object_id;
		std::int16_t x;
		std::int16_t y;
		std::int16_t type;
		std::uint8_t dir;
		char name[5];
		std::int16_t appr2;
		std::int32_t status;
		std::uint8_t loc;
	};

	struct HB_PACKED PacketEventMotionMove {
		PacketHeader header;
		std::uint16_t object_id;
		std::uint8_t dir;
		std::uint8_t v1;
		std::uint8_t v2;
		std::int16_t x;
		std::int16_t y;
	};

	struct HB_PACKED PacketEventMotionShort {
		PacketHeader header;
		std::uint16_t object_id;
		std::uint8_t dir;
		std::uint8_t v1;
		std::uint8_t v2;
	};

	struct HB_PACKED PacketEventMotionMagic {
		PacketHeader header;
		std::uint16_t object_id;
		std::uint8_t dir;
		std::int8_t v1;
		std::int8_t v2;
	};

	struct HB_PACKED PacketEventMotionAttack {
		PacketHeader header;
		std::uint16_t object_id;
		std::uint8_t dir;
		std::int8_t v1;
		std::int8_t v2;
		std::int16_t v3;
	};

	struct HB_PACKED PacketEventMotionDirOnly {
		PacketHeader header;
		std::uint16_t object_id;
		std::uint8_t dir;
	};

	struct HB_PACKED PacketEventNearTypeBShort {
		PacketHeader header;
		std::int16_t x;
		std::int16_t y;
		std::int16_t v1;
		std::int16_t v2;
		std::int16_t v3;
		std::int16_t v4;
	};

	struct HB_PACKED PacketEventNearTypeBDword {
		PacketHeader header;
		std::int16_t x;
		std::int16_t y;
		std::int16_t v1;
		std::int16_t v2;
		std::int16_t v3;
		std::uint32_t v4;
	};
	HB_PACK_END
}
}
