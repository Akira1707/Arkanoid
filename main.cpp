#include<SFML/Graphics.hpp>
#include<time.h>
#include <random>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace sf;

const int WIDTH = 520;
const int HEIGHT = 500;
const float PI = 3.14;

class Game {
private:
    RenderWindow window;
    Clock bonusClock;
    float bonusDuration = 5.0f;
    Font font;
    Texture t1, t2, t3, t4, b1, b2, b3, b4, b5;
    Sprite sBackG, sBall, sPaddle;
    RectangleShape FPaddle;
    std::vector<RectangleShape> blocks;
    std::vector<Text> texts;
    std::vector<int> numbers;
    std::vector<Sprite> sHearts;
    std::vector<Sprite> Bonuses;
    std::vector<int> types;

    float dBall = 5, dBonus = 3;
    int angleBall = 30;
    float x = 250, y = 200;
    int BlocksLeft;
    int scores = 0;
    int numberLives = 5;
    bool started = false, filmy = false,change = false, bonusActive = false;
    int Adhesion = 0;
    Text textLives, textScores, message, bonusText;

public:
    Game() : window(VideoMode(WIDTH, HEIGHT), "Arkanoid Game") {
        window.setFramerateLimit(60);
        font.loadFromFile("fonts/arial.ttf");

        t1.loadFromFile("images/BackG.png");
        t2.loadFromFile("images/ball.png");
        t3.loadFromFile("images/paddle.png");
        t4.loadFromFile("images/heart.png");

        FPaddle.setSize(Vector2f(520, 9));
        FPaddle.setPosition(0, 440);
        FPaddle.setFillColor(Color(226, 238, 245));

        sBackG.setTexture(t1);
        sBall.setTexture(t2);
        sPaddle.setTexture(t3);        

        sPaddle.setPosition(230, 440);
        sBall.setPosition(250, 200);  

        b1.loadFromFile("images/B01.png");
        b2.loadFromFile("images/B02.png");
        b3.loadFromFile("images/B03.png");
        b4.loadFromFile("images/B04.png");
        b5.loadFromFile("images/B05.png");

        initGame();
    }

