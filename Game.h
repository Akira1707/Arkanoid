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
#include "Bonuses.h"
#include "ApplyVisitor.h"
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
    std::vector<Block> blocks;
    Bonuses bonuses;

    int BlocksLeft = 0;
    Scores scores;
    Lives lives;
    Text  message;
    bool started;
    ApplyVisitor bonusVisitor;

    void initGame();
    void update();
    void processEvents();
    void render(); 

public:
    Game();
    void play();
};