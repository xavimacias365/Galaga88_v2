#ifndef CLASSES_H
#define CLASSES_H
#pragma once

#include "raylib.h"

// --- Base Game Class ---
class Game {
	// Aqui deberia de estar las variables globales. Creo que en este punto del desarrollo mover estas variables ahora sería perder el tiempo (vamos muy apurados).
};

// --- Scene ---
class Scene {
	// Los mismo pero con las variables level1, MainMenu, level2, etc.
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
protected:
	bool active = false;
public:
	Player() {}
	Player(bool active ,Rectangle rec, Vector2 speed, Color color) : active(active) , Entity(rec, speed, color) {}

	bool IsActive() const { return active; }
	void ChangeState(bool a) { active = a; }

};

// --- Explosion ---
class Explosion : public Entity {
protected:
	bool active = false;

public:
	Explosion() {}
	Explosion(Rectangle rec, Vector2 speed, Color color, bool active) : Entity(rec, speed, color), active(active) {}

	bool IsActive() const { return active; }
	void ChangeState(bool a) { active = a; }

};

class EnemyExplosion : public Explosion {
protected:
	int frameCounter = 0;
	int currentFrame = 0;

public:
	EnemyExplosion() {}
	EnemyExplosion(Rectangle rec, Vector2 speed, Color color, bool active, int frameCounter, int currentFrame) : Explosion(rec, speed, color, active), frameCounter(frameCounter), currentFrame(currentFrame) {}

	void UpdateAnimation(int maxFrames, int frameSpeed) {
		if (!IsActive()) { return; }

		frameCounter++;
		if (frameCounter >= frameSpeed) {
			frameCounter = 0;
			currentFrame++;
			if (currentFrame >= maxFrames) {
				currentFrame = 0;
				ChangeState(false);
			}
		}
	}

	void Activate(Vector2 pos, float width = 64, float height = 64) {
		rec.x = pos.x;
		rec.y = pos.y;
		rec.width = width;
		rec.height = height;
		currentFrame = 0;
		frameCounter = 0;
		ChangeState(true);
	}

	int GetCurrentFrame() const { return currentFrame; }

};

class PlayerExplosion : public Explosion {
protected:
	int frameCounter = 0;
	int currentFrame = 0;

public:
	PlayerExplosion() {}
	PlayerExplosion(Rectangle rec, Vector2 speed, Color color, bool active, int frameCounter, int currentFrame) : Explosion(rec, speed, color, active), frameCounter(frameCounter), currentFrame(currentFrame) {}

	void UpdateAnimation(int maxFrames, int frameSpeed) {
		if (!IsActive()) { return; }

		frameCounter++;
		if (frameCounter >= frameSpeed) {
			frameCounter = 0;
			currentFrame++;
			if (currentFrame >= maxFrames) {
				currentFrame = 0;
				ChangeState(false);
			}
		}
	}

	void Activate(Vector2 pos, float width = 64, float height = 64) {
		rec.x = pos.x;
		rec.y = pos.y;
		rec.width = width;
		rec.height = height;
		currentFrame = 0;
		frameCounter = 0;
		ChangeState(true);
	}

	int GetCurrentFrame() const { return currentFrame; }

};

// --- Enemy ---
class Enemy : public Entity {
protected:
	bool active = false;
	int shot = 0;
	int frameCounter = 0;
	int currentFrame = 0;

public:
	Enemy() {}
	Enemy(Rectangle rec, Vector2 speed, Color color, bool active, int shot, int frameCounter, int currentFrame) : Entity(rec, speed, color), active(active), shot(shot), frameCounter(frameCounter), currentFrame(currentFrame) {}

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
	
	void DetectChangeState(bool a) {
		if (active && !a) {
			OnDeactivate();
		}
		active = a;
	}

	void OnDeactivate() {

	}

	void SetShot(int s) { shot = s; }
	int GetShot() { return shot; }

};

