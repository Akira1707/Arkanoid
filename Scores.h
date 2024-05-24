#pragma once
#include<SFML/Graphics.hpp>
using namespace sf;

class Scores {
public:
	Scores(Font& font);
	void update(int d);
	void Draw(RenderWindow& window);
private:
	int score = 0;
	Text textScores;
};