#pragma once

#include "Collider.h"

class Bullet
{
private:

	sf::Sprite shape;
	sf::RectangleShape body;
	float rotate;

	sf::Vector2f direction;
	float movementSpeed;

public:
	Bullet();
	Bullet(sf::Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed);
	virtual ~Bullet();

	//Accessor
	const sf::Vector2f getPosition() const;
	const sf::FloatRect getBounds() const;
	sf::Sprite& getSprite();
	bool isIntersects(sf::FloatRect other);
	float getRotationAngle(float angle);

	//Modifiers
	void setRotation(float angle);

	//Functions
	void update();
	Collider getCollider();
	void render(sf::RenderTarget* target);

};

