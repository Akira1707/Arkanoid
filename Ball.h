#pragma once
#include "GameObject.h"
#include "Block.h"
#include "Paddle.h"
#include "Scores.h"
#include "Constants.h"

class Ball : public GameObject {
public:
	Ball(Vector2f position_);
	void LoadImg(const std::string& file_name);
	void Draw(RenderWindow& window) override;
	void Update() override;
	void ChangeAngle();
	float GetAngle();
	void SetAngle(float angle);
	float getSpeed();
	void setSpeed(float d);
	void ChangeSpeed(float d);
	void Start();

	bool CollisionBlock(Block& block, Scores& scores);
	bool CollisionPaddle(Paddle& sPaddle);
	bool CollisionWall();

private:
	Sprite sBall;
	Texture b;
	float dBall;
	float angleBall;
};
