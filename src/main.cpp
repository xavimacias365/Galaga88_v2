/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include <iostream>
#include "raylib.h"
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir
#include <vector>
using namespace std;

#include "classes.h"
#include "resources.h"

// Defines
#define screenWidth 840
#define screenHeight 1080
#define fontSize 37

// Global variables
bool gameOver;
bool pause;
bool victory;
bool main_menu = 1;
bool credits;
bool launchSequence;
bool inGame;
enum LevelStage { LEVEL1, LEVEL2, STAGE0 };
LevelStage level = LEVEL1;

bool showCollisions;

int score;
int highscore;
int besthighscore;
int lives;
int activeEnemies;
int blink;
float alpha;
bool soundPlayed;

const char* main_menu_text_start;

enum LightningState { NUMBER, MOVING, FLASH, FINISH };
LightningState lstate = NUMBER;

MainMenuEnemy enemy;
MainMenuLightning lightning;
LaunchSequenceEnemy enemyboss;
vector<Zakko> zakkos;
vector<Don> dons;
vector<BabyDon> babydons;
vector<Goei> goeis;
Player player;
vector<PlayerShot> shot;
vector<EnemyShot> eshot;
vector<MiniBossGalaga> miniboss;
vector<PlayerExplosion> explosion;
vector<EnemyExplosion> eexplosion;

// functions
void LoadGame();
void InitGame();
void UpdateGame();
void DrawGame();
void UnloadGame();
void UpdateDrawFrame();

void MainMenu();
void Credits();
void LaunchSequence();
void InGame();
void GameOver();
void Victory();
void Restart();
void Clear();

void Stage0();
void level1();
void level2();
int CountEnemiesOnScreen();

void GameCheats();

int main () {
	// Tell the window to use vsync and work on high DPI displays
//	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(screenWidth, screenHeight, "Galaga88 - Repeaters Studio");

	InitAudioDevice();
	LoadGame();
	InitGame();
	SetTargetFPS(60);

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	srand(time(NULL));

	// game loop
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		UpdateDrawFrame();
	}

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}

void InitGame() {

	// Global variables Default
	gameOver = false;
	pause = false;
	victory = false;
	main_menu = true;
	credits = false;
	launchSequence = false;
	inGame = false;

	showCollisions = false;

	score = 0;
	besthighscore = 0;
	lives = 1;
	activeEnemies = 0;
	blink = 0;
	alpha = 0.0f;
	soundPlayed = false;

	main_menu_text_start = "TO START PRESS < ENTER >!";

	enemy = MainMenuEnemy({ 0, 555, 64, 64 }, { 5, 0 }, WHITE, true, 0, 0, 0);
	lightning = MainMenuLightning({ 20 + 220, 70 - 220, 64, 64 }, { 5, 5 }, WHITE, true, 0, 0, 0);
	enemyboss = LaunchSequenceEnemy({ screenWidth / 2.0f - 48, screenHeight / 2.0f - 32, 96, 64 }, { 0, 0 }, WHITE, true, 0, 0, 0);

	player = Player(true, { ((screenWidth - 50) / 2), screenHeight - (screenHeight / 10), 64, 64 }, { 5, 5 }, WHITE);

	level1();
}

void UpdateGame() {
	if (main_menu == true) {
		MainMenu();
	}
	else if (credits == true) {
		Credits();
	}
	else if (launchSequence == true) {
		LaunchSequence();
	}
	else if (inGame == true) {
		InGame();
	}
	else if (gameOver == true) {
		GameOver();
	}
	else if (victory == true) {
		Victory();
	}

	GameCheats();
}

