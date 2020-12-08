#include "stdafx.h"
#include "Platform.h"

Platform::Platform(sf::Texture* texture, sf::Vector2f position)
{
	sprite.setPosition(position);
	sprite.setTexture(*texture);
	sprite.setScale(1.f, 1.f);
	body.setPosition(position);
	body.setSize(sf::Vector2f(texture->getSize()));
}

Platform::~Platform()
{

}

Collider Platform::getCollider()
{
	return Collider(body);
}

void Platform::render(sf::RenderTarget* target)
{
	target->draw(sprite);
}

sf::Sprite Platform::getSprite()
{
	return this->sprite;
}
