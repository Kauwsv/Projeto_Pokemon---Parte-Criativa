#include "background.h"

void carregarBackground(Background background[]){
    for(int i = 0; i < 3; i++){
        background[i].textura = LoadTexture(TextFormat("recursos/menu/background%d.png", i+1));
        background[i].posicao1 = (Vector2){-(background[i].textura.width), 0};
        background[i].posicao2 = (Vector2){0, 0};
    }
        
    background[2].posicao1.y = 25;
    background[2].posicao2.y = 25;

    background[0].velocidade = 0.2;
    background[1].velocidade = 0.8;
    background[2].velocidade = 1.2;
    return;
}

void descarregarBackground(Background background[]){
    for(int i = 0; i < 3; i++){
       UnloadTexture(background[i].textura);
    }
    return;
}

void desenhaBackground(Background background[], float escalaTela){
    for(int i = 0; i < 3; i++){
        DrawTexturePro(background[i].textura,
         (Rectangle){0, 0, background[i].textura.width, background[i].textura.height},
         (Rectangle){background[i].posicao1.x * escalaTela, background[i].posicao1.y * escalaTela, background[i].textura.width * escalaTela, background[i].textura.height * escalaTela},
         (Vector2){0, 0},
         0,
         WHITE);

         DrawTexturePro(background[i].textura,
         (Rectangle){0, 0, background[i].textura.width, background[i].textura.height},
         (Rectangle){(background[i].posicao2.x) * escalaTela, background[i].posicao2.y * escalaTela, background[i].textura.width * escalaTela, background[i].textura.height * escalaTela},
         (Vector2){0, 0},
         0,
         WHITE);
    }
    return;
}

void atualizaBackground(Background background[]){
    for(int i = 0; i < 3; i++){
        background[i].posicao1.x -= background[i].velocidade;
        background[i].posicao2.x -= background[i].velocidade;

        if(background[i].posicao1.x <= -(background[i].textura.width)){
            background[i].posicao1.x = (background[i].posicao2.x + background[i].textura.width);
        }

        if(background[i].posicao2.x <= -(background[i].textura.width)){
            background[i].posicao2.x = (background[i].posicao1.x + background[i].textura.width);
        }
    }
    return;
}