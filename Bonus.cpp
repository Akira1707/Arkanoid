#include "Bonus.h"
#include "Game.h" 
using namespace sf;

Bonus::Bonus(Sprite& bonus, int type)
    : bonus(bonus), type(type) {}

void Bonus::update() {
    bonus.setPosition(bonus.getPosition().x, bonus.getPosition().y + dBonus);
}

void Bonus::draw(RenderWindow& window) {
    if (bonus.getPosition().y > 440) {
        bonus.setPosition(bonus.getPosition().x, bonus.getPosition().y + 100);
    }
    window.draw(bonus);
}



