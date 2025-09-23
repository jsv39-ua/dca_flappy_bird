#include <MainGameState.hpp>
#include <iostream>
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
}

void MainGameState::handleInput()
{
    if(IsKeyPressed(KEY_SPACE)){
        player.vy += -300;
    }
}

void MainGameState::update(float deltaTime)
{
    player.vy += 98 * deltaTime;
    player.y += player.vy * deltaTime;
}

void MainGameState::render()
{

    BeginDrawing();
    ClearBackground(BLACK);
    DrawText("Bienvenido a Flappy Bird DCA", 50, 50, 15, YELLOW);
    DrawCircle(player.x, player.y, 17, RED);
    EndDrawing();
}