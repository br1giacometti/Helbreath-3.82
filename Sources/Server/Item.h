// Item.h: interface for the CItem class.
//
// This file now includes the unified shared Item implementation.
// See Dependencies/Shared/Item/ for the actual definitions.
//
//////////////////////////////////////////////////////////////////////

#pragma once

// MODERNIZED: Prevent old winsock.h from loading (must be before windows.h)
#define _WINSOCKAPI_

#include <windows.h>
#include "CommonTypes.h"

// Include unified shared Item system
#include "Item/SharedItem.h"
