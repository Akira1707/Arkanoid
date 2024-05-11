#pragma once
#include<SFML/Graphics.hpp>
#include<time.h>
#include<random>
#include<vector>
#include<math.h>
#include<algorithm>

#include "Block.h"
#include "Bonus.h"

const int WIDTH = 520;
const int HEIGHT = 500;
const float PI = 3.14;

using namespace sf;

class Game {
private:
    RenderWindow window;
    Clock bonusClock;
    float bonusDuration = 5.0f;
    Font font;
    Texture t1, t2, t3, t4, b1, b2, b3, b4, b5;
    Sprite sBackG, sBall, sPaddle;
    RectangleShape FPaddle;
    std::vector<Block> blocks;
    std::vector<Sprite> sHearts;
    std::vector<Bonus> Bonuses;

    float dBall = 5, dBonus = 3;
    int angleBall = 30;
    float x = 250, y = 200;
    int BlocksLeft;
    int scores = 0;
    int numberLives = 5;
    bool started = false, filmy = false, change = false, bonusActive = false;
    int Adhesion = 0;
    Text textLives, textScores, message, bonusText;

public:
    Game();
    void play();

private:
    void initGame();
    void update();
    void applyBonus(int type);

    void processEvents();
    void render();
};