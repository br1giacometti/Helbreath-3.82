#pragma once

/****************************************************************
*		 This client was writen by Diuuude & Snoopy81.			*
*					Based on Cleroth work.						*
*																*
*			V3.51 compatibility by Cleroth						*
*			V3.51 dialogs by Diuuude							*
*			Effects, mobs, Apocalypse, Heldenian				*
*			& finalizing by Snoopy81							*
*			V3.82 Crafting & Angels by Snoopy81					*
*****************************************************************/

/****************************************************************
*	Find here all compilation options							*
*	I removed useless ones and tryed to add some explanations	*
*	( Snoopy81 06/2005 )										*
*****************************************************************/

/*** Put here global data for your server ***/
#include "Version.h"

#define NAME_WORLDNAME1			"WS1" // Name for default (1st) server
#define DEF_SERVER_IP			"127.0.0.1"
#define DEF_SERVER_PORT			2500
#define DEF_GSERVER_PORT		9907

#define LOGICAL_WIDTH			640
#define LOGICAL_HEIGHT			480
// Window size is now in settings.json (ConfigManager)
#define BASE_SCREEN_WIDTH		LOGICAL_WIDTH
#define BASE_SCREEN_HEIGHT		LOGICAL_HEIGHT
#define SCREENX					((LOGICAL_WIDTH - BASE_SCREEN_WIDTH) / 2)
#define SCREENY					((LOGICAL_HEIGHT - BASE_SCREEN_HEIGHT) / 2)
#define LOGICAL_MAX_X			(LOGICAL_WIDTH - 1)
#define LOGICAL_MAX_Y			(LOGICAL_HEIGHT - 1)
#define VIEW_TILE_WIDTH			(LOGICAL_WIDTH / 32)
#define VIEW_TILE_HEIGHT		(LOGICAL_HEIGHT / 32)
#define VIEW_CENTER_TILE_X		(VIEW_TILE_WIDTH / 2)
#define VIEW_CENTER_TILE_Y		(VIEW_TILE_HEIGHT / 2)
#define ICON_PANEL_WIDTH		LOGICAL_WIDTH
#define ICON_PANEL_HEIGHT		53
#define ICON_PANEL_OFFSET_X		((LOGICAL_WIDTH - ICON_PANEL_WIDTH) / 2)

#define CHAT_INPUT_X			10
#define CHAT_INPUT_Y			(LOGICAL_HEIGHT - ICON_PANEL_HEIGHT - 16)
#define EVENTLIST2_BASE_Y		(CHAT_INPUT_Y - (6 * 15) - 4)
#define LEVELUP_TEXT_X			(LOGICAL_WIDTH - 90)
#define LEVELUP_TEXT_Y			(EVENTLIST2_BASE_Y + (5 * 15))


/*** Some more compilation options ***/
#define DEF_MAKE_ACCOUNT		// Enable acc creation. Missing sprites, fixed!
#define DEF_USE_LOGIN
#define DEF_COMMA_GOLD			// Allows to show comma nbe as original HB (ie: 1,200,000)

#define DEF_WINDOWED_MODE		// Shows HB in a windowed mode (for debug purpose only, sprite will bug....)
