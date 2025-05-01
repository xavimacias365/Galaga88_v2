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

// global variables
bool gameOver;
bool pause;
bool victory;
bool main_menu;
bool credits;

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
	InitWindow(1280, 800, "Galaga88");

	InitAudioDevice();
	LoadGame();
	InitGame();
	SetTargetFPS(60);

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// Load a texture from the resources directory
	Texture wabbit = LoadTexture("wabbit_alpha.png");
	
	// game loop
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		// drawing
		BeginDrawing();

		UpdateDrawFrame();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);

		// draw some text using the default font
		DrawText("Hello Raylib", 200,200,20,WHITE);

		// draw our texture to the screen
		DrawTexture(wabbit, 400, 200, WHITE);
		
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
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

void UpdateDrawFrame() {
	UpdateGame();
	//DrawGame();
}
