#ifndef CLASSES_H
#define CLASSES_H
#pragma once

class Game {};

class Scene {};

//class TileMap {};

class EnemyManager {};

class Entity {
protected:
	Rectangle rec;
	Vector2 speed;
	Color color;
};

class Player : public Entity {};

class Enemy : public Entity {
private:

};

class Object : public Entity {};

class ShotManager {};

class Shot : public Entity {};

class RenderComponent {};

class Sprite : public RenderComponent {};

class StaticImage : public RenderComponent {};

class ResourceManager {};

#endif // CLASSES_H
