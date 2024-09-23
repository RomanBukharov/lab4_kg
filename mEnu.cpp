#include <gl/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "menu.h"
#include "stb-master/stb_easy_font.h"

#include "tExtur.h"



Button *btn;
int btnCnt = 0;

float mouseX,mouseY;
int animationLine = 0;
float ss1 = 2;
float ss2 = 2;
float ss3 = 2;

void print_string(float x, float y, char *text, float r, float g, float b)
{

    static char buffer[99999];
    int num_quads;
    stb_easy_font_width(text);

    num_quads = stb_easy_font_print(x, y, text, NULL, buffer, sizeof(buffer));

    glColor3f(r,g,b);

    glEnableClientState(GL_VERTEX_ARRAY);

    glVertexPointer(2, GL_FLOAT, 16, buffer);

    glDrawArrays(GL_QUADS, 0, num_quads*4);
    glDisableClientState(GL_VERTEX_ARRAY);

}


int Menu_AddButton(char *name, float x, float y, float width, float height, float textS)
{
    btnCnt++;
    btn = (Button*)realloc(btn, sizeof(btn[0])*btnCnt);

    snprintf(btn[btnCnt-1].name, nameLen, "%s", name);
    float *vert = btn[btnCnt-1].vert;
    vert[0]=vert[6]=x;
    vert[2]=vert[4]=x+width;
    vert[1]=vert[3]=y;
    vert[5]=vert[7]=y+height;
    btn[btnCnt-1].isHover=0;
    btn[btnCnt-1].isDown=0;

    Button *b= btn + btnCnt - 1;
    b->num_quads = stb_easy_font_print(0, 0, name,0,b->buffer, sizeof(b->buffer));
    b->textPosX = x +(width-stb_easy_font_width(name)*textS)/2.0;
    b->textPosY = y +(height-stb_easy_font_height(name)*textS)/2.0;
    b->textPosY+= textS*2;
    b->textS = textS;

    return btnCnt-1;
}

void ShowButton(int buttonId)
{
    Button btn1 = btn[buttonId];
    glVertexPointer(2, GL_FLOAT, 0, btn1.vert);
    glEnableClientState(GL_VERTEX_ARRAY);

    if (btn1.isHover){
        glColor3f(0.1f, 0.5f, 0.1f);
    }
    else{
        glColor3f(0.3, 1.0, 0.6);
    }

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    glLineWidth(1);
    glDrawArrays(GL_LINE_LOOP,0,4);
    glDisableClientState(GL_VERTEX_ARRAY);

    glPushMatrix();
    glTranslatef(btn1.textPosX,btn1.textPosY,0);
    glScalef(btn1.textS,btn1.textS,0);

    glColor4f(1.0f, 0.0f, 0.0f, 0.0f);//text

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 16, btn1.buffer);
    glDrawArrays(GL_QUADS, 0, btn1.num_quads*4);
    glDisableClientState(GL_VERTEX_ARRAY);
    glPopMatrix();
    glColor3f(1,1,1);
}

void Menu_ShowMenu()
{
    for(int i=0; i<btnCnt; i++){
        ShowButton(i);
    }
}


char isCordInButton(int buttonID, float x, float y)
{
    float *vert=btn[buttonID].vert;
    return (x>vert[0]) && (y>vert[1]) && (x<vert[4]) && (y<vert[5]);
}

int Menu_MouseMove (float x, float y)
{
    mouseX = x;
    mouseY = y;
    int movebtn=-1;
    for (int i=0; i<btnCnt; i++)
        if (isCordInButton(i, mouseX, mouseY))
        {
            btn[i].isHover =1;
            movebtn = i;
        }
        else
        {
            btn[i].isDown=0;
            btn[i].isHover=0;
        }
    return movebtn;
}

int Menu_MouseDown()
{
    int downbtn=-1;
    for (int i=0; i<btnCnt; i++)
        if (isCordInButton(i, mouseX, mouseY))
        {
            btn[i].isDown =1;
            downbtn = i;
        }
    return downbtn;
}

char *Menu_GetButtonName(int buttonID)
{
return btn[buttonID].name;
}

void Menu_changeState(){
    if(menuProperties.isActive == false)
        menuProperties.isActive = true;
    else
        menuProperties.isActive = false;
}

void Menu_Clear()
{
    btnCnt=0;
    free(btn);
    btn=0;
}

void MouseDown()
{
    int buttonId = Menu_MouseDown();
    if(buttonId<0) return;
    char *name = Menu_GetButtonName(buttonId);
    switch (buttonId)
    {
    case 0://play
        Menu_Clear();
        Menu_changeState();

        break;
    case 1://exit
        PostQuitMessage(0);
        break;
    }
}

int getAnimationLine()
{
    return animationLine;
}

int getButtonId(int current)
{
    int buttonId = Menu_MouseDown();
    if(buttonId < 0 || buttonId > 2) return current;
    return buttonId;
}
