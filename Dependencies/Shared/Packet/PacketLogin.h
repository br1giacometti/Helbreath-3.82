#pragma once

#include "PacketCommon.h"
#include "PacketHeaders.h"

#include <cstdint>

namespace hb {
namespace net {
	HB_PACK_BEGIN
	struct HB_PACKED LoginRequest
	{
		PacketHeader header;
		char account_name[10];
		char password[10];
		char world_name[30];
	};
	HB_PACK_END

	HB_PACK_BEGIN
	struct HB_PACKED CreateCharacterRequest
	{
		PacketHeader header;
		char character_name[10];
		char account_name[10];
		char password[10];
		char world_name[30];
		std::uint8_t gender;
		std::uint8_t skin;
		std::uint8_t hairstyle;
		std::uint8_t haircolor;
		std::uint8_t underware;
		std::uint8_t str;
		std::uint8_t vit;
		std::uint8_t dex;
		std::uint8_t intl;
		std::uint8_t mag;
		std::uint8_t chr;
	};
	HB_PACK_END

	HB_PACK_BEGIN
	struct HB_PACKED DeleteCharacterRequest
	{
		PacketHeader header;
		char character_name[10];
		char account_name[10];
		char password[10];
		char world_name[30];
	};
	HB_PACK_END

	HB_PACK_BEGIN
	struct HB_PACKED ChangePasswordRequest
	{
		PacketHeader header;
		char account_name[10];
		char password[10];
		char new_password[10];
		char new_password_confirm[10];
	};
	HB_PACK_END

	HB_PACK_BEGIN
	struct HB_PACKED CreateAccountRequest
	{
		PacketHeader header;
		char account_name[10];
		char password[10];
		char email[50];
		char quiz[45];
		char answer[25];
	};
	HB_PACK_END

	HB_PACK_BEGIN
	struct HB_PACKED CreateAccountRequestFull
	{
		PacketHeader header;
		char account_name[10];
		char password[10];
		char email[50];
		char gender[10];
		char age[10];
		char padding1[4];
		char padding2[2];
		char padding3[2];
		char country[17];
		char ssn[28];
		char quiz[45];
		char answer[20];
		char cmd_line[50];
	};
	HB_PACK_END

	HB_PACK_BEGIN
	struct HB_PACKED EnterGameRequest
	{
		PacketHeader header;
		char character_name[10];
		char map_name[10];
		char account_name[10];
		char password[10];
		std::int32_t level;
		char world_name[10];
		char cmd_line[120];
	};
	HB_PACK_END

	HB_PACK_BEGIN
	struct HB_PACKED EnterGameRequestFull
	{
		PacketHeader header;
		char character_name[10];
		char map_name[10];
		char account_name[10];
		char password[10];
		std::int32_t level;
		char world_name[30];
		char cmd_line[120];
	};
	HB_PACK_END
}
}
