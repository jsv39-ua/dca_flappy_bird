#include <StateMachine.hpp>
#include <MainGameState.hpp>
#include <memory>
#include <chrono>
extern "C" {
 #include <raylib.h>
}
#include <iostream>


int main()
{ 
    float delta_time = 0.0f;

    

    int screenWidth = 288;
    int screenHeight = 512;

    InitWindow(screenWidth, screenHeight, "ventana basica");

    InitAudioDevice();

    // Esperar a que cargue el audio device
    WaitTime(0.1);

    // Verificar que el dispositivo de audio esté inicializado
    if (!IsAudioDeviceReady()) {
        std::cerr << "Error: No se pudo inicializar el dispositivo de audio" << std::endl;
        CloseWindow();
        return -1;
    }
    
    StateMachine state_machine = StateMachine();
    state_machine.add_state(std::make_unique<MainGameState>(), false);
    state_machine.handle_state_changes(delta_time);



    while (!WindowShouldClose())
    {
        delta_time = GetFrameTime();
        state_machine.handle_state_changes(delta_time);
        state_machine.getCurrentState()->handleInput();
        state_machine.getCurrentState()->update(delta_time);
        state_machine.getCurrentState()->render();       
    }

    CloseAudioDevice();
    CloseWindow();
    
    return 0;
}