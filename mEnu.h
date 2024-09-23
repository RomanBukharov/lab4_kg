#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#define nameLen 20

typedef struct
{
    char name[nameLen];
    float vert[8];
    char isHover, isDown;
    //text
    float buffer[50*nameLen];
    int num_quads;
    float textPosX,textPosY,textS;
} Button;

struct Menu
{
    bool isActive = false;
};
extern Menu menuProperties;

int Menu_AddButton(char *name, float x, float y, float width, float height, float textS);
void Menu_ShowMenu();
int Menu_MouseMove(float x, float y);
int Menu_MouseDown();
int Menu_MouseUp();
char *Menu_GetButtonName(int buttonID);
void Menu_Clear();
void MouseDown();
int getButtonId(int current);
int getAnimationLine();
void Menu_changeState();
void print_string(float x, float y, char *text, float r, float g, float b);



#endif // MENU_H_INCLUDED