void DrawGame() {

	// Drawing
	BeginDrawing();
	// Setup the back buffer for drawing (clear color and depth buffers)
	ClearBackground(BLACK);

	// Draw Main Menu
		// CENTER IMG FORMULA -> (screenWidth - myImage.width) / 2
		// CENTER TEXT FORMULA -> (screenWidth - MeasureText("TEXT", fontSize)) / 2		FONT SIZE = 37
		// CORRECT IMG SCALE -> (screenWidth - myImage.width * fminf((desiredWidth / myImage.width), (desiredHeight / myImage.height)) / 2.0f)

	Rectangle sourceRec = { 0.0f, 0.0f, 16.0f,  16.0f };
	float scale = (float)screenWidth / (float)main_menu_background.width;

	if (main_menu == true) {
		DrawTextureEx(main_menu_background, { 0, 0 }, 0.0f, ((float)screenWidth / main_menu_background.width, (float)screenHeight / main_menu_background.height), WHITE);
		DrawTextureEx(main_menu_logo0, { (screenWidth - (main_menu_logo.width * fminf((800.0f / main_menu_logo.width), (400.0f / main_menu_logo.height)))) / 2.0f, (screenHeight / 4.0f) - ((main_menu_logo.height * fminf((800.0f / main_menu_logo.width), (400.0f / main_menu_logo.height))) / 2.0f) }, 0.0f, fminf((800.0f / main_menu_logo.width), (400.0f / main_menu_logo.height)), WHITE);

		// Logo animation && lightning
		if (lstate == NUMBER) {
			if (alpha < 1.0f) {
				alpha += 0.01f;
				if (alpha > 1.0f) alpha = 1.0f;

				Color fadeColor = { 255, 255, 255, (unsigned char)(alpha * 255) };
				DrawTextureEx(main_menu_logo1, { (screenWidth - (main_menu_logo.width * fminf((800.0f / main_menu_logo.width), (400.0f / main_menu_logo.height)))) / 2.0f, (screenHeight / 4.0f) - ((main_menu_logo.height * fminf((800.0f / main_menu_logo.width), (400.0f / main_menu_logo.height))) / 2.0f) }, 0.0f, fminf((800.0f / main_menu_logo.width), (400.0f / main_menu_logo.height)), fadeColor);
			}

			if (alpha >= 1.0f) {
				lstate = MOVING;
				alpha = 0.0f;
			}
		}
		else if (lstate == MOVING) {
			DrawTextureEx(main_menu_logo1, { (screenWidth - (main_menu_logo.width * fminf((800.0f / main_menu_logo.width), (400.0f / main_menu_logo.height)))) / 2.0f, (screenHeight / 4.0f) - ((main_menu_logo.height * fminf((800.0f / main_menu_logo.width), (400.0f / main_menu_logo.height))) / 2.0f) }, 0.0f, fminf((800.0f / main_menu_logo.width), (400.0f / main_menu_logo.height)), WHITE);

			if (lightning.GetX() == 20 && lightning.GetY() == 70) {
				lstate = FLASH;
			}

		}
		else if (lstate == FLASH) {
			lightning.SetX(lightning.GetX() + 500);
			lightning.SetY(lightning.GetY() - 500);

			DrawTextureEx(main_menu_logo2, { (screenWidth - (main_menu_logo.width * fminf((800.0f / main_menu_logo.width), (400.0f / main_menu_logo.height)))) / 2.0f, (screenHeight / 4.0f) - ((main_menu_logo.height * fminf((800.0f / main_menu_logo.width), (400.0f / main_menu_logo.height))) / 2.0f) }, 0.0f, fminf((800.0f / main_menu_logo.width), (400.0f / main_menu_logo.height)), WHITE);

			lstate = FINISH;

		}
		else if (lstate == FINISH) {
			DrawTextureEx(main_menu_logo, { (screenWidth - (main_menu_logo.width * fminf((800.0f / main_menu_logo.width), (400.0f / main_menu_logo.height)))) / 2.0f, (screenHeight / 4.0f) - ((main_menu_logo.height * fminf((800.0f / main_menu_logo.width), (400.0f / main_menu_logo.height))) / 2.0f) }, 0.0f, fminf((800.0f / main_menu_logo.width), (400.0f / main_menu_logo.height)), WHITE);

		}

		// Main Menu Text
		DrawText("TO START PRESS [ENTER]!", (screenWidth - MeasureText("TO START PRESS [ENTER]!", fontSize)) / 2, (screenHeight - (screenHeight / 3)), fontSize, GREEN);
		if (blink >= 0 && blink <= 40) { DrawText("INSERT COIN", (screenWidth - MeasureText("INSERT COIN", fontSize)) / 2, (screenHeight - ((screenHeight / 3) + 50)), fontSize, GREEN); }
		DrawText("© 1981 1987 NAMCO", (screenWidth - MeasureText("© 1981 1987 NAMCO", fontSize)) / 2, 806, fontSize, WHITE);
		DrawText("ALL RIGHTS RESERVED", (screenWidth - MeasureText("ALL RIGHTS RESERVED", fontSize)) / 2, 867, fontSize, WHITE); // (X) 150
		DrawTextureEx(main_menu_namco, { ((screenWidth - main_menu_namco.width) / 2.0f), screenHeight - (screenHeight / 10) }, 0.0f, (main_menu_namco.width / 32, main_menu_namco.height / 32), WHITE);

		DrawTextureEx(main_menu_logo_lightning, { lightning.GetX(), lightning.GetY() }, 0.0f, fminf((800.0f / main_menu_logo.width), (400.0f / main_menu_logo.height)), WHITE);
		DrawTexturePro(main_menu_enemy, sourceRec, enemy.GetRec(), { 0, 0 }, 0.0f, WHITE);

	}
	else if (credits == true) {
		// Credits text
		DrawTextureEx(credits_screen, { 0, 0 }, 0.0f, ((float)screenWidth / credits_screen.width, (float)screenHeight / credits_screen.height), WHITE);
		DrawText("PRESS [ENTER] TO CONTINUE!", (screenWidth - MeasureText("PRESS [ENTER] TO CONTINUE!", fontSize)) / 2, (screenHeight / 4) - 50, fontSize, GREEN);
	}
	else if (launchSequence == true) {
		// Launch Sequence
		DrawTextureEx(launch_background, { 0,0 }, 0.0f, ((float)screenWidth / credits_screen.width, (float)screenHeight / credits_screen.height), WHITE);
		DrawTexturePro(player_sprite, sourceRec, player.GetRec(), { 0, 0 }, 0.0f, WHITE);

		// Launch Sequence Enemy
		if (player.GetY() <= 0) {
			float scale2 = 4.0f;
			sourceRec = { 0.0f, (float)(enemyboss.GetCurrentFrame() * 64), 96.0f, 64.0f };
			Rectangle destRec = { (float)(screenWidth / 2 - (96 * scale2) / 2), (float)(screenHeight / 2 - (64 * scale2) / 2), 96.0f * scale2, 64.0f * scale2 };
			DrawTexturePro(launch_sequence_enemy_sprite, sourceRec, destRec, { 0, 0 }, 0.0f, WHITE);
		}

	}
	else if (inGame == true || gameOver == true) {

		// Fade in animation
		DrawTextureEx(level3_background, { 0, 0 }, 0.0f, ((float)screenWidth / credits_screen.width, (float)screenHeight / credits_screen.height), WHITE);

		Color fadeColor = WHITE;

		if (alpha < 1.0f) {
			alpha += 0.01f;
			if (alpha > 1.0f) alpha = 1.0f;
			fadeColor = { 255, 255, 255, (unsigned char)(alpha * 255) };
		}

		// Draw Background levels
		switch (level) {
		case LEVEL1:
			DrawTextureEx(level1_background, { 0, 0 }, 0.0f, ((float)screenWidth / credits_screen.width, (float)screenHeight / credits_screen.height), fadeColor);
			break;

		case LEVEL2:
			DrawTextureEx(level2_background, { 0, 0 }, 0.0f, ((float)screenWidth / credits_screen.width, (float)screenHeight / credits_screen.height), WHITE);
			break;

		case STAGE0:
			DrawTextureEx(level3_background, { 0, 0 }, 0.0f, ((float)screenWidth / credits_screen.width, (float)screenHeight / credits_screen.height), WHITE);
			break;
		}

		// Draw Stage indicator
		if (level == LEVEL1) {
			DrawTextureEx(stage_indicator, { (float)(screenWidth - stage_indicator.width * scale), (float)(screenHeight - stage_indicator.height * scale) }, 0.0f, scale, WHITE);
		}
		else if (level == LEVEL2) {
			DrawTextureEx(stage_indicator, { (float)(screenWidth - stage_indicator.width * scale), (float)(screenHeight - stage_indicator.height * scale) }, 0.0f, scale, WHITE);
			DrawTextureEx(stage_indicator, { (float)(screenWidth - stage_indicator.width * scale - ((stage_indicator.width * scale) / 2)), (float)(screenHeight - stage_indicator.height * scale) }, 0.0f, scale, WHITE);
		}

		// Draw Player
		sourceRec = { 0.0f, 0.0f, 16.0f,  16.0f };
		if (player.IsActive()) { DrawTexturePro(player_sprite, sourceRec, player.GetRec(), { 0, 0 }, 0.0f, WHITE); }

		// Draw Zakko Enemies
		for (const Zakko& z : zakkos) {
			if (z.IsActive()) {
				sourceRec = { 0.0f, z.GetCurrentFrame() * 16.0f, 16.0f, 16.0f };
				DrawTexturePro(zakko_sprite, sourceRec, z.GetRec(), { 0, 0 }, 0.0f, WHITE);
			}
		}

		// Draw Goei Enemies
		for (const Goei& g : goeis) {
			if (g.IsActive()) {
				sourceRec = { 0.0f, g.GetCurrentFrame() * 16.0f, 16.0f, 16.0f };
				DrawTexturePro(goei_sprite, sourceRec, g.GetRec(), { 0, 0 }, 0.0f, WHITE);
			}
		}

		// Draw Don Enemies
		for (const Don& d : dons) {
			if (d.IsActive()) {
				sourceRec = { 0.0f, d.GetCurrentFrame() * 16.0f, 16.0f, 16.0f };
				switch (d.GetVariant()) {
				case 0: DrawTexturePro(don1_sprite, sourceRec, d.GetRec(), { 0, 0 }, 0.0f, WHITE); break;
				case 1: DrawTexturePro(don2_sprite, sourceRec, d.GetRec(), { 0, 0 }, 0.0f, WHITE); break;
				case 2:	DrawTexturePro(don3_sprite, sourceRec, d.GetRec(), { 0, 0 }, 0.0f, WHITE); break;
				case 3:	DrawTexturePro(don4_sprite, sourceRec, d.GetRec(), { 0, 0 }, 0.0f, WHITE); break;
				}
			}
		}

		// Draw Baby Don Enemies
		for (const BabyDon& bd : babydons) {
			if (bd.IsActive()) {
				sourceRec = { 0.0f, bd.GetCurrentFrame() * 16.0f, 16.0f, 16.0f };
				switch (bd.GetVariant()) {
				case 0: DrawTexturePro(baby_don1_sprite, sourceRec, bd.GetRec(), { 0, 0 }, 0.0f, WHITE); break;
				case 1: DrawTexturePro(baby_don2_sprite, sourceRec, bd.GetRec(), { 0, 0 }, 0.0f, WHITE); break;
				case 2:	DrawTexturePro(baby_don3_sprite, sourceRec, bd.GetRec(), { 0, 0 }, 0.0f, WHITE); break;
				case 3:	DrawTexturePro(baby_don4_sprite, sourceRec, bd.GetRec(), { 0, 0 }, 0.0f, WHITE); break;
				}
			}
		}

		// Draw MiniBoss Galaga Enemies
		for (const MiniBossGalaga& mbg : miniboss) {
			if (mbg.IsActive()) {
				sourceRec = { 0.0f, mbg.GetCurrentFrame() * 16.0f, 16.0f, 16.0f };

				if (mbg.GetEntityLives() == 2) {
					DrawTexturePro(mini_boss_galaga_sprite, sourceRec, mbg.GetRec(), { 0, 0 }, 0.0f, WHITE);
				}
				else if (mbg.GetEntityLives() == 1) {
					DrawTexturePro(mini_boss_galaga_damaged_sprite, sourceRec, mbg.GetRec(), { 0, 0 }, 0.0f, WHITE);
				}
			}
		}

		// Draw Player Shoots
		for (const Shot& s : shot) {
			if (s.IsActive()) {
				sourceRec = { 0.0f, 0.0f, 16.0f,  16.0f };
				Rectangle dest = { s.GetX() - (sourceRec.width * scale - s.GetRec().width) / 2, s.GetY() - (sourceRec.height * scale - s.GetRec().height) / 2, sourceRec.width * scale, sourceRec.height * scale };
				DrawTexturePro(shot_sprite, sourceRec, dest, { 0, 0 }, 0.0f, WHITE);
			}
		}

		// Draw Enemy Shoots
		for (const EnemyShot& es : eshot) {
			if (es.IsActive()) {
				sourceRec = { 0.0f, es.GetCurrentFrame() * 16.0f, 16.0f, 16.0f };
				Rectangle dest = { es.GetX() - (sourceRec.width * scale - es.GetRec().width) / 2, es.GetY() - (sourceRec.height * scale - es.GetRec().height) / 2, sourceRec.width * scale, sourceRec.height * scale };
				DrawTexturePro(zakko_shot_sprite, sourceRec, dest, { 0, 0 }, 0.0f, WHITE);
			}
		}

		// Draw Player Explosion
		for (const PlayerExplosion& e : explosion) {
			if (e.IsActive()) {
				sourceRec = { 0.0f, e.GetCurrentFrame() * 32.0f, 32.0f, 32.0f };
				Rectangle dest = { e.GetX(), e.GetY(), 64, 64 };
				DrawTexturePro(enemy_explosion, sourceRec, dest, { 0, 0 }, 0.0f, WHITE);
			}
		}

		// Draw Enemy Explosion
		for (const EnemyExplosion& ee : eexplosion) {
			if (ee.IsActive()) {
				sourceRec = { 0.0f, ee.GetCurrentFrame() * 32.0f, 32.0f, 32.0f };
				Rectangle dest = { ee.GetX(), ee.GetY(), 64, 64 };
				DrawTexturePro(enemy_explosion, sourceRec, dest, { 0, 0 }, 0.0f, WHITE);
			}
		}
	}

	if (gameOver == true) {
		// Game Over text
		DrawText("GAME OVER!", (screenWidth - MeasureText("GAME OVER!", fontSize)) / 2, (screenHeight / 2) - fontSize, fontSize, RED);
		DrawText("PRESS [ENTER] TO PLAY AGAIN", (screenWidth - MeasureText("PRESS [ENTER] TO PLAY AGAIN", fontSize)) / 2, (screenHeight / 2) + fontSize, fontSize, RED);
	}

	if (victory == true) {
		// Victory screen text
		DrawTextureEx(win_screen, { 0, 0 }, 0.0f, ((float)screenWidth / credits_screen.width, (float)screenHeight / credits_screen.height), WHITE);
		DrawText("PRESS [ENTER] TO PLAY AGAIN", (screenWidth - MeasureText("PRESS [ENTER] TO PLAY AGAIN", fontSize)) / 2, screenHeight - fontSize * 2, fontSize, RED);
	}

	if (pause == true) {
		// Pause text
		DrawText("GAME PAUSED!", (screenWidth - MeasureText("GAME PAUSED!", fontSize)) / 2, screenHeight - 137, fontSize, RED);
	}

	if (showCollisions == true) {
		// Draw Entity Collisions
		if (main_menu == true) {
			DrawRectangleLines(
				(int)lightning.GetRec().x,
				(int)lightning.GetRec().y,
				(int)lightning.GetRec().width,
				(int)lightning.GetRec().height,
				PURPLE
			);

			DrawRectangleLines(
				(int)enemy.GetRec().x,
				(int)enemy.GetRec().y,
				(int)enemy.GetRec().width,
				(int)enemy.GetRec().height,
				DARKGREEN
			);
		}
		if (launchSequence == true || inGame == true) {
			DrawRectangleLines(
				(int)player.GetRec().x,
				(int)player.GetRec().y,
				(int)player.GetRec().width,
				(int)player.GetRec().height,
				BLUE
			);
		}
		if (inGame == true || gameOver == true) {
			for (const Zakko& z : zakkos) {
				DrawRectangleLines(
					(int)z.GetRec().x,
					(int)z.GetRec().y,
					(int)z.GetRec().width,
					(int)z.GetRec().height,
					RED
				);
			}

			for (const Goei& g : goeis) {
				DrawRectangleLines(
					(int)g.GetRec().x,
					(int)g.GetRec().y,
					(int)g.GetRec().width,
					(int)g.GetRec().height,
					GREEN
				);
			}

			for (const Don& d : dons) {
				DrawRectangleLines(
					(int)d.GetRec().x,
					(int)d.GetRec().y,
					(int)d.GetRec().width,
					(int)d.GetRec().height,
					PINK
				);
			}

			for (const BabyDon& bd : babydons) {
				DrawRectangleLines(
					(int)bd.GetRec().x,
					(int)bd.GetRec().y,
					(int)bd.GetRec().width,
					(int)bd.GetRec().height,
					PINK
				);
			}

			for (const MiniBossGalaga& mbg : miniboss) {
				DrawRectangleLines(
					(int)mbg.GetRec().x,
					(int)mbg.GetRec().y,
					(int)mbg.GetRec().width,
					(int)mbg.GetRec().height,
					DARKBLUE
				);
			}

			for (const Shot& s : shot) {
				DrawRectangleLines(
					(int)s.GetRec().x,
					(int)s.GetRec().y,
					(int)s.GetRec().width,
					(int)s.GetRec().height,
					BLUE
				);
			}

			for (const EnemyShot& es : eshot) {
				DrawRectangleLines(
					(int)es.GetRec().x,
					(int)es.GetRec().y,
					(int)es.GetRec().width,
					(int)es.GetRec().height,
					RED
				);
			}

			for (const Explosion& e : explosion) {
				DrawRectangleLines(
					(int)e.GetRec().x,
					(int)e.GetRec().y,
					(int)e.GetRec().width,
					(int)e.GetRec().height,
					DARKPURPLE
				);
			}

			for (const EnemyExplosion& ee : eexplosion) {
				DrawRectangleLines(
					(int)ee.GetRec().x,
					(int)ee.GetRec().y,
					(int)ee.GetRec().width,
					(int)ee.GetRec().height,
					PURPLE
				);
			}
		}
	}

	// Lives, Score and High Score
	DrawText((TextFormat("%i ", lives)), (screenWidth + MeasureText("%i", fontSize)) / 10, 25, fontSize, YELLOW);
	DrawText("UP", (screenWidth + MeasureText("%i", fontSize)) / 10 + MeasureText("%i", fontSize), 25, fontSize, YELLOW);

	DrawText((TextFormat("%02i ", score)), 50, 25 + MeasureText("%i", fontSize), fontSize, WHITE);

	DrawText("HIGH SCORE", (screenWidth - MeasureText("HIGH SCORE", fontSize)) / 2, 25, fontSize, RED);
	DrawText((TextFormat("%02i ", highscore)), (screenWidth - MeasureText("%02i", fontSize)) / 2, 25 + MeasureText("%i", fontSize), fontSize, WHITE);

	// end the frame and get ready for the next one  (display frame, poll input, etc...)
	EndDrawing();
}

