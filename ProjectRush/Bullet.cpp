#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet()
{

}

Bullet::Bullet(sf::Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed)
{
	this->rotate = 90;
	this->shape.setTexture(*texture);
	this->body.setSize(sf::Vector2f(texture->getSize()));
	this->body.setPosition(pos_x, pos_y);
	this->shape.setPosition(pos_x, pos_y);
	//this->shape.setScale(0.2f, 0.2f);
	this->direction.x = dir_x;
	this->direction.y = dir_y;
	this->movementSpeed = movement_speed;
	this->shape.setOrigin(sf::Vector2f(this->shape.getGlobalBounds().width / 2, this->shape.getGlobalBounds().height / 2));
	this->shape.setRotation(0);
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

float Bullet::getRotationAngle(float angle)
{
	return this->rotate = angle;
}

void Bullet::setRotation(float angle)
{
	this->shape.setRotation(angle);
}

void Bullet::update()
{
	this->setRotation(this->rotate);
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
