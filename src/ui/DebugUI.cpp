// github.com/eteriaal/rpt
// src/ui/DebugUI.cpp

#include "DebugUI.h"

namespace DebugUI {
    void draw(DebugParams& params) {
        ImGui::Begin("Debug Controls");

        ImGui::Text("Renderer");
        ImGui::SliderFloat("Rot Y", &params.rotationSpeedY, 0.f, 100.f);
        ImGui::SliderFloat("Rot X", &params.rotationSpeedX, 0.f, 100.f);
        ImGui::SliderFloat("Rot Z", &params.rotationSpeedZ, 0.f, 100.f);
        ImGui::Checkbox("Wireframe", &params.wireframe);

        ImGui::Separator();
        ImGui::Text("Camera");
        ImGui::SliderFloat("Distance", &params.camDistance, 0.5f, 10.f);
        ImGui::SliderFloat("Height", &params.camHeight, 0.5f, 10.f);
        ImGui::SliderFloat("FOV", &params.fov, 15.f, 120.f);

        ImGui::End();
    }
}