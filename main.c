#include "init.h"

#include "raylib.h"

#include "stage.h"

#include <math.h>

#include <raylib.h>

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

const int N_IMGS = 9;

int main() {

  const int screenHeight = 800;
  const int screenWidth = 450;
  int counter[3] = {0, 0, 0};

  InitWindow(screenHeight, screenWidth, "ACMoid");
  InitAudioDevice();
  SetTargetFPS(60);

  Sound bulletSound, laughSound, malwareSound, fightSound;
  Music cyberpunkMusic, opening, breakFree;
  int facing = 0, stage = 0, ShootRate = 0, fase = 0, NUM_SHIPS = 10,
      ShootRateBoss = 0;
  Texture2D bg, beginning, score[10], lifebar, gameOver, explosion[16],
      shipInterior;
  Entity player, enemyShip[120], boss;
  Shoot bullets[51], bossBullets[51]; // 50 vai ser o numero de tiros

  initThings(&bg, &lifebar, score, &gameOver, explosion, &player, bullets,
             bossBullets, &bulletSound, &laughSound, &malwareSound,
             &cyberpunkMusic, &beginning, &opening, enemyShip, NUM_SHIPS,
             &shipInterior, &boss, &breakFree, &fightSound);
  PlayMusicStream(cyberpunkMusic);
  PlayMusicStream(opening); 
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(WHITE);
      switch (stage){ //Phase selection
      case -2:
        NUM_SHIPS += 8;
        updateThings(&player, bullets, enemyShip, NUM_SHIPS, fase);
        stage = 3;
        break;
      case -1:
        fase = 0;
        NUM_SHIPS = 10;
        updateThings(&player, bullets, enemyShip, NUM_SHIPS, fase);
        stage = 0;
        break;
      case 0:
        UpdateMusicStream(opening);
        SetMusicVolume(opening, 0.8);
        menu(beginning, &stage);
        break;
      case 1:
        UpdateMusicStream(cyberpunkMusic);
        SetMusicVolume(cyberpunkMusic, 0.2);
        history(beginning, &stage);
        break;
      case 2:
        UpdateMusicStream(opening);
        SetMusicVolume(opening, 0.8);
        tutorial(beginning, &stage);
        break;
      case 3:
        UpdateMusicStream(cyberpunkMusic);
        SetMusicVolume(cyberpunkMusic, 0.2);
        levelOne(bg, lifebar, score, gameOver, explosion, &player, &facing, screenHeight, screenWidth, bullets, &ShootRate, bulletSound, enemyShip, NUM_SHIPS, &stage, counter, &fase, laughSound, malwareSound);
        break;
      case 4:
        UpdateMusicStream(cyberpunkMusic);
        SetMusicVolume(cyberpunkMusic, 0.2);
        preRobo(beginning, &stage);
        break;
      case 5:
        UpdateMusicStream(cyberpunkMusic);
        SetMusicVolume(cyberpunkMusic, 0.2);
        levelTwo(shipInterior, lifebar, score, gameOver, &player, &facing, screenHeight, screenWidth, bullets, bossBullets, &ShootRate, &ShootRateBoss, bulletSound, &boss, NUM_SHIPS, &stage, laughSound, malwareSound, fightSound);
        break;
      case 6:
        posRobo(beginning, &stage);
        break;
      case 7:
        UpdateMusicStream(breakFree);
        SetMusicVolume(breakFree, 0.2);
        creditos(beginning, &stage);
        break;
      default: 
        break;
      }
      EndDrawing();
    }
  //Unload things
  for (int i = 0; i < N_IMGS; ++i) {
    UnloadTexture(player.leftWalk[i]);
    UnloadTexture(player.rightWalk[i]);
  }

  UnloadMusicStream(cyberpunkMusic);
  UnloadMusicStream(opening);
  UnloadSound(fightSound);
  UnloadSound(malwareSound);
  UnloadSound(laughSound);
  UnloadSound(bulletSound);

  for(int i=0;i<10;i++ )UnloadTexture(score[i]);
  for(int i=0;i<16;i++ )UnloadTexture(explosion[i]);
  UnloadTexture(shipInterior);
  UnloadTexture(lifebar);
  UnloadTexture(gameOver);
  
  
  UnloadTexture(player.standing);
  UnloadTexture(bg);
  UnloadTexture(beginning);
  CloseWindow();

  return 0;
}



