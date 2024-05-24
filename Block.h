#pragma once
#include "GameObject.h"

class Block : public GameObject{
public:
	Block(Vector2f position_, Font& font);
	void Draw(RenderWindow& windoem) override;
    void Update() override;
    FloatRect GetBounds();
    int GetType();
    int GetNumber();
    void SetNumber(int n);
private:
    RectangleShape block;
    Text text;  
    int number; 
    int type;
};