#pragma once
#include "GameObject.h"
using namespace sf;

class Bonus : public GameObject {
public:
	Bonus(Vector2f position_, Font& font);
	void Update() override;
	void Draw(RenderWindow& window) override;
	int getType();
	FloatRect GetBounds();

private:
	Sprite bonus;
	Texture t;
	int type;
	const float dBonus = 3.0;
};

