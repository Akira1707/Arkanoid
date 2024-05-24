#pragma once
#include "Bonus.h"
#include <vector>
using namespace sf;

class Bonuses {
private:
    std::vector<std::unique_ptr<Bonus>> bonuses;
    BonusVisitor& visitor;
public:
    Bonuses(Font& font, BonusVisitor& visitor);
    std::vector<std::unique_ptr<Bonus>>& getBonuses() { return bonuses; }
    void update(Paddle& sPaddle, Ball& sBall);
};

