#pragma once


class Item
{
private:
	sf::Texture texture;
	sf::RectangleShape shape;
	sf::RectangleShape hitbox;
	std::string type;

public:
	Item(sf::Texture* texture, std::string type, float x, float y);
	~Item();

	//Accessors
	const sf::Vector2f getPosition() const;
	sf::FloatRect getGlobalBounds();
	const std::string& getType() const;

	bool isIntersects(sf::FloatRect other);

	//Functions
	void update();

	//Render
	void render(sf::RenderTarget* target);
};

