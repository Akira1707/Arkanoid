#include "Scores.h"

Scores::Scores(Font& font) {
    textScores.setFont(font);
    textScores.setCharacterSize(24);
    textScores.setFillColor(Color::White);
    textScores.setPosition(200, 460);
}
void Scores::update(int d) {
    score += d;
}
void Scores::Draw(RenderWindow& window) {
    textScores.setString("Scores: " + std::to_string(score));
    window.draw(textScores);
}