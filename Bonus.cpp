#include "Bonus.h"

Bonus::Bonus(Vector2f position_, Font& font) : GameObject(position_) {
    int randValue = rand() % 100;

    if (randValue > 90) { type = 1; }                  //меняют размер каретки
    else if (randValue > 80) { type = 2; }              //меняют скорость шарика
    else if (randValue > 70) { type = 3; }              //меняют прилипание шарика к каретке
    else if (randValue > 60) { type = 4; }              //одноразовое дно для шарика
    else if (randValue > 50) { type = 5; }              //шарик в произвольный момент меняет траекторию
    else { type = 0; }
}

void Bonus::Update() {
    position_.y += dBonus;
}

void Bonus::Draw(RenderWindow& window) {
    switch (type) {
    case 1:
    {                   
        t.loadFromFile("images/B01.png");
        bonus.setTexture(t);
        break;
    }
    case 2:
    {             
        t.loadFromFile("images/B02.png");
        bonus.setTexture(t);
        break;
    }
    case 3:
    {              
        t.loadFromFile("images/B03.png");
        bonus.setTexture(t);
        break;
    }
    case 4:
    {           
        t.loadFromFile("images/B04.png");
        bonus.setTexture(t);
        break;
    }
    case 5:
    {              
        t.loadFromFile("images/B05.png");
        bonus.setTexture(t);
        break;
    }
    }

    if (position_.y > 440) {
        position_.y = 1000;
    }

    bonus.setPosition(position_);
    window.draw(bonus);
}


int Bonus::getType() {
    return type;
}

FloatRect Bonus::GetBounds() { return bonus.getGlobalBounds(); }



