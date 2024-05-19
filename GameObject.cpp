#include "GameObject.h"

GameObject::GameObject(Vector2f position_): position_(position_){}
void GameObject::SetPosition(float x, float y) { position_ = Vector2f(x, y); }
Vector2f GameObject::GetPosition() { return position_; }
GameObject::~GameObject(){}