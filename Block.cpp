#include "Block.h"

Block::Block(Vector2f position_, Font& font): GameObject(position_) {
    int randValue = rand() % 100;
    if (randValue > 95) {                           //Блоки, увеличивающие скорость шарика
        block.setFillColor(Color(64, 134, 68));
        type = 1;
        number = 1;
    }
    else if (randValue > 85) {                      //Неразрушаемые блок
        block.setFillColor(Color(90, 100, 105));   
        type = 2;
        number = 1;
    }
    else {
        block.setFillColor(Color(165, 110, 188));     //Блоки имеют уровень здоровья
        type = 3;
        number = rand() % 10 - 3;
        if (number < 1) number = 1;
    }
    
    block.setSize(Vector2f(42,19));

    text.setFont(font);
    text.setCharacterSize(16);  
    text.setFillColor(Color::White);
}

FloatRect Block::GetBounds(){
    return block.getGlobalBounds();
}

void Block::Draw(RenderWindow& window) {
    block.setPosition(position_);
    if (number > 0) { 
        window.draw(block);
        if (type == 3 && number > 1) {
            text.setString(std::to_string(number));
            text.setPosition(position_.x + 13, position_.y + 1);
            window.draw(text);
        }
    }       
}

void Block::Update() {};
int Block::GetType() { return type; }
int Block::GetNumber() { return number; }
void Block:: SetNumber(int n) { number = n; }
