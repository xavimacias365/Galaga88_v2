
#include "draw.h"

//void DrawGame() {
//
//	// Drawing
//	BeginDrawing();
//	// Setup the back buffer for drawing (clear color and depth buffers)
//	ClearBackground(BLACK);
//
//	// Draw Main Menu
//		// CENTER IMG FORMULA -> (screenWidth - myImage.width) / 2
//		// CENTER TEXT FORMULA -> (screenWidth - MeasureText("TEXT", fontSize)) / 2		FONT SIZE = 37
//		// CORRECT IMG SCALE -> (screenWidth - myImage.width * fminf((desiredWidth / myImage.width), (desiredHeight / myImage.height)) / 2.0f)
//
//	Rectangle sourceRec = { 0.0f, 0.0f, 16.0f,  16.0f };
//	float scale = (float)screenWidth / (float)main_menu_background.width;
//
//	if (main_menu == true) {
//		DrawTextureEx(main_menu_background, { 0, 0 }, 0.0f, ((float)screenWidth / main_menu_background.width, (float)screenHeight / main_menu_background.height), WHITE);
//		DrawTextureEx(main_menu_logo0, { (screenWidth - (main_menu_logo.width * fminf((800.0f / main_menu_logo.width), (400.0f / main_menu_logo.height)))) / 2.0f, (screenHeight / 4.0f) - ((main_menu_logo.height * fminf((800.0f / main_menu_logo.width), (400.0f / main_menu_logo.height))) / 2.0f) }, 0.0f, fminf((800.0f / main_menu_logo.width), (400.0f / main_menu_logo.height)), WHITE);
//
//		// Logo animation
//		if (lstate == NUMBER) {
//			if (alpha < 1.0f) {
//				alpha += 0.01f;
//				if (alpha > 1.0f) alpha = 1.0f;
//
//				Color fadeColor = { 255, 255, 255, (unsigned char)(alpha * 255) };
//				DrawTextureEx(main_menu_logo1, { (screenWidth - (main_menu_logo.width * fminf((800.0f / main_menu_logo.width), (400.0f / main_menu_logo.height)))) / 2.0f, (screenHeight / 4.0f) - ((main_menu_logo.height * fminf((800.0f / main_menu_logo.width), (400.0f / main_menu_logo.height))) / 2.0f) }, 0.0f, fminf((800.0f / main_menu_logo.width), (400.0f / main_menu_logo.height)), fadeColor);
//				//fadeColor = Fade(WHITE, alpha);
//			}
//
//			if (alpha >= 1.0f) {
//				lstate = MOVING;
//				alpha = 0.0f;
//			}
//		}
//		else if (lstate == MOVING) {
//			DrawTextureEx(main_menu_logo1, { (screenWidth - (main_menu_logo.width * fminf((800.0f / main_menu_logo.width), (400.0f / main_menu_logo.height)))) / 2.0f, (screenHeight / 4.0f) - ((main_menu_logo.height * fminf((800.0f / main_menu_logo.width), (400.0f / main_menu_logo.height))) / 2.0f) }, 0.0f, fminf((800.0f / main_menu_logo.width), (400.0f / main_menu_logo.height)), WHITE);
//
//			if (lightning.GetX() == 20 && lightning.GetY() == 70) {
//				lstate = FLASH;
//			}
//
//		}
//		else if (lstate == FLASH) {
//			lightning.SetX(lightning.GetX() + 500);
//			lightning.SetY(lightning.GetY() - 500);
//
//			DrawTextureEx(main_menu_logo2, { (screenWidth - (main_menu_logo.width * fminf((800.0f / main_menu_logo.width), (400.0f / main_menu_logo.height)))) / 2.0f, (screenHeight / 4.0f) - ((main_menu_logo.height * fminf((800.0f / main_menu_logo.width), (400.0f / main_menu_logo.height))) / 2.0f) }, 0.0f, fminf((800.0f / main_menu_logo.width), (400.0f / main_menu_logo.height)), WHITE);
//
//			lstate = FINISH;
//
//		}
//		else if (lstate == FINISH) {
//			DrawTextureEx(main_menu_logo, { (screenWidth - (main_menu_logo.width * fminf((800.0f / main_menu_logo.width), (400.0f / main_menu_logo.height)))) / 2.0f, (screenHeight / 4.0f) - ((main_menu_logo.height * fminf((800.0f / main_menu_logo.width), (400.0f / main_menu_logo.height))) / 2.0f) }, 0.0f, fminf((800.0f / main_menu_logo.width), (400.0f / main_menu_logo.height)), WHITE);
//
//		}
//
//		DrawText("TO START PRESS [ENTER]!", (screenWidth - MeasureText("TO START PRESS [ENTER]!", fontSize)) / 2, (screenHeight - (screenHeight / 3)), fontSize, GREEN);
//		if (blink >= 0 && blink <= 40) { DrawText("INSERT COIN", (screenWidth - MeasureText("INSERT COIN", fontSize)) / 2, (screenHeight - ((screenHeight / 3) + 50)), fontSize, GREEN); }
//		DrawText("© 1981 1987 NAMCO", (screenWidth - MeasureText("© 1981 1987 NAMCO", fontSize)) / 2, 806, fontSize, WHITE);
//		DrawText("ALL RIGHTS RESERVED", (screenWidth - MeasureText("ALL RIGHTS RESERVED", fontSize)) / 2, 867, fontSize, WHITE); // (X) 150
//		DrawTextureEx(main_menu_namco, { ((screenWidth - main_menu_namco.width) / 2.0f), screenHeight - (screenHeight / 10) }, 0.0f, (main_menu_namco.width / 32, main_menu_namco.height / 32), WHITE);
//
//		DrawTextureEx(main_menu_logo_lightning, { lightning.GetX(), lightning.GetY() }, 0.0f, fminf((800.0f / main_menu_logo.width), (400.0f / main_menu_logo.height)), WHITE);
//		DrawTexturePro(main_menu_enemy, sourceRec, enemy.GetRec(), { 0, 0 }, 0.0f, WHITE);
//
//	}
//	else if (credits == true) {
//		DrawTextureEx(credits_screen, { 0, 0 }, 0.0f, ((float)screenWidth / credits_screen.width, (float)screenHeight / credits_screen.height), WHITE);
//		DrawText("PRESS [ENTER] TO CONTINUE!", (screenWidth - MeasureText("PRESS [ENTER] TO CONTINUE!", fontSize)) / 2, (screenHeight / 4) - 50, fontSize, GREEN);
//	}
//	else if (launchSequence == true) {
//		DrawTextureEx(launch_background, { 0,0 }, 0.0f, ((float)screenWidth / credits_screen.width, (float)screenHeight / credits_screen.height), WHITE);
//		DrawTexturePro(player_sprite, sourceRec, player.GetRec(), { 0, 0 }, 0.0f, WHITE);
//
//	}
//	else if (inGame == true || gameOver == true && level == LEVEL1) {
//
//		DrawTextureEx(level3_background, { 0, 0 }, 0.0f, ((float)screenWidth / credits_screen.width, (float)screenHeight / credits_screen.height), WHITE);
//
//		if (alpha < 1.0f) {
//			alpha += 0.01f;
//			if (alpha > 1.0f) alpha = 1.0f;
//
//			Color fadeColor = { 255, 255, 255, (unsigned char)(alpha * 255) };
//			DrawTextureEx(level1_background, { 0, 0 }, 0.0f, ((float)screenWidth / credits_screen.width, (float)screenHeight / credits_screen.height), fadeColor);
//		}
//		else {
//			Color fadeColor = WHITE;
//			DrawTextureEx(level1_background, { 0, 0 }, 0.0f, ((float)screenWidth / credits_screen.width, (float)screenHeight / credits_screen.height), fadeColor);
//		}
//
//		// Draw Player
//		if (player.IsActive()) { DrawTexturePro(player_sprite, sourceRec, player.GetRec(), { 0, 0 }, 0.0f, WHITE); }
//
//		// Draw Zakko Enemies
//		for (const Zakko& z : zakkos) {
//			if (z.IsActive()) {
//				sourceRec = { 0.0f, z.GetCurrentFrame() * 16.0f, 16.0f, 16.0f };
//				DrawTexturePro(zakko_sprite, sourceRec, z.GetRec(), { 0, 0 }, 0.0f, WHITE);
//			}
//		}
//
//		// Draw Goei Enemies
//		for (const Goei& g : goeis) {
//			if (g.IsActive()) {
//				sourceRec = { 0.0f, g.GetCurrentFrame() * 16.0f, 16.0f, 16.0f };
//				DrawTexturePro(goei_sprite, sourceRec, g.GetRec(), { 0, 0 }, 0.0f, WHITE);
//			}
//		}
//
//		// Draw Don Enemies
//		for (const Don& d : dons) {
//			if (d.IsActive()) {
//				sourceRec = { 0.0f, d.GetCurrentFrame() * 16.0f, 16.0f, 16.0f };
//				switch (d.GetVariant()) {
//				case 0: DrawTexturePro(don1_sprite, sourceRec, d.GetRec(), { 0, 0 }, 0.0f, WHITE); break;
//				case 1: DrawTexturePro(don2_sprite, sourceRec, d.GetRec(), { 0, 0 }, 0.0f, WHITE); break;
//				case 2:	DrawTexturePro(don3_sprite, sourceRec, d.GetRec(), { 0, 0 }, 0.0f, WHITE); break;
//				case 3:	DrawTexturePro(don4_sprite, sourceRec, d.GetRec(), { 0, 0 }, 0.0f, WHITE); break;
//				}
//			}
//		}
//
//		// Draw Player Shoots
//		for (const Shot& s : shot) {
//			if (s.IsActive()) {
//				sourceRec = { 0.0f, 0.0f, 16.0f,  16.0f };
//				Rectangle dest = { s.GetX() - (sourceRec.width * scale - s.GetRec().width) / 2, s.GetY() - (sourceRec.height * scale - s.GetRec().height) / 2, sourceRec.width * scale, sourceRec.height * scale };
//				DrawTexturePro(shot_sprite, sourceRec, dest, { 0, 0 }, 0.0f, WHITE);
//			}
//		}
//
//		// Draw Enemy Shoots
//		for (const EnemyShot& es : eshot) {
//			if (es.IsActive()) {
//				sourceRec = { 0.0f, es.GetCurrentFrame() * 16.0f, 16.0f, 16.0f };
//				Rectangle dest = { es.GetX() - (sourceRec.width * scale - es.GetRec().width) / 2, es.GetY() - (sourceRec.height * scale - es.GetRec().height) / 2, sourceRec.width * scale, sourceRec.height * scale };
//				DrawTexturePro(zakko_shot_sprite, sourceRec, dest, { 0, 0 }, 0.0f, WHITE);
//			}
//		}
//
//		// Draw Player Explosion
//		for (const PlayerExplosion& e : explosion) {
//			if (e.IsActive()) {
//				sourceRec = { 0.0f, e.GetCurrentFrame() * 32.0f, 32.0f, 32.0f };
//				Rectangle dest = { e.GetX(), e.GetY(), 64, 64 };
//				DrawTexturePro(enemy_explosion, sourceRec, dest, { 0, 0 }, 0.0f, WHITE);
//				//DrawTexturePro(enemy_explosion, sourceRec, e.GetRec(), { 0, 0 }, 0.0f, WHITE);
//			}
//		}
//
//		// Draw Enemy Explosion
//		for (const EnemyExplosion& ee : eexplosion) {
//			if (ee.IsActive()) {
//				sourceRec = { 0.0f, ee.GetCurrentFrame() * 32.0f, 32.0f, 32.0f };
//				Rectangle dest = { ee.GetX(), ee.GetY(), 64, 64 };
//				DrawTexturePro(enemy_explosion, sourceRec, dest, { 0, 0 }, 0.0f, WHITE);
//				//DrawTexturePro(enemy_explosion, sourceRec, ee.GetRec(), { 0, 0 }, 0.0f, WHITE);
//			}
//		}
//	}
//
//	if (gameOver == true) {
//		DrawText("GAME OVER!", (screenWidth - MeasureText("GAME OVER!", fontSize)) / 2, (screenHeight / 2) - fontSize, fontSize, RED);
//		DrawText("PRESS [ENTER] TO PLAY AGAIN", (screenWidth - MeasureText("PRESS [ENTER] TO PLAY AGAIN", fontSize)) / 2, (screenHeight / 2) + fontSize, fontSize, RED);
//	}
//
//	if (victory == true) {
//		DrawTextureEx(win_screen, { 0, 0 }, 0.0f, ((float)screenWidth / credits_screen.width, (float)screenHeight / credits_screen.height), WHITE);
//		DrawText("PRESS [ENTER] TO PLAY AGAIN", (screenWidth - MeasureText("PRESS [ENTER] TO PLAY AGAIN", fontSize)) / 2, screenHeight - fontSize * 2, fontSize, RED);
//	}
//
//	if (pause == true) {
//		DrawText("GAME PAUSED!", (screenWidth - MeasureText("GAME PAUSED!", fontSize)) / 2, screenHeight - 137, fontSize, RED);
//	}
//
//	if (showCollisions == true) {
//		if (main_menu == true) {
//			DrawRectangleLines(
//				(int)lightning.GetRec().x,
//				(int)lightning.GetRec().y,
//				(int)lightning.GetRec().width,
//				(int)lightning.GetRec().height,
//				PURPLE
//			);
//
//			DrawRectangleLines(
//				(int)enemy.GetRec().x,
//				(int)enemy.GetRec().y,
//				(int)enemy.GetRec().width,
//				(int)enemy.GetRec().height,
//				DARKGREEN
//			);
//		}
//		if (launchSequence == true || inGame == true) {
//			DrawRectangleLines(
//				(int)player.GetRec().x,
//				(int)player.GetRec().y,
//				(int)player.GetRec().width,
//				(int)player.GetRec().height,
//				BLUE
//			);
//		}
//		if (inGame == true || gameOver == true) {
//			for (const Zakko& z : zakkos) {
//				DrawRectangleLines(
//					(int)z.GetRec().x,
//					(int)z.GetRec().y,
//					(int)z.GetRec().width,
//					(int)z.GetRec().height,
//					RED
//				);
//			}
//
//			for (const Goei& g : goeis) {
//				DrawRectangleLines(
//					(int)g.GetRec().x,
//					(int)g.GetRec().y,
//					(int)g.GetRec().width,
//					(int)g.GetRec().height,
//					GREEN
//				);
//			}
//
//			for (const Don& d : dons) {
//				DrawRectangleLines(
//					(int)d.GetRec().x,
//					(int)d.GetRec().y,
//					(int)d.GetRec().width,
//					(int)d.GetRec().height,
//					PINK
//				);
//			}
//
//			for (const Shot& s : shot) {
//				DrawRectangleLines(
//					(int)s.GetRec().x,
//					(int)s.GetRec().y,
//					(int)s.GetRec().width,
//					(int)s.GetRec().height,
//					BLUE
//				);
//			}
//
//			for (const EnemyShot& es : eshot) {
//				DrawRectangleLines(
//					(int)es.GetRec().x,
//					(int)es.GetRec().y,
//					(int)es.GetRec().width,
//					(int)es.GetRec().height,
//					RED
//				);
//			}
//
//			for (const Explosion& e : explosion) {
//				DrawRectangleLines(
//					(int)e.GetRec().x,
//					(int)e.GetRec().y,
//					(int)e.GetRec().width,
//					(int)e.GetRec().height,
//					DARKPURPLE
//				);
//			}
//
//			for (const EnemyExplosion& ee : eexplosion) {
//				DrawRectangleLines(
//					(int)ee.GetRec().x,
//					(int)ee.GetRec().y,
//					(int)ee.GetRec().width,
//					(int)ee.GetRec().height,
//					PURPLE
//				);
//			}
//		}
//	}
//
//	// Lives, Score and High Score
//	DrawText((TextFormat("%i ", lives)), (screenWidth + MeasureText("%i", fontSize)) / 10, 25, fontSize, YELLOW);
//	DrawText("UP", (screenWidth + MeasureText("%i", fontSize)) / 10 + MeasureText("%i", fontSize), 25, fontSize, YELLOW);
//
//	DrawText((TextFormat("%02i ", score)), 50, 25 + MeasureText("%i", fontSize), fontSize, WHITE);
//
//	DrawText("HIGH SCORE", (screenWidth - MeasureText("HIGH SCORE", fontSize)) / 2, 25, fontSize, RED);
//	DrawText((TextFormat("%02i ", highscore)), (screenWidth - MeasureText("%02i", fontSize)) / 2, 25 + MeasureText("%i", fontSize), fontSize, WHITE);
//
//	// end the frame and get ready for the next one  (display frame, poll input, etc...)
//	EndDrawing();
//}
