#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Block {
public:
    RectangleShape block;
    Text text;  
    int number;  
    Block(Vector2f position, Vector2f size, Color color, int number, Font& font);
    void draw(sf::RenderWindow& window);
};
