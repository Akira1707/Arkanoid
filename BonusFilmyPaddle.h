#pragma once
#include "Bonus.h"

class BonusFilmyPaddle : public Bonus {
public:
	BonusFilmyPaddle(Vector2f position_, Font& font);
	void accept(BonusVisitor& visitor, Paddle& sPaddle, Ball& sBall) override;
	void Apply(Paddle& sPaddle, Ball& sBall);
};
