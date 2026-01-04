// github.com/eteriaal/rpt
// src/main.cpp

#include "app/Application.h"

int main(int argc, char* argv[]) {
    Application app;
    if(!app.init())
        return -1;
        
    app.run();
    return 0;
} 