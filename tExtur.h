#ifndef TEXTUR_H_INCLUDED
#define TEXTUR_H_INCLUDED

void Load_Texture( char *filename, GLuint *textureID, int swarp, int twarp, int filter);
void Show_Background(GLuint texture);
void Sprite_animation(GLuint texture, int n, int frameLine, float posX, float posY, bool lookRight);

#endif // TEXTUR_H_INCLUDED