void UpdateDrawFrame() {
	UpdateGame();
	DrawGame();
}

void MainMenu() {

 //Main Menu Lightning movement
	if (lstate == MOVING) {
		if (lightning.GetX() > 20 && lightning.GetY() < 70) {
			lightning.SetX(lightning.GetX() - lightning.GetSpeed().x);
			lightning.SetY(lightning.GetY() + lightning.GetSpeed().y);
		}
	}

	if (lightning.GetX() == 20 && lightning.GetY() == 70) {
		PlaySound(main_menu_lightning);
	}

// Main Menu Enemy movement
	if (enemy.GetX() == 0) { PlaySound(main_menu_enemy_fly); }
	if (enemy.GetX() < screenWidth + 50) {
		enemy.SetX(enemy.GetX() + enemy.GetSpeed().x);
	}

// Text blink
	blink++;
	if (blink >= 90) {
		blink = 0;
	}

// Change State
	if (IsKeyPressed(KEY_ENTER)) {
		PlaySound(main_menu_start);
		main_menu = false;
		credits = true;
	}
}

void Credits() {
// Pass to next screen
	if (IsKeyPressed(KEY_ENTER)) {
		PlaySound(select);
		credits = false;
		launchSequence = true;
	}

}

void LaunchSequence() {

	UpdateMusicStream(main_menu_music);

	if (player.GetY() >= -screenHeight) {
		player.SetY(player.GetY() - player.GetSpeed().y);
	}

	if (player.GetY() <= 0 && !soundPlayed) {
		PlaySound(launch_sequence_enemy);
		soundPlayed = true;
	}
	
	if (IsKeyPressed(KEY_ENTER) || player.GetY() <= -screenHeight / 2) {
		launchSequence = false;
		inGame = true;
		player.SetY(screenHeight - (screenHeight / 5));
	}

	enemyboss.UpdateAnimation(2, 20);

}

