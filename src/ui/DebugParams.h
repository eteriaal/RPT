// github.com/eteriaal/rpt
// src/ui/DebugParams.h

#pragma once
#include <glm/glm.hpp>

struct DebugParams {
    float rotationSpeedY = 30.f;
    float rotationSpeedX = 20.f;
    float rotationSpeedZ = 10.f;
    float camDistance = 3.f;
    float camHeight = 2.5f;
    float fov = 45.f;
    bool wireframe = false;
};