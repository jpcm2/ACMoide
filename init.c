#include "init.h"
#include <raylib.h>
#include <string.h>

void getTexture(const char *filename, Texture2D *texture) {
  char imgsPath[50] = "../resources/img/";
  strcat(imgsPath, filename);
  *texture = LoadTexture(imgsPath);
}

void loadWalkImages(Texture2D *textures, char *walkTo) {
  char **filenames = NULL;
  char *leftImgs[] = {"L1.png", "L2.png", "L3.png", "L4.png", "L5.png",
                      "L6.png", "L7.png", "L8.png", "L9.png"};
  char *rightImgs[] = {"R1.png", "R2.png", "R3.png", "R4.png", "R5.png",
                       "R6.png", "R7.png", "R8.png", "R9.png"};

  if (strcmp(walkTo, "left") == 0) {
    filenames = leftImgs;
  } else if (strcmp(walkTo, "right") == 0) {
    filenames = rightImgs;
  }

  for (int i = 0; i < 9; ++i) {
    getTexture(filenames[i], &textures[i]);
  }
}

void initThings(Texture2D *bg, Texture2D *lifebar, Texture2D *score,
                Texture2D *gameOver, Texture2D *explosion, Entity *player,
                Shoot *bullets, Shoot *bossBullets, Sound *bulletSound,
                Sound *laughSound, Sound *malwareSound, Music *cyberpunkMusic,
                Texture2D *beginning, Music *opening, Entity *enemyShip,
                int numShips, Texture2D *shipInterior, Entity *boss, Music *breakFree, Sound *fightSound) {
  getTexture("bg.png", &(*bg));
  getTexture("fundo.png", &(*beginning));
  getTexture("boss.png", &((*boss).standing));
  getTexture("shipInterior.png", &(*shipInterior));
  getTexture("R5.png", &((*player).standing));
  getTexture("lifebar2.png", &(*lifebar));
  getTexture("numbers-1.png", &(score[1]));
  getTexture("numbers-0.png", &(score[0]));
  getTexture("numbers-2.png", &(score[2]));
  getTexture("numbers-3.png", &(score[3]));
  getTexture("numbers-4.png", &(score[4]));
  getTexture("numbers-5.png", &(score[5]));
  getTexture("numbers-6.png", &(score[6]));
  getTexture("numbers-7.png", &(score[7]));
  getTexture("numbers-8.png", &(score[8]));
  getTexture("numbers-9.png", &(score[9]));
  getTexture("game_over.png", &(*gameOver));

  getTexture("exp2_0_1.png", &explosion[16]);
  getTexture("exp2_0_2.png", &explosion[15]);
  getTexture("exp2_0_3.png", &explosion[14]);
  getTexture("exp2_0_4.png", &explosion[13]);
  getTexture("exp2_0_5.png", &explosion[12]);
  getTexture("exp2_0_6.png", &explosion[11]);
  getTexture("exp2_0_7.png", &explosion[10]);
  getTexture("exp2_0_8.png", &explosion[9]);
  getTexture("exp2_0_9.png", &explosion[8]);
  getTexture("exp2_0_10.png", &explosion[7]);
  getTexture("exp2_0_11.png", &explosion[6]);
  getTexture("exp2_0_12.png", &explosion[5]);
  getTexture("exp2_0_13.png", &explosion[4]);
  getTexture("exp2_0_14.png", &explosion[3]);
  getTexture("exp2_0_15.png", &explosion[2]);
  getTexture("exp2_0_16.png", &explosion[1]);
  loadWalkImages((*player).leftWalk, "left");
  loadWalkImages((*player).rightWalk, "right");
  player->health = 3;
  player->coordinate = (Vector2){10.0, 390.0};
  player->speed = (float)3.0;
  player->walkCount = 0;
  player->pos.x = player->coordinate.x;
  player->pos.y = player->coordinate.y;
  player->pos.width = 30;
  player->pos.height = 30;
  boss->health = 40;
  boss->coordinate = (Vector2){400, 310};
  boss->speed = (float)2.0;
  boss->pos.x = boss->coordinate.x;
  boss->pos.y = boss->coordinate.y;
  boss->pos.width = 60;
  boss->pos.height = 100;
  for (int i = 0; i < 30; ++i) {
    bossBullets[i].pos.x = boss->coordinate.x;
    bossBullets[i].pos.y = boss->coordinate.y;
    bossBullets[i].pos.width = 20.0;
    bossBullets[i].pos.height = 5.0;
    bossBullets[i].speed = 10.0;
    bossBullets[i].active = 0;
    bossBullets[i].color = RED;
  }
  for (int i = 0; i < 30; ++i) {
    bullets[i].pos.x = player->coordinate.x;
    bullets[i].pos.y = player->coordinate.y;
    bullets[i].pos.width = 20.0;
    bullets[i].pos.height = 5.0;
    bullets[i].speed = 10.0;
    bullets[i].active = 0;
    bullets[i].color = GOLD;
  }
  for (int i = 0; i < numShips; ++i) {
    enemyShip[i].health = 1;
    int tempX, tempY;
    if (i == 0) {
      tempX = GetRandomValue(10, 750);
      tempY = GetRandomValue(10, 390);
    } else {
      int achei = 0;
      while (!achei) {
        tempX = GetRandomValue(300, 750);
        tempY = GetRandomValue(10, 390);
        Rectangle border =
            (Rectangle){(float)tempX, (float)tempY, enemyShip[i].pos.width,
                        enemyShip[i].pos.height};
        int cond = 1;
        for (int j = i - 1; j >= 0 && cond == 1; --j) {
          if (CheckCollisionRecs(border, enemyShip[j].pos)) {
            cond = 0;
          }
        }
        if (cond == 1) {
          achei = 1;
        }
      }
    }
    enemyShip[i].slope = GetRandomValue(0, acos(-1)); // magnitude*sentido
    enemyShip[i].coordinate =
        (Vector2){(float)player->coordinate.x + GetRandomValue(0, 800),
                  (float)player->coordinate.y + GetRandomValue(0, 450)};
    enemyShip[i].speed = 2.0f;
    enemyShip[i].pos.x = enemyShip[i].coordinate.x;
    enemyShip[i].pos.y = enemyShip[i].coordinate.y;
    enemyShip[i].pos.width = 20;
    enemyShip[i].pos.height = 30;
    enemyShip[i].standing = LoadTexture("../resources/img/enemy.png");
    enemyShip[i].active = 1;
  }
  *bulletSound = LoadSound("../resources/sound/bullet.mp3");
  *laughSound = LoadSound("../resources/sound/risada.mp3");
  *malwareSound = LoadSound("../resources/sound/malware.mp3");
  *fightSound = LoadSound("../resources/sound/fightSound.mp3");
  *cyberpunkMusic = LoadMusicStream("../resources/sound/cyberpunk.mp3");
  *opening = LoadMusicStream("../resources/sound/opening.mp3");
  *breakFree = LoadMusicStream("../resources/sound/breakFree.mp3");
}

