#include "BonusChangePaddle.h"
#include "BonusVisitor.h"

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