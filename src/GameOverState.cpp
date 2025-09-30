#include <GameOverState.hpp>
#include <iostream>
#include <StateMachine.hpp>
#include <MainGameState.hpp>



GameOverState::GameOverState(){

}

GameOverState::GameOverState(int puntos){
    this->finalScore = puntos;
}

void GameOverState::init(){


}

void GameOverState::handleInput(){

    if (IsKeyPressed(KEY_SPACE)){
        this->state_machine->add_state(std::make_unique<MainGameState>(), true);

    }
    


}

void GameOverState::update(float deltaTime) {

}

void GameOverState::render(){

    BeginDrawing();
    ClearBackground(BLACK);

    DrawText("Game Over", 288/2, 512/2, 15, YELLOW);
    DrawText(TextFormat("Punticos: %i", finalScore), 50, 100, 20, YELLOW);


    EndDrawing();

}