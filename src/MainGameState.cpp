#include <MainGameState.hpp>
#include <iostream>
#include <deque>
#include <GameOverState.hpp>
#include <StateMachine.hpp>
extern "C" {
 #include <raylib.h>
}



MainGameState::MainGameState()
{
    
}

// Cosas que hacer al destruir el estado, como descargar sonidos
MainGameState::~MainGameState(){

    UnloadSound(dieSound);
    UnloadSound(hitSound);
    UnloadSound(flapSound);
    UnloadSound(pointSound);

    UnloadTexture(birdSprite);
    UnloadTexture(pipeSprite);
    UnloadTexture(background);
    
}

void MainGameState::init()
{
    player.x = 150;
    player.y = 200;
    player.vy = 0;
    player.puntos = 0;
    spawnTimer = 0;
    spawnEvery = 200;

    isDying = false;


    // Cargar sonidos a utilizar
    flapSound = LoadSound("sounds/wing.wav");
    dieSound = LoadSound("sounds/die.wav");
    hitSound = LoadSound("sounds/hit.wav");
    pointSound = LoadSound("sounds/point.wav");

    SetMasterVolume(1.0f);

    

    birdSprite = LoadTexture("assets/bluebird-midflap.png");
    pipeSprite = LoadTexture("assets/pipe-green.png");
    background = LoadTexture("assets/background-day.png");

    player.width = birdSprite.width;
    player.height = birdSprite.height;

    PIPE_H = pipeSprite.height;
    PIPE_W = pipeSprite.width;
    PIPE_GAP = player.height * 4.5;

    std::cout<<"Pipe_H y Pipe_W = "<<PIPE_H<<" "<<PIPE_W<<std::endl;

    SetTargetFPS(60);
    
}

void MainGameState::handleInput()
{      

    if(isDying){
        return;
    }

    // Salto
    if(IsKeyPressed(KEY_SPACE)){
        player.vy = -200;
        PlaySound(flapSound);
    }
}

void MainGameState::update(float deltaTime)
{   
    // Gravedad y velocidad vertical del jugador
    player.vy += 550 * deltaTime;
    player.y += player.vy * deltaTime;

    DIFFICULTY += 0.0005;
    PIPE_GAP -= 0.001;

    // Caja de colision para el jugador

    Rectangle playerCol = {player.x, player.y + (float)5.0, (float)player.width , (float)player.height - (float)10.0};

    
    // Velocidad a la que aumenta el timer
    spawnTimer += 1 * deltaTime;

    // Spawnear tubos cada spawnEvery
    if(spawnTimer >= spawnEvery * deltaTime){

        float pipe_y_offset_top = GetRandomValue(100, GetScreenHeight() - PIPE_GAP - 100);
        
        float x_top = GetScreenWidth();

        Rectangle tuboArriba = {x_top, pipe_y_offset_top - PIPE_H, PIPE_W, PIPE_H};
        Rectangle tuboAbajo  = {x_top, pipe_y_offset_top + PIPE_GAP, PIPE_W, PIPE_H};
        
        PipePair parTubo = {tuboArriba, tuboAbajo};

        tuberias.push_back(parTubo);
        
        spawnTimer = 0;
    };

    
    // Dejar de renderizar tuberias pasadas
    // Se pasa por referencia para poder actualizar los tubos reales y no copias suyas
    for (PipePair& parTuberia : tuberias){
    
        parTuberia.top.x -= DIFFICULTY * PIPE_SPEED * deltaTime;
        parTuberia.bot.x -= DIFFICULTY * PIPE_SPEED * deltaTime;

        if(tuberias.front().top.x < -PIPE_W){
            tuberias.pop_front();
        };


        /*************************************/
        // Calcular colisiones jugador/tuberia
            
        if (CheckCollisionRecs(parTuberia.top, playerCol) || CheckCollisionRecs(parTuberia.bot, playerCol) || (player.y < 0 || player.y > GetScreenHeight())){
            // Enviar a pantalla de gameover
            std::cout << "Colssision!!" << std::endl;
            if (!hitSoundPlayed){
                PlaySound(hitSound);
                hitSoundPlayed = true;
            }
            
            
            //std::cout<< "Isdying " << isDying <<std::endl;
            if (!isDying){
                isDying = true;
                deathTimer = 0.0f;
                player.vy = -300; // AL morir da un salto pa arriba
                PlaySound(dieSound);
            }

            

            // Aqui podria meter una animacion de muerte

            //this->state_machine->add_state(std::make_unique<GameOverState>(player.puntos), true);
        } 
        
        // Añadir puntos al jugador al pasar un tubo
        if (!parTuberia.scored && (parTuberia.top.x + PIPE_W) < player.x && !isDying) {
            player.puntos++;
            PlaySound(pointSound);
            parTuberia.scored = true;
        }
    };

    
    if (isDying) {
    deathTimer += deltaTime;
    
    if (deathTimer >= deathDelay) {
        this->state_machine->add_state(std::make_unique<GameOverState>(player.puntos), true);
    }
    return; // <- mientras está muriendo, no seguimos moviendo tubos ni sumando puntos
}

    
}

void MainGameState::render()
{

    BeginDrawing();
    ClearBackground(SKYBLUE);
    DrawTexture(background, 0, 0, WHITE);
    
    DrawText("Bienvenido a Flappy Bird DCA", 50, 50, 15, YELLOW);
    DrawTexture(birdSprite, player.x, player.y, WHITE);
    //Rectangle playerCol = {player.x, player.y + 2.5, player.width , player.height -10};
    //DrawRectangleRec(playerCol, BLUE);


    DrawText(TextFormat("Punticos: %i", player.puntos), 50, 100, 20, YELLOW);

    DrawFPS(GetScreenWidth() - 20, GetScreenHeight() - 20);

    for(PipePair p : tuberias){
        
        DrawTextureEx(this->pipeSprite, {p.top.x + PIPE_W, p.top.y + PIPE_H}, 180.f, 1.0f, WHITE);
        DrawTextureEx(this->pipeSprite, {p.bot.x , p.bot.y}, 0.f, 1.0f, WHITE);

    }
    EndDrawing();
}