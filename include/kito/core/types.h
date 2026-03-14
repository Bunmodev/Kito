#pragma once
#include <string>

struct WindowConfig {
    std::string title;
    int width, height;
    bool fullscreen, resizable;
};