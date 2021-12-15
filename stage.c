//Files
#include "stage.h"
#include "init.h"

//Libraries
#include <math.h>
#include <string.h>
#include <stdio.h>



//Global variables
int checkSecondLevelHeight = 0, frameColision = 0, checkSecondLevel = 0,indice=0,invertedy=0, invertedx=0,exploded=0,end=0,shipDestroyed;
double radian = acos(-1);

void menu(Texture2D inicio, int *stage) {
  Vector2 pos;
  Vector2 mouse = GetMousePosition();
  pos = (Vector2){(float)0 - mouse.x / 2, (float)0 - mouse.y / 2};
  DrawTextureV(inicio, pos, WHITE);
  char titulo[50] = "ACMoid";
  Vector2 LocalTitulo = (Vector2){(float)195.0, (float)140};
  DrawText(titulo, LocalTitulo.x, LocalTitulo.y, 40, GOLD);
  DrawLine(LocalTitulo.x, LocalTitulo.y + 50, LocalTitulo.x + 385,
           LocalTitulo.y + 50, GOLD);
  char frase[50] = "Clique na tecla [ESPAÇO] para continuar!";
  DrawText(frase, LocalTitulo.x, LocalTitulo.y + 100, 20, GOLD);
  if (IsKeyPressed(KEY_SPACE)) {
    *stage = 1;
  }
}

void tutorial(Texture2D inicio, int *stage) {
  Vector2 pos;
  Vector2 mouse = GetMousePosition();
  pos = (Vector2){0.0f - mouse.x / 2, 0.0f - mouse.y / 2};
  DrawTextureV(inicio, pos, WHITE);
  char titulo[50] = "Comandos de Movimento:";
  char comando1[60] =
      "- Pressione [A], [W], [S] e [D]";
  char comando2[50] = "- Pressione [K] para atirar";
  char comando3[50] = "- Pressione [ENTER] para iniciar o jogo!";
  Vector2 LocalTitulo = (Vector2){30.0f, 120.0f};
  DrawText(titulo, LocalTitulo.x, LocalTitulo.y, 40, GOLD);
  DrawLine(LocalTitulo.x, LocalTitulo.y + 50, LocalTitulo.x + 480,
           LocalTitulo.y + 50, GOLD);
  DrawText(comando1, LocalTitulo.x, LocalTitulo.y + 90, 20, GOLD);
  DrawText(comando2, LocalTitulo.x, LocalTitulo.y + 130, 20, GOLD);
  DrawText(comando3, LocalTitulo.x, LocalTitulo.y + 170, 20, RED);

  if (IsKeyPressed(KEY_ENTER)) {
    *stage = 3;
  }
}

void history(Texture2D inicio, int *stage) {
  Vector2 pos;
  Vector2 mouse = GetMousePosition();
  pos = (Vector2){0.0f - mouse.x / 2, 0.0f - mouse.y / 2};
  DrawTextureV(inicio, pos, WHITE);
  Rectangle container = {25.0f, 25.0f, 800 - 50.0f, 450 - 320.0f};
  char text[500] =
      "    Grande aventureiro, seu cyborgue enlouqueceu! Algum estagiário esqueceu "
      "\nde por um free na atualização do seu código e agora o ACM-43 "
      "\nestá tomando controle dos outros cyborgues e atacando a todos!! "
      "Rá-\npido, volte para a nave, você é a nossa última esperança...";
  DrawRectangle(25, 25, 450 - 50.0f, 450 - 320.0f, BLACK);
  DrawRectangleLinesEx(container, 3, GRAY);
  DrawText(text, 35, 30, 20, GOLD);

  if (IsKeyPressed(KEY_ENTER)) {
    *stage = 2;
  }
}

