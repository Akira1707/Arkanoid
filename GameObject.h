#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class GameObject {
protected:
	Vector2f position_;
public:
	GameObject(Vector2f position_);
	virtual void Draw(RenderWindow& window) = 0;
	virtual void Update() = 0;
	void SetPosition(float x, float y);
	Vector2f GetPosition();
	virtual ~GameObject();
};
