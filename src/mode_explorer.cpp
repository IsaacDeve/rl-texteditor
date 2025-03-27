#include "mode_explorer.hpp"
#include "modes.hpp"
#include <iostream>

namespace mode_explorer {
    void Update() {
        if (IsKeyDown(KEY_RIGHT_CONTROL)) {
            if (IsKeyPressed(KEY_LEFT))
            {
                current_mode = MODE_EDITOR;
                std::cout << "Switched to MODE_EDITOR" << std::endl;
            }
        }
    }

    void Draw()
    {
        DrawText("Explorer Mode", 10, 10, 20, WHITE);
    }
}