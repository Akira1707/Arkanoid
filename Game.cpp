#include "Game.h"

Game::Game() 
    : window(VideoMode(WIDTH, HEIGHT), "Arkanoid Game")
{
    initGame();
}

void Game::initGame() {
    window.setFramerateLimit(60);
    font.loadFromFile("fonts/arial.ttf");

    t.loadFromFile("images/BackG.png");
    sBackG.setTexture(t);
    h.loadFromFile("images/heart.png");

    ((Ball*)sBall)->LoadImg("images/ball.png");
    ((Paddle*)sPaddle)->LoadImg("images/paddle.png");

    for (int i = 0; i <= 11; i++) {
        for (int j = 0; j <= 9; j++)
        {
            Vector2f position(i * 43 + 2, j * 20);

            GameObject* block = new Block(position, font);
            if ( ((Block*)block)->GetType() != 2) BlocksLeft += 1;
            blocks.push_back(block);

            GameObject* bonus = new Bonus(position, font);
            Bonuses.push_back(bonus);
        }
    }

    for (int i = 0; i < numberLives; i++) {
        Sprite heart(h);
        heart.setPosition(i * 22 + 80, 465);
        sHearts.push_back(heart);
    }

    FPaddle.setSize(Vector2f(520, 9));
    FPaddle.setPosition(0, 440);
    FPaddle.setFillColor(Color(226, 238, 245));

    textLives.setFont(font);
    textLives.setCharacterSize(24);
    textLives.setFillColor(Color::White);
    textLives.setPosition(10, 460);
    textLives.setString("Lives: ");

    textScores.setFont(font);
    textScores.setCharacterSize(24);
    textScores.setFillColor(Color::White);
    textScores.setPosition(200, 460);

    message.setFont(font);
    message.setCharacterSize(50);
    message.setFillColor(Color::White);
    message.setPosition(180, 200);
    message.setString("Start");  

    bonusText.setFont(font);
    bonusText.setCharacterSize(24);
    bonusText.setFillColor(Color::White);
    bonusText.setPosition(350, 460);
}

void Game::update() {
    float elapsedTime = bonusClock.getElapsedTime().asSeconds();

    //У бонусов ограничение по времени(меняют прилипание шарика к каретке и шарик в произвольный момент меняет траекторию)
    if (elapsedTime > bonusDuration) {
        Adhesion = 0;
        change = false;
    }
    else if (Adhesion > 0 || change == true) {
        bonusText.setString("Time: " + std::to_string(static_cast<int>(bonusDuration - elapsedTime)));
    }

    // Бонус: меняют прилипание шарика к каретке
    float d = ((Paddle*)sPaddle)->change();
    if (Adhesion == 2) {
        sBall->SetPosition(sBall->GetPosition().x + d, sBall->GetPosition().y);
        if (Keyboard::isKeyPressed(Keyboard::Enter)) Adhesion = 1;
    }
    if (Adhesion <2) {
        sBall->Update();        
        if (change) { ((Ball*)sBall)->ChangeAngle();}        // Бонус: шарик в произвольный момент меняет траекторию.
    }

    for (int i = 0; i < blocks.size(); i++) {
        CollisionBallBlock(sBall, blocks[i]);
        if (((Block*)blocks[i])->GetNumber() <= 0 && ((Bonus*)Bonuses[i])->getType() > 0) {
            Bonuses[i]->Update();
        }
        CollisionBonusPaddle(Bonuses[i], sPaddle);
    }

    CollisionBallPaddle(sBall, sPaddle);
    CollisionWall(sBall);
}

void Game::CollisionBallBlock(GameObject* sBall, GameObject* block) {
    Ball* ball = dynamic_cast<Ball*>(sBall);
    Block* blk = dynamic_cast<Block*>(block);
    if (FloatRect(ball->GetPosition().x, ball->GetPosition().y, 12, 12).intersects(blk->GetBounds()))
    {
        ball->SetAngle(-ball->GetAngle());
        if (blk->GetType() == 3) {
            scores += 1;
            blk->SetNumber(blk->GetNumber() - 1);
            if (blk->GetNumber() == 0) {
                BlocksLeft -= 1;
                blk->SetPosition(-100, -100);
            }
        }
        else if (blk->GetType() == 1) {
            blk->SetNumber(blk->GetNumber() - 1);
            scores += 1;
            BlocksLeft -= 1;
            blk->SetPosition(-100, -100);
            ball->ChangeSpeed(0.3);
        }
    }
}

