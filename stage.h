#ifndef INIT_H
#define INIT_H

#include "init.h"
#include "raylib.h"

void menu(Texture2D beginning, int *stage);
void tutorial(Texture2D beginning, int *stage);
void history(Texture2D inicio, int *stage);
void levelOne(Texture2D bg, Texture2D lifebar, Texture2D *score,
              Texture2D gameOver, Texture2D *explosion, Entity *player,
              int *facing, int screenHeight, int screenWidth, Shoot *bullets,
              int *ShootRate, Sound bulletSound, Entity *enemyShip,
              int numShips, int *stage, int *counter, int *fase,Sound laughSound,Sound malwareSound);
void preRobo(Texture2D inicio, int *stage);
void levelTwo(Texture2D bg, Texture2D lifebar, Texture2D *score,
              Texture2D gameOver, Entity *player, int *facing, int screenHeight,
              int screenWidth, Shoot *bullets, Shoot *bossBullets,
              int *shootRate, int *shootRateBoss, Sound bulletSound,
              Entity *boss, int numShips, int *stage,Sound laughSound,Sound malwareSound,Sound fightSound);
void posRobo(Texture2D inicio, int *stage);
void creditos(Texture2D inicio, int *stage);

#endif