void InGame() {
	if (IsKeyPressed('P')) { pause = !pause; }
	if (!pause) {
		// Player Movement
		if (IsKeyDown('A') || IsKeyDown(KEY_LEFT)) { player.SetX(player.GetX() - player.GetSpeed().x); }
		if (IsKeyDown('D') || IsKeyDown(KEY_RIGHT)) { player.SetX(player.GetX() + player.GetSpeed().x); }

		// Player Wall Colisions
		if (player.GetX() <= 0) { player.SetX(0); }
		if (player.GetX() + player.GetRec().width >= screenWidth) { player.SetX(screenWidth - player.GetRec().width); }

		// Player Shooting
		if (IsKeyPressed(KEY_SPACE)) {
			for (Shot& s : shot) {
				if (!s.IsActive()) {
					s.SetX((player.GetX() + player.GetRec().width / 2) - 3);
					s.SetY(player.GetY());
					s.ChangeState(true);
					PlaySound(fighter_shot);
					break;
				}
			}
		}

		// Player Death
		if (lives == 0) {
			player.ChangeState(false);
			gameOver = true;
			inGame = false;
		}
		else if (lives < 0) {
			lives = 0;
		}
		else {
			player.ChangeState(true);
		}

	//#-------#

		// Zakko Movement
		for (Zakko& z : zakkos) {
			if (z.IsActive()) {
				z.SetX(z.GetX() + z.GetSpeed().x);
			}
		}

		// Zakko Wall Collisions
		float leftMostZakkoCol = screenWidth;
		float rightMostZakkoCol = 0.0f;

		// Find edges
		for (Zakko& z : zakkos) {
			if (z.IsActive()) {
				if (z.GetX() < leftMostZakkoCol) { leftMostZakkoCol = z.GetX(); }
				if (z.GetX() + z.GetRec().width > rightMostZakkoCol) { rightMostZakkoCol = z.GetX() + z.GetRec().width; }
			}
		}

		// Check collision with walls
		bool hitLeftWall = (leftMostZakkoCol <= 0);
		bool hitRightWall = (rightMostZakkoCol >= screenWidth - 16);
		if (hitLeftWall || hitRightWall) {
			for (Zakko& z : zakkos) {
				Vector2 speed = z.GetSpeed();
				speed.x *= -1;
				z.SetSpeed(speed);
			}
		}

		// Zakko Frame Animation
		for (Zakko& z : zakkos) {
			if (z.IsActive()) {
				z.UpdateAnimation(2, 20);
			}
		}

		// Zakko Shooting
		for (Zakko& z : zakkos) {
			if (z.IsActive()) {
				z.SetShot(rand() % 150);

				if (z.GetShot() == 1) {
					for (EnemyShot& es : eshot) {
						if (!es.IsActive()) {
							es.SetX((z.GetX() + z.GetRec().width / 2) - 3);
							es.SetY(z.GetY());
							es.ChangeState(true);
							PlaySound(enemy_shot);
							break;
						}
					}
				}
			}
		}

		// Zakko Shot Frame Animation
		for (EnemyShot& es : eshot) {
			if (es.IsActive()) {
				es.UpdateAnimation(2, 20);
			}
		}

		//#-------#

		// Goei Movement
		for (Goei& g : goeis) {
			if (g.IsActive()) {
				g.SetX(g.GetX() + g.GetSpeed().x);
			}
		}

		// Goei Wall Collisions
		float leftMostGoeiCol = screenWidth;
		float rightMostGoeiCol = 0.0f;

		// Find edges
		for (Goei& g : goeis) {
			if (g.IsActive()) {
				if (g.GetX() < leftMostGoeiCol) { leftMostGoeiCol = g.GetX(); }
				if (g.GetX() + g.GetRec().width > rightMostGoeiCol) { rightMostGoeiCol = g.GetX() + g.GetRec().width; }
			}
		}

		// Check collision with walls
		hitLeftWall = (leftMostGoeiCol <= 0);
		hitRightWall = (rightMostGoeiCol >= screenWidth - 16);
		if (hitLeftWall || hitRightWall) {
			for (Goei& g : goeis) {
				Vector2 speed = g.GetSpeed();
				speed.x *= -1;
				g.SetSpeed(speed);
			}
		}

		// Goei Frame Animation
		for (Goei& g : goeis) {
			if (g.IsActive()) {
				g.UpdateAnimation(2, 20);
			}
		}

		//#-------#

		// Don Movement
		for (Don& d : dons) {
			if (d.IsActive()) {
				d.SetX(d.GetX() + d.GetSpeed().x);
			}
		}

		// Don Wall Collisions
		float leftMostDonCol = screenWidth;
		float rightMostDonCol = 0.0f;

		// Find edges
		for (Don& d : dons) {
			if (d.IsActive()) {
				if (d.GetX() < leftMostDonCol) { leftMostDonCol = d.GetX(); }
				if (d.GetX() + d.GetRec().width > rightMostDonCol) { rightMostDonCol = d.GetX() + d.GetRec().width; }
			}
		}

		// Check collision with walls
		hitLeftWall = (leftMostDonCol <= 0);
		hitRightWall = (rightMostDonCol >= screenWidth - 16);
		if (hitLeftWall || hitRightWall) {
			for (Don& d : dons) {
				Vector2 speed = d.GetSpeed();
				speed.x *= -1;
				d.SetSpeed(speed);
			}
		}

		// Don Frame Animation
		for (Don& d : dons) {
			if (d.IsActive()) {
				d.UpdateAnimation(2, 20);
			}
		}

		// Baby don
		for (BabyDon& bd : babydons) {
			if (bd.IsActive()) {
				bd.SetY(bd.GetY() + bd.GetSpeed().y);
				bd.UpdateAnimation(2, 20);
			}

			if (bd.GetY() > screenHeight) {
				bd.ChangeState(false);
			}
		}

		//#-------#

		// MiniBossGalaga Movement
		for (MiniBossGalaga& mbg : miniboss) {
			if (mbg.IsActive()) {
				mbg.SetX(mbg.GetX() + mbg.GetSpeed().x);
			}
		}

		// MiniBossGalaga Wall Collisions
		float leftMostMBGCol = screenWidth;
		float rightMostMBGCol = 0.0f;

		// Find edges
		for (MiniBossGalaga& mbg : miniboss) {
			if (mbg.IsActive()) {
				if (mbg.GetX() < leftMostMBGCol) { leftMostMBGCol = mbg.GetX(); }
				if (mbg.GetX() + mbg.GetRec().width > rightMostMBGCol) { rightMostMBGCol = mbg.GetX() + mbg.GetRec().width; }
			}
		}

		// Check collision with walls
		hitLeftWall = (leftMostMBGCol <= 0);
		hitRightWall = (rightMostMBGCol >= screenWidth - 16);
		if (hitLeftWall || hitRightWall) {
			for (MiniBossGalaga& mbg : miniboss) {
				Vector2 speed = mbg.GetSpeed();
				speed.x *= -1;
				mbg.SetSpeed(speed);
			}
		}

		// MiniBossGalaga Frame Animation
		for (MiniBossGalaga& mbg : miniboss) {
			if (mbg.IsActive()) {
				mbg.UpdateAnimation(2, 20);
			}
		}

		//#-------#

		// Shot Behaviour
		for (Shot& s : shot) {
			if (s.IsActive()) {
				s.SetY(s.GetY() - s.GetSpeed().y);
			}

		// Colision with enemy
		for (Zakko& z : zakkos) {
			if (z.IsActive() && s.IsActive()) {
				if  (CheckCollisionRecs(s.GetRec(), z.GetRec())) {
					s.ChangeState(false);
					z.ChangeState(false);
					PlaySound(enemy_killed);

					// Explosion
					for (EnemyExplosion& ee : eexplosion) {
						if (!ee.IsActive()) {
							ee.Activate({ z.GetX() + z.GetRec().width / 2 - 32, z.GetY() + z.GetRec().height / 2 - 32 }, 64, 64);
						}
					}
					
					// Score
					score += 100;
				}
			}
		}

		for (Goei& g : goeis) {
			if (g.IsActive() && s.IsActive()) {
				if (CheckCollisionRecs(s.GetRec(), g.GetRec())) {
					s.ChangeState(false);
					g.ChangeState(false);
					PlaySound(enemy_killed);

					// Explosion
					for (EnemyExplosion& ee : eexplosion) {
						if (!ee.IsActive()) {
							ee.Activate({ g.GetX(), g.GetY() }, g.GetRec().width, g.GetRec().height);
						}
					}

					// Score
					score += 50;
				}
			}
		}

		for (Don& d : dons) {
			if (d.IsActive() && s.IsActive()) {
				if (CheckCollisionRecs(s.GetRec(), d.GetRec())) {
					s.ChangeState(false);
					d.ChangeState(false);
					PlaySound(enemy_killed);

					int parentVariant = d.GetVariant();
					Vector2 origin = { d.GetX(), d.GetY() };
					Vector2 commonSpeed = { 0.0f, 7.5f };
					vector<Vector2> offsets = {
						{ -48.0f, 0.0f },
						{ -16.0f, 0.0f },
						{  16.0f, 0.0f },
						{  48.0f, 0.0f }
					};

					int spawned = 0;
					for (BabyDon& bd : babydons) {
						if (!bd.IsActive()) {
							Rectangle rec = { origin.x + offsets[spawned].x, origin.y + offsets[spawned].y, 32, 32 };
							bd = BabyDon(rec, commonSpeed, WHITE, true, 0, 0, 0, 0);
							bd.SetVariant(parentVariant);
							spawned++;
							if (spawned >= 4) break;
						}
					}

					// Explosion
					for (EnemyExplosion& ee : eexplosion) {
						if (!ee.IsActive()) {
							ee.Activate({ d.GetX(), d.GetY() }, d.GetRec().width, d.GetRec().height);
							break;
						}
					}

					// Score
					score += 50;
				}
			}
		}

		for (BabyDon& bd : babydons) {
			if (bd.IsActive() && s.IsActive()) {
				if (CheckCollisionRecs(s.GetRec(), bd.GetRec())) {
					s.ChangeState(false);
					bd.ChangeState(false);
					PlaySound(enemy_killed);

					// Explosion
					for (EnemyExplosion& ee : eexplosion) {
						if (!ee.IsActive()) {
							ee.Activate({ bd.GetX(), bd.GetY() }, bd.GetRec().width, bd.GetRec().height);
						}
					}

					// Score
					score += 25;
				}
			}
		}

		for (MiniBossGalaga& mbg : miniboss) {
			if (mbg.IsActive() && s.IsActive() && CheckCollisionRecs(s.GetRec(), mbg.GetRec())) {
				s.ChangeState(false);

				if (mbg.GetEntityLives() > 1) {
					mbg.SetEntityLives(mbg.GetEntityLives() - 1);
					PlaySound(enemy_killed);
				}
				else {
					mbg.ChangeState(false);
					PlaySound(enemy_killed);

					// Explosion
					for (EnemyExplosion& ee : eexplosion) {
						if (!ee.IsActive()) {
							ee.Activate({ mbg.GetX(), mbg.GetY() }, mbg.GetRec().width, mbg.GetRec().height);
							break;
						}
					}

					// Score
					score += 150;
				}
			}
		}

		// Despawn shot
			if (s.GetY() < 0) {
				s.ChangeState(false);
			}
		}

		//#-------#

		// Enemy Shot Behaviour
		for (EnemyShot& es : eshot) {
			if (es.IsActive()) {
				es.SetY(es.GetY() + es.GetSpeed().y);
			}

			// Colision shots with Player (death)
			if (es.IsActive()) {
				if (CheckCollisionRecs(es.GetRec(), player.GetRec())) {
					for (EnemyExplosion& e : eexplosion) {
						e.Activate({ player.GetX(), player.GetY() });
					}
					es.ChangeState(false);
					lives -= 1;
					PlaySound(fighter_killed);
					PlayMusicStream(game_over_music);
				}
			}

			// Despawn shot
			if (es.GetY() > screenHeight) {
				es.ChangeState(false);
			}
		}

		// Colision baby dons with Player (death)
		for (BabyDon& bd : babydons) {
			if (bd.IsActive()) {
				if (CheckCollisionRecs(bd.GetRec(), player.GetRec())) {
					for (EnemyExplosion& e : eexplosion) {
						e.Activate({ player.GetX(), player.GetY() });
					}
					bd.ChangeState(false);
					lives -= 1;
					PlaySound(fighter_killed);
					PlayMusicStream(game_over_music);
				}
			}
		}

		// Explosions
		for (PlayerExplosion& e : explosion) {
			e.UpdateAnimation(4, 6);
		}

		for (EnemyExplosion& e : eexplosion) {
			e.UpdateAnimation(4, 6);
		}

		//#-------#

		// Score

		if (score > highscore) {
			highscore = score;
		}

		// Win Condition
		if (CountEnemiesOnScreen() == 0 && level == LEVEL1) {
			level = LEVEL2;
			level2();
		}
		else if (CountEnemiesOnScreen() == 0 && level == LEVEL2) {
			inGame = false;
			victory = true;
			PlayMusicStream(victory_music);
		}

	}
}

