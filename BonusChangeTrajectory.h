#pragma once
#include "Bonus.h"

class BonusChangeTrajectory : public Bonus {
public:
	BonusChangeTrajectory(Vector2f position_, Font& font);
	void accept(BonusVisitor& visitor, Paddle& sPaddle, Ball& sBall) override;
	void Apply(Paddle& sPaddle, Ball& sBall);
};