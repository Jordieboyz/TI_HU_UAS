/*
 * Definitions.hpp
 *
 *  Created on: 11 Jan 2021
 *      Author: lucasw00079
 */

#ifndef SRC_DEFINITIONS_HPP_
#define SRC_DEFINITIONS_HPP_

/****************************
* WINDOW SCREEN SETTINGS
****************************/
#define PI						3.141592653f
#define WINDOW_LENGTH			1280
#define WINDOW_HEIGHT			720
#define FPS_SECOND				60.0f
#define MOVEMENT_SPEED			15.0f

#define TIME_SCALE_PAR_INC_SEC		16.0f
#define TIME_SCALE_PAR_INC_MOVE_SEC (10.0f * TIME_SCALE_PAR_INC_SEC)
#define TIME_SCALE_PAR_INC_SHOOT	8.0f
#define TIME_SCALE_INC_UPDATE		(TIME_SCALE_PAR_INC_SEC / FPS_SECOND)

/****************************
* LEVEL SETTINGS/TEXTURES
****************************/
#define BRICK_TEXTURE 					"res/level-textures/texture_brick.png"
#define DOOR_TEXTURE					"res/level-textures/door.png"
#define GLASS_TEXTURE					"res/level-textures/glass_panel.png"
#define GLASS_TEXTURE_BROKEN			"res/level-textures/glass_panel_broken.png"
#define GLASS_TEXTURE_ROTATED			"res/level-textures/glass_panel.png"
#define GLASS_TEXTURE_BROKEN_ROTATED	"res/level-textures/glass_panel_broken.png"

#define LEVEL_ONE_BACKGROUND			"res/level-textures/back_level_1.png"
#define LEVEL_TWO_BACKGROUND			"res/level-textures/back_level_2.png"
#define LEVEL_THREE_BACKGROUND			"res/level-textures/back_level_3.png"

#define LEVEL_ONE_BMP					"res/level-textures/level_1.bmp"
#define LEVEL_TWO_BMP					"res/level-textures/level_2.bmp"
#define LEVEL_THREE_BMP					"res/level-textures/level_3.bmp"

/****************************
* STATIC STATE SETTINGS
****************************/

#define TRANSPARENT_TEXTURE 			"res/1280x720-transparent.png"

#define LOGO_TEXTURE					"res/menu-states/logo_game.png"
#define PAUSE_MENU_BACKGROUND_TEXTURE	"res/menu-states/back_pause.png"
#define MAIN_MENU_BACKGROUND_TEXTURE	"res/menu-states/back_main.png"
#define WIN_MENU_BAKCGROUND_TEXTURE		"res/menu-states/back_win.png"
#define GAME_OVER_BACKGROUND_TEXTURE	"res/menu-states/back_gameover.png"
#define COMPLETED_BACKGROUND_TEXTURE	"res/menu-states/back_completed.png"

#define LEVEL_1_TEXTURE					"res/menu-states/level_1_normal.png"
#define LEVEL_1_TEXTURE_HOVER			"res/menu-states/level_1_hover.png"
#define LEVEL_2_TEXTURE					"res/menu-states/level_2_normal.png"
#define LEVEL_2_TEXTURE_HOVER			"res/menu-states/level_2_hover.png"
#define LEVEL_3_TEXTURE					"res/menu-states/level_3_normal.png"
#define LEVEL_3_TEXTURE_HOVER			"res/menu-states/level_3_hover.png"

#define TEXT_MAIN_MENU_TEXTURE			"res/menu-states/text_main_menu_normal.png"
#define TEXT_MAIN_MENU_TEXTURE_HOVER	"res/menu-states/text_main_menu_hover.png"
#define TEXT_RESTART_TEXTURE			"res/menu-states/text_restart_normal.png"
#define TEXT_RESTART_TEXTURE_HOVER		"res/menu-states/text_restart_hover.png"
#define LOGO_GAME_OVER_TEXTURE			"res/menu-states/logo_gameover.png"

#define TEXT_BUTTON_FONT				"res/Fonts/super-legend-boy.otf"
#define TEXT_SCORE_FONT					"res/Fonts/Arial.ttf"

/****************************
* ANIMATED SPRITES CONFIG
****************************/
#define HOTLINE_MIAMI_SPRITE_N_IMG_X	8
#define HOTLINE_MIAMI_SPRITE_N_IMG_Y	1
#define HOTLINE_MIAMI_SPRITE_N_IMG		(HOTLINE_MIAMI_SPRITE_N_IMG_X * \
											HOTLINE_MIAMI_SPRITE_N_IMG_Y)

