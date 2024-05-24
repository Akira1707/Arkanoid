#include "BonusChangeAdhesion.h"
#include "BonusVisitor.h"

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