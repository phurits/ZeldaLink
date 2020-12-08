#include "stdafx.h"
#include "Item.h"

Item::Item(sf::Texture* texture, std::string type, float x, float y)
	:type(type)
{
	this->shape.setTexture(texture);
	this->shape.setSize(sf::Vector2f(texture->getSize().x * 2.f, texture->getSize().y * 2.f));
	this->shape.setPosition(x, y);
}

Item::~Item()
{

}

sf::FloatRect Item::getGlobalBounds()
{
	return this->shape.getGlobalBounds();
}

const std::string& Item::getType() const
{
	return this->type;
}

void Item::update()
{

}

void Item::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
