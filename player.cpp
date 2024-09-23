#include <gl/gl.h>
#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <malloc.h>
#include "player.h"

#include <time.h>

int collisionMap[15][21] = {
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0},
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0},
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0},
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0},
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}
};

void Player_Move(){


    if(checkCollisionVertical(75,150,0) != 1 && checkCollisionVertical(75,150,1) != 2){
        player.posY+=player.gravity/2;
    } else {
        player.isOnFloor = true;
    }

    if (GetKeyState(VK_SPACE) < 0 && player.isOnFloor == true && checkCollisionVertical(75,150,LEFT) == 1 ){
        player.jumpHeight = 55;
        player.isOnFloor=false;
        player.frameLine = STAY;
    }

    if (GetKeyState('D') < 0 ){
        player.lookRight = true;
        player.posX += checkCollisionHorizontal(100, 0.0, 1);
        if(player.isOnFloor){
            player.frameLine = WALK;
        }
    } else if (GetKeyState('A') < 0) {
        player.lookRight = false;
        player.posX -= checkCollisionHorizontal(0, 0.0, LEFT);

        if(player.isOnFloor){
            player.frameLine = WALK;
        }
    } else if (player.isOnFloor){
        player.frameLine = JUMP;
    }

    if(player.jumpHeight == -1){
        player.isOnFloor = true;
    } else if(player.isOnFloor == false){
        player.posY -= player.jumpHeight - player.gravity;
        player.jumpHeight -= 1;
    }
}

float checkCollisionHorizontal(float deltaX, float deltaY, int side){
    int x = floor((player.posX + 0 + deltaX)/50);
    int y = floor((player.posY + 111 + deltaY)/50);
    if(collisionMap[y][x] == 2){
        printf("%s\n", "hh");
        collisionMap[y][x] = 0;
    }
    if(collisionMap[y][x+side] == 0 || collisionMap[y][x+side] == 2){
        return player.velocity;
    } else {
        return 0;
    }
}

int checkCollisionVertical(float deltaX, float deltaY, int side){
    int x = floor((player.posX - 0 + deltaX)/50);
    int y = floor((player.posY + 0 + deltaY)/50);
    for(int i = 1; i <= 1; i++){
        if (collisionMap[y][x] == 2){
            printf("%s\n", "vv");
            collisionMap[y][x] = 0;

        } else if(collisionMap[y][x] == 1 || collisionMap[y][x+1] == 1 ){
            return 1;
        } else if(collisionMap[y][x] == 0 ){
            return 0;
        } else {
            return -1;
        }
    }
}

void respawnEgg(int x){
    srand(time(NULL));

    int num = 1 + rand() % (20 - 1 + 1);
    while(x == num){
        int num = 1 + rand() % (20 - 1 + 1);
    }

    for (int i = 0; i < 15; i++){
        if(collisionMap[i][num] == 1){
            collisionMap[i-1][num] = 2;
            return;
        }
    }
}
