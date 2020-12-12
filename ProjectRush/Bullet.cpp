#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet()
{

}

Bullet::Bullet(sf::Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed)
{
	this->shape.setTexture(*texture);
	this->body.setSize(sf::Vector2f(texture->getSize()));
	this->body.setPosition(pos_x, pos_y);
	this->shape.setPosition(pos_x, pos_y);
	this->shape.setScale(1.f, 1.f);
	this->direction.x = dir_x;
	this->direction.y = dir_y;
	this->movementSpeed = movement_speed;
}

Bullet::~Bullet()
{

}

const sf::Vector2f Bullet::getPosition() const
{
	return this->shape.getPosition();
}

const sf::FloatRect Bullet::getBounds() const
{
	return this->shape.getGlobalBounds();
}

sf::Sprite& Bullet::getSprite()
{
	return this->shape;
}

bool Bullet::isIntersects(sf::FloatRect other)
{
	if (this->shape.getGlobalBounds().intersects(other))
		return true;
	return false;
}

void Bullet::update()
{
	this->shape.move(this->movementSpeed * this->direction);
}

Collider Bullet::getCollider()
{
	return Collider(this->body);
}

void Bullet::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
