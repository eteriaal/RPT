// github.com/eteriaal/rpt
// src/app/Application.h

#pragma once

#include "platform/Window.h"
#include "graphics/Renderer.h"
#include "ui/DebugUI.h"

class Application {
public:
    bool init();
    void run();

private:
    Window window;
    Renderer renderer;
};
