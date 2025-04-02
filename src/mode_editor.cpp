#include <iostream>
#include <string>

#include <iostream>
#include <fstream> 

#include "mode_editor.hpp"
#include "camera.hpp"
#include "modes.hpp"

#include "winh.hpp"

namespace mode_editor {

    int fontSize = 30;

    static int deleteDelay = 0;
    static int backspaceDelay = 0;

    static int cursorLeftDelay = 0;
    static int cursorRightDelay = 0;

    static int delayTime = 35000;

    int cursor = 0;

    float screenLeft = camera::camera.target.x - (GetScreenWidth() / 2.0f) / camera::camera.zoom;
    float screenRight = camera::camera.target.x + (GetScreenWidth() / 2.0f) / camera::camera.zoom;
    float screenTop = camera::camera.target.y - (GetScreenHeight() / 2.0f) / camera::camera.zoom;
    float screenBottom = camera::camera.target.y + (GetScreenHeight() / 2.0f) / camera::camera.zoom;


    std::string pathLoaded = "";
    std::string currentText = "";
    bool ableType = true;

    int letterCount = 0;
    int key;

    Vector2 curPos = {0, 0};

    Font font;

    bool IsOnScreen(Vector2& pos) {
        return (
            pos.x + fontSize > 0 &&
            pos.y + fontSize > 0 &&
            pos.x < GetScreenWidth() &&
            pos.y < GetScreenHeight()
        );
    }

    void InitEditor() {

        current_mode = MODE_EDITOR;
        font = LoadFont("C:/Windows/Fonts/consola.ttf");
        camera::camera.offset = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
        camera::camera.target = { 0, 0 };
        camera::camera.rotation = 0.0f;
        camera::camera.zoom = 1.0f;

        camera::camtarget = { 0, 0 };
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
        camera::camera.target.x += (camera::camtarget.x - camera::camera.target.x) * 1.5f * GetFrameTime();
        camera::camera.target.y += (camera::camtarget.y - camera::camera.target.y) * 1.5f * GetFrameTime();
        if (IsKeyDown(KEY_RIGHT_CONTROL)) {
            if (IsKeyPressed(KEY_RIGHT))
            {
                current_mode = MODE_EXPLORER;
                std::cout << "Switched to MODE_EXPLORER" << std::endl;
            }
        }
        if (IsKeyDown(KEY_LEFT_CONTROL)) {
            if (IsKeyPressed(KEY_S)) {
                if (pathLoaded == "") {

                    std::wstring wloadedPath = winh::OpenFileDialog();
                    pathLoaded = std::string(wloadedPath.begin(), wloadedPath.end());
                }
                std::ofstream file(pathLoaded);
                file << currentText;
                file.close();
            }

            if (IsKeyDown(KEY_LEFT_SHIFT))
            {
                if (IsKeyPressed(KEY_S)) {
                    std::wstring wloadedPath = winh::OpenFileDialog();
                    pathLoaded = std::string(wloadedPath.begin(), wloadedPath.end());
                    std::ofstream file(pathLoaded);
                    file << currentText;
                    file.close();
                }
            }

            if (IsKeyPressed(KEY_L)) {
                cursor = 0;
                letterCount = 0;
                std::wstring wloadedPath = winh::OpenFileDialog();
                pathLoaded = std::string(wloadedPath.begin(), wloadedPath.end());
                std::ifstream file(pathLoaded);
                std::string line;
                currentText = "";
                char ch;
                while (file.get(ch)) {
                    currentText += ch;
                    letterCount++;
                    cursor++;
                }
                
                file.close();
            }

            if (IsKeyPressed(KEY_KP_ADD) || IsKeyPressed(KEY_EQUAL)) {
                fontSize += 5;
            }
            if (IsKeyPressed(KEY_KP_SUBTRACT) || IsKeyPressed(KEY_MINUS)) {
                fontSize -= 5;
            }
        }
    }

