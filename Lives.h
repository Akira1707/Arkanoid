#pragma once
#include<SFML/Graphics.hpp>
using namespace sf;

class Lives {
public:
	Lives(Font& font, int numberLives);
	void update();
	void Draw(RenderWindow& window, Text& message);
private:
	int numberLives;
	Text textLives;
	Texture h;
	std::vector<Sprite> sHearts;
};
