#include "Food.hpp"


Food::Food (FoodType type){
    m_body = {static_cast<float>(GetRandomValue(0,GetScreenWidth()-30)),-30,30,30};
    m_speed = 500.0f;
    m_type = type;
    m_brocolli = LoadTexture("assets/brocolli.png");
    m_rotiCanai = LoadTexture("assets/roti-canai.png");
}


void Food::update(){
    m_body.y += m_speed * GetFrameTime();
}

void Food::draw() const{
    if (m_type == FoodType::Healthy){
        DrawTextureEx(m_brocolli,{m_body.x,m_body.y},0.0f,0.1f, WHITE);
    } else {
        DrawTextureEx(m_rotiCanai,{m_body.x,m_body.y},0.0f,0.1f, WHITE);
    }
}

Rectangle Food::getBounds() const {
    return m_body;
}



FoodType Food::getType() const {
    return m_type;
}

bool Food::isOutOfBounds() const {
    return m_body.y > GetScreenHeight();
}
