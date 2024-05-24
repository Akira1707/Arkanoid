#pragma once
#include "GameObject.h"
#include "Paddle.h"
#include "Ball.h"
#include "BonusVisitor.h"

class BonusVisitor;

class Bonus : public GameObject {
public:
	Bonus(Vector2f position_, Font& font, int type);
	void Update() override;
	void Draw(RenderWindow& window);
	void LoadImg(const std::string& file_name);
	int getType();
	bool getActive();
	void CollisionPaddle(Paddle& sPaddle);

	virtual void accept(BonusVisitor& visitor, Paddle& sPaddle, Ball& sBall) = 0;
protected:
	Sprite bonus;
	Texture t;
	int type;
	bool active = false;
	const float dBonus = 3.0;
	Clock bonusClock;
	Text bonusText;
	RectangleShape FPaddle;
};

class BonusChangePaddle : public Bonus {
public:
	BonusChangePaddle(Vector2f position_, Font& font);
	void accept(BonusVisitor& visitor, Paddle& sPaddle, Ball& sBall) override;
	void Apply(Paddle& sPaddle, Ball& sBall);
};

class BonusChangeSpeed : public Bonus {
public:
	BonusChangeSpeed(Vector2f position_, Font& font);
	void accept(BonusVisitor& visitor, Paddle& sPaddle, Ball& sBall) override;
	void Apply(Paddle& sPaddle, Ball& sBall);
};

class BonusChangeAdhesion : public Bonus {
public:
	BonusChangeAdhesion(Vector2f position_, Font& font);
	void accept(BonusVisitor& visitor, Paddle& sPaddle, Ball& sBall) override;
	void Apply(Paddle& sPaddle, Ball& sBall);
private:
	int choose = 0;
	float dB = 0;
};

class BonusFilmyPaddle : public Bonus {
public:
	BonusFilmyPaddle(Vector2f position_, Font& font);
	void accept(BonusVisitor& visitor, Paddle& sPaddle, Ball& sBall) override;
	void Apply(Paddle& sPaddle, Ball& sBall);
};

class BonusChangeTrajectory : public Bonus {
public:
	BonusChangeTrajectory(Vector2f position_, Font& font);
	void accept(BonusVisitor& visitor, Paddle& sPaddle, Ball& sBall) override;
	void Apply(Paddle& sPaddle, Ball& sBall);
};


