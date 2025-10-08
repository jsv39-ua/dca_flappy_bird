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
    int puntos;
    int height;
    int width;
};

struct PipePair {
    Rectangle top, bot;
    bool scored=false;
};





class MainGameState : public GameState
{
    public:
        MainGameState();
        ~MainGameState();

        void init() override;
        void handleInput() override;
        void update(float deltaTime) override;
        void render() override;

        void pause(){};
        void resume(){};

    
    private:
        char entered_key;
        Bird player;
        Texture2D birdSprite;
        Texture2D pipeSprite;
        Texture2D background;
        std::deque<PipePair> tuberias;

        // Dimensiones de las tuberías
        const int anchoTubo = 50;
        const int altoTubo = 50;
        const int PIPE_SPEED = 70;

        float spawnTimer;
        float spawnEvery;
        float PIPE_W = 32;
        float PIPE_H = 320;
        float PIPE_GAP;
        float PLAYER_RADIUS = 17;
        float DIFFICULTY = 1.0f;

        // Animacion de morir
        bool isDying = false;
        float deathTimer = 0.0f;
        float deathDelay = 1.5f;

        // Comprobar que se haya reproducido sonido de golpe
        bool hitSoundPlayed = false;

        Sound flapSound;
        Sound dieSound;
        Sound hitSound;
        Sound pointSound;
};