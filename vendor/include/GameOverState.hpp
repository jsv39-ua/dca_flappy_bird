#pragma once
#include <deque>
#include <GameState.hpp>
extern "C" {
 #include <raylib.h>
}

class GameOverState : public GameState {

    public:
        GameOverState();
        GameOverState(int puntos);
        ~GameOverState  () = default;

        void init() override;
        void handleInput() override;
        void update(float deltaTime) override;
        void render() override;

        void pause(){};
        void resume(){};

    private:
        int finalScore;
};