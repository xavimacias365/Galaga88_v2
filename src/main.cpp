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
enum LevelStage { LEVEL1, LEVEL2 };
LevelStage level = LEVEL1;

bool showCollisions;

int score;
int highscore;
int lives;
int activeEnemies;
int currentMusic;
int blink;
float alpha;

const char* main_menu_text_start;

enum LightningState { NUMBER, MOVING, FLASH, FINISH };
LightningState lstate = NUMBER;

MainMenuEnemy enemy;
MainMenuLightning lightning;
vector<Zakko> zakkos;
vector<Don> dons;
vector<Goei> goeis;
Player player;
vector<PlayerShot> shot;
vector<EnemyShot> eshot;

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

void level1();
void level2();

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
	lives = 1;
	activeEnemies = 0;
	currentMusic = 0;
	blink = 0;
	alpha = 0.0f;

	main_menu_text_start = "TO START PRESS < ENTER >!";

	enemy = MainMenuEnemy({ 0, 555, 64, 64 }, { 5, 0 }, WHITE, true, 0, 0, 0);
	lightning = MainMenuLightning({ 20 + 220, 70 - 220, 64, 64 }, { 5, 5 }, WHITE, true, 0, 0, 0);

	player = Player({ ((screenWidth - 50) / 2), screenHeight - (screenHeight / 10), 64, 64 }, { 5, 5 }, WHITE);

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

		// Logo animation
		if (lstate == NUMBER) {
			if (alpha < 1.0f) {
				alpha += 0.01f;
				if (alpha > 1.0f) alpha = 1.0f;

				Color fadeColor = { 255, 255, 255, (unsigned char)(alpha * 255) };
				DrawTextureEx(main_menu_logo1, { (screenWidth - (main_menu_logo.width * fminf((800.0f / main_menu_logo.width), (400.0f / main_menu_logo.height)))) / 2.0f, (screenHeight / 4.0f) - ((main_menu_logo.height * fminf((800.0f / main_menu_logo.width), (400.0f / main_menu_logo.height))) / 2.0f) }, 0.0f, fminf((800.0f / main_menu_logo.width), (400.0f / main_menu_logo.height)), fadeColor);
				//fadeColor = Fade(WHITE, alpha);
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
		
		DrawText("TO START PRESS [ENTER]!", (screenWidth - MeasureText("TO START PRESS [ENTER]!", fontSize)) / 2, (screenHeight - (screenHeight / 3)), fontSize, GREEN);
		if (blink >= 0 && blink <= 40) { DrawText("INSERT COIN", (screenWidth - MeasureText("INSERT COIN", fontSize)) / 2, (screenHeight - ((screenHeight / 3) + 50)), fontSize, GREEN); }
		DrawText("© 1981 1987 NAMCO", (screenWidth - MeasureText("© 1981 1987 NAMCO", fontSize)) / 2, 806, fontSize, WHITE);
		DrawText("ALL RIGHTS RESERVED", (screenWidth - MeasureText("ALL RIGHTS RESERVED", fontSize)) / 2, 867, fontSize, WHITE); // (X) 150
		DrawTextureEx(main_menu_namco, { ((screenWidth - main_menu_namco.width) / 2.0f), screenHeight - (screenHeight / 10) }, 0.0f, (main_menu_namco.width / 32, main_menu_namco.height / 32), WHITE);

		DrawTextureEx(main_menu_logo_lightning, { lightning.GetX(), lightning.GetY() }, 0.0f, fminf((800.0f / main_menu_logo.width), (400.0f / main_menu_logo.height)), WHITE);
		DrawTexturePro(main_menu_enemy, sourceRec, enemy.GetRec(), { 0, 0 }, 0.0f, WHITE);

	}
	else if (credits == true) {
		DrawTextureEx(credits_screen, { 0, 0 }, 0.0f, ((float)screenWidth / credits_screen.width, (float)screenHeight / credits_screen.height), WHITE);
		DrawText("PRESS [ENTER] TO CONTINUE!", (screenWidth - MeasureText("PRESS [ENTER] TO CONTINUE!", fontSize)) / 2, (screenHeight / 4) - 50, fontSize, GREEN);
	}
	else if (launchSequence == true) {
		DrawTextureEx(launch_background, { 0,0 }, 0.0f, ((float)screenWidth / credits_screen.width, (float)screenHeight / credits_screen.height), WHITE);
		DrawTexturePro(player_sprite, sourceRec, player.GetRec(), { 0, 0 }, 0.0f, WHITE);

	}
	else if (inGame == true || gameOver == true && level == LEVEL1) {

		DrawTextureEx(level3_background, { 0, 0 }, 0.0f, ((float)screenWidth / credits_screen.width, (float)screenHeight / credits_screen.height), WHITE);

		if (alpha < 1.0f) {
			alpha += 0.01f;
			if (alpha > 1.0f) alpha = 1.0f;

			Color fadeColor = { 255, 255, 255, (unsigned char)(alpha * 255) };
			DrawTextureEx(level1_background, { 0, 0 }, 0.0f, ((float)screenWidth / credits_screen.width, (float)screenHeight / credits_screen.height), fadeColor);
		}
		else {
			Color fadeColor = WHITE;
			DrawTextureEx(level1_background, { 0, 0 }, 0.0f, ((float)screenWidth / credits_screen.width, (float)screenHeight / credits_screen.height), fadeColor);
		}
		
		// Draw Player
		DrawTexturePro(player_sprite, sourceRec, player.GetRec(), { 0, 0 }, 0.0f, WHITE);

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
	}

	if (gameOver == true) {
		DrawText("GAME OVER!", (screenWidth - MeasureText("GAME OVER!", fontSize)) / 2, (screenHeight / 2) - fontSize, fontSize, RED);
		DrawText("PRESS [ENTER] TO PLAY AGAIN", (screenWidth - MeasureText("PRESS [ENTER] TO PLAY AGAIN", fontSize)) / 2, (screenHeight / 2) + fontSize, fontSize, RED);
	}

	if (victory == true) {
		DrawTextureEx(win_screen, { 0, 0 }, 0.0f, ((float)screenWidth / credits_screen.width, (float)screenHeight / credits_screen.height), WHITE);
		DrawText("PRESS [ENTER] TO PLAY AGAIN", (screenWidth - MeasureText("PRESS [ENTER] TO PLAY AGAIN", fontSize)) / 2, screenHeight - fontSize * 2, fontSize, RED);
	}

	if (pause == true) {
		DrawText("GAME PAUSED!", (screenWidth - MeasureText("GAME PAUSED!", fontSize)) / 2, screenHeight - 137, fontSize, RED);
	}

	if (showCollisions == true) {
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

	if (player.GetY() > -screenHeight) {
		player.SetY(player.GetY() - player.GetSpeed().y);
	}
	
	if (IsKeyPressed(KEY_ENTER) || player.GetY() <= -screenHeight  / 2) {
		launchSequence = false;
		inGame = true;
		player.SetY(screenHeight - (screenHeight / 5));
	}

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
			gameOver = true;
			inGame = false;
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
				z.SetShot(rand() % 100);

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

					// Score
						score += 100;
						if (score > highscore) {
							highscore = score;
						}
					}
				}
			}

			for (Goei& g : goeis) {
				if (g.IsActive() && s.IsActive()) {
					if (CheckCollisionRecs(s.GetRec(), g.GetRec())) {
						s.ChangeState(false);
						g.ChangeState(false);
						PlaySound(enemy_killed);

						// Score
						score += 50;
						if (score > highscore) {
							highscore = score;
						}
					}
				}
			}

			for (Don& d : dons) {
				if (d.IsActive() && s.IsActive()) {
					if (CheckCollisionRecs(s.GetRec(), d.GetRec())) {
						s.ChangeState(false);
						d.ChangeState(false);
						PlaySound(enemy_killed);

						// Score
						score += 50;
						if (score > highscore) {
							highscore = score;
						}
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

			// Colision with Player (death)
			if (es.IsActive()) {
				if (CheckCollisionRecs(es.GetRec(), player.GetRec())) {
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

		//#-------#

		// Win Condition
		if (score == 1500) {
			inGame = false;
			victory = true;
			PlayMusicStream(victory_music);
		}

	}
}

void GameOver() {
	UpdateMusicStream(game_over_music);
	if (IsKeyPressed(KEY_ENTER)) {
		gameOver = false;
		lives += 1;
		main_menu = true;

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

void Victory() {
	UpdateMusicStream(victory_music);
	if (IsKeyPressed(KEY_ENTER)) {
		victory = false;
		lives += 1;
		main_menu = true;

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
	shot.clear();
	eshot.clear();

	level1();
}

void level1() {

	player = Player({ ((screenWidth - 50) / 2), screenHeight - (screenHeight / 10), 64, 64 }, { 5, 5 }, WHITE);

	for (int i = 0; i < 10; ++i) {
		zakkos.push_back(Zakko({ i * 64.0f, 100, 64, 64 }, { 1.0f, 0 }, WHITE, true, 0, 0, 0));
	}

	for (int i = 0; i < 10; ++i) {
		dons.push_back(Don({ i * 64.0f, 300, 64, 64 }, { 1.0f, 0 }, WHITE, true, 0, 0, 0));
	}

	for (int i = 0; i < 50; ++i) {
		shot.push_back(PlayerShot({ (player.GetRec().x + player.GetRec().width) / 2, player.GetRec().y, 12, 24 }, { 0, 10 }, WHITE, false));
	}

	for (int i = 0; i < 50; ++i) {
		eshot.push_back(EnemyShot({ (enemy.GetRec().x + enemy.GetRec().width) / 2, enemy.GetRec().y, 12, 24 }, { 0, 10 }, WHITE, false, 0, 0));
	}
}

void level2() {

	player = Player({ ((screenWidth - 50) / 2), screenHeight - (screenHeight / 10), 64, 64 }, { 5, 5 }, WHITE);

	for (int i = 0; i < 10; ++i) {
		goeis.push_back(Goei({ i * 64.0f, 200, 64, 64 }, { 1.0f, 0 }, WHITE, true, 0, 0, 0));
	}

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
	}
	if (IsKeyPressed(KEY_FIVE)) {
		gameOver = true;
		pause = false;
		victory = false;
		main_menu = false;
		credits = false;
		launchSequence = false;
		inGame = false;
	}
}
