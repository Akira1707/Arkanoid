#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Bonus {
public:
    Sprite bonus;
    int type; 
    float dBonus = 3.0;

    Bonus(Sprite& sprite, int type);
    void update();
    void draw(sf::RenderWindow& window);    
};
