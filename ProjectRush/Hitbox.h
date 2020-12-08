#pragma once


class Hitbox
{
private:
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	float offsetX;
	float offsetY;

public:
	Hitbox(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);
	~Hitbox();

	//Accessors
	const sf::Vector2f& getPosition() const;
	sf::RectangleShape& getHitbox();
	sf::Sprite& getSprite();
	const sf::FloatRect& getGlobalBounds() const;

	//Modifiers
	void setPosition(sf::Vector2f& position);
	void setPosition(float x, float y);
	void setOffset(float offset_x, float offset_y);
	void setScale(float x, float y);

	//Functions
	bool Intersect(const sf::FloatRect& frect);

	void update();
	void render(sf::RenderTarget& target);
};

