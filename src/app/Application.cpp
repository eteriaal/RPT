// github.com/eteriaal/rpt
// src/app/Application.cpp

#include "app/Application.h"
#include "ui/DebugUI.h"

bool Application::init() {
    if (!window.create(1280, 720, "RPT")) return false;

    if (!renderer.init(window)) return false;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window.getGLFWwindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui::StyleColorsDark();

    return true;
}

void Application::run() {
    DebugParams debugParams;

    while (!window.shouldClose()) {
        window.pollEvents();

        renderer.render(debugParams);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        DebugUI::draw(debugParams);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        window.swapBuffers();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}