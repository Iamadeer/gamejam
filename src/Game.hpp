#pragma once

#include "raylib.h"
#include "Player.hpp"
#include "Food.hpp"

#include <vector>

enum class GameState{
    InGame,
    GameOver
};

class Game{

public:
    Game();
    void run();
    void update();
    void draw();
    void spawnFood();

    void checkGameOver();
    void drawGameOver();
    void restart();

private:
    Player m_player;
    std::vector<Food> m_foods;
    GameState m_state;
    int m_score;
    float m_spawntime;
    float m_spawnInterval;
   

};