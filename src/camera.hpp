#pragma once
#include "raylib.h"

namespace camera {
    extern Camera2D camera;
    extern Vector2 camtarget;
    void Update(Vector2& camPos);
}