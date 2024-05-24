#include "BonusChangeSpeed.h"
#include "BonusVisitor.h"

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