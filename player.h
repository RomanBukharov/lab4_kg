#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#define WALK 0
#define STAY 1
#define JUMP 2
#define RIGHT 0
#define LEFT 1

struct Player
{
    float velocity = 3;
    float jumpHeight=-1.0;
    float gravity=20.0;
    float posX=0.0;
    float posY=130.0;
    bool isOnFloor = true;
    bool lookRight = true;
    int frameLine = 2;

};
extern Player player;

void Player_Move();
float checkCollisionHorizontal(float deltaX, float deltaY, int side);
int checkCollisionVertical(float deltaX, float deltaY, int side);


#endif // PLAYER_H_INCLUDED
