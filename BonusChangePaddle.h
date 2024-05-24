#pragma once
#include "Bonus.h"

class BonusChangePaddle : public Bonus {
public:
	BonusChangePaddle(Vector2f position_, Font& font);
	void accept(BonusVisitor& visitor, Paddle& sPaddle, Ball& sBall) override;
	void Apply(Paddle& sPaddle, Ball& sBall);
};


