#pragma once

#include <SFML/Graphics.hpp>

class Item
{
private:
	sf::Texture texture;
	sf::RectangleShape shape;
	std::string type;

public:
	Item(sf::Texture* texture, std::string type, float x, float y);
	~Item();

	//Accessors
	sf::FloatRect getGlobalBounds();
	const std::string& getType() const;

	//Functions
	void update();

	//Render
	void render(sf::RenderTarget* target);
};

