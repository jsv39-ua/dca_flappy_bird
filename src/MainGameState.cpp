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
    player.x = 200;
    player.y = 200;
    spawnTimer = 0;
    
    
}

void MainGameState::handleInput()
{
    if(IsKeyPressed(KEY_SPACE)){
        player.vy = -300;
    }
}

void MainGameState::update(float deltaTime)
{
    player.vy += 500 * deltaTime;
    player.y += player.vy * deltaTime;

    if(spawnTimer > spawnEvery * deltaTime){
        float pipe_y_offset_top = GetRandomValue(PIPE_H ,GetScreenWidth()/2);
        float x_top = GetScreenWidth();
        Rectangle tuboArriba = {x_top, -pipe_y_offset_top, PIPE_W, PIPE_H};
        Rectangle tuboAbajo = {x_top, (PIPE_H - pipe_y_offset_top) + GetRandomValue(PIPE_H/2, GetScreenWidth()/2), PIPE_W, PIPE_H};
        
        PipePair parTubo = {tuboArriba, tuboAbajo};

        tuberias.push_back(parTubo);
        
    };

    // Se pasa por referencia para poder actualizar los tubos reales y no copias suyas
    for (PipePair& parTuberia : tuberias){
    
    parTuberia.top.x -= PIPE_SPEED * deltaTime;
    parTuberia.bot.x -= PIPE_SPEED * deltaTime;

    if(tuberias.front().top.x < 0){
        tuberias.pop_front();
        };
    };
}

void MainGameState::render()
{

    BeginDrawing();
    ClearBackground(BLACK);
    DrawText("Bienvenido a Flappy Bird DCA", 50, 50, 15, YELLOW);
    DrawCircle(player.x, player.y, 17, RED);

    for(PipePair tuberia : tuberias){
        
    }
    EndDrawing();
}