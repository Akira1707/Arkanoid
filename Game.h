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

    GameObject* sBall = new Ball(Vector2f(250, 200));
    GameObject* sPaddle = new Paddle(Vector2f(230, 440));

    Texture t, h;
    Sprite sBackG;
    RectangleShape FPaddle;
    std::vector<GameObject*> blocks;
    std::vector<GameObject*> Bonuses;
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

    void CollisionBallBlock(GameObject* sBall, GameObject* block);

    void CollisionBallPaddle(GameObject* sBall, GameObject* sPaddle);
    void CollisionWall(GameObject* sBall);
    void CollisionBonusPaddle(GameObject* bonus, GameObject* sPaddle);

public:
    Game();
    void play();
};