void GameOver() {

	// Explosions
	for (PlayerExplosion& e : explosion) {
		e.UpdateAnimation(4, 6);
	}

	for (EnemyExplosion& e : eexplosion) {
		e.UpdateAnimation(4, 6);
	}

	UpdateMusicStream(game_over_music);
	if (IsKeyPressed(KEY_ENTER)) {
		gameOver = false;
		lives += 1;
		main_menu = true;
		soundPlayed = false;

		if (score > highscore) {
			highscore = besthighscore;
		}

		// Reset entities for next game
		lightning.SetPos(20 + 220, 70 - 220);
		lstate = NUMBER;
		enemy.SetX(0);
		player.SetX((screenWidth - 48) / 2);

		for (Shot& s : shot) {
			s.ChangeState(false);
			s.SetPos(-100, -100);
		}

		for (EnemyShot& es : eshot) {
			es.ChangeState(false);
			es.SetPos(-100, -100);
		}

		for (PlayerExplosion& e : explosion) {
			e.ChangeState(false);
			e.SetPos(-100, -100);
		}

		score = 0;
		Restart();

	}
}

void Victory() {
	UpdateMusicStream(victory_music);
	if (IsKeyPressed(KEY_ENTER)) {
		victory = false;
		lives += 1;
		main_menu = true;
		soundPlayed = false;

		if (score > highscore) {
			besthighscore = score;
		}

		// Reset entities for next game
		lightning.SetPos(20 + 220, 70 - 220);
		lstate = NUMBER;
		enemy.SetX(0);
		player.SetX((screenWidth - 48) / 2);

		for (Shot& s : shot) {
			s.ChangeState(false);
			s.SetPos(-100, -100);
		}

		for (EnemyShot& es : eshot) {
			es.ChangeState(false);
			es.SetPos(-100, -100);
		}

		score = 0;
		Restart();

	}
}

