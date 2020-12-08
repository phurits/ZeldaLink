#pragma once

#include "Collider.h"

class Platform
{
private:
	sf::Sprite sprite;
	sf::RectangleShape body;
public:
	Platform(sf::Texture* texture, sf::Vector2f position);
	~Platform();

	Collider getCollider();
	void render(sf::RenderTarget* target);
	sf::Sprite getSprite();
};