void updateThings(Entity *player, Shoot *bullets, Entity *enemyShip,
                  int numShips, int fase) {
  player->health = 3;
  player->coordinate = (Vector2){10.0, 390.0};
  player->speed = (float)3.0;
  player->walkCount = 0;
  player->pos.x = player->coordinate.x;
  player->pos.y = player->coordinate.y;
  player->pos.width = 30;
  player->pos.height = 30;
  for (int i = 0; i < 30; ++i) {
    bullets[i].pos.x = player->coordinate.x;
    bullets[i].pos.y = player->coordinate.y;
    bullets[i].pos.width = 20.0;
    bullets[i].pos.height = 5.0;
    bullets[i].speed = 10.0;
    bullets[i].active = 0;
    bullets[i].color = GOLD;
  }
  for (int i = 0; i < numShips; ++i) {
    enemyShip[i].health = 1;
    int tempX, tempY;
    if (i == 0) {
      tempX = GetRandomValue(0, 750);
      tempY = GetRandomValue(0, 390);
    } else {
      int achei = 0;
      while (!achei) {
        tempX = GetRandomValue(300, 750);
        tempY = GetRandomValue(10, 390);
        Rectangle border =
            (Rectangle){(float)tempX, (float)tempY, enemyShip[i].pos.width,
                        enemyShip[i].pos.height};
        int cond = 1;
        for (int j = i - 1; j >= 0 && cond == 1; --j) {
          if (CheckCollisionRecs(border, enemyShip[j].pos)) {
            cond = 0;
          }
        }
        if (cond == 1) {
          achei = 1;
        }
      }
    }
    enemyShip[i].slope = GetRandomValue(0, -acos(-1)); // magnitude*sentido
    enemyShip[i].invertedy = 0;
    enemyShip[i].invertedx = 0;
    enemyShip[i].coordinate = (Vector2){(float)tempX, (float)tempY};
    enemyShip[i].speed = 2.0f + (0.2f) * fase;
    enemyShip[i].pos.x = enemyShip[i].coordinate.x;
    enemyShip[i].pos.y = enemyShip[i].coordinate.y;
    enemyShip[i].pos.width = 20;
    enemyShip[i].pos.height = 30;
    enemyShip[i].standing = LoadTexture("../resources/img/enemy.png");
    enemyShip[i].active = 1;
  }
}
