#define MAX_GLOWIES 100

#include "raylib.h"
#include <iostream>
#include <string>
#include <random>

#include "mode_editor.hpp"
#include "mode_explorer.hpp"

#include "camera.hpp"

#include "modes.hpp"

int main(void) {

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(GetScreenWidth(), GetScreenHeight(), "rlte");

    mode_editor::InitEditor();


    SetTargetFPS(240); 


    try {
        while (!WindowShouldClose()) {
        
            BeginDrawing();
        
            ClearBackground(BLACK);
        
            switch(current_mode) {
                case MODE_EDITOR: {
                    mode_editor::Update();
                    mode_editor::Draw();
                    break;
                }
                case MODE_EXPLORER: {
                    mode_explorer::Update();
                    mode_explorer::Draw();
                    break;
                }
            }
        
            EndDrawing();
        
        }
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }


    UnloadFont(mode_editor::font);
    CloseWindow();
    return 0;
}