void levelOne(Texture2D bg, Texture2D lifebar, Texture2D *score,
              Texture2D gameOver, Texture2D *explosion, Entity *player,
              int *facing, int screenHeight, int screenWidth, Shoot *bullets,
              int *ShootRate, Sound bulletSound, Entity *enemyShip,
              int numShips, int *stage, int *counter, int *fase, Sound laughSound,Sound malwareSound) {

  DrawTexture(bg, -screenWidth / 2.0f + (player->pos.x)/5, -screenHeight / 2.0f + (player->pos.y)/5, WHITE);
  // implementar uma câmera usar esse DrawTexture
  for (int i = 0; i < numShips; ++i) {
    // Ships texture
    if (enemyShip[i].active)
      DrawTextureV(enemyShip[i].standing, enemyShip[i].coordinate, WHITE);
    DrawTexture(score[i % 9], 720, 15, WHITE);
    DrawTexture(score[counter[0]], 720, 15, WHITE);
    DrawTexture(score[counter[1]], 720 - 50, 15, WHITE);
    DrawTexture(score[counter[2]], 720 - 100, 15, WHITE);
    // Ships mov
    /* enemyShip[i].coordinate.x -= enemyShip[i].speed / (2.0); */
    /* if (enemyShip[i].coordinate.x <= 10) { */
    /*   enemyShip[i].coordinate.x = 750; */
    /* } */
    /* enemyShip[i].pos.x=enemyShip[i].coordinate.x; */
    if (enemyShip[i].coordinate.y >= screenHeight ||
        enemyShip[i].coordinate.y <= 0) {
      switch (GetRandomValue(1, 2)) {
      case 1: // Appears in the same side, but shift width with an offset for
              // the slope
        enemyShip[i].coordinate.y <= 0
            ? (enemyShip[i].coordinate.y = 0)
            : (enemyShip[i].coordinate.y = screenHeight);
        enemyShip[i].coordinate.x = (GetRandomValue(0, screenWidth));
        enemyShip[i].slope += radian + GetRandomValue(0, radian);
        enemyShip[i].invertedy = !enemyShip[i].invertedy;
        enemyShip[i].slope < radian / 2
            ? (invertedx = enemyShip[i].invertedx)
            : (enemyShip[i].invertedx = !enemyShip[i].invertedx);
        break;
      case 2:
        enemyShip[i].coordinate.y <= 0
            ? (enemyShip[i].coordinate.y = screenHeight)
            : (enemyShip[i].coordinate.y =
                   0); // Appears in the opposite side, but shift width
        enemyShip[i].coordinate.x = (GetRandomValue(0, screenWidth));
        enemyShip[i].slope = GetRandomValue(0, radian);
        enemyShip[i].slope < radian / 2
            ? (invertedx = enemyShip[i].invertedx)
            : (enemyShip[i].invertedx = !enemyShip[i].invertedx);
        break;
      }
    } else if (enemyShip[i].coordinate.x >= screenWidth * 2.0f ||
               enemyShip[i].coordinate.x <= 0) {
      switch (GetRandomValue(1, 2)) {
      case 1:
        enemyShip[i].coordinate.x <= 0
            ? (enemyShip[i].coordinate.x = 0)
            : (enemyShip[i].coordinate.x = screenWidth * 2.0f);
        enemyShip[i].coordinate.y = (GetRandomValue(0, screenHeight));
        enemyShip[i].slope += radian + GetRandomValue(0, radian);
        enemyShip[i].invertedx = !enemyShip[i].invertedx;
        enemyShip[i].slope < radian / 2
            ? (invertedy = enemyShip[i].invertedy)
            : (enemyShip[i].invertedy = !enemyShip[i].invertedy);
        break;
      case 2:
        enemyShip[i].coordinate.x <= 0
            ? (enemyShip[i].coordinate.x = screenWidth * 2.0f)
            : (enemyShip[i].coordinate.x =
                   0); // Appears in the opposite side, but shift width
        enemyShip[i].coordinate.y = (GetRandomValue(0, screenHeight));
        enemyShip[i].slope = GetRandomValue(0, radian);
        enemyShip[i].slope < radian / 2
            ? (invertedy = enemyShip[i].invertedy)
            : (enemyShip[i].invertedy = !enemyShip[i].invertedy);
        break;
      }
    }
    // ship movement
    if (enemyShip[i].invertedy)
      enemyShip[i].coordinate.y +=
          -(sin(enemyShip[i].slope) + enemyShip[i].speed);
    else
      enemyShip[i].coordinate.y +=
          +(sin(enemyShip[i].slope) + enemyShip[i].speed);
    if (enemyShip[i].invertedx)
      enemyShip[i].coordinate.x +=
          -(cos(enemyShip[i].slope) + enemyShip[i].speed);
    else
      enemyShip[i].coordinate.x +=
          +(cos(enemyShip[i].slope) + enemyShip[i].speed);
    enemyShip[i].pos.x = enemyShip[i].coordinate.x;
    enemyShip[i].pos.y = enemyShip[i].coordinate.y;
  }

  // Checks for collision between player and ships
  for (int i = 0; i < numShips; ++i)
    if (CheckCollisionRecs(player->pos, enemyShip[i].pos) &&
        enemyShip[i].active) {
      if (!((frameColision++ % 20)))
        player->health--;
    }

  int left = 0, right = 0, up = 0, down = 0, flag;
  if (IsKeyDown(KEY_D)) {
    player->coordinate.x += player->speed;
    if (player->coordinate.x >= 750) {
      player->coordinate.x -= player->speed;
    }
    player->pos.x = player->coordinate.x;
    player->pos.y = player->coordinate.y;
    right = 1;
    left = 0;
    up = 0;
    down = 0;
    *facing = 1;
  }
  if (IsKeyDown(KEY_A)) {
    player->coordinate.x -= player->speed;
    if (player->coordinate.x <= 0) {
      player->coordinate.x += player->speed;
    }
    player->pos.x = player->coordinate.x;
    player->pos.y = player->coordinate.y;
    right = 0;
    left = 1;
    up = 0;
    down = 0;
    *facing = -1;
  }
  if (IsKeyDown(KEY_W)) {
    player->coordinate.y -= player->speed;
    if (player->coordinate.y <= 10) {
      player->coordinate.y += player->speed;
    }
    player->pos.x = player->coordinate.x;
    player->pos.y = player->coordinate.y;
    right = 0;
    left = 0;
    up = 1;
    down = 0;
    *facing = -1;
    player->walkCount = 0;
  }
  if (IsKeyDown(KEY_S)) {
    player->coordinate.y += player->speed;
    if (player->coordinate.y >= 390) {
      player->coordinate.y -= player->speed;
    }
    player->pos.x = player->coordinate.x;
    player->pos.y = player->coordinate.y;
    right = 0;
    left = 0;
    up = 0;
    down = 1;
    *facing = 1;
    player->walkCount = 0;
  }
  if (player->walkCount + 1 > 60) {
    player->walkCount = 0;
  }
  if (right) {
    DrawTextureV(player->rightWalk[player->walkCount / 9], player->coordinate,
                 WHITE);
    player->walkCount++;
  } else if (left) {
    DrawTextureV(player->leftWalk[player->walkCount / 9], player->coordinate,
                 WHITE);
    player->walkCount++;
  } else {
    DrawTextureV(player->standing, player->coordinate, WHITE);
  }
  if (IsKeyDown(KEY_K) && player->health > 0) {
    *ShootRate += 5;
    for (int i = 0; i < 25; ++i) {
      if (!bullets[i].active && *ShootRate % 40 == 0) {
        SetSoundVolume(bulletSound, 1.0);
        PlaySound(bulletSound);
        bullets[i].pos.x = player->coordinate.x + 10;
        bullets[i].pos.y = player->coordinate.y + 20;
        bullets[i].active = 1;
        bullets[i].side = *facing;
        if (up || down) {
          bullets[i].direction = 'V';
        } else {
          bullets[i].direction = 'H';
        }
        break;
      }
    }
  }
  for (int i = 0; i < 25; ++i) {
    if (bullets[i].active) {
      for (int j = 0; j < numShips; j++) {
        /* if (CheckCollisionRecs(enemyShip[j].pos, bullets[i].pos) && */
        /*     bullets[i].active && enemyShip[j].active) { */
        if (CheckCollisionRecs(enemyShip[j].pos, bullets[i].pos) &&
            bullets[i].active && enemyShip[j].active) {
          printf("acertou mizeravi!");
          shipDestroyed = j;
          exploded = !exploded;
          enemyShip[j].active = 0;
          for (int e = 0; e < 16; e++)
            DrawTexture(explosion[e++ % 16],
                        enemyShip[shipDestroyed].coordinate.x,
                        enemyShip[shipDestroyed].coordinate.y, WHITE);
          bullets[i].active = 0;
          counter[0] = ((counter[0]) % 10) + 1;
          if (counter[0] % 10 == 0) {
            counter[1] = ((counter[1] % 10)) + 1;
            if (counter[1] % 10 == 0)
              counter[2] = ((counter[2] % 10)) + 1;
            /* } */
          }
        }
      }
      if (bullets[i].direction == 'H') {
        bullets[i].pos.x += bullets[i].speed * bullets[i].side;
      } else {
        bullets[i].pos.width = 5.0;
        bullets[i].pos.height = 20.0;
        bullets[i].pos.y += bullets[i].speed * bullets[i].side;
      }
      if (bullets[i].pos.x >= 820 || bullets[i].pos.x <= -10 ||
          bullets[i].pos.y >= 480 || bullets[i].pos.y <= -10) {
        if (bullets[i].pos.width == 5) {
          bullets[i].pos.width = 20.0;
          bullets[i].pos.height = 5.0;
        }
        bullets[i].active = 0;
        *ShootRate = 0;
      }
    }
  }
  switch (player->health) {
  case 1:
    DrawTexture(lifebar, -90 - 30 + screenWidth / 2.0f,
                -390 + screenHeight / 2.0f, WHITE);
    break;
  case 2:
    DrawTexture(lifebar, -90 - 30 + screenWidth / 2.0f,
                -390 + screenHeight / 2.0f, WHITE);
    DrawTexture(lifebar, -160 - 30 + screenWidth / 2.0f,
                -390 + screenHeight / 2.0f, WHITE);
    break;
  case 3:
    DrawTexture(lifebar, -90 - 30 + screenWidth / 2.0f,
                -390 + screenHeight / 2.0f, WHITE);
    DrawTexture(lifebar, -160 - 30 + screenWidth / 2.0f,
                -390 + screenHeight / 2.0f, WHITE);
    DrawTexture(lifebar, -20 - 30 + screenWidth / 2.0f,
                -390 + screenHeight / 2.0f, WHITE);
    break;
  default:
    PlaySound(laughSound);
    DrawTexture(gameOver, -screenWidth / 2.0f, -screenHeight / 2.0f, WHITE);
    for (int i = 0; i < 3; ++i) {
      counter[i] = 0;
    }
    char tryAgain[50] = "Pressione [ENTER] para tentar novamente";
    Vector2 LocalTitulo = (Vector2){120.0f, 180.0f};
    DrawText(tryAgain, LocalTitulo.x, LocalTitulo.y, 25, GOLD);
    if (IsKeyDown(KEY_ENTER)) {
      *stage = -1;
      player->health = 3;
    }
  }
  for (int i = 0; i < 25; ++i) {
    if (bullets[i].active)
      DrawRectangleRec(bullets[i].pos, bullets[i].color);
  }
  flag = 1;
  for (int i = 0; i < numShips; ++i) {
    if (enemyShip[i].active) {
      flag = 0;
    }
  }
  if (flag) {
    if (*fase == 0) {
      *fase = 1;
      *stage = -2;
    } else if (*fase == 1) {
      *fase = 2;
      *stage = -2;
    } else if (*fase == 2) {
      *fase = 3;
      *stage = -2;
    }
    if (*fase == 3) {
      *stage = 4;
      frameColision = 0;
    }
  }
}

