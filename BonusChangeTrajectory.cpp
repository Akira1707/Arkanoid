#include "BonusChangeTrajectory.h"
#include "BonusVisitor.h"

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