#define ANIMATIONS_WALK_M16				"res/animation-strip/sprPWalkM16_strip8.png"
#define ANIMATIONS_ATTACK_M16			"res/animation-strip/sprPAttackM16_strip2.png"

#define ANIMATIONS_WALK_MP5				"res/animation-strip/sprPWalkMP5_strip8.png"
#define ANIMATIONS_ATTACK_MP5			"res/animation-strip/sprPAttackMP5_strip3.png"

#define ANIMATIONS_WALK_SHOTGUN			"res/animation-strip/sprPWalkSHOTGUN_strip8.png"
#define ANIMATIONS_ATTACK_SHOTGUN		"res/animation-strip/sprPAttackSHOTGUN_strip12.png"

#define ANIMATIONS_PLAYER_DEAD			"res/sprPBackCar.png"

/****************************
* WALL_GENERATOR
*****************************/
#define WALL_GENERATOR_RGB_MASK			0xFF00FFFF
#define WALL_GENERATOR_WALL_COL			0xFFFFFFFF
#define WALL_GENERATOR_COL_TO_SEARCH	0xFF00FA00 //0x00FF00FA Lucas
#define WALL_GENERATOR_COL_BARRIER		0x00F0FF00
#define WALL_GENERATOR_COL_GLASS 		0x00FF1400

#define NPC_FOV							130.0f
#define NPC_H_FOV						(NPC_FOV / 2.0f)
#define NPC_MOVEMENT_SPEED				9.0f

/****************************
* WEAPONS
*****************************/
#define MP5_TEXTURE						"res/animation-strip/weapon_MP5.png"
#define M16_TEXTURE						"res/animation-strip/weapon_M16.png"
#define SHOTGUN_TEXTURE					"res/animation-strip/weapon_SHOTGUN.png"

#define BULLET_SIZE						10.f

/****************************
* DOOR
*****************************/
#define DOOR_ROTATION_SPEED_DEGREES		50.f
#define DOOR_MAX_ROTATION_DEGREES		90.f

/****************************
* SOUND EFFECT SETTINGS
*****************************/
#define SHOOT_SOUND_EFFECT 				"res/sounds/shotgun.wav"
#define MENU_SELECT_EFFECT 				"res/sounds/menu_sound.wav"
#define BACKGROUND_MUSIC 				"res/sounds/background_music.wav"
#define PAIN_SOUND_EFFECT 				"res/sounds/pain.wav"
#define VOICE_LINE_1 					"res/sounds/whos_the_man.wav"
#define VOICE_LINE_2 					"res/sounds/i_am_dangerous.wav"
#define VOICE_LINE_3 					"res/sounds/i_am_on_fire.wav"
#define VOICE_LINE_4 					"res/sounds/thats_the_way_this_is_done.wav"
#define VOICE_LINE_5 					"res/sounds/they_never_knew_what_hit_them.wav"
#define VOICE_LINE_ENEMY_1 				"res/sounds/enemy/come_to_papa.wav"
#define VOICE_LINE_ENEMY_2 				"res/sounds/enemy/attacking.wav"
#define VOICE_LINE_ENEMY_3 				"res/sounds/enemy/what_are_you_doing.wav"
#define VOICE_LINE_ENEMY_4 				"res/sounds/enemy/i_heard_something_over_there.wav"
#define VOICE_LINE_ENEMY_5 				"res/sounds/enemy/stop_it.wav"
#define MP5_SOUND 						"res/sounds/mp5.wav"
#define M16_SOUND 						"res/sounds/m16.wav"
#define SHOTGUN_SOUND 					"res/sounds/shotgun.wav"

#define TIME_SCALE_PAR_INC_SEC			16.0f
#define TIME_SCALE_PAR_INC_MOVE_SEC 	(10.0f * TIME_SCALE_PAR_INC_SEC)
#define TIME_SCALE_PAR_INC_SHOOT		8.0f
#define TIME_SCALE_INC_UPDATE			(TIME_SCALE_PAR_INC_SEC / FPS_SECOND)


/****************************
* NETWORK SETTINGS
*****************************/
#define SERVER_IP 						"127.0.0.1"
#define SERVER_PORT_STR					"2046"
#define SERVER_PORT_DEC					2046

#endif /* SRC_DEFINITIONS_HPP_ */
