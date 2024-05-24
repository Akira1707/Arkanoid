#pragma once
#include "Bonus.h"

class BonusChangeSpeed : public Bonus {
public:
	BonusChangeSpeed(Vector2f position_, Font& font);
	void accept(BonusVisitor& visitor, Paddle& sPaddle, Ball& sBall) override;
	void Apply(Paddle& sPaddle, Ball& sBall);
};

