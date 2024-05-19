#include "Game.h"

Game::Game() 
    : window(VideoMode(WIDTH, HEIGHT), "Arkanoid Game"),
    sBall(sf::Vector2f(250, 200)), 
    sPaddle(sf::Vector2f(230, 440)) 
{
    initGame();
}

void Game::initGame() {
    window.setFramerateLimit(60);
    font.loadFromFile("fonts/arial.ttf");

    t.loadFromFile("images/BackG.png");
    sBackG.setTexture(t);
    h.loadFromFile("images/heart.png");

    sBall.LoadImg("images/ball.png");
    sPaddle.LoadImg("images/paddle.png");

    for (int i = 0; i <= 11; i++) {
        for (int j = 0; j <= 9; j++)
        {
            Vector2f position(i * 43 + 2, j * 20);

            Block block(position, font);
            if (block.GetType() != 2) BlocksLeft += 1;
            blocks.push_back(block);

            Bonus bonus(position, font);
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
    float d = sPaddle.update();
    if (Adhesion == 2) {
        sBall.SetPosition(sBall.GetPosition().x + d, sBall.GetPosition().y);
        if (Keyboard::isKeyPressed(Keyboard::Enter)) Adhesion = 1;
    }
    if (Adhesion <2) {
        sBall.Update();        
        if (change) { sBall.ChangeAngle();}        // Бонус: шарик в произвольный момент меняет траекторию.
    }

    for (int i = 0; i < blocks.size(); i++) {
        CollisionBallBlock(sBall, blocks[i]);
        if (blocks[i].GetNumber() <= 0 && Bonuses[i].getType() > 0) {
            Bonuses[i].Update();
        }
        CollisionBonusPaddle(Bonuses[i], sPaddle);
    }

    CollisionBallPaddle(sBall, sPaddle);
    CollisionWall(sBall);
}

void Game::CollisionBallBlock(Ball& sBall, Block& block) {
    if (FloatRect(sBall.GetPosition().x, sBall.GetPosition().y, 12, 12).intersects(block.GetBounds()))
    {
        sBall.SetAngle(-sBall.GetAngle());
        if (block.GetType() == 3) {
            scores += 1;
            block.SetNumber(block.GetNumber() - 1);
            if (block.GetNumber() == 0) {
                BlocksLeft -= 1;
                block.SetPosition(-100, -100);
            }
        }
        else if (block.GetType() == 1) {
            block.SetNumber(block.GetNumber() - 1);
            scores += 1;
            BlocksLeft -= 1;
            block.SetPosition(-100, -100);
            sBall.ChangeSpeed(0.3);
        }
    }
}

void Game::CollisionBallPaddle(Ball& sBall, Paddle& sPaddle) {
    if (FloatRect(sBall.GetPosition().x, sBall.GetPosition().y + 2, 12, 10).intersects(sPaddle.GetBounds())) {
        sBall.SetAngle(-sBall.GetAngle());
        if (Adhesion == 1) {
            Adhesion = 2;
        }
    }
}

void Game::CollisionWall(Ball& sBall) {
    if (sBall.GetPosition().x < 0 || sBall.GetPosition().x > WIDTH || sBall.GetPosition().y < 0) sBall.SetAngle(180 - sBall.GetAngle());
    if (sBall.GetPosition().y < 0) sBall.SetAngle(-sBall.GetAngle());
    if (sBall.GetPosition().y > 440) {
        change = false;
        if (filmy) {
            filmy = false;
            sBall.SetAngle(-sBall.GetAngle());
        }
        else {
            scores -= 5;
            numberLives -= 1;
            sBall.SetPosition(250,200);
            sPaddle.SetScale(- 0.1);
            float angle;
            do {
                angle = rand() % 140;
            } while ((angle > 75 && angle < 105) || (angle < 15));
            sBall.SetAngle(angle);
        }
    }
}

void Game::CollisionBonusPaddle(Bonus& bonus, Paddle& sPaddle) {
    if (bonus.getType() > 0 && bonus.GetBounds().intersects(sPaddle.GetBounds())) {
        bonus.SetPosition(-100, 0);
        applyBonus(bonus.getType());
        if (bonus.getType() || bonus.getType() == 5) {
            bonusClock.restart();
        }
    }
}

void Game::applyBonus(int type) {
    switch (type) {
    case 1: {         
        float m = 2 * (rand() % 2) - 1;
        sPaddle.SetScale(m*0.1);
        break;
    }
    case 2: {         
        float m = 2 * (rand() % 2) - 1;
        sBall.ChangeSpeed(m * 0.3);
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
    
    sBall.Draw(window);
    sPaddle.Draw(window);

    for (int i = 0; i < blocks.size(); i++) {
        blocks[i].Draw(window);
        if (blocks[i].GetNumber() <= 0 && Bonuses[i].getType() != 0) {
            Bonuses[i].Draw(window);
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