#pragma once
#include<SFML/Graphics.hpp>
#include<time.h>
#include<random>
#include<vector>
#include<math.h>
#include<algorithm>

#include "Ball.h"
#include "Paddle.h"
#include "Block.h"
#include "Bonus.h"
#include "Constants.h"
#include "Scores.h"
#include "Lives.h"

using namespace sf;

class Game {
private:
    RenderWindow window;
    Clock bonusClock;
    float bonusDuration = 5.0f;
    Font font;

    Texture t;
    Sprite sBackG;
    Ball sBall;
    Paddle sPaddle;
    RectangleShape FPaddle;
    std::vector<Block> blocks;
    std::vector<Bonus> Bonuses;

    int BlocksLeft = 0;
    Scores scores;
    Lives lives;
    Text  message, bonusText;
    bool started = false, filmy = false, change = false, bonusActive = false;
    int Adhesion = 0;

    void initGame();
    void update();
    void applyBonus(int type);
    void processEvents();
    void render();
    void CollisionBonusPaddle(Bonus& bonus, Paddle& sPaddle);   

public:
    Game();
    void play();
};