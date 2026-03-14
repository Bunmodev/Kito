#pragma once

enum class UnitType { Pixel, Percent, Auto };

struct Dimension {
    float value = 0;
    UnitType type = UnitType::Auto;
};

struct Spacing {
    float top = 0, right = 0, bottom = 0, left = 0;
    
    // Helper to set all sides at once
    void setAll(float val) { top = right = bottom = left = val; }
};