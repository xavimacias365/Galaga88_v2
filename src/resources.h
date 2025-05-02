#ifndef RESOURCES_H
#define RESOURCES_H
#pragma once

#include "raylib.h"

	// Textures
extern Texture2D main_menu_background;
extern Texture2D main_menu_logo;
extern Texture2D main_menu_namco;
extern Texture2D main_menu_enemy;

extern Texture2D credits_screen;

extern Texture2D launch_background;

extern Texture2D level1_background;
extern Texture2D player;
extern Texture2D shot;
extern Texture2D stage_indicator;
//extern Texture2D zako_enemy_sprite;
extern Texture2D zako_frame1;
extern Texture2D zako_frame2;
extern Texture2D enemy_explosion;

extern Texture2D win_screen;


	// Font
extern Font customFont;


	// Sounds
extern Sound fighter_shot;
extern Sound fighter_killed;
extern Sound enemy_shot;
extern Sound enemy_killed;


	// Music
extern Music main_menu_music;
extern Music game_over_music;
extern Music victory_music;


#endif // RESOURCES_H
