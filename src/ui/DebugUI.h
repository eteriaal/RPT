// github.com/eteriaal/rpt
// src/ui/DebugUI.h

#pragma once
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include "ui/DebugParams.h"

namespace DebugUI {
    void draw(DebugParams& params);
}
