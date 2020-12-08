#include "stdafx.h"
#include "Hitbox.h"

Hitbox::Hitbox(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height)
	:sprite(sprite), offsetX(offset_x), offsetY(offset_y)
{
	this->hitbox.setPosition(this->sprite.getPosition().x + offset_x, this->sprite.getPosition().y + offset_y);
	this->hitbox.setSize(sf::Vector2f(width, height));
	this->hitbox.setFillColor(sf::Color::Transparent);
	this->hitbox.setOutlineThickness(1.f);
	this->hitbox.setOutlineColor(sf::Color::Red);
}

Hitbox::~Hitbox()
{

}

//Accessors
const sf::Vector2f& Hitbox::getPosition() const
{
	return this->hitbox.getPosition();
}

sf::RectangleShape& Hitbox::getHitbox()
{
	return this->hitbox;
}

sf::Sprite& Hitbox::getSprite()
{
	return this->sprite;
}

const sf::FloatRect& Hitbox::getGlobalBounds() const
{
	return this->hitbox.getGlobalBounds();
}

//Modifiers
void Hitbox::setPosition(sf::Vector2f& position)
{
	this->hitbox.setPosition(position);
	this->sprite.setPosition(position.x - this->offsetX, position.y - this->offsetY);
}

void Hitbox::setPosition(float x, float y)
{
	this->hitbox.setPosition(x, y);
	//this->sprite.setPosition(x - this->offsetX, y - this->offsetY);

}

void Hitbox::setOffset(float offset_x, float offset_y)
{
	this->offsetX = offset_x;
	this->offsetY = offset_y;
}

void Hitbox::setScale(float x, float y)
{
	this->hitbox.setScale(1.f, 1.f);
	this->sprite.setScale(x, y);
}

//Functions
bool Hitbox::Intersect(const sf::FloatRect& frect)
{
	return this->hitbox.getGlobalBounds().intersects(frect);
}

void Hitbox::update()
{
	this->hitbox.setPosition(this->sprite.getPosition().x + this->offsetX, this->sprite.getPosition().y + this->offsetY);
}

void Hitbox::render(sf::RenderTarget& target)
{
	target.draw(this->hitbox);
}
