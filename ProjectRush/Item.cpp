#include "stdafx.h"
#include "Item.h"

Item::Item(sf::Texture* texture, std::string type, float x, float y)
	:type(type)
{
	this->shape.setTexture(texture);
	this->shape.setSize(sf::Vector2f(texture->getSize().x , texture->getSize().y ));
	this->hitbox.setSize(sf::Vector2f(texture->getSize().x, texture->getSize().y));
	this->hitbox.setOutlineThickness(1.f);
	this->hitbox.setFillColor(sf::Color(255, 255, 255, 0));
	this->hitbox.setOutlineColor(sf::Color::Red);
	this->shape.setPosition(x, y);

	if (this->type == "HEART")
	{
		this->shape.setSize(sf::Vector2f(50.f, 50.f));
		this->hitbox.setSize(this->shape.getSize());
	}
	if (this->type == "FIRE_RATE")
	{
		this->shape.setSize(sf::Vector2f(50.f, 75.f));
		this->hitbox.setSize(this->shape.getSize());
	}
	if(this->type == "DMG_BOOST")
	{
		this->shape.setSize(sf::Vector2f(50.f, 75.f));
			this->hitbox.setSize(this->shape.getSize());
	}
	if (this->type == "GREEN_GEM")
	{
		this->shape.setSize(sf::Vector2f(25.f, 40.f));
		this->hitbox.setSize(this->shape.getSize());
	}
	if (this->type == "BLUE_GEM")
	{
		this->shape.setSize(sf::Vector2f(25.f, 40.f));
		this->hitbox.setSize(this->shape.getSize());
	}
	if (this->type == "RED_GEM")
	{
		this->shape.setSize(sf::Vector2f(25.f, 40.f));
		this->hitbox.setSize(this->shape.getSize());
	}
}

Item::~Item()
{

}

const sf::Vector2f Item::getPosition() const
{
	return this->shape.getPosition();
}

sf::FloatRect Item::getGlobalBounds()
{
	return this->shape.getGlobalBounds();
}

const std::string& Item::getType() const
{
	return this->type;
}

bool Item::isIntersects(sf::FloatRect other)
{
	if (this->shape.getGlobalBounds().intersects(other))
		return true;
	return false;
}

void Item::update()
{

}

void Item::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
	
	target->draw(this->hitbox);
}
