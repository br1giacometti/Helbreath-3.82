#pragma once

#include "PacketCommon.h"

#include <cstdint>

namespace hb {
namespace net {
	HB_PACK_BEGIN
	struct HB_PACKED PacketHeader
	{
		std::uint32_t msg_id;
		std::uint16_t msg_type;
	};
	HB_PACK_END
}
}
