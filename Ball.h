#pragma once
#include "GameObject.h"
#include "Block.h"
#include "Paddle.h"
#include "Scores.h"
#include "Constants.h"
using namespace sf;

class Ball : public GameObject {
public:
	Ball(Vector2f position_);
	void LoadImg(const std::string& file_name);
	void Draw(RenderWindow& window) override;
	void Update() override;
	void ChangeAngle();
	float GetAngle();
	void SetAngle(float angle);
	void ChangeSpeed(float d);

	bool CollisionBlock(Block& block, Scores& scores);
	void CollisionPaddle(Paddle& sPaddle, int& Adhesion);
	bool CollisionWall(bool& change, bool& filmy);

private:
	Sprite sBall;
	Texture b;
	float dBall;
	float angleBall;
};
