#pragma once
#include <deque>
#include <GameState.hpp>
extern "C" {
 #include <raylib.h>
}

struct Bird{
    float x;
    float y;
    float vy;
};

struct PipePair {
    Rectangle top, bot;
    bool scored=false;
};





class MainGameState : public GameState
{
    public:
        MainGameState();
        ~MainGameState() = default;

        void init() override;
        void handleInput() override;
        void update(float deltaTime) override;
        void render() override;

        void pause(){};
        void resume(){};

    
    private:
        char entered_key;
        Bird player;
        std::deque<PipePair> tuberias;

        // Dimensiones de las tuberías
        const int anchoTubo = 50;
        const int altoTubo = 50;
        const int PIPE_SPEED = 50;

        float spawnTimer;
        float spawnEvery;
        float PIPE_W = 32;
        float PIPE_H = 320;
};