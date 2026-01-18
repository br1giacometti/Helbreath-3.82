// SharedItem.h: Master include file for the unified Item system
//
// Include this single header to get access to all Item-related types:
//   - ItemEnums.h       - Type-safe enums (EquipPos, ItemType, etc.)
//   - ItemAttributes.h  - Attribute parsing and formatting
//   - Item.h            - Unified CItem class
//
// Note: Display names are now stored directly in the database.
// The server sends display names in m_cName, no client-side lookup needed.
//
//////////////////////////////////////////////////////////////////////

#pragma once

// Item enums and constants
#include "ItemEnums.h"

// Attribute parsing helpers
#include "ItemAttributes.h"

// Unified CItem class
#include "Item.h"