// --- Enemies ---
class MainMenuEnemy : public Enemy {
public:
	MainMenuEnemy() {}
	MainMenuEnemy(Rectangle rec, Vector2 speed, Color color, bool active, int shot, int frameCounter, int currentFrame) : Enemy(rec, speed, color, active, shot, frameCounter, currentFrame) {}
};

class MainMenuLightning : public Enemy {
public:
	MainMenuLightning() {}
	MainMenuLightning(Rectangle rec, Vector2 speed, Color color, bool active, int shot, int frameCounter, int currentFrame) : Enemy(rec, speed, color, active, shot, frameCounter, currentFrame) {}
};

class LaunchSequenceEnemy : public Enemy {
public:
	LaunchSequenceEnemy() {}
	LaunchSequenceEnemy(Rectangle rec, Vector2 speed, Color color, bool active, int shot, int frameCounter, int currentFrame) : Enemy(rec, speed, color, active, shot, frameCounter, currentFrame) {}
};

class Zakko : public Enemy {
public:
	Zakko() {}
	Zakko(Rectangle rec, Vector2 speed, Color color, bool active, int shot, int frameCounter, int currentFrame) : Enemy(rec, speed, color, active, shot, frameCounter, currentFrame) {}
};

class Goei : public Enemy {
public:
	Goei() {}
	Goei(Rectangle rec, Vector2 speed, Color color, bool active, int shot, int frameCounter, int currentFrame) : Enemy(rec, speed, color, active, shot, frameCounter, currentFrame) {}
};

class Don : public Enemy {
private:
	int variant = 0;

public:
	Don() {}
	Don(Rectangle rec, Vector2 speed, Color color, bool active, int shot, int frameCounter, int currentFrame) : Enemy(rec, speed, color, active, shot, frameCounter, currentFrame) {
		variant = rand() % 4;
	}

	int GetVariant() const { return variant; }
	void SetVariant(int v) { variant = v; }

};

class BabyDon : public Enemy {
private:
	int variant = 0;

public:
	BabyDon() {}
	BabyDon(Rectangle rec, Vector2 speed, Color color, bool active, int shot, int frameCounter, int currentFrame, int variant) : Enemy(rec, speed, color, active, shot, frameCounter, currentFrame), variant(variant) {}

	int GetVariant() const { return variant; }
	void SetVariant(int v) { variant = v; }
};

class MiniBossGalaga : public Enemy {
private:
	int lives = 0;
	int variant = 0;

public:
	MiniBossGalaga() {}
	MiniBossGalaga(Rectangle rec, Vector2 speed, Color color, bool active, int shot, int frameCounter, int currentFrame, int lives) : Enemy(rec, speed, color, active, shot, frameCounter, currentFrame), lives(lives) {}

	int GetEntityLives() const { return lives; }
	void SetEntityLives(int l) { lives = l; }

};

class BossGalaga : public Enemy {
private:
	int lives = 0;
	int variant = 0;
	int spawn = 0;

public:
	BossGalaga() {}
	BossGalaga(Rectangle rec, Vector2 speed, Color color, bool active, int shot, int frameCounter, int currentFrame, int lives, int variant, int spawn) : Enemy(rec, speed, color, active, shot, frameCounter, currentFrame), lives(lives), variant(variant), spawn(spawn) {}

	int GetEntityLives() const { return lives; }
	void SetEntityLives(int bl) { lives = bl; }
	int GetVariant() const { return variant; }
	void SetVariant(int bv) { variant = bv; }
	int GetSpawn() const { return spawn; }
	void SetSpawn(int s) { spawn = s; }
	
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
protected:
	bool active = false;
	int frameCounter = 0;
	int currentFrame = 0;

public:
	EnemyShot() {}
	EnemyShot(Rectangle rec, Vector2 speed, Color color, bool active, int frameCounter, int currentFrame) : Shot(rec, speed, color, active), frameCounter(frameCounter), currentFrame(currentFrame) {}

	bool IsActive() const { return active; }
	void ChangeState(bool a) { active = a; }

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
