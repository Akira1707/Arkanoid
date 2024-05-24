#include "Bonuses.h"

Bonuses::Bonuses(Font& font, BonusVisitor& visitor) : visitor(visitor) {
    for (int i = 0; i <= 11; i++) {
        for (int j = 0; j <= 9; j++)
        {
            int randValue = rand() % 100;
            int type = 0;
            Vector2f position(i * 43 + 2, j * 20);

            if (randValue > 90) {                               //меняют размер каретки
                type = 1; 
                bonuses.push_back(std::make_unique<BonusChangePaddle>(position, font));
            }                  
            else if (randValue > 80) {                          //меняют скорость шарика
                type = 2; 
                bonuses.push_back(std::make_unique<BonusChangeSpeed>(position, font));
            }
            else if (randValue > 70) {                          //меняют прилипание шарика к каретке
                type = 3; 
                bonuses.push_back(std::make_unique<BonusChangeAdhesion>(position, font));
            }
            else if (randValue > 60) {                          //одноразовое дно для шарика
                type = 4; 
                bonuses.push_back(std::make_unique<BonusFilmyPaddle>(position, font));
            }
            else if (randValue > 50) {                          //шарик в произвольный момент меняет траекторию
                type = 5; 
                bonuses.push_back(std::make_unique<BonusChangeTrajectory>(position, font));
            }
            else {
                bonuses.push_back(std::make_unique<BonusChangePaddle>(position, font));
            }
        }
    }
}

void Bonuses::update(Paddle& sPaddle, Ball& sBall) {
    for (auto& bonus : bonuses) {
        if (bonus->getType() > 0) {
            bonus->CollisionPaddle(sPaddle);
            if (bonus->getActive()) {
                bonus->accept(visitor, sPaddle, sBall);
            }
        }        
    }
}

