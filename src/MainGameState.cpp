#include <MainGameState.hpp>
#include <iostream>
#include <deque>
extern "C" {
 #include <raylib.h>
}



MainGameState::MainGameState()
{
    
}

void MainGameState::init()
{
    player.x = 150;
    player.y = 200;
    spawnTimer = 0;
    spawnEvery = 250;

    SetTargetFPS(60);
    
}

void MainGameState::handleInput()
{   
    // Salto
    if(IsKeyPressed(KEY_SPACE)){
        player.vy = -300;
    }
}

void MainGameState::update(float deltaTime)
{   
    // Gravedad y velocidad vertical del jugador
    player.vy += 550 * deltaTime;
    player.y += player.vy * deltaTime;

    // Caja de colision para el jugador

    Rectangle playerCol = {player.x - PLAYER_RADIUS / 2 , player.y - PLAYER_RADIUS / 2 , PLAYER_RADIUS , PLAYER_RADIUS};

    
    // Velocidad a la que aumenta el timer
    spawnTimer += 1 * deltaTime;

    DrawText(TextFormat("Next pipe in: %f", spawnEvery * deltaTime), 50, 70, 20, YELLOW);

    // Spawnear tubos cada spawnEvery
    if(spawnTimer >= spawnEvery * deltaTime){
        float pipe_y_offset_top = GetRandomValue(PIPE_H ,GetScreenWidth()/2);
        float x_top = GetScreenWidth();
        Rectangle tuboArriba = {x_top, -pipe_y_offset_top, PIPE_W, PIPE_H};
        Rectangle tuboAbajo = {x_top, (PIPE_H - pipe_y_offset_top) + GetRandomValue(PIPE_H/2, GetScreenWidth()/2), PIPE_W, PIPE_H};
        
        PipePair parTubo = {tuboArriba, tuboAbajo};

        tuberias.push_back(parTubo);
        
        spawnTimer = 0;
    };

    

    // Se pasa por referencia para poder actualizar los tubos reales y no copias suyas
    for (PipePair& parTuberia : tuberias){
    
    parTuberia.top.x -= PIPE_SPEED * deltaTime;
    parTuberia.bot.x -= PIPE_SPEED * deltaTime;

    if(tuberias.front().top.x < 0){
        tuberias.pop_front();
        };


        /*************************************/
        // Calcular colisiones jugador/tuberia
        
        if (CheckCollisionRecs(parTuberia.top, playerCol) || CheckCollisionRecs(parTuberia.bot, playerCol)){
            // Enviar a pantalla de gameover
            std::cout << "Colision!!" << std::endl;
        }
    };

    

    
}

void MainGameState::render()
{

    BeginDrawing();
    ClearBackground(BLACK);
    
    DrawText("Bienvenido a Flappy Bird DCA", 50, 50, 15, YELLOW);
    DrawCircle(player.x, player.y, PLAYER_RADIUS, RED);
    DrawRectanglePro({player.x - PLAYER_RADIUS / 2 , player.y - PLAYER_RADIUS / 2 , PLAYER_RADIUS , PLAYER_RADIUS}, {0, 0}, 0, BLUE);


    DrawText(TextFormat("Next pipe in: %f", spawnTimer), 50, 100, 20, RED);

    DrawFPS(GetScreenWidth() - 20, GetScreenHeight() - 20);

    for(PipePair tuberia : tuberias){
        Rectangle topPipe = tuberia.top;
        Rectangle botPipe = tuberia.bot;

        DrawRectangle(topPipe.x, topPipe.y, topPipe.width, topPipe.height, GREEN);
        DrawRectangle(botPipe.x, botPipe.y, botPipe.width, botPipe.height, GREEN);
    }
    EndDrawing();
}