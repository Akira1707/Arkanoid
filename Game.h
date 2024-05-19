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

using namespace sf;

class Game {
private:
    RenderWindow window;
    Clock bonusClock;
    float bonusDuration = 5.0f;
    Font font;

    Texture t, h;
    Sprite sBackG;
    Ball sBall;
    Paddle sPaddle;
    RectangleShape FPaddle;
    std::vector<Block> blocks;
    std::vector<Bonus> Bonuses;
    std::vector<Sprite> sHearts;

    int BlocksLeft = 0;
    int scores = 0;
    int numberLives = 5;
    Text textLives, textScores, message, bonusText;
    bool started = false, filmy = false, change = false, bonusActive = false;
    int Adhesion = 0;

    void initGame();
    void update();
    void applyBonus(int type);
    void processEvents();
    void render();

    void CollisionBallBlock(Ball& sBall, Block& block);
    void CollisionBallPaddle(Ball& sBall, Paddle& sPaddle);
    void CollisionWall(Ball& sBall);
    void CollisionBonusPaddle(Bonus& bonus, Paddle& sPaddle);   

public:
    Game();
    void play();
};