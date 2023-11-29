#include <raylib.h>

#ifndef BACKGROUND_H
#define BACKGROUND_H

typedef struct{
    Texture2D textura;
    Vector2 posicao1;
    Vector2 posicao2;
    float velocidade; 
} Background;

void carregarBackground(Background background[]);
void descarregarBackground(Background background[]);
void desenhaBackground(Background background[], float escalaTela);
void atualizaBackground(Background background[]);

#endif