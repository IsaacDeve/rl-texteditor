#define MAX_GLOWIES 100

#include "raylib.h"
#include <iostream>
#include <string>
#include <random>

static int backspaceDelay = 0;

std::string pathLoaded = "";
std::string currentText = "";
bool ableType = true;

int letterCount = 0;
int key;

typedef struct Character {

} Character;

Color GetRandomRGB(bool alpha = false) {
    return {
        (unsigned char)(rand() % 256),
        (unsigned char)(rand() % 256),
        (unsigned char)(rand() % 256),
        (unsigned char)(alpha ? rand() % 256 : 255)
    };
}

int main(void) {

    Vector2 lightPos = { 400, 300 };
    float radius = 50.0f;



    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(GetScreenWidth(), GetScreenHeight(), "rlte");

    Font font = LoadFontEx("C:/Windows/Fonts/consola.ttf", 32, nullptr, 250);

    SetTargetFPS(240); 

    while (!WindowShouldClose()) {
        key = GetCharPressed();
        if ((key >= 32) && (key <= 125) && (key > 0) && (letterCount < 1023)) {
            currentText += (char)key;
            letterCount++;
        }

        if (IsKeyPressed(KEY_ENTER)) {
            currentText += '\n';
            letterCount++;
        }

        if (IsKeyPressed(KEY_BACKSPACE) && letterCount > 0) {
            currentText.pop_back();
            letterCount--;
            backspaceDelay = 0;
        }
        else if (IsKeyDown(KEY_BACKSPACE) && letterCount > 0) {
            backspaceDelay++;
            if (backspaceDelay > 35000 * GetFrameTime() && backspaceDelay % 2 == 0) {
                currentText.pop_back();
                letterCount--;
            }
        }
        else {
            backspaceDelay = 0;
        }
    BeginDrawing();


    ClearBackground(BLACK);
    Vector2 pos = {10, 10};
    for (char c : currentText) {
        if (c == '\n') {
            pos.y += 30;
            pos.x = 10;
            continue;
        }
        std::string s(1, c);
        DrawTextEx(font, s.c_str(), pos, 30, 0, WHITE);
        DrawCircleGradient(pos.x + 8, pos.y+25/2, 35, Fade(GetRandomRGB(), 0.3f), Fade(BLANK, 0.0f));
        pos.x += MeasureTextEx(font, s.c_str(), 30, 0).x;
    }
    

    DrawCircleGradient(GetMouseX(), GetMouseY(), radius, Fade(YELLOW, 0.4f), Fade(BLANK, 0.0f));


    EndDrawing();

    }
    return 0;
}