void preRobo(Texture2D inicio, int *stage){
  Vector2 pos;
  Vector2 mouse = GetMousePosition();
  pos = (Vector2){0.0f - mouse.x / 2, 0.0f - mouse.y / 2};
  DrawTextureV(inicio, pos, WHITE);
  Rectangle container = {25.0f, 25.0f, 800 - 50.0f, 450 - 320.0f};
  char text[500] =
      "    Graças ao seu grande esforço esta árdua batalha está se "
      "aproxi-\nmando"
      " ao fim, confiamos na sua força para derrotar o ACM-43! "
      "\nOs estagiários que sobraram acabaram fugindo, agora é com você ACM! ";
  DrawRectangle(25, 25, 450 - 50.0f, 450 - 320.0f, BLACK);
  DrawRectangleLinesEx(container, 3, GRAY);
  DrawText(text, 35, 30, 20, GOLD);

  if (IsKeyPressed(KEY_ENTER)) {
    *stage = 5;
  }
}

void levelTwo(Texture2D bg, Texture2D lifebar, Texture2D *score,
              Texture2D gameOver, Entity *player, int *facing, int screenHeight,
              int screenWidth, Shoot *bullets, Shoot *bossBullets,
              int *shootRate, int *shootRateBoss, Sound bulletSound,
              Entity *boss, int numShips, int *stage, Sound laughSound,Sound malwareSound, Sound fightSound) {
  DrawTexture(bg, 0 - player->coordinate.x / 4, 0, WHITE);
  if (end == 0) {
    DrawTextureV(boss->standing, boss->coordinate, WHITE);
  }
  DrawText(TextFormat("ACMDROID Life: %d", boss->health), 520, 10, 25, RED);
  double lastShotTime = -8;
  // Phase setup
  if (!checkSecondLevel) {
    PlaySound(fightSound);
    checkSecondLevel = 1;
    player->coordinate.y = 360;
    player->coordinate.x = 100;
    player->pos.y = player->coordinate.y;
    player->pos.x = player->coordinate.x;
    player->health = 3;
    boss->coordinate.x = 500;
    boss->health = 40;
    boss->pos.x = boss->coordinate.x;
  }

  // Low gravity simulator
  if (player->coordinate.y < 360 && end == 0) {
    player->coordinate.y += 1 + ((player->coordinate.y - 400) * (-1)) / 150;
    player->pos.y = player->coordinate.y;
  }

  // Checks for collision between player and boss
  if (CheckCollisionRecs(player->pos, boss->pos) && end == 0) {
    if (!((frameColision++ % 20)))
      player->health--;
  } else if (end == 0) {
    if (player->pos.x - boss->pos.x > 0 && boss->pos.x < 650)
      boss->pos.x++;
    else if (boss->pos.x > 4)
      boss->pos.x--;
    boss->coordinate.x = boss->pos.x;
  }

  /// Keyboard input
  int left = 0, right = 0, up = 0, down = 0;
  if (IsKeyDown(KEY_D) && player->coordinate.x < 710 && player->health > 0 &&
      end == 0) {
    player->coordinate.x += player->speed;
    if (player->coordinate.x >= 750) {
      player->coordinate.x -= player->speed;
    }
    player->pos.x = player->coordinate.x;
    player->pos.y = player->coordinate.y;
    right = 1;
    left = 0;
    up = 0;
    down = 0;
    *facing = 1;
  }
  if (IsKeyDown(KEY_A) && player->coordinate.x > 45 && player->health > 0 &&
      end == 0) {
    player->coordinate.x -= player->speed;
    if (player->coordinate.x <= 0) {
      player->coordinate.x += player->speed;
    }
    player->pos.x = player->coordinate.x;
    player->pos.y = player->coordinate.y;
    right = 0;
    left = 1;
    up = 0;
    down = 0;
    *facing = -1;
  }
  if (IsKeyDown(KEY_W) && (player->coordinate.y > 200) && player->health > 0 &&
      end == 0) {
    player->coordinate.y -= player->speed;
    if (player->coordinate.y <= 10) {
      player->coordinate.y += player->speed + 2;
    }
    player->pos.x = player->coordinate.x;
    player->pos.y = player->coordinate.y;
    right = 0;
    left = 0;
    up = 1;
    down = 0;
    *facing = -1;
    player->walkCount = 0;
  }
  if (player->walkCount + 1 > 60) {
    player->walkCount = 0;
  }
  if (right) {
    DrawTextureV(player->rightWalk[player->walkCount / 9], player->coordinate,
                 WHITE);
    player->walkCount++;
  } else if (left) {
    DrawTextureV(player->leftWalk[player->walkCount / 9], player->coordinate,
                 WHITE);
    player->walkCount++;
  } else {
    DrawTextureV(player->standing, player->coordinate, WHITE);
  }
  if (IsKeyDown(KEY_K) && player->health > 0 && end == 0) {
    *shootRate += 5;
    for (int i = 0; i < 50; ++i) {
      if (!bullets[i].active && *shootRate % 40 == 0) {
        SetSoundVolume(bulletSound, 1.0);
        PlaySound(bulletSound);
        bullets[i].pos.x = player->coordinate.x + 10;
        bullets[i].pos.y = player->coordinate.y + 20;
        bullets[i].active = 1;
        bullets[i].side = *facing;
        bullets[i].direction = 'H';
        break;
      }
    }
  }
  for (int i = 0; i < 50 && end == 0; ++i) {
    if (bullets[i].active) {
      if (CheckCollisionRecs(boss->pos, bullets[i].pos)) {
        bullets[i].active = 0;
        boss->health--;
      }
      if (bullets[i].direction == 'H') {
        bullets[i].pos.x += bullets[i].speed * bullets[i].side;
      } else {
        bullets[i].pos.width = 5.0;
        bullets[i].pos.height = 20.0;
        bullets[i].pos.y += bullets[i].speed * bullets[i].side;
      }
      if (bullets[i].pos.x >= 820 || bullets[i].pos.x <= -10 ||
          bullets[i].pos.y >= 480 || bullets[i].pos.y <= -10) {
        if (bullets[i].pos.width == 5) {
          bullets[i].pos.width = 20.0;
          bullets[i].pos.height = 5.0;
        }
        bullets[i].active = 0;
        *shootRate = 0;
      }
    }
  }

  // Makes ACMDROID Bullets follow the player and checks if it hits the player
  for (int i = 0; i < 50 && end == 0; i++) {
    bossBullets[i].direction = 'H';
    if (CheckCollisionRecs(player->pos, bossBullets[i].pos) &&
        bossBullets[i].active) {
      player->health--;
      bossBullets[i].active = 0;
    }
    if ((player->pos.x - boss->pos.x > 0) && !bossBullets[i].active)
      bossBullets[i].side = 1;
    else if (!bossBullets[i].active)
      bossBullets[i].side = -1;
  }

  // Boss bullet mechanic
  if (GetTime() > lastShotTime + 8 && end == 0) {
    lastShotTime = GetTime();
    *shootRateBoss += 2;
    for (int i = 0; i < 50; ++i) {
      if (!bossBullets[i].active && *shootRateBoss % 40 == 0 && end == 0) {
        SetSoundVolume(bulletSound, 1.0);
        PlaySound(bulletSound);
        bossBullets[i].pos.x = boss->coordinate.x + 10;
        bossBullets[i].pos.y = boss->coordinate.y + 20;
        bossBullets[i].active = 1;
        int test = GetRandomValue(0,50);
        if(test==10) PlaySound(laughSound);
        if(test==20) PlaySound(malwareSound);
        break;
      }
    }
    
  }
  for (int i = 0; i < 50 && end == 0; ++i) {
    if (bossBullets[i].active) {
      if (bossBullets[i].direction == 'H') {
        bossBullets[i].pos.x += bossBullets[i].speed * bossBullets[i].side;
      }
      if (bossBullets[i].pos.x >= 820 || bossBullets[i].pos.x <= -10 ||
          bossBullets[i].pos.y >= 480 || bossBullets[i].pos.y <= -10) {
        bossBullets[i].active = 0;
        *shootRateBoss = 0;
      }
    }
  }
  // Health configs
  switch (player->health) {
  case 1:
    DrawTexture(lifebar, -90 - 30 + screenWidth / 2.0f,
                -390 + screenHeight / 2.0f, WHITE);
    break;
  case 2:
    DrawTexture(lifebar, -90 - 30 + screenWidth / 2.0f,
                -390 + screenHeight / 2.0f, WHITE);
    DrawTexture(lifebar, -160 - 30 + screenWidth / 2.0f,
                -390 + screenHeight / 2.0f, WHITE);
    break;
  case 3:
    DrawTexture(lifebar, -90 - 30 + screenWidth / 2.0f,
                -390 + screenHeight / 2.0f, WHITE);
    DrawTexture(lifebar, -160 - 30 + screenWidth / 2.0f,
                -390 + screenHeight / 2.0f, WHITE);
    DrawTexture(lifebar, -20 - 30 + screenWidth / 2.0f,
                -390 + screenHeight / 2.0f, WHITE);
    break;
  default:
    DrawTexture(gameOver, -screenWidth / 2.0f, -screenHeight / 2.0f, WHITE);
    char tryAgain[50] = "Pressione [ENTER] para tentar novamente";
    checkSecondLevel = 0;
    Vector2 LocalTitulo = (Vector2){180.0f, 140.0f};
    DrawText(tryAgain, LocalTitulo.x, LocalTitulo.y, 25, GOLD);
    if (IsKeyDown(KEY_ENTER)) {
      checkSecondLevel = 0;
      *stage = 0;
      player->health = 3;
    }
  }

  for (int i = 0; i < 50 && end == 0; ++i) {
    if (bullets[i].active && end == 0)
      DrawRectangleRec(bullets[i].pos, bullets[i].color);
  }

  for (int i = 0; i < 50 && end == 0; ++i) {
    if (bossBullets[i].active)
      DrawRectangleRec(bossBullets[i].pos, bossBullets[i].color);
  }
  if (boss->health <= 0) {
    end = 1;
    DrawText("O ACMDroid foi derrotado! Pressione [ENTER] para continuar!",
             110.0f, 160.0f, 20, GOLD);
    if (IsKeyPressed(KEY_ENTER)) {
      *stage = 6;
    }
  }
}

