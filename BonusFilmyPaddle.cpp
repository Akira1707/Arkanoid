#include "BonusFilmyPaddle.h"
#include "BonusVisitor.h"

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