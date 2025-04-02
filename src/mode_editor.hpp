#pragma once
#include "raylib.h"
#include <string>

namespace mode_editor {
    extern Camera2D camera;
    extern int fontSize;

    extern int deleteDelay;
    extern int backspaceDelay;

    extern int cursorLeftDelay;
    extern int cursorRightDelay;

    extern int delayTime;
    
    extern int cursor;

    extern float screenLeft;
    extern float screenRight;
    extern float screenTop;
    extern float screenBottom;

    extern std::string pathLoaded;
    extern std::string currentText;
    extern bool ableType;
    extern int letterCount;
    extern int key;
    extern Vector2 curPos;
    extern Font font;

    bool IsOnScreen(Vector2& pos);
    void InitEditor();

    Color GetRandomRGB(bool alpha = false);
    void Update();
    void Draw();
}