void posRobo(Texture2D inicio, int *stage) {
  Vector2 pos;
  Vector2 mouse = GetMousePosition();
  pos = (Vector2){0.0f - mouse.x / 2, 0.0f - mouse.y / 2};
  DrawTextureV(inicio, pos, WHITE);
  Rectangle container = {25.0f, 25.0f, 800 - 50.0f, 450 - 320.0f};
  char text[500] = "    Uau, meus olhos se emocionaram com esta batalha épica, "
                   "sempre a-\ncreditei "
                   "que a força estava com você!! Agora finalmente poderemos "
                   "vol-\ntar a trabalhar"
                   " em paz na nave... ";
  DrawRectangle(25, 25, 450 - 50.0f, 450 - 320.0f, BLACK);
  DrawRectangleLinesEx(container, 3, GRAY);
  DrawText(text, 35, 30, 20, GOLD);

  if (IsKeyPressed(KEY_ENTER)) {
    *stage = 7;
  }
}

void creditos(Texture2D inicio, int *stage) {
  Vector2 pos;
  Vector2 mouse = GetMousePosition();
  pos = (Vector2){0.0f - mouse.x / 2, 0.0f - mouse.y / 2};
  DrawTextureV(inicio, pos, WHITE);
  Rectangle container = {25.0f, 25.0f, 800 - 50.0f, 450 - 280.0f};
  char text[500] = "Ednelson Luan Lourenço Cavalcanti - ellc\n"
                   "Enzo Gurgel Bissoli - egb2\n"
                   "João Pedro de Campos Medeiros - jpcm2\n"
                   "Lucas Santiago Monterazo - lsm6\n"
                   "Vínicus Lima Ventura - vlv2\n";
  DrawRectangle(25, 25, 450 - 50.0f, 450 - 320.0f, BLACK);
  DrawRectangleLinesEx(container, 3, GRAY);
  DrawText(text, 35, 30, 20, GOLD);

  if (IsKeyPressed(KEY_ENTER)) {
    *stage = 0;
  }
} 