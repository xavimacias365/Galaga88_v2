#ifndef CLASSES_H
#define CLASSES_H
#pragma once

#include "raylib.h"

// --- Base Game Class ---
class Game {
	// TO DO: Add game loop control and scene management.
};

// --- Scene ---
class Scene {
	// TO DO: Manage TileMap, Player, Enemies, etc.
};

//class TileMap {};



// --- Entity Base Class ---
class Entity {
protected:
	Rectangle rec;
	Vector2 speed;
	Color color;

public:
	Entity() {}
	Entity(Rectangle rec, Vector2 speed, Color color) : rec(rec), speed(speed), color(color) {}

	Rectangle GetRec() const { return rec; }
	void SetRec(Rectangle r) { rec = r; }
	void SetPos(float x, float y) { rec.x = x; rec.y = y; }
	
	void SetX(float x) { rec.x = x; }
	void SetY(float y) { rec.y = y; } 
	float GetX() const { return rec.x; }
	float GetY() const { return rec.y; }
	Vector2 GetSpeed() const { return speed; }
	void SetSpeed(Vector2 s) { speed = s; }
	Color getColor() const { return color; }

	virtual ~Entity() = default;
};

// --- Player ---
class Player : public Entity {
public:
	Player() {}
	Player(Rectangle rec, Vector2 speed, Color color) : Entity(rec, speed, color) {}

};

// --- Enemy ---
class Enemy : public Entity {
protected:
	bool active = false;
	int move = 0;
	int cnt = 0;
	int frameCounter = 0;
	int currentFrame = 0;

public:
	Enemy() {}
	Enemy(Rectangle rec, Vector2 speed, Color color, bool active, int move, int cnt, int frameCounter, int currentFrame) : Entity(rec, speed, color), active(active), move(move), cnt(cnt), frameCounter(frameCounter), currentFrame(currentFrame) {}

	bool IsActive() const { return active; }

	void UpdateAnimation(int maxFrames, int frameSpeed) {
		frameCounter++;
		if (frameCounter >= frameSpeed) {
			frameCounter = 0;
			currentFrame++;
			if (currentFrame >= maxFrames) {
				currentFrame = 0;
			}
		}
	}

	int GetCurrentFrame() const { return currentFrame; }

	void ChangeState(bool a) { active = a; }

};

// --- Enemies ---
class MainMenuEnemy : public Enemy {
public:
	MainMenuEnemy() {}
	MainMenuEnemy(Rectangle rec, Vector2 speed, Color color, bool active, int move, int cnt, int frameCounter, int currentFrame) : Enemy(rec, speed, color, active, move, cnt, frameCounter, currentFrame) {}
};

class MainMenuLightning : public Enemy {
public:
	MainMenuLightning() {}
	MainMenuLightning(Rectangle rec, Vector2 speed, Color color, bool active, int move, int cnt, int frameCounter, int currentFrame) : Enemy(rec, speed, color, active, move, cnt, frameCounter, currentFrame) {}
};

class Zakko : public Enemy {
public:
	Zakko() {}
	Zakko(Rectangle rec, Vector2 speed, Color color, bool active, int move, int cnt, int frameCounter, int currentFrame) : Enemy(rec, speed, color, active, move, cnt, frameCounter, currentFrame) {}
};

// --- Enemy Manager ---
class EnemyManager {
	// TO DO: Spawn and Manage all enemies.
};

// --- Object (non-enemy, non-player game elements) ---
class Object : public Entity {
public:
	Object() {}
	Object(Rectangle rec, Vector2 speed, Color color) : Entity(rec, speed, color) {}
};

// --- Shot Base Class ---
class Shot : public Entity {
protected:
	bool active = false;

public:
	Shot() {}
	Shot(Rectangle rec, Vector2 speed, Color color, bool active) : Entity(rec, speed, color), active(active) {}

	bool IsActive() const { return active; }
	void ChangeState(bool a) { active = a; }

};

// --- Enemy Shot ---
class EnemyShot : public Shot {
public:
	EnemyShot() {}
	EnemyShot(Rectangle rec, Vector2 speed, Color color, bool active) : Shot(rec, speed, color, active) {}
};

// --- Player Shot ---
class PlayerShot : public Shot {
public:
	PlayerShot() {}
	PlayerShot(Rectangle rec, Vector2 speed, Color color, bool active) : Shot(rec, speed, color, active) {}
};

// --- Shot Manager ---
class ShotManager {
	// TO DO: Manage Active Shots.
};


// --- Render System ---
class RenderComponent {
	// TODO: Base class for sprite/static rendering
};

class Sprite : public RenderComponent {
	// TODO: Sprite animations
};

class StaticImage : public RenderComponent {
	// TODO: Still image rendering
};

class ResourceManager {
	// TODO: Load and provide access to shared resources
};

#endif // CLASSES_H
