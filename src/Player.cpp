#include "Player.hpp"


Player::Player(float x, float y){
    m_body = {x,y,100,30};  
    m_baseSpeed = 250.0f;
    m_happiness = 100.0f;
    m_healthiness = 100.0f;
    m_timer = 1.0f;
    m_baseWidth = 100.0f;
    
}



void Player::update(){
    m_body.width = getWidth();

    if (IsKeyDown(KEY_LEFT)){
        m_body.x -= getSpeed() * GetFrameTime();
    } else 
    if (IsKeyDown(KEY_RIGHT)){
        m_body.x += getSpeed() * GetFrameTime();
    }


    if (m_body.x < 0){
        m_body.x = 0;
    }

    if (m_body.x + m_body.width > GetScreenWidth()){
        m_body.x = GetScreenWidth() - m_body.width;
    }

    m_timer -= GetFrameTime();
    if (m_timer <= 0){
        m_happiness -=1;
        m_timer = 1.0f;
    }



    
}


void Player::draw(){
    DrawRectangleRec(m_body, BROWN);

    float width = 300;
    float height = 25;

    //Happiness bar background
    DrawRectangle(30,30,width, height, GRAY);

    //Happiness bar
    DrawRectangle(30,30,width* (m_happiness/100), height, YELLOW);

    DrawText(TextFormat("Happiness: %.0f", m_happiness), 30,5,20, BLACK);
    

    DrawRectangle(30,100,width, height, GRAY);

    DrawRectangle(30,100,width * (m_healthiness/100), height, GREEN);

    DrawText(TextFormat("Healthiness: %.0f", m_healthiness), 30,75,20, BLACK);

}

void Player::eat(FoodType type){
    if (type == FoodType::Healthy){
        m_healthiness += 10;
        m_happiness -= 5;
    } else {
        m_happiness +=10;
        m_healthiness -= 10;
    }

    m_happiness = std::clamp(m_happiness, 0.0f, 100.0f);
    m_healthiness = std::clamp(m_healthiness, 0.0f, 100.0f);
}

Rectangle Player::getBounds() const {
    return m_body;
}

float Player::getHappiness() const {
    return m_happiness;
}

float Player::getHealtiness() const {
    return m_healthiness;
}

float Player::getSpeed() const{
    return m_baseSpeed * (m_healthiness/50);
}

float Player::getWidth() const {
    // 100 /5 20 10
    
    return std::max(m_baseWidth,m_baseWidth + ((50-m_healthiness)*2));
}