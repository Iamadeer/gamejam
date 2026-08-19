#pragma once

#include <algorithm>
#include "Food.hpp"
#include "raylib.h"

class Player{

public:
    Player(float x, float y);

    void update();
    void draw();

    void eat(FoodType type);

    Rectangle getBounds() const;

    float getHappiness() const;
    float getHealtiness() const;

    float getSpeed() const;
    float getWidth() const;

private:
    Rectangle m_body;
    float m_baseSpeed;
    float m_baseWidth;
    float m_happiness;
    float m_healthiness;

    float m_timer;

};