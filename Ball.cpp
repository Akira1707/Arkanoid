#include "Ball.h"

Ball::Ball(Vector2f position_) :GameObject(position_) {
    dBall = 5.0;
    angleBall = 30.0;
}

void Ball::LoadImg(const std::string& file_name) {
    b.loadFromFile(file_name);
    sBall.setTexture(b);
}

void Ball::Draw(RenderWindow& window) {
    sBall.setPosition(position_);
    window.draw(sBall);
}

void Ball::Update() {
    position_.x += dBall * cos(angleBall * PI / 180);
    position_.y += dBall * sin(angleBall * PI / 180);
}

void Ball::ChangeAngle() {
    int changed = rand() % 100;
    if (changed > 95) {
        do {
            angleBall = rand() % 360;
        } while (15 > angleBall || angleBall > 345 || (angleBall > 75 && angleBall < 105) || (angleBall > 165 && angleBall < 195) || (angleBall > 255 && angleBall < 285));
    }
}

float Ball::GetAngle() { return angleBall; }
void Ball::SetAngle(float angle) { angleBall = angle; }
void Ball::ChangeSpeed(float d) { dBall += d; }


