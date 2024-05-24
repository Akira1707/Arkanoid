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


BonusChangePaddle::BonusChangePaddle(Vector2f position_, Font& font)
    : Bonus(position_, font, 1) {
    LoadImg("images/B01.png");
}

void BonusChangePaddle::accept(BonusVisitor& visitor, Paddle& sPaddle, Ball& sBall) {
    visitor.visit(*this, sPaddle, sBall);
}

void BonusChangePaddle::Apply(Paddle& sPaddle, Ball& sBall) {
    float m = 2 * (rand() % 2) - 1;
    sPaddle.SetScale(m * 0.1);
    active = false;
}

BonusChangeSpeed::BonusChangeSpeed(Vector2f position_, Font& font)
    : Bonus(position_, font, 2) {
    LoadImg("images/B02.png");
}

void BonusChangeSpeed::accept(BonusVisitor& visitor, Paddle& sPaddle, Ball& sBall) {
    visitor.visit(*this, sPaddle, sBall);
}

void BonusChangeSpeed::Apply(Paddle& sPaddle, Ball& sBall) {
    float m = 2 * (rand() % 2) - 1;
    sBall.ChangeSpeed(m * 0.3);
    active = false;
}

BonusChangeAdhesion::BonusChangeAdhesion(Vector2f position_, Font& font)
    : Bonus(position_, font, 3) {
    LoadImg("images/B03.png");
}

void BonusChangeAdhesion::accept(BonusVisitor& visitor, Paddle& sPaddle, Ball& sBall) {
    visitor.visit(*this, sPaddle, sBall);
}

void BonusChangeAdhesion::Apply(Paddle& sPaddle, Ball& sBall) {
    float elapsedTime = bonusClock.getElapsedTime().asSeconds();
    if (elapsedTime > 5.0) {
        active = false;
        if (choose == 2) sBall.setSpeed(dB);
        choose = 0;
        return;
    }
    bonusText.setString("Time: " + std::to_string(static_cast<int>(5.0 - elapsedTime)));

    if (choose == 2) {
        float d = sPaddle.change(0.1);
        sBall.SetPosition(sBall.GetPosition().x + d * 61, sBall.GetPosition().y);
        if (Keyboard::isKeyPressed(Keyboard::Enter)) {
            choose = 1;
            sBall.setSpeed(dB);
        }
    }
    else if (sBall.CollisionPaddle(sPaddle)) {
        if (choose == 0) {
            dB = sBall.getSpeed();
            sBall.setSpeed(0);
        }
        choose = 2;
    }
}

BonusFilmyPaddle::BonusFilmyPaddle(Vector2f position_, Font& font)
    : Bonus(position_, font, 4) {
    LoadImg("images/B04.png");
}

void BonusFilmyPaddle::accept(BonusVisitor& visitor, Paddle& sPaddle, Ball& sBall) {
    visitor.visit(*this, sPaddle, sBall);
}

void BonusFilmyPaddle::Apply(Paddle& sPaddle, Ball& sBall) {
    float elapsedTime = bonusClock.getElapsedTime().asSeconds();
    if (elapsedTime > 5.0) { active = false; return; }
    bonusText.setString("Time: " + std::to_string(static_cast<int>(5.0 - elapsedTime)));

    if (sBall.CollisionPaddle(sPaddle)) {
        sBall.SetAngle(-sBall.GetAngle());
    }
    else if (sBall.GetPosition().y > 430) {
        sBall.SetAngle(-sBall.GetAngle());
        active = false; return;
    }
}


BonusChangeTrajectory::BonusChangeTrajectory(Vector2f position_, Font& font)
    : Bonus(position_, font, 5) {
    LoadImg("images/B05.png");
}

void BonusChangeTrajectory::accept(BonusVisitor& visitor, Paddle& sPaddle, Ball& sBall) {
    visitor.visit(*this, sPaddle, sBall);
}

void BonusChangeTrajectory::Apply(Paddle& sPaddle, Ball& sBall) {
    float elapsedTime = bonusClock.getElapsedTime().asSeconds();
    if (elapsedTime > 5.0) { active = false; return; }
    bonusText.setString("Time: " + std::to_string(static_cast<int>(5.0 - elapsedTime)));

    if (sBall.CollisionWall()) {
        active = false;
    }
    else {
        sBall.ChangeAngle();
    }
}