void Restart() {
	zakkos.clear();
	goeis.clear();
	dons.clear();
	babydons.clear();
	miniboss.clear();
	shot.clear();
	eshot.clear();

	level = LEVEL1;
	level1();
}

void Clear() {
	zakkos.clear();
	goeis.clear();
	dons.clear();
	babydons.clear();
	miniboss.clear();
	shot.clear();
	eshot.clear();
}

void level1() {

	player = Player(true, { ((screenWidth - 50) / 2), screenHeight - (screenHeight / 10), 64, 64 }, { 5, 5 }, WHITE);

	for (int i = 0; i < 10; ++i) {
		zakkos.push_back(Zakko({ i * 64.0f, 100, 64, 64 }, { 1.0f, 0 }, WHITE, true, 0, 0, 0));
	}

	for (int i = 0; i < 10; ++i) {
		dons.push_back(Don({ i * 64.0f, 300, 64, 64 }, { 1.0f, 0 }, WHITE, true, 0, 0, 0));
	}

	for (int i = 0; i < 50; ++i) {
		babydons.push_back(BabyDon({ -100, -100, 64, 64 }, { 1.0f, 7.5f }, WHITE, false, 0, 0, 0, 0));
	}

	for (int i = 0; i < 10; ++i) {
		miniboss.push_back(MiniBossGalaga({ i * 64.0f, 200, 64, 64 }, { 1.0f, 0 }, WHITE, true, 0, 0, 0, 2));
	}

	for (int i = 0; i < 50; ++i) {
		shot.push_back(PlayerShot({ -100, -100, 12, 24 }, { 0, 10 }, WHITE, false));
	}

	for (int i = 0; i < 50; ++i) {
		eshot.push_back(EnemyShot({ -100, -100, 12, 24 }, { 0, 10 }, WHITE, false, 0, 0));
	}

	for (int i = 0; i < 50; ++i) {
		explosion.push_back(PlayerExplosion({ -100, -100, 12, 24 }, { 0, 0 }, WHITE, false, 0, 0));
	}

	for (int i = 0; i < 50; ++i) {
		eexplosion.push_back(EnemyExplosion({ -100, -100, 0, 0 }, { 0, 0 }, WHITE, false, 0, 0));
	}
}

