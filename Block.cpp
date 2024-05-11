#include "Block.h"

Block::Block(Vector2f position, Vector2f size, Color color, int number, Font& font)
    : number(number){
    block.setPosition(position);
    block.setSize(size);
    block.setFillColor(color);

    text.setFont(font);
    text.setString(std::to_string(number));
    text.setCharacterSize(16);  
    text.setFillColor(Color::White);
    text.setPosition(position.x + 13, position.y + 1);
}
void Block::draw(RenderWindow& window) {
    window.draw(block);
    if (block.getFillColor() == Color(165, 110, 188) && number > 1) {
        text.setString(std::to_string(number));
        window.draw(text);
    }
}