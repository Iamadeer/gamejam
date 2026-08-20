#pragma once

#include "raylib.h"
#include <cstdio>

enum class FoodType{
    Healthy,
    Unhealthy
};

class Food{

public:
    Food(FoodType type);

    void update();
    void draw() const;
    Rectangle getBounds() const;
    FoodType getType() const;
    bool isOutOfBounds() const;

private:
    Rectangle m_body;
    float m_speed;
    FoodType m_type;
    Texture2D m_brocolli;
    Texture2D m_rotiCanai;
    
};