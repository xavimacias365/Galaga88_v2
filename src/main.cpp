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

int score;
int highscore;
int shootRate;
int shootRate2;
int activeEnemies;
int enemieskill;
int currentMusic;
int blink;

const char* main_menu_text_start;

// functions
void LoadGame();
void InitGame();
void UpdateGame();
//void DrawGame();
void UnloadGame();
void UpdateDrawFrame();


int main () {
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(screenWidth, screenHeight, "Galaga88");

	InitAudioDevice();
	LoadGame();
	InitGame();
	SetTargetFPS(60);

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	Texture wabbit = LoadTexture("wabbit_alpha.png");

	// game loop
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		UpdateDrawFrame();
	}

	// cleanup
	// unload our texture so it can be cleaned up
	UnloadTexture(wabbit);

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}

void InitGame() {

	// global variables
	bool gameOver = false;
	bool pause = false;
	bool victory = false;
	bool main_menu = true;
	bool credits = false;
	bool launchSequence = false;
	bool inGame = false;

	int score = 0;
	int shootRate = 0;
	int shootRate2 = 0;
	int activeEnemies = 0;
	int enemieskill = 0;
	int currentMusic = 0;
	int blink = 0;

	const char* main_menu_text_start = "TO START PRESS < ENTER >!";

	//Player player /*= { 0 }*/;
	//Shot shot[50] /*= { 0 }*/;
	//Enemy enemy[10] /*= { 0 }*/;
	//EnemyShot e_shoot[50] /*= { 0 }*/;

// Player
	Player player;
	player.SetX(420);
	player.SetY(900);

}

void UpdateGame() {
	if (main_menu == true) {

		UpdateMusicStream(main_menu_music);

		blink++;
		if (blink >= 90) {
			blink = 0;
		}

		if (IsKeyPressed(KEY_ENTER)) {
			main_menu = false;
			credits = true;
		}
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

	if (main_menu == true) {
		DrawTextureEx(main_menu_background, { 0, 0 }, 0.0f, ((float)screenWidth / main_menu_background.width, (float)screenHeight / main_menu_background.height), WHITE);
		DrawTextureEx(main_menu_logo, { (screenWidth - (main_menu_logo.width * fminf((800.0f / main_menu_logo.width), (400.0f / main_menu_logo.height)))) / 2.0f, ((screenHeight / 4.0f) - (main_menu_logo.height - fminf((800.0f / main_menu_logo.width), (400.0f / main_menu_logo.height)))) }, 0.0f, fminf((800.0f / main_menu_logo.width), (400.0f / main_menu_logo.height)), WHITE);
		DrawText("TO START PRESS [ENTER]!", (screenWidth - MeasureText("TO START PRESS [ENTER]!", fontSize)) / 2, (screenHeight - (screenHeight / 3)), fontSize, GREEN);
		if (blink >= 0 && blink <= 40) { DrawText("INSERT COIN", (screenWidth - MeasureText("INSERT COIN", fontSize)) / 2, (screenHeight - ((screenHeight / 3) + 50)), fontSize, GREEN); }
		DrawText("© 1981 1987 NAMCO", (screenWidth - MeasureText("© 1981 1987 NAMCO", fontSize)) / 2, 806, fontSize, WHITE);
		DrawText("ALL RIGHTS RESERVED", (screenWidth - MeasureText("ALL RIGHTS RESERVED", fontSize)) / 2, 867, fontSize, WHITE); // (X) 150
		DrawTextureEx(main_menu_namco, { 290, 959 }, 0.0f, (main_menu_namco.width / 32, main_menu_namco.height / 32), WHITE);
	}
	else if (credits == true) {
		DrawTextureEx(credits_screen, { 0, 0 }, 0.0f, ((float)screenWidth / credits_screen.width, (float)screenHeight / credits_screen.height), WHITE);
		DrawText("PRESS [ENTER] TO CONTINUE!", (screenWidth - MeasureText("PRESS [ENTER] TO CONTINUE", fontSize)) / 2, (screenHeight / 4) - 50, fontSize, GREEN);
	}

	// end the frame and get ready for the next one  (display frame, poll input, etc...)
	EndDrawing();
}

void UpdateDrawFrame() {
	UpdateGame();
	DrawGame();
}
