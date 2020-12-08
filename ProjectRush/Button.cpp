#include "stdafx.h"
#include "Button.h"

Button::Button(float x, float y, float width, float height, sf::Font* font, std::string text, unsigned int text_size
	, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
	this->buttonState = BTN_IDLE;

	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setPosition(x, y);

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setOutlineColor(sf::Color::Black);
	this->text.setOutlineThickness(1.f);
	this->text.setCharacterSize(text_size);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y
	);

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	this->shape.setFillColor(this->idleColor);
}

Button::~Button()
{
}

//Accessors
const bool Button::isPressed() const
{
	if (this->buttonState == BTN_ACTIVE)
	{
		return true;
	}
	return false;
}

//Functions

void Button::update(const sf::Vector2f mousePos)
{
	/*Update the boolean for the hover and press*/

	//Idle
	this->buttonState = BTN_IDLE;
	//Hover
	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = BTN_HOVER;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_ACTIVE;
		}
	}
	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		this->text.setScale(1.f, 1.f);
		this->text.setFillColor(sf::Color(255, 255, 255, 255));
		break;
	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		this->text.setScale(1.1f, 1.1f);
		this->text.setFillColor(sf::Color(180, 0, 0, 255));
		break;
	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		this->text.setFillColor(sf::Color(255, 255, 255, 255));
		break;
	default:
		this->shape.setFillColor(sf::Color::Red);
		break;
	}
}

void Button::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
	target->draw(this->text);
}
