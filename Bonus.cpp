#include "Bonus.h"

Bonus::Bonus(Vector2f position_, Font& font, int type) : GameObject(position_), type(type) {
    bonusText.setFont(font);
    bonusText.setCharacterSize(24);
    bonusText.setFillColor(Color::White);
    bonusText.setPosition(350, 460);

    FPaddle.setSize(Vector2f(520, 9));
    FPaddle.setPosition(0, 440);
    FPaddle.setFillColor(Color(226, 238, 245));
}

void Bonus::Update() {
    position_.y += dBonus;
}

void Bonus::Draw(RenderWindow& window) {
    if (active) { 
        window.draw(bonusText); 
        if (type == 4) window.draw(FPaddle);
    }
    if (position_.y > 440) {
        position_.y = 1000;
    }
    bonus.setPosition(position_);
    window.draw(bonus);
}

void Bonus::LoadImg(const std::string& file_name) {
    t.loadFromFile(file_name);
    bonus.setTexture(t);
}

int Bonus::getType() {
    return type;
}

bool Bonus::getActive() { return active; }

void Bonus::CollisionPaddle(Paddle& sPaddle) {
    if (type > 0 && bonus.getGlobalBounds().intersects(sPaddle.GetBounds())) {
        SetPosition(-100, 0);
        active = true;
        bonusClock.restart();
    }
}











