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
    if (changed > 97) {
        do {
            angleBall = rand() % 360;
        } while (15 > angleBall || angleBall > 345 || (angleBall > 75 && angleBall < 105) || (angleBall > 165 && angleBall < 195) || (angleBall > 255 && angleBall < 285));
    }
}

float Ball::GetAngle() { return angleBall; }
void Ball::SetAngle(float angle) { angleBall = angle; }
void Ball::ChangeSpeed(float d) { dBall += d; }
float Ball::getSpeed() { return dBall; }
void Ball::setSpeed(float d) { dBall = d; }

void Ball::Start() {
    SetPosition(250, 200);
    float angle;
    do {
        angle = rand() % 140;
    } while ((angle > 75 && angle < 105) || (angle < 15));
    angleBall = angle;
}

bool Ball:: CollisionBlock(Block& block, Scores& scores) {
    if (FloatRect(position_.x, position_.y, 12, 12).intersects(block.GetBounds()))
    {
        angleBall = -angleBall;
        if (block.GetType() == 3) {
            scores.update(1);
            block.SetNumber(block.GetNumber() - 1);
            if (block.GetNumber() == 0) {
                block.SetPosition(-100, -100);
                return true;
            }            
        }
        else if (block.GetType() == 1) {
            block.SetNumber(block.GetNumber() - 1);
            scores.update(1);
            block.SetPosition(-100, -100);
            dBall += 0.3;
            return true;
        }
    }
    return false;
}

bool Ball::CollisionPaddle(Paddle& sPaddle){
    if (FloatRect(position_.x, position_.y + 2, 12, 8).intersects(sPaddle.GetBounds())) {
        angleBall = -angleBall;
        return true;
    }
    return false;
}

bool Ball::CollisionWall(){
    if (position_.x < 0 || position_.x > WIDTH || position_.y < 0) angleBall = 180 - angleBall; 
    if (position_.y < 0) angleBall = -angleBall;
    if (position_.y > 435) {
        return true;
    }
    return false;
}

