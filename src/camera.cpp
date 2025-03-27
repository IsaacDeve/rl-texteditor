#include "raylib.h"
#include "camera.hpp"

namespace camera {
    Camera2D camera = { 0 };
    Vector2 camtarget = { 0, 0 };
    void Update(Vector2& camPos) {
        camera.target = camPos;
        camera.offset = { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 };
        camera.rotation = 0.0f;
        camera.zoom = 1.0f;
    }
}