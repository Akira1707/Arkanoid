#pragma once
#include "GameObject.h"
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

private:
	Sprite sBall;
	Texture b;
	float dBall;
	float angleBall;
};
