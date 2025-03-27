#include <iostream>

#include "mode_editor.hpp"
#include "camera.hpp"
#include "modes.hpp"

namespace mode_editor {

    static int backspaceDelay = 0;
    int cursor = 0;

    std::string pathLoaded = "";
    std::string currentText = "";
    bool ableType = true;

    int letterCount = 0;
    int key;

    Vector2 curPos = {0, 0};

    Font font;

    void InitEditor() {
        current_mode = MODE_EDITOR;
        font = LoadFont("C:/Windows/Fonts/consola.ttf");
    }

    Color GetRandomRGB(bool alpha) {
        return {
            (unsigned char)(rand() % 256),
            (unsigned char)(rand() % 256),
            (unsigned char)(rand() % 256),
            (unsigned char)(alpha ? rand() % 256 : 255)
        };
    }

    void Update() {
        camera::Update(curPos);
        if (IsKeyDown(KEY_RIGHT_CONTROL)) {
            if (IsKeyPressed(KEY_RIGHT))
            {
                current_mode = MODE_EXPLORER;
                std::cout << "Switched to MODE_EXPLORER" << std::endl;
            }
        }
        if (IsKeyDown(KEY_LEFT_CONTROL)) {
            if (IsKeyPressed(KEY_S)) {
                
            }
        }
    }

    void Draw() {
        if (IsKeyDown(KEY_RIGHT_CONTROL)) { return; }
        if (IsKeyDown(KEY_LEFT_CONTROL)) { return; }
        key = GetCharPressed();
        if ((key >= 32) && (key <= 125) && (key > 0) && (letterCount < 1023)) {
            currentText.insert(cursor, 1, (char)key);
            cursor++;
            letterCount++;
        }

        if (IsKeyPressed(KEY_ENTER)) {
            currentText += '\n';
            cursor++;
            letterCount++;
        }

        if (IsKeyPressed(KEY_BACKSPACE) && letterCount > 0) {
            currentText.erase(cursor - 1, 1);
            letterCount--;
            cursor--;
            backspaceDelay = 0;
        }
        else if (IsKeyDown(KEY_BACKSPACE) && letterCount > 0) {
            backspaceDelay++;
            if (backspaceDelay > 35000 * GetFrameTime() && backspaceDelay % 2 == 0) {
                currentText.erase(cursor - 1, 1);
                cursor--;
                letterCount--;
            }
        }
        else {
            backspaceDelay = 0;
        }

        if (IsKeyPressed(KEY_LEFT) && cursor > 0) cursor--;
        if (IsKeyPressed(KEY_RIGHT) && cursor < currentText.length()) cursor++;

        int symbol = 0;
        Vector2 pos = {10, 10};
        for (char c : currentText) {
            if (symbol == cursor) {
                DrawRectangle(pos.x, pos.y, 2, 30, WHITE);
                curPos = pos;
            }
    
            if (c == '\n') {
                pos.y += 30;
                pos.x = 10;
            } else {
                DrawTextEx(font, std::string(1, c).c_str(), pos, 30, 0, WHITE);
                pos.x += MeasureTextEx(font, std::string(1, c).c_str(), 30, 0).x;
            }
    
            DrawCircleGradient(pos.x - 10, pos.y + 25 / 2, 50, Fade(GetRandomRGB(), 0.3f), Fade(BLANK, 0.0f));
            symbol++;
        }
        if (cursor == currentText.length()) {
            DrawRectangle(curPos.x, curPos.y+23, 20, 2, WHITE);
            curPos = pos;
        }

        if (cursor < 0) cursor = 0;
        if (cursor > currentText.length()) cursor = currentText.length();

    }
}