    void play() {
        started = filmy = change = bonusActive = false;
        Adhesion = 0;
        while (window.isOpen()) {
            processEvents();
            if (started) update();
            render();
        }
    }

private:
    void initGame() {
        for (int i = 0; i <= 11; i++) {
            for (int j = 0; j <= 9; j++)
            {
                RectangleShape block(Vector2f(42, 19));
                block.setPosition(i * 43 + 2, j * 20);

                int number = rand() % 10 - 2;
                if (number < 1) number = 1;                

                int randValue = rand() % 100;
                if (randValue > 95) {
                    block.setFillColor(Color(64, 134, 68));          //Блоки, увеличивающие скорость шарика
                    number = 1;
                }
                else if (randValue > 85) {
                    block.setFillColor(Color(90, 100, 105));         //Неразрушаемые блоки
                }
                else {
                    block.setFillColor(Color(165, 110, 188));       //Блоки имеют уровень здоровья
                }

                blocks.push_back(block);
                numbers.push_back(number);               

                Text text(std::to_string(number), font, 16);
                text.setFillColor(Color::White);
                text.setPosition(i * 43 + 15, j * 20 + 1);
                texts.push_back(text);

                randValue = rand() % 100;
                int type;
                Sprite bonus;
                if (randValue > 90) {
                    bonus.setTexture(b1);
                    type = 1;
                }
                else if (randValue > 80) {
                    bonus.setTexture(b2);
                    type = 2;
                }
                else if (randValue > 70) {
                    bonus.setTexture(b3);
                    type = 3;
                }
                else if (randValue > 60) {
                    bonus.setTexture(b4);
                    type = 4;
                }
                else if (randValue > 50) {
                    bonus.setTexture(b5);
                    type = 5;                        
                }
                else {
                    bonus.setTexture(b5);
                    type = 0;
                }
                bonus.setPosition(i * 43 + 2, j * 20);
                Bonuses.push_back(bonus);
                types.push_back(type);
            }
        }

        BlocksLeft = blocks.size();
        for (int i = 0; i < numberLives; i++) {
            Sprite heart(t4);
            heart.setPosition(i * 22 + 80, 465);
            sHearts.push_back(heart);
        }
        
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

    void update() {
        float elapsedTime = bonusClock.getElapsedTime().asSeconds();
        //У бонусов ограничение по времени(меняют прилипание шарика к каретке и шарик в произвольный момент меняет траекторию)
        if (elapsedTime > bonusDuration) {           
            Adhesion = 0;
            change = false;            
        }
        else if (Adhesion > 0|| change == true){
            bonusText.setString("Time: " + std::to_string(static_cast<int>(bonusDuration - elapsedTime)));
        }

        // Бонус: меняют прилипание шарика к каретке
        if (Adhesion == 2) {
            if (Keyboard::isKeyPressed(Keyboard::Right)) { 
                sPaddle.move(6, 0);
                if (sPaddle.getGlobalBounds().left + sPaddle.getGlobalBounds().width > WIDTH) {
                    sPaddle.setPosition(WIDTH - sPaddle.getGlobalBounds().width, sPaddle.getPosition().y);
                }
                else x += 6;
            }
            if (Keyboard::isKeyPressed(Keyboard::Left)) {
                sPaddle.move(-6, 0);
                if (sPaddle.getGlobalBounds().left < 0) {
                    sPaddle.setPosition(0, sPaddle.getPosition().y);
                }
                else x -= 6;
            }
            if (Keyboard::isKeyPressed(Keyboard::Enter)) Adhesion = 1;          
        }
        else {
            x += dBall * cos(angleBall * PI / 180);
            y += dBall * sin(angleBall * PI / 180);

            // Бонус: шарик в произвольный момент меняет траекторию.
            if (change) {
                int changed = rand() % 100;
                if (changed > 95){
                    do{
                        angleBall = rand() % 360;
                    } while (15 > angleBall || angleBall > 345 || (angleBall > 75 && angleBall < 105) || (angleBall > 165 && angleBall < 195) || (angleBall > 255 && angleBall < 285));
                }
            }

            //Проверить пересечение шара и прямоугольного блока.
            for (int i = 0; i < blocks.size(); i++) {
                if (FloatRect(x + 3, y + 3, 6, 6).intersects(blocks[i].getGlobalBounds()))
                {
                    angleBall = -angleBall;
                    if (blocks[i].getFillColor() == Color(165, 110, 188)) {
                        scores += 1;
                        numbers[i] -= 1;
                        if (numbers[i] == 0) {
                            blocks[i].setPosition(-100, 0);
                            BlocksLeft -= 1;
                        }
                    }
                    else if (blocks[i].getFillColor() == Color(64, 134, 68)) {
                        numbers[i] -= 1;
                        scores += 1;
                        BlocksLeft -= 1;
                        dBall += 0.5;
                    }
                }               
            }

            //Проверить пересечение шара и каретка.
            if (FloatRect(x, y, 12, 12).intersects(sPaddle.getGlobalBounds())) {
                angleBall = -angleBall;
                if (Adhesion == 1){ 
                    Adhesion = 2;
                }
            }

            // отражаясь от стен
            if (x < 0 || x > WIDTH || y < 0) angleBall = 180 - angleBall;
            if (y < 0) angleBall = -angleBall;
            if (y > 440) {
                change = false;
                if (filmy) {
                    filmy = false;
                    angleBall = -angleBall;
                }
                else {
                    scores -= 5;
                    numberLives -= 1;
                    x = 250; y = 200;
                    sPaddle.setPosition(230, 440);
                    sBall.setPosition(x, y);
                    sPaddle.setScale(sPaddle.getScale().x - 0.1f, sPaddle.getScale().y);
                    do {
                      angleBall = rand() % 140;
                    } while (angleBall > 75 && angleBall < 105);
                    return;
                }
            }

            if (Keyboard::isKeyPressed(Keyboard::Right)) sPaddle.move(6, 0);
            if (Keyboard::isKeyPressed(Keyboard::Left)) sPaddle.move(-6, 0);
            if (sPaddle.getGlobalBounds().left < 0) {
                sPaddle.setPosition(0, sPaddle.getPosition().y);
            }
            if (sPaddle.getGlobalBounds().left + sPaddle.getGlobalBounds().width > WIDTH) {
                sPaddle.setPosition(WIDTH - sPaddle.getGlobalBounds().width, sPaddle.getPosition().y); 
            }
        }

        //Бонусы
        for (int i = 0; i < blocks.size(); i++) {
            if (numbers[i] <= 0 && types[i] > 0) {
                Bonuses[i].setPosition(Bonuses[i].getPosition().x, Bonuses[i].getPosition().y + dBonus);
            }
            if (types[i] > 0 && Bonuses[i].getGlobalBounds().intersects(sPaddle.getGlobalBounds())) {
                Bonuses[i].setPosition(-100, 0);
                applyBonus(types[i]);
                if (types[i] == 3 || types[i] == 5) {
                    bonusClock.restart();
                }
            }
        }        

        sBall.setPosition(x, y);         
    }

    void applyBonus(int type) {
        switch (type) {
        case 1: {         //меняют размер каретки
            Vector2f currentSize = sPaddle.getScale();
            float m = 2 * (rand() % 2) - 1;
            float newX;
            newX = currentSize.x + 0.1 * m;
            if (newX > 4.0f) newX = 4.0f;
            if (newX < 0.2f) newX = 0.2f;
            sPaddle.setScale(newX, currentSize.y);
            break;
        }
        case 2: {         //меняют скорость шарика
            float m = 2 * (rand() % 2) - 1;
            dBall += 0.5 * m;
            break;
        }
        case 3: {        //меняют прилипание шарика к каретке
            Adhesion = 1;
            break;
        }
        case 4: {        //одноразовое дно для шарика
            filmy = true;
            break;
        }
        case 5: {        //шарик в произвольный момент меняет траекторию
            change = true;
            break;
        }
        }
    }

    void processEvents() {
        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed)
                window.close();
            if (e.type == Event::KeyPressed && e.key.code == Keyboard::Enter)
                started = true;
        }
    }

    void render() {
        window.clear();
        window.draw(sBackG);
        window.draw(sBall);
        if (filmy) {
            window.draw(FPaddle);
        }
        window.draw(sPaddle);
        window.draw(textLives);
        textScores.setString("Scores: " + std::to_string(scores));
        window.draw(textScores);

        for (int i = 0; i < blocks.size(); i++) {
            window.draw(blocks[i]);
            if (blocks[i].getFillColor() == Color(165, 110, 188) && numbers[i] > 1) {
                texts[i].setString(std::to_string(numbers[i]));
                window.draw(texts[i]);
            }
            if (numbers[i] <= 0 && types[i] != 0) {                
                if (Bonuses[i].getPosition().y > 440) {
                    Bonuses[i].setPosition(Bonuses[i].getPosition().x, Bonuses[i].getPosition().y + 100);
                }
                window.draw(Bonuses[i]);
            }
        }

        for (int i = 0; i < numberLives; i++) {
            window.draw(sHearts[i]);
        }
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
};

int main(){
    srand(time(0));
    Game game;
    game.play();
    return 0;
}