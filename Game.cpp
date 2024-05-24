#include "Game.h"

Game::Game() 
    : window(VideoMode(WIDTH, HEIGHT), "Arkanoid Game"),
    sBall(sf::Vector2f(250, 200)), 
    sPaddle(sf::Vector2f(230, 440)), scores(font), lives(font, 5)
{
    initGame();
}

void Game::initGame() {
    window.setFramerateLimit(60);
    font.loadFromFile("fonts/arial.ttf");

    t.loadFromFile("images/BackG.png");
    sBackG.setTexture(t);

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

    FPaddle.setSize(Vector2f(520, 9));
    FPaddle.setPosition(0, 440);
    FPaddle.setFillColor(Color(226, 238, 245));

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

    if (elapsedTime > bonusDuration) {
        Adhesion = 0;
        change = false;
    }
    else if (Adhesion > 0 || change == true) {
        bonusText.setString("Time: " + std::to_string(static_cast<int>(bonusDuration - elapsedTime)));
    }

    float d = sPaddle.change();
    if (Adhesion == 2) {
        sBall.SetPosition(sBall.GetPosition().x + d, sBall.GetPosition().y);
        if (Keyboard::isKeyPressed(Keyboard::Enter)) Adhesion = 1;
    }
    if (Adhesion <2) {
        sBall.Update();        
        if (change) { sBall.ChangeAngle();}        
    }

    for (int i = 0; i < blocks.size(); i++) {
        if (sBall.CollisionBlock(blocks[i], scores)) { BlocksLeft -= 1; };
        if (blocks[i].GetNumber() <= 0 && Bonuses[i].getType() > 0) {
            Bonuses[i].Update();
        }
        CollisionBonusPaddle(Bonuses[i], sPaddle);
    }

    sBall.CollisionPaddle(sPaddle, Adhesion);
    if (sBall.CollisionWall(change, filmy)) {
        scores.update(-5);
        lives.update();
        sPaddle.SetScale(-0.1);
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

    if (BlocksLeft == 0) {
        message.setString("Win!");
        window.draw(message);
        window.display();
        sleep(seconds(5));
        window.close();
    }
    
    if (!started) {
        window.draw(message);
    }
    if (Adhesion > 0 || change == true) {
        window.draw(bonusText);
    }

    lives.Draw(window, message);
    window.display();
}

void Game::play() {
    while (window.isOpen()) {
        processEvents();
        if (started) update();
        render();
    }
}