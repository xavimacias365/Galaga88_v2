#ifndef RESOURCES_H
#define RESOURCES_H
#pragma once

#include "raylib.h"

	// Textures
extern Texture2D main_menu_background;
extern Texture2D main_menu_logo0;
extern Texture2D main_menu_logo1;
extern Texture2D main_menu_logo;
extern Texture2D main_menu_logo2;
extern Texture2D main_menu_namco;
extern Texture2D main_menu_enemy;
extern Texture2D main_menu_logo_lightning;

extern Texture2D credits_screen;

extern Texture2D launch_background;
extern Texture2D launch_sequence_enemy_sprite;

extern Texture2D level1_background;
extern Texture2D level2_background;
extern Texture2D level3_background;
extern Texture2D player_sprite;
extern Texture2D shot_sprite;
extern Texture2D zakko_shot_sprite;
extern Texture2D stage_indicator;
extern Texture2D zakko_sprite;
extern Texture2D goei_sprite;
extern Texture2D don1_sprite;
extern Texture2D don2_sprite;
extern Texture2D don3_sprite;
extern Texture2D don4_sprite;
extern Texture2D baby_don1_sprite;
extern Texture2D baby_don2_sprite;
extern Texture2D baby_don3_sprite;
extern Texture2D baby_don4_sprite;
extern Texture2D mini_boss_galaga_sprite;
extern Texture2D mini_boss_galaga_damaged_sprite;
extern Texture2D enemy_explosion;

extern Texture2D win_screen;


	// Font
extern Font customFont;


	// Sounds
extern Sound main_menu_lightning;
extern Sound main_menu_enemy_fly;
extern Sound main_menu_start;

extern Sound select;
extern Sound launch_sequence_enemy;

extern Sound fighter_shot;
extern Sound fighter_killed;
extern Sound enemy_shot;
extern Sound enemy_killed;


	// Music
extern Music main_menu_music;
extern Music game_over_music;
extern Music victory_music;


#endif // RESOURCES_H