void level2() {

	for (int i = 0; i < 10; ++i) {
		goeis.push_back(Goei({ i * 64.0f, 400, 64, 64 }, { 1.0f, 0 }, WHITE, true, 0, 0, 0));
	}

	for (int i = 0; i < 50; ++i) {
		shot.push_back(PlayerShot({ -100, -100, 12, 24 }, { 0, 10 }, WHITE, false));
	}

	for (int i = 0; i < 50; ++i) {
		explosion.push_back(PlayerExplosion({ -100, -100, 12, 24 }, { 0, 0 }, WHITE, false, 0, 0));
	}

	for (int i = 0; i < 50; ++i) {
		eexplosion.push_back(EnemyExplosion({ -100, -100, 0, 0 }, { 0, 0 }, WHITE, false, 0, 0));
	}

}

void Stage0() {

	player = Player(true, { ((screenWidth - 50) / 2), screenHeight - (screenHeight / 10), 64, 64 }, { 5, 5 }, WHITE);

	for (int i = 0; i < 10; ++i) {
		zakkos.push_back(Zakko({ i * 64.0f, 100, 64, 64 }, { 1.0f, 0 }, WHITE, true, 0, 0, 0));
	}

	for (int i = 0; i < 10; ++i) {
		dons.push_back(Don({ i * 64.0f, 300, 64, 64 }, { 1.0f, 0 }, WHITE, true, 0, 0, 0));
	}

	for (int i = 0; i < 50; ++i) {
		babydons.push_back(BabyDon({ -100, -100, 64, 64 }, { 1.0f, 7.5f }, WHITE, false, 0, 0, 0, 0));
	}

	for (int i = 0; i < 10; ++i) {
		miniboss.push_back(MiniBossGalaga({ i * 64.0f, 200, 64, 64 }, { 1.0f, 0 }, WHITE, true, 0, 0, 0, 2));
	}

	for (int i = 0; i < 10; ++i) {
		goeis.push_back(Goei({ i * 64.0f, 400, 64, 64 }, { 1.0f, 0 }, WHITE, true, 0, 0, 0));
	}

	for (int i = 0; i < 50; ++i) {
		shot.push_back(PlayerShot({ -100, -100, 12, 24 }, { 0, 10 }, WHITE, false));
	}

	for (int i = 0; i < 50; ++i) {
		eshot.push_back(EnemyShot({ -100, -100, 12, 24 }, { 0, 10 }, WHITE, false, 0, 0));
	}

	for (int i = 0; i < 50; ++i) {
		explosion.push_back(PlayerExplosion({ -100, -100, 12, 24 }, { 0, 0 }, WHITE, false, 0, 0));
	}

	for (int i = 0; i < 50; ++i) {
		eexplosion.push_back(EnemyExplosion({ -100, -100, 0, 0 }, { 0, 0 }, WHITE, false, 0, 0));
	}
}