    void Draw() {
        if (IsKeyDown(KEY_RIGHT_CONTROL)) { return; }

        BeginMode2D(camera::camera);

        int symbol = 0;
        Vector2 pos = {10, 10};
        for (char c : currentText) {
            if (symbol == cursor) {
                DrawRectangle(pos.x, pos.y, 2, fontSize, WHITE);
                curPos = pos;
            }
    
            if (c == '\n') {
                pos.y += 30;
                pos.x = 10;
            } else {
                if (IsOnScreen(GetWorldToScreen2D(pos, camera::camera))) {
                    DrawTextEx(font, std::string(1, c).c_str(), pos, fontSize, 0, WHITE);
                }
                
                pos.x += MeasureTextEx(font, std::string(1, c).c_str(), fontSize, 0).x;
                
            }
                
    
            DrawCircleGradient(pos.x - 10, pos.y + 25 / 2, fontSize + fontSize/3, Fade(BLACK, 0.3f), Fade(BLANK, 0.0f));
            //DrawCircleGradient(pos.x - 10, pos.y + 25 / 2, fontSize + fontSize/3, Fade(YELLOW, 0.06f), Fade(BLANK, 0.0f));
            symbol++;
        }
        if (cursor == currentText.length()) {
            DrawRectangle(curPos.x, curPos.y+fontSize, fontSize/2, 2+fontSize/10, WHITE);
            curPos = pos;
        }

        camera::camtarget = curPos;

        if (IsKeyDown(KEY_LEFT_CONTROL)) { return; }

        key = GetCharPressed();
        if ((key >= 32) && (key <= 125) && (key > 0) && (letterCount < 1023)) {
            currentText.insert(cursor, 1, (char)key);
            cursor++;
            letterCount++;
        }

        if (IsKeyPressed(KEY_TAB)) {
            currentText.insert(cursor, "    ");
            cursor += 4;
            letterCount += 4;
        }

        if (IsKeyPressed(KEY_ENTER)) {
            currentText += '\n';
            cursor++;
            letterCount++;
        }

        if (IsKeyPressed(KEY_BACKSPACE) && letterCount > 0) {
            if (cursor > 0) {
                currentText.erase(cursor - 1, 1);
                cursor--;
                letterCount--;
            }
            backspaceDelay = 0;
        }
        else if (IsKeyDown(KEY_BACKSPACE) && letterCount > 0) {
            backspaceDelay++;
            if (backspaceDelay > delayTime * GetFrameTime() && backspaceDelay % 2 == 0) {
                if (cursor > 0) {
                    currentText.erase(cursor - 1, 1);
                    cursor--;
                    letterCount--;
                }
            }
        }
        else {
            backspaceDelay = 0;
        }

        if (IsKeyPressed(KEY_DELETE) && letterCount > 0) {
            if (cursor < currentText.length()) {
                currentText.erase(cursor, 1);
                letterCount--;
            }
        } else if (IsKeyDown(KEY_DELETE) && letterCount > 0) {
            deleteDelay++;
            if (deleteDelay > delayTime * GetFrameTime() && deleteDelay % 2 == 0) {
                if (cursor < currentText.length()) {
                    currentText.erase(cursor, 1);
                    letterCount--;
                }
            }
        } else {
            //backspaceDelay = 0;
        }

        if (cursor < 0) cursor = 0;
        if (cursor > currentText.length()) cursor = currentText.length();

        if (IsKeyPressed(KEY_LEFT) && cursor > 0) { cursor--; }
        else if (IsKeyPressed(KEY_RIGHT) && cursor < currentText.length()) { cursor++; }

        if (IsKeyDown(KEY_LEFT) && cursor > 0) {
            cursorLeftDelay++;
            if (cursorLeftDelay > delayTime * GetFrameTime() && cursorLeftDelay % 2 == 0) {
                cursor--;
            }
        }
        else { cursorLeftDelay = 0; }

        if (IsKeyDown(KEY_RIGHT) && cursor < currentText.length()) {
            cursorRightDelay++;
            if (cursorRightDelay > delayTime * GetFrameTime() && cursorRightDelay % 2 == 0) {
                cursor++;
            }
        }
        else { cursorRightDelay = 0; }

        if (IsKeyPressed(KEY_RIGHT) && cursor < currentText.length()) { cursor++; };
        
        EndMode2D();
    }
}