#include "Paddle.h"

Paddle::Paddle(Vector2f position_) : GameObject(position_) {
    scale = 1.0;
}

void Paddle::LoadImg(const std::string& file_name) {
    p.loadFromFile(file_name);
    sPaddle.setTexture(p);
}

float Paddle::change(float v) {
    if (Keyboard::isKeyPressed(Keyboard::Right)) {
        position_.x += v;
        if (position_.x + sPaddle.getGlobalBounds().width > WIDTH) {
            position_.x = WIDTH - sPaddle.getGlobalBounds().width;
        }
        else 
            return v;
    }
    if (Keyboard::isKeyPressed(Keyboard::Left)) {
        position_.x -= v;
        if (position_.x < 0) {
            position_.x = 0;
        }
        else
            return -v;
    }
}

void Paddle::Draw(RenderWindow& window) {
    sPaddle.setPosition(position_);
    sPaddle.setScale(scale, 1.0);
    window.draw(sPaddle);
}

void Paddle::SetScale(float s){ 
    scale += s; 
    if (scale > 4.0) scale = 4.0f;
    if (scale < 0.2) scale = 0.2f;
}

void Paddle::Update() {};
FloatRect Paddle::GetBounds() { return sPaddle.getGlobalBounds(); }