int CountEnemiesOnScreen() {
	activeEnemies = 0;

	for (Zakko& z : zakkos) {
		if (z.IsActive()) activeEnemies++;
	}

	for (Goei& g : goeis) {
		if (g.IsActive()) activeEnemies++;
	}

	for (Don& d : dons) {
		if (d.IsActive()) activeEnemies++;
	}

	for (BabyDon& bd : babydons) {
		if (bd.IsActive()) activeEnemies++;
	}

	for (MiniBossGalaga& mbg : miniboss) {
		if (mbg.IsActive()) activeEnemies++;
	}

	return activeEnemies;
}

void GameCheats() {
	if (IsKeyPressed(KEY_O)) {
		showCollisions = !showCollisions;
	}

	if (IsKeyPressed(KEY_I)) {
		lives += 1;
	}

	if (IsKeyPressed(KEY_ONE)) {
		gameOver = false;
		pause = false;
		victory = false;
		main_menu = true;
		credits = false;
		launchSequence = false;
		inGame = false;
	}
	if (IsKeyPressed(KEY_TWO)) {
		gameOver = false;
		pause = false;
		victory = false;
		main_menu = false;
		credits = true;
		launchSequence = false;
		inGame = false;
	}
	if (IsKeyPressed(KEY_THREE)) {
		gameOver = false;
		pause = false;
		victory = false;
		main_menu = false;
		credits = false;
		launchSequence = true;
		inGame = false;
	}
	if (IsKeyPressed(KEY_FOUR)) {
		gameOver = false;
		pause = false;
		victory = false;
		main_menu = false;
		credits = false;
		launchSequence = false;
		inGame = true;
		level = LEVEL1;
		Clear();
		level1();
	}
	if (IsKeyPressed(KEY_FIVE)) {
		gameOver = false;
		pause = false;
		victory = false;
		main_menu = false;
		credits = false;
		launchSequence = false;
		inGame = true;
		level = LEVEL2;
		Clear();
		level2();
	}
	if (IsKeyPressed(KEY_SIX)) {
		gameOver = true;
		pause = false;
		victory = false;
		main_menu = false;
		credits = false;
		launchSequence = false;
		inGame = false;
	}
	if (IsKeyPressed(KEY_SEVEN)) {
		gameOver = false;
		pause = false;
		victory = true;
		main_menu = false;
		credits = false;
		launchSequence = false;
		inGame = false;
	}
	if (IsKeyPressed(KEY_EIGHT)) {
		gameOver = false;
		pause = false;
		victory = false;
		main_menu = false;
		credits = false;
		launchSequence = false;
		inGame = true;
		level = STAGE0;
		Clear();
		Stage0();
	}
}

/*

MIT License

	Copyright (c) 2025 Repeaters Studio - Galaga 88.

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.

*/
