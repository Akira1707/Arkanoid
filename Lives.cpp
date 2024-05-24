#include "Lives.h"

Lives::Lives(Font& font, int numberLives): numberLives(numberLives) {
	h.loadFromFile("images/heart.png");
    for (int i = 0; i < numberLives; i++) {
        Sprite heart(h);
        heart.setPosition(i * 22 + 80, 465);
        sHearts.push_back(heart);
    }

    textLives.setFont(font);
    textLives.setCharacterSize(24);
    textLives.setFillColor(Color::White);
    textLives.setPosition(10, 460);
    textLives.setString("Lives: ");
}

void Lives::update(){ numberLives -= 1; }

void Lives::Draw(RenderWindow& window, Text& message) {
    for (int i = 0; i < numberLives; i++) {
        window.draw(sHearts[i]);
    }

    window.draw(textLives);
    if (numberLives == 0) {
        message.setString("Game over!");
        window.draw(message);
        window.display();
        sleep(seconds(5));
        window.close();
    }
}