#ifndef LOADTEXTURE_H
#include "math.h"
#include "raylib.h"
#define LOADTEXTURE_H

typedef struct {
  int health;
  Vector2 coordinate;
  int walkCount;
  float speed;
  Rectangle pos;
  int active;

  Texture2D standing;
  Texture2D rightWalk[10];
  Texture2D leftWalk[10];
  float slope; // for the enemy trajectory
  int invertedy;
  int invertedx;
} Entity;

typedef struct {
  Rectangle pos;
  float speed;
  int active;
  Color color;
  int side;
  char direction;
} Shoot;

void getTexture(const char *filename, Texture2D *texture);
void loadWalkImages(Texture2D *textures, char *walkTo);
void initThings(Texture2D *bg, Texture2D *lifebar, Texture2D *score,
                Texture2D *gameover, Texture2D *explosion, Entity *player,
                Shoot *bullets, Shoot *bossBullets, Sound *bulletSound,
                Sound *laughSound, Sound *malwareSound, Music *cyberpunkMusic,
                Texture2D *beginning, Music *opening, Entity *enemyShip,
                int numShips, Texture2D *shipInterior, Entity *boss, Music *breakFree, Sound *fightSound);
void updateThings(Entity *player, Shoot *bullets, Entity *enemyShip,
                  int numShips, int fase);
#endif
