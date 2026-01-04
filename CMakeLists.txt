cmake_minimum_required(VERSION 3.28...4.2) 
project(RPT LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---------------------------------------------------------------------- #

include(FetchContent)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.2
)
FetchContent_MakeAvailable(glm)

FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.92.5
)
FetchContent_MakeAvailable(imgui)

add_library(imgui STATIC
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp  
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)       
target_include_directories(imgui PUBLIC ${imgui_SOURCE_DIR} ${imgui_SOURCE_DIR}/backends)
target_link_libraries(imgui PRIVATE glfw)

FetchContent_Declare(
    stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG master
)
FetchContent_MakeAvailable(stb)

add_library(stb_interface INTERFACE)
target_include_directories(stb_interface INTERFACE ${stb_SOURCE_DIR})
add_library(stb::stb ALIAS stb_interface)

add_library(glad STATIC external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

# ---------------------------------------------------------------------- #

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/app/Application.cpp
    src/graphics/Renderer.cpp 
    src/graphics/Shader.cpp 
    src/platform/WindowGLFW.cpp 
    src/ui/DebugUI.cpp
)
target_include_directories(${PROJECT_NAME} PRIVATE src/)

target_link_libraries(${PROJECT_NAME} PRIVATE glfw glad imgui glm::glm stb::stb)