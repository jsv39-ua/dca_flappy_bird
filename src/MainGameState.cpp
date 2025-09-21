#include <MainGameState.hpp>
#include <iostream>
extern "C" {
 #include <raylib.h>
}

MainGameState::MainGameState()
{
    BeginDrawing();
    DrawText("Bienvenido a Flappy Bird DCA", 50, 50, 5, YELLOW);
    EndDrawing();
}

void MainGameState::init()
{

}

void MainGameState::handleInput()
{

}

void MainGameState::update(float deltaTime)
{

}

void MainGameState::render()
{

}