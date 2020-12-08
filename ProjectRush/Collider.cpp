#include "stdafx.h"
#include "Collider.h"

Collider::Collider(sf::RectangleShape& body) :
	body(body)
{

}

Collider::~Collider()
{

}

sf::Vector2f Collider::getPosition()
{
	return body.getPosition();
}

sf::Vector2f Collider::getHalfSize()
{
	return { body.getSize() / 2.f };
}

sf::FloatRect Collider::getGlobalBounds()
{
	return body.getGlobalBounds();
}

float Collider::getWidth()
{
	return body.getGlobalBounds().width;
}

float Collider::getHeight()
{
	return body.getGlobalBounds().height;
}

void Collider::move(float dx, float dy)
{
	body.move(dx, dy);
}

bool Collider::checkCollision(Collider other, sf::Sprite& spriteOther, sf::Vector2f& direction, float push)
{
	sf::Vector2f otherPosition = other.getPosition();
	sf::Vector2f otherHalfSize = other.getHalfSize();
	sf::Vector2f thisPosition = getPosition();
	sf::Vector2f thisHalfSize = getHalfSize();
	float otherWidth = other.getWidth();
	float otherHeight = other.getHeight();
	float thisWidth = getGlobalBounds().width;
	float thisHeight = getGlobalBounds().height;

	float delta_x = (otherPosition.x + otherWidth / 2.f) - (thisPosition.x + thisWidth / 2.f);
	float delta_y = (otherPosition.y + otherHeight / 2.f) - (thisPosition.y + thisHeight / 2.f);

	float intersectX = abs(delta_x) - (otherHalfSize.x + thisHalfSize.x);
	float intersectY = abs(delta_y) - (otherHalfSize.y + thisHalfSize.y);

	if (intersectX < 0.0f && intersectY < 0.0f)
	{
		push = std::min(std::max(push, 0.0f), 1.0f);

		if (intersectX > intersectY)
		{
			if (delta_x > 0.0f)
			{
				move(intersectX * (1.0f - push), 0.f);
				other.move(-intersectX * push, 0.f); //if collide with the left side -> move up
				spriteOther.move(-intersectX * push, 0.f);

				direction.x = 1.f;
				direction.y = 0.f;
			}
			else
			{
				move(-intersectX * (1.0f - push), 0.f);
				other.move(0.f, intersectY * push * 0.2f); //if collide with the right side -> move up
				spriteOther.move(0.f, intersectY * push * 0.2f);

				direction.x = -1.f;
				direction.y = 0.f;
			}
		}
		else
		{
			if (delta_y > 0.0f)
			{
				move(0.f, intersectY * (1.0f - push));
				other.move(0.f, -intersectY * push);
				//spriteOther.move(0.f, -intersectY * push);
				direction.x = 0.f;
				direction.y = 1.f;
			}
			else
			{
				move(0.f, -intersectY * (1.0f - push));
				other.move(0.f, intersectY * push);
				spriteOther.move(0.f, intersectY * push);
				direction.x = 0.f;
				direction.y = -1.f;
			}
		}
		return true;
	}

	return false;
}
