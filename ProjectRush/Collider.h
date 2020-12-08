#pragma once
class Collider
{
private:

	sf::RectangleShape& body;

public:
	Collider(sf::RectangleShape& body);
	~Collider();

	//Accessor
	sf::Vector2f getPosition();
	sf::Vector2f getHalfSize();
	sf::FloatRect getGlobalBounds();
	float getWidth();
	float getHeight();

	void move(float dx, float dy);
	bool checkCollision(Collider other, sf::Sprite& spriteOther, sf::Vector2f& direction, float push);

};

