#include "Game.hpp"

Game::Game() : m_player(350,950), m_score(0),m_state(GameState::InGame), m_spawnInterval(1.0f), m_spawntime(0.0f){
}

void Game::run(){
    InitWindow(1280,800,"Food Catcher");

    ToggleFullscreen();


    SetTargetFPS(60);

    while (!WindowShouldClose()){
        update();
        draw();
    }

    CloseWindow();
}

void Game::update(){
    if (m_state == GameState::InGame){
        m_player.update();

        m_spawntime -= GetFrameTime();

        if (m_spawntime <=0.0f){
            spawnFood();
            m_spawntime = m_spawnInterval;
        }


        for (auto food = m_foods.begin(); food != m_foods.end();){
            food->update();

            if (CheckCollisionRecs(m_player.getBounds(), food->getBounds())){
                m_player.eat(food->getType());
                m_score++;

                food = m_foods.erase(food);
            }

            else if (food->isOutOfBounds()){
                food = m_foods.erase(food);
            }

            else{
                food++;
            }
        }

        checkGameOver();
    } else {
        Rectangle restartButton = {GetScreenWidth()/2 - 100,400,200,60};

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(),restartButton)){
            restart();
        }
    }
}

void Game::spawnFood(){
    FoodType type;
    int rng = GetRandomValue(1,2);
    if (rng == 1){
        type = FoodType::Healthy;
    } else {
        type = FoodType::Unhealthy;
    }


    m_foods.emplace_back(type);
}

void Game::draw(){
    BeginDrawing();

    ClearBackground(LIGHTGRAY);

    if (m_state == GameState::InGame){

        m_player.draw();

        for (Food food : m_foods){
            food.draw();
        }

        DrawText(TextFormat("Score: %d", m_score), 30,145,20,BLACK);

    } else{

        drawGameOver();
    }
    EndDrawing();



}

void Game::checkGameOver(){
    if (m_player.getHappiness() <=0.0f || m_player.getHealtiness() <= 0.0f){
        m_state = GameState::GameOver;
    }
}

void Game::drawGameOver(){
    DrawRectangle(0,0,GetScreenWidth(),GetScreenHeight(),BLACK);

    const char* message;

    if (m_player.getHappiness()<=0.0f){
        message = "You became too depressed to continue living";
    }

    else{
        message = "You became too obese and died";
    }

    DrawText("Game Over", GetScreenWidth()/2 - MeasureText("Game Over",60)/2,200,60,WHITE);

    DrawText(message, GetScreenWidth()/2 - MeasureText(message,30)/2,280,30,WHITE);

    DrawText(TextFormat("Food eaten: %d", m_score), GetScreenWidth()/2 - MeasureText(TextFormat("Food eaten: %d", m_score), 25)/2,330,25,WHITE);

    Rectangle restartButton = {GetScreenWidth()/2 - 100,400,200,60};

    DrawRectangleRec(restartButton, LIGHTGRAY);

    DrawText("RESTART", restartButton.x +restartButton.width /2 - MeasureText("RESTART",25)/2, restartButton.y+17,25,WHITE);



}

void Game::restart(){
    m_player = Player(350,950);

    m_foods.clear();

    m_score = 0;

    m_spawntime = 0;

    m_state = GameState::InGame;
}