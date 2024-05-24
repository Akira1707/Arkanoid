#pragma once
#include "GameObject.h"
#include "Constants.h"

class Paddle : public GameObject {
public:
	Paddle(Vector2f position_);
	void LoadImg(const std::string& file_name);
	void Draw(RenderWindow& window) override;
	void Update() override;
	float change(float v = 6);
	FloatRect GetBounds();
	void SetScale(float s);
private:
	Sprite sPaddle;
	Texture p;
	float scale;
};
