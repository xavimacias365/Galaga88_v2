
#include "resources.h"

	// Textures
Texture2D main_menu_background;
Texture2D main_menu_logo0;
Texture2D main_menu_logo1;
Texture2D main_menu_logo;
Texture2D main_menu_logo2;
Texture2D main_menu_namco;
Texture2D main_menu_enemy;
Texture2D main_menu_logo_lightning;

Texture2D credits_screen;

Texture2D launch_background;
Texture2D launch_sequence_enemy_sprite;

Texture2D level1_background;
Texture2D level3_background;
Texture2D player_sprite;
Texture2D shot_sprite;
Texture2D zakko_shot_sprite;
Texture2D stage_indicator;
Texture2D zakko_sprite;
Texture2D goei_sprite;
Texture2D don1_sprite;
Texture2D don2_sprite;
Texture2D don3_sprite;
Texture2D don4_sprite;
Texture2D baby_don1_sprite;
Texture2D baby_don2_sprite;
Texture2D baby_don3_sprite;
Texture2D baby_don4_sprite;
Texture2D mini_boss_galaga_sprite;
Texture2D mini_boss_galaga_damaged_sprite;
Texture2D enemy_explosion;

Texture2D win_screen;


	// Fonts
Font customFont;


	// Sounds
Sound main_menu_lightning;
Sound main_menu_enemy_fly;
Sound main_menu_start;

Sound select;
Sound launch_sequence_enemy;

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
	main_menu_logo0 = LoadTexture("resources/Textures/UI/original_logo.png");
	main_menu_logo1 = LoadTexture("resources/Textures/UI/logo_no_lightning.png");
	main_menu_logo = LoadTexture("resources/Textures/UI/logo.png");
	main_menu_logo2 = LoadTexture("resources/Textures/UI/logo_white_lightning.png");
	main_menu_namco = LoadTexture("resources/Textures/texts/logo_namco.png");
	main_menu_enemy = LoadTexture("resources/Textures/UI/enemy_title_screen.png");
	main_menu_logo_lightning = LoadTexture("resources/Textures/UI/logo_lightning.png");

	credits_screen = LoadTexture("resources/Textures/UI/credits.png");

	launch_background = LoadTexture("resources/Textures/level-background/launch.png");
	launch_sequence_enemy_sprite = LoadTexture("resources/Textures/UI/enemy_background.png");

	level1_background = LoadTexture("resources/Textures/level-background/stage1.png");
	level3_background = LoadTexture("resources/Textures/level-background/stage3.png");
	player_sprite = LoadTexture("resources/Textures/entities/player/fighter.png");
	shot_sprite = LoadTexture("resources/Textures/entities/enemies/projectiles/disparoplayer.png");
	zakko_shot_sprite = LoadTexture("resources/Textures/entities/enemies/projectiles/zako_dim1_shot.png");
	stage_indicator = LoadTexture("resources/Textures/items/stage_indicator.png");
	zakko_sprite = LoadTexture("resources/Textures/entities/enemies/zako_dim1.png");
	goei_sprite = LoadTexture("resources/Textures/entities/enemies/goei_dim1.png");
	don1_sprite = LoadTexture("resources/Textures/entities/enemies/don1.png");
	don2_sprite = LoadTexture("resources/Textures/entities/enemies/don2.png");
	don3_sprite = LoadTexture("resources/Textures/entities/enemies/don3.png");
	don4_sprite = LoadTexture("resources/Textures/entities/enemies/don4.png");
	baby_don1_sprite = LoadTexture("resources/Textures/entities/enemies/don1_baby.png");
	baby_don2_sprite = LoadTexture("resources/Textures/entities/enemies/don2_baby.png");
	baby_don3_sprite = LoadTexture("resources/Textures/entities/enemies/don3_baby.png");
	baby_don4_sprite = LoadTexture("resources/Textures/entities/enemies/don4_baby.png");
	mini_boss_galaga_sprite = LoadTexture("resources/Textures/entities/enemies/mini_boss.png");
	mini_boss_galaga_damaged_sprite = LoadTexture("resources/Textures/entities/enemies/mini_boss_damaged.png");
	enemy_explosion = LoadTexture("resources/Textures/entities/player/explosion.png");

	win_screen = LoadTexture("resources/Textures/UI/win_condition.png");


// Load Font
	customFont = LoadFont("resources/Textures/texts/font/font.png");
	customFont = LoadFontEx("resources/Textures/texts/font/font.png", 8, 0, 42);
	SetTextLineSpacing(16);


// Load Sounds
	main_menu_lightning = LoadSound("resources/audio/sfx/main_menu_lightning.wav");
	main_menu_enemy_fly = LoadSound("resources/audio/sfx/main_menu_enemy.wav");
	main_menu_start = LoadSound("resources/audio/sfx/main_menu_start.wav");

	select = LoadSound("resources/audio/sfx/select.wav");
	launch_sequence_enemy = LoadSound("resources/audio/sfx/launch_sequence_enemy.ogg");

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

// cleanup
// unload our textures so it can be cleaned up
void UnloadGame() {

	UnloadTexture(main_menu_background);
	UnloadTexture(main_menu_logo0);
	UnloadTexture(main_menu_logo1);
	UnloadTexture(main_menu_logo);
	UnloadTexture(main_menu_logo2);
	UnloadTexture(main_menu_namco);
	UnloadTexture(main_menu_enemy);
	UnloadTexture(main_menu_logo_lightning);

	UnloadTexture(credits_screen);

	UnloadTexture(launch_background);
	UnloadTexture(launch_sequence_enemy_sprite);

	UnloadTexture(level1_background);
	UnloadTexture(level3_background);
	UnloadTexture(player_sprite);
	UnloadTexture(shot_sprite);
	UnloadTexture(zakko_shot_sprite);
	UnloadTexture(stage_indicator);
	UnloadTexture(zakko_sprite);
	UnloadTexture(goei_sprite);
	UnloadTexture(don1_sprite);
	UnloadTexture(don2_sprite);
	UnloadTexture(don3_sprite);
	UnloadTexture(don4_sprite);
	UnloadTexture(baby_don1_sprite);
	UnloadTexture(baby_don2_sprite);
	UnloadTexture(baby_don3_sprite);
	UnloadTexture(baby_don4_sprite);
	UnloadTexture(mini_boss_galaga_sprite);
	UnloadTexture(mini_boss_galaga_damaged_sprite);
	UnloadTexture(enemy_explosion);

	UnloadTexture(win_screen);


	UnloadFont(customFont);


	UnloadSound(main_menu_lightning);
	UnloadSound(main_menu_enemy_fly);
	UnloadSound(main_menu_start);

	UnloadSound(select);
	UnloadSound(launch_sequence_enemy);

	UnloadSound(fighter_shot);
	UnloadSound(fighter_killed);
	UnloadSound(enemy_shot);
	UnloadSound(enemy_killed);


	UnloadMusicStream(main_menu_music);
	UnloadMusicStream(game_over_music);
	UnloadMusicStream(victory_music);

}
