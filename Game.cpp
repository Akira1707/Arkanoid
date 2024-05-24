#include "Game.h"

Game::Game() 
    : window(VideoMode(WIDTH, HEIGHT), "Arkanoid Game"),
    sBall(sf::Vector2f(250, 200)), 
    sPaddle(sf::Vector2f(230, 440)), scores(font), lives(font, 5), bonuses(font, bonusVisitor)
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
        }
    }

    message.setFont(font);
    message.setCharacterSize(50);
    message.setFillColor(Color::White);
    message.setPosition(180, 200);
    message.setString("Start");  
}

void Game::update() {
    for (int i = 0; i < blocks.size(); i++) {
        if (sBall.CollisionBlock(blocks[i], scores)) { 
            BlocksLeft -= 1; 
        };
        if (blocks[i].GetNumber() <= 0 && bonuses.getBonuses()[i]->getType() > 0) {
            bonuses.getBonuses()[i]->Update();
        }
    }
    bonuses.update(sPaddle, sBall);
    float d = sPaddle.change();
    sBall.Update();
    sBall.CollisionPaddle(sPaddle);
    if (sBall.CollisionWall()) {
        scores.update(-5);
        lives.update();
        sPaddle.SetScale(-0.1);
        sBall.Start();
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
    
    sBall.Draw(window);
    for (int i = 0; i < blocks.size(); i++) {
        blocks[i].Draw(window);
        if (blocks[i].GetNumber() <= 0 && bonuses.getBonuses()[i]->getType() != 0) {
            bonuses.getBonuses()[i]->Draw(window);
        }
    }   
    sPaddle.Draw(window);

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