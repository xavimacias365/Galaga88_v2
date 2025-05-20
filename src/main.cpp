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

// global variables
bool gameOver;
bool pause;
bool victory;
bool main_menu = 1;
bool credits;
bool launchSequence;
bool inGame;
enum LevelStage { LEVEL1, LEVEL2 };
LevelStage level = LEVEL1;

int score;
int highscore;
int shotRate;
int shotRate2;
int activeEnemies;
int enemieskill;
int currentMusic;
int blink;
float alpha;

const char* main_menu_text_start;

enum LightningState { NUMBER, MOVING, FLASH, FINISH };
LightningState lstate = NUMBER;

MainMenuEnemy enemy;
MainMenuLightning lightning;
vector<Zakko> zakkos;
Player player;
vector<PlayerShot> shot;

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

//	Texture wabbit = LoadTexture("wabbit_alpha.png");

	// game loop
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		UpdateDrawFrame();
	}

	// cleanup
	// unload our texture so it can be cleaned up
//	UnloadTexture(wabbit);

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}

void InitGame() {

	// global variables
	gameOver = false;
	pause = false;
	victory = false;
	main_menu = true;
	credits = false;
	launchSequence = false;
	inGame = false;

	score = 0;
	shotRate = 0;
	shotRate2 = 0;
	activeEnemies = 0;
	enemieskill = 0;
	currentMusic = 0;
	blink = 0;
	alpha = 0.0f;

	main_menu_text_start = "TO START PRESS < ENTER >!";

	enemy = MainMenuEnemy({ 0, 555, 64, 64 }, { 5, 0 }, WHITE, true, 0, 0, 0, 0);
	lightning = MainMenuLightning({ 20 + 200, 70 - 200, 64, 64 }, { 5, 5 }, WHITE, true, 0, 0, 0, 0);

	for (int i = 0; i < 10; ++i) {
		zakkos.push_back(Zakko({ i * 64.0f, 100, 32, 32 }, { 1.0f, 0 }, WHITE, true, 0, 0, 0, 0));
	}

	player = Player({ ((screenWidth - 48) / 2), screenHeight - (screenHeight / 10), 64, 64 }, { 5, 5 }, WHITE);
	
	for (int i = 0; i < 50; ++i) {
		shot.push_back(PlayerShot({player.GetRec().x + player.GetRec().width / 2, player.GetRec().y, 5, 10}, {0, 10}, WHITE, false));
	}

// Player
	Player player;
	player.SetX(420);
	player.SetY(900);

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
}

void DrawGame() {

// Drawing
	BeginDrawing();
	// Setup the back buffer for drawing (clear color and depth buffers)
	ClearBackground(BLACK);

	// Load a texture from the resources directory
//	Texture wabbit = LoadTexture("wabbit_alpha.png");

	// draw some text using the default font
//	DrawText("Hello Raylib", 200, 200, 20, WHITE);

	// draw our texture to the screen
//	DrawTexture(wabbit, 400, 200, WHITE);

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
		DrawTextureEx(main_menu_enemy, { enemy.GetX(), enemy.GetY() }, 0.0f, (float)screenWidth / (float) main_menu_background.width, WHITE);
	}
	else if (credits == true) {
		DrawTextureEx(credits_screen, { 0, 0 }, 0.0f, ((float)screenWidth / credits_screen.width, (float)screenHeight / credits_screen.height), WHITE);
		DrawText("PRESS [ENTER] TO CONTINUE!", (screenWidth - MeasureText("PRESS [ENTER] TO CONTINUE!", fontSize)) / 2, (screenHeight / 4) - 50, fontSize, GREEN);
	}
	else if (launchSequence == true) {
		DrawTextureEx(launch_background, { 0,0 }, 0.0f, ((float)screenWidth / credits_screen.width, (float)screenHeight / credits_screen.height), WHITE);

		DrawTextureEx(player_sprite, { player.GetX(), player.GetY() }, 0.0f, (float)screenWidth / (float)main_menu_background.width, WHITE);
	}
	else if (inGame == true && level == LEVEL1) {

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
		DrawTextureEx(player_sprite, { player.GetX(), player.GetY() }, 0.0f, (float)screenWidth / (float)main_menu_background.width, WHITE);

		// Draw Zakko Enemies
		for (const Zakko& z : zakkos) {
			if (z.IsActive()) {
				sourceRec = { 0.0f, z.GetCurrentFrame() * 16.0f, 16.0f, 16.0f };
				DrawTexturePro(zakko_sprite, sourceRec, Rectangle { z.GetX(), z.GetY(), sourceRec.width * scale, sourceRec.height * scale }, { 0, 0 }, 0.0f, WHITE);
			}
		}

		// Draw Player Shoots
		for (const Shot& s : shot) {
			if (s.IsActive()) {
<<<<<<< Updated upstream
				DrawTexturePro(shot_sprite, sourceRec, Rectangle{ s.GetX(), s.GetY(), sourceRec.width * scale, sourceRec.height * scale }, { 0, 0 }, 0.0f, WHITE);
=======
				//DrawTexturePro(shot_sprite, sourceRec, Rectangle{ s.GetX(), s.GetY(), sourceRec.width * scale, sourceRec.height * scale }, { 0, 0 }, 0.0f, WHITE);
				DrawTextureEx(shot_sprite, { s.GetX()-29.0f, s.GetY()-38.0f }, 0.0f, scale, WHITE);
>>>>>>> Stashed changes
			}
		}
	}

	if (pause == true) {
		DrawText("GAME PAUSED!", (screenWidth - MeasureText("GAME PAUSED!", fontSize)) / 2, screenHeight - 137, fontSize, RED);
	}

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
	
	if (IsKeyPressed(KEY_ENTER) || player.GetY() <= -screenHeight) {
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
			shotRate += 5;

			for (Shot& s : shot) {
				if (s.IsActive() == 0 && shotRate % 35 == 0) {
					s.SetX((player.GetX() + player.GetRec().width / 2) - 3);
					s.SetY(player.GetY());
					s.ChangeState(true);
					PlaySound(fighter_shot);
					break;
				}
			}
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

		//#-------#

		// Shot Behaviour
		for (Shot& s : shot) {
			if (s.IsActive()) {
				s.SetY(s.GetSpeed().y);
			}

		// Colision with enemy


		// Despawn shot
			if (s.GetY() <= 0) {
				s.ChangeState(false);
			}
		}
	}
}
