#pragma once
#include "Bonus.h"

class BonusChangeAdhesion : public Bonus {
public:
	BonusChangeAdhesion(Vector2f position_, Font& font);
	void accept(BonusVisitor& visitor, Paddle& sPaddle, Ball& sBall) override;
	void Apply(Paddle& sPaddle, Ball& sBall);
private:
	int choose = 0;
	float dB = 0;
};
