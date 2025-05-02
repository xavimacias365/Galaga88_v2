
#include "resources.h"

	// Textures
Texture2D main_menu_background;
Texture2D main_menu_logo;
Texture2D main_menu_namco;
Texture2D main_menu_enemy;

Texture2D credits_screen;

Texture2D launch_background;

Texture2D level1_background;
Texture2D player;
Texture2D shot;
Texture2D stage_indicator;
//Texture2D zako_enemy_sprite;
Texture2D zako_frame1;
Texture2D zako_frame2;
Texture2D enemy_explosion;

Texture2D win_screen;


	// Fonts
Font customFont;


	// Sounds
Sound fighter_shot;
Sound fighter_killed;
Sound enemy_shot;
Sound enemy_killed;


	// Music
Music main_menu_music;
Music game_over_music;
Music victory_music;



void LoadGame() {

// Load Textures 
	main_menu_background = LoadTexture("resources/Textures/level-background/menu.png");
	main_menu_logo = LoadTexture("resources/Textures/UI/logo.png");
	main_menu_namco = LoadTexture("resources/Textures/texts/logo_namco.png");
	main_menu_enemy = LoadTexture("resources/Textures/UI/enemy_title_screen.png");

	credits_screen = LoadTexture("resources/Textures/UI/credits.png");

	launch_background = LoadTexture("resources/Textures/level-background/launch.png");

	level1_background = LoadTexture("resources/Textures/level-background/stage1.png");
	player = LoadTexture("resources/Textures/entities/player/fighter.png");
	shot = LoadTexture("resources/Textures/entities/enemies/projectiles/disparoplayer.png");
	stage_indicator = LoadTexture("resources/Textures/items/stage_indicator.png");
//	zako_enemy_sprite = LoadTexture("resources/Textures/entities/enemies/zako_dim1.png");
	zako_frame1 = LoadTexture("resources/Textures/entities/enemies/zako_dim1_1.png");
	zako_frame2 = LoadTexture("resources/Textures/entities/enemies/zako_dim1_2.png");
	enemy_explosion = LoadTexture("resources/Textures/entities/player/explosion.png");

	win_screen = LoadTexture("resources/Textures/UI/win_condition.png");


// Load Font
	customFont = LoadFont("resources/Textures/texts/font/font.png");
	customFont = LoadFontEx("resources/Textures/texts/font/font.png", 8, 0, 42);
	SetTextLineSpacing(16);


// Load Sounds
	fighter_shot = LoadSound("resources/audio/sfx/fighter_shoot.wav");
	fighter_killed = LoadSound("resources/audio/sfx/fighter_destroyed.wav");
	enemy_shot = LoadSound("resources/audio/sfx/galaga_shot.wav");
	enemy_killed = LoadSound("resources/audio/sfx/galaga_destroyed.wav");


// Load Music
	main_menu_music = LoadMusicStream("resources/audio/music/02_game_start.wav");
	PlayMusicStream(main_menu_music);
	game_over_music = LoadMusicStream("resources/audio/music/13_game_over.wav");
	victory_music = LoadMusicStream("resources/audio/music/12_ending.wav");

}

void UnloadGame() {

	UnloadTexture(main_menu_background);
	UnloadTexture(main_menu_logo);
	UnloadTexture(main_menu_namco);
	UnloadTexture(main_menu_enemy);

	UnloadTexture(credits_screen);

	UnloadTexture(launch_background);

	UnloadTexture(level1_background);
	UnloadTexture(player);
	UnloadTexture(shot);
	UnloadTexture(stage_indicator);
	//	UnloadTexture(zako_enemy_sprite);
	UnloadTexture(zako_frame1);
	UnloadTexture(zako_frame2);
	UnloadTexture(enemy_explosion);

	UnloadTexture(win_screen);


	UnloadFont(customFont);


	UnloadSound(fighter_shot);
	UnloadSound(fighter_killed);
	UnloadSound(enemy_shot);
	UnloadSound(enemy_killed);


	UnloadMusicStream(main_menu_music);
	UnloadMusicStream(game_over_music);
	UnloadMusicStream(victory_music);

}