void Game::CollisionBallPaddle(GameObject* sBall, GameObject* sPaddle) {
    if (FloatRect(sBall->GetPosition().x, sBall->GetPosition().y + 2, 12, 10).intersects(((Paddle*)sPaddle)->GetBounds())) {
        ((Ball*)sBall)->SetAngle(-((Ball*)sBall)->GetAngle());
        if (Adhesion == 1) {
            Adhesion = 2;
        }
    }
}

void Game::CollisionWall(GameObject* sBall) {
    Ball* ball = dynamic_cast<Ball*>(sBall);
    if (ball->GetPosition().x < 0 ||ball->GetPosition().x > WIDTH || ball->GetPosition().y < 0) ball->SetAngle(180 - ball->GetAngle());
    if (ball->GetPosition().y < 0) ball->SetAngle(-ball->GetAngle());
    if (ball->GetPosition().y > 440) {
        change = false;
        if (filmy) {
            filmy = false;
            ball->SetAngle(-ball->GetAngle());
        }
        else {
            scores -= 5;
            numberLives -= 1;
            ball->SetPosition(250,200);
            ((Paddle*)sPaddle)->SetScale(- 0.1);
            float angle;
            do {
                angle = rand() % 140;
            } while ((angle > 75 && angle < 105) || (angle < 15));
            ball->SetAngle(angle);
        }
    }
}

void Game::CollisionBonusPaddle(GameObject* bonus, GameObject* sPaddle) {
    Bonus* b = dynamic_cast<Bonus*>(bonus);
    Paddle* paddle = dynamic_cast<Paddle*>(sPaddle);
    if (b->getType() > 0 && b->GetBounds().intersects(paddle->GetBounds())) {
        b->SetPosition(-100, 0);
        applyBonus(b->getType());
        if (b->getType() || b->getType() == 5) {
            bonusClock.restart();
        }
    }
}

void Game::applyBonus(int type) {
    switch (type) {
    case 1: {         
        float m = 2 * (rand() % 2) - 1;
        ((Paddle*)sPaddle)->SetScale(m*0.1);
        break;
    }
    case 2: {         
        float m = 2 * (rand() % 2) - 1;
        ((Ball*)sBall)->ChangeSpeed(m * 0.3);
        break;
    }
    case 3: {       
        Adhesion = 1;
        break;
    }
    case 4: {        
        filmy = true;
        break;
    }
    case 5: {       
        change = true;
        break;
    }
    }
}

void Game::processEvents() {
    Event e;
    while (window.pollEvent(e)) {
        if (e.type == Event::Closed)
            window.close();
        if (e.type == Event::KeyPressed && e.key.code == Keyboard::Enter)
            started = true;
    }
}

void Game::render() {
    window.clear();
    window.draw(sBackG);

    if (filmy) {
        window.draw(FPaddle);
    }    
    
    sBall->Draw(window);
    sPaddle->Draw(window);

    for (int i = 0; i < blocks.size(); i++) {
        blocks[i]->Draw(window);
        if (((Block*)blocks[i])->GetNumber() <= 0 && ((Bonus*)Bonuses[i])->getType() != 0) {
            Bonuses[i]->Draw(window);
        }
    }

    for (int i = 0; i < numberLives; i++) {
        window.draw(sHearts[i]);
    }

    window.draw(textLives);
    textScores.setString("Scores: " + std::to_string(scores));
    window.draw(textScores);

    if (BlocksLeft == 0) {
        message.setString("Win!");
        window.draw(message);
        window.display();
        sleep(seconds(5));
    }
    if (numberLives == 0) {
        message.setString("Game over!");
        window.draw(message);
        window.display();
        sleep(seconds(5));
    }
    if (!started) {
        window.draw(message);
    }
    if (Adhesion > 0 || change == true) {
        window.draw(bonusText);
    }

    window.display();
}

void Game::play() {
    while (window.isOpen()) {
        processEvents();
        if (started) update();
        render();
    }
}