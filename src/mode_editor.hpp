#pragma once
#include "raylib.h"
#include <string>

namespace mode_editor {
    extern Camera2D camera;
    extern int backspaceDelay;
    extern int cursor;
    extern std::string pathLoaded;
    extern std::string currentText;
    extern bool ableType;
    extern int letterCount;
    extern int key;
    extern Vector2 curPos;
    extern Font font;

    void InitEditor();

    Color GetRandomRGB(bool alpha = false);
    void Update();
    void Draw();
}
