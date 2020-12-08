#pragma once

class Entity
{
private:

protected:

public:
	Entity();
	~Entity();

	//Functions
	virtual void move(const float& dt, const float dir_x, const float dir_y);

	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderWindow* target) = 0;
};

