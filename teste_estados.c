#include <raylib.h>
#include <time.h>
#include <stdlib.h>
#include "background.h"

int main(){
    float escalaTela = 5;

    int selectedOption = 0;//menu_opções
    char *menuOptions[4] = {"start", "pokedex", "export data", "exit"};//"start-0", "pokedex-1", "export data-2", "exit-3" (menu)
    
    int frame_largura = 166; //logo
    int frame_altura = 56; //logo

    int frameAtual = 0; //logo
    float tempoFrame = 0.0f; //logo
    float tempo_max_frame = 0.09f; //logo

    int escolha = 0; // 0 for boy, 1 for girl
    int avatar_genero = -1;//armazena a escolha

    char nome[200] = { };//armazena nome

    int largura_tela = 240;
    int altura_tela = 160;

    int estado_jogo = -1;

    InitWindow(largura_tela * escalaTela, altura_tela * escalaTela, "jogo");
    SetTargetFPS(60);

    Background background[3];

    carregarBackground(background);
    Font fonte = LoadFont("recursos/fonts/pokemon_fire_red_70.ttf");
    Font fonte2 = LoadFont("recursos/fonts/pokemon_fire_red_32.ttf");
    Texture2D texturaQuadroMenu = LoadTexture("recursos/menu/menuOptions.png");//menu
    Texture2D setaMenu = LoadTexture("recursos/menu/pointer.png");
    Texture2D logo = LoadTexture("recursos/menu/logo.png");
    Texture2D boy = LoadTexture("recursos/menu/boy_escolha.png");
    Texture2D girl = LoadTexture("recursos/menu/girl_escolha.png");
    Texture2D background_avatar_escolha = LoadTexture("recursos/menu/background4.png");
    Texture2D caixa_nome = LoadTexture("recursos/menu/nome_editado.png");
    
    // Loop principal
    while (!WindowShouldClose()) {
        // Atualização e renderização aqui

        // Menu inicial (atualiza)_________________________________________________________________________________________________
        atualizaBackground(background);

        //controla o tempo do logo
        tempoFrame += GetFrameTime();
        if (tempoFrame >= tempo_max_frame) { //se o tempo que o frame deveria ficar aparente for atingido
            tempoFrame = 0.0f; //reseta o tempo
            if(frameAtual == 5){
                frameAtual = 0;
            } else {
                frameAtual++; //troca frame
            }

            if(frameAtual == 0){
                tempo_max_frame = 2.5f;
            } else {
                tempo_max_frame = 0.09f;
            }
        }

        if (IsKeyPressed(KEY_UP))//sai da primeira para última opção
        {
            selectedOption--;
            if (selectedOption < 0)
            {
                selectedOption = 3;
            }
        }
        else if (IsKeyPressed(KEY_DOWN))//sai da última para primeira opção
        {
            selectedOption++;
            if (selectedOption > 3)
            {
                selectedOption = 0;
            }
        }
        else if (IsKeyPressed(KEY_ENTER))
        {
            switch (selectedOption)
            {
            case 0:
                estado_jogo = 0;
                break;
            case 1:
                // pokedex
                break;
            case 2:
                // export data
                break;
            case 3:
                // exit
                CloseWindow();
                break;
            }
        }//menu

        if (IsKeyPressed(KEY_ONE)) {
            estado_jogo = -1; // Botão que retorna ao menu
        }

        // Menu incial(fim)___________________________________________________________________________________________________________

        // Escolha avatar (Atualiza)______________________________________________________________________________________________

        if (IsKeyPressed(KEY_LEFT))
        {
            escolha = 0;
        }
        else if (IsKeyPressed(KEY_RIGHT))
        {
            escolha = 1;
        }
        else if (IsKeyPressed(KEY_SPACE)){ 
            avatar_genero = escolha;
            estado_jogo = 1;
        }
        // Escolha avatar(fim)_________________________________________________________________________________________________________
        
        // Pede nome(atualiza)
        if (IsKeyPressed(KEY_ENTER))
        {
            CloseWindow();
        }
        else
        {
            int key = GetKeyPressed();
            int tamanho = strlen(nome);
            nome[tamanho] = (char)key;
            nome[tamanho + 1] = '\0';
        }

        BeginDrawing();

        // Limpar o fundo
        ClearBackground(WHITE);

        // Lógica baseada no estado
        switch (estado_jogo) {
            case -1:
                // Desenho menu inicial
                desenhaBackground(background, escalaTela);
                
                DrawTexturePro(texturaQuadroMenu,
                    (Rectangle) {0, 0, 104, 77},
                    (Rectangle) {600, 560, 104 * escalaTela, 77 * escalaTela},
                    (Vector2) {(104 * escalaTela)/2, (77*escalaTela)/2},
                    0,
                    WHITE);

                for (int i = 0; i < 4; i++)
                {
                    Vector2 size = MeasureTextEx(fonte, menuOptions[i], 80, 5);

                    if (i == selectedOption)
                    {
                        DrawTexturePro(setaMenu,
                            (Rectangle) {0, 0, 6, 10},
                            (Rectangle) {(600-(size.x/2)-(6 * escalaTela)), 460 + 70 * i, 6 * escalaTela, 10 * escalaTela},
                            (Vector2) {(6 * escalaTela)/2, (10 * escalaTela)/2},
                            0,
                            WHITE);

                        DrawTextPro(
                            fonte, 
                            TextFormat("%s", menuOptions[i]),
                            (Vector2){ 600, 450 + 70 * i}, //a posição na tela onde você deseja desenhar o texto.
                            (Vector2){size.x/2,size.y/2}, //o ponto de origem do texto. Isso afeta a rotação e o alinhamento do texto.
                            0, //a rotação do texto em graus.
                            80, //tamaho
                            5, //spacing
                            GRAY
                        );
                    }
                    else
                    {
                        DrawTextPro(
                            fonte,
                            TextFormat("%s", menuOptions[i]),
                            (Vector2){ 600, 450 + 70 * i},
                            (Vector2){size.x/2,size.y/2},
                            0,
                            80,
                            5,
                            GRAY
                        );
                    }
                }

                // Definir as coordenadas e dimensões do frame atual //logo
                Rectangle origem_retangulo = { 0, frameAtual * frame_altura, frame_largura, frame_altura };
                Rectangle destino_retangulo = { 
                    (largura_tela*escalaTela) / 2 - (frame_largura*escalaTela) / 2, 
                    (altura_tela*escalaTela) / 5 - (frame_altura*escalaTela) / 2, 
                    frame_largura*escalaTela, 
                    frame_altura*escalaTela};

                // Desenhar o frame atual
                DrawTexturePro(logo, origem_retangulo, destino_retangulo, (Vector2){ 0, 0 }, 0.0f, WHITE);
                        // desenho menu incial (fim)
            break;
            
            case 0:
                DrawTexturePro(background_avatar_escolha,
                    (Rectangle){0, 0, background_avatar_escolha.width, background_avatar_escolha.height},
                    (Rectangle){0, 0, background_avatar_escolha.width * escalaTela, background_avatar_escolha.height * escalaTela},
                    (Vector2){0, 0},
                    0,
                    WHITE);

                if (escolha == 0)
                {
                    DrawTexturePro(boy, 
                    (Rectangle){0, 0, boy.width, boy.height}, 
                    (Rectangle){(largura_tela*escalaTela)/4 - (boy.width*escalaTela)/2, (altura_tela*escalaTela)/2 - (boy.height*escalaTela)/2, boy.width*escalaTela, boy.height*escalaTela},
                    (Vector2) {0,0},
                    0,
                    WHITE);
                    DrawTexturePro(girl,
                    (Rectangle){0, 0, girl.width, girl.height},
                    (Rectangle){(largura_tela*escalaTela)*3/4 - (girl.width*escalaTela)/2, (altura_tela*escalaTela)/2 - (girl.height*escalaTela)/2, girl.width*escalaTela, girl.height*escalaTela},
                    (Vector2){0,0},
                    0,
                    GRAY);
                }
                else
                {
                    DrawTexturePro(boy, 
                    (Rectangle){0, 0, boy.width, boy.height}, 
                    (Rectangle){(largura_tela*escalaTela)/4 - (boy.width*escalaTela)/2, (altura_tela*escalaTela)/2 - (boy.height*escalaTela)/2, boy.width*escalaTela, boy.height*escalaTela},
                    (Vector2) {0,0},
                    0,
                    GRAY);
                    DrawTexturePro(girl,
                    (Rectangle){0, 0, girl.width, girl.height},
                    (Rectangle){(largura_tela*escalaTela)*3/4 - (girl.width*escalaTela)/2, (altura_tela*escalaTela)/2 - (girl.height*escalaTela)/2, girl.width*escalaTela, girl.height*escalaTela},
                    (Vector2){0,0},
                    0,
                    WHITE);
                }

                Vector2 tamanho_fonte2 = MeasureTextEx(fonte2, "Escolha Seu Avatar:", 55, 3.5);

                DrawTextPro(
                    fonte2, 
                    "Escolha Seu Avatar:",
                    (Vector2){(largura_tela*escalaTela/2)+3, ((altura_tela*escalaTela)*26/30)+3}, //a posição na tela onde você deseja desenhar o texto.
                    (Vector2){tamanho_fonte2.x/2,tamanho_fonte2.y/2}, //o ponto de origem do texto. Isso afeta a rotação e o alinhamento do texto.
                    0, //a rotação do texto em graus.
                    55, //tamaho
                    3.5, //spacing
                    DARKGRAY
                );

                DrawTextPro(
                    fonte2, 
                    "Escolha Seu Avatar:",
                    (Vector2){largura_tela*escalaTela/2, (altura_tela*escalaTela)*26/30}, //a posição na tela onde você deseja desenhar o texto.
                    (Vector2){tamanho_fonte2.x/2,tamanho_fonte2.y/2}, //o ponto de origem do texto. Isso afeta a rotação e o alinhamento do texto.
                    0, //a rotação do texto em graus.
                    55, //tamaho
                    3.5, //spacing
                    WHITE
                );

            break;
            case 1:
                DrawTexturePro(background_avatar_escolha,
                    (Rectangle){0, 0, background_avatar_escolha.width, background_avatar_escolha.height},
                    (Rectangle){0, 0, background_avatar_escolha.width * escalaTela, background_avatar_escolha.height * escalaTela},
                    (Vector2){0, 0},
                    0,
                    WHITE);
                
                DrawTexturePro(caixa_nome,
                    (Rectangle){0, 0, caixa_nome.width, caixa_nome.height},
                    (Rectangle){(largura_tela*escalaTela)/2, (altura_tela*escalaTela)/2, caixa_nome.width*escalaTela, caixa_nome.height*escalaTela},
                    (Vector2){caixa_nome.width*escalaTela/2,caixa_nome.height*escalaTela/2},
                    0,
                    WHITE);

            break;

            default:
                break;
        }

        // Outras operações de desenho aqui

        EndDrawing();
    }

    descarregarBackground(background);
    UnloadFont(fonte);
    UnloadFont(fonte2);
    UnloadTexture(texturaQuadroMenu);
    UnloadTexture(setaMenu);
    UnloadTexture(logo);
    UnloadTexture(boy);
    UnloadTexture(girl);
    CloseWindow();

    return 0;
}