#pragma once
#include "Player.h"
#include "Bullet.h"
#include "Platform.h"
#include "MainMenuState.h"
#include "Enemy.h"

class Game
{
private:
	//Variables
	sf::RenderWindow* window;
	sf::Event ev;
	std::vector<sf::VideoMode> VideoModes;
	sf::VideoMode windowBounds;
	sf::View view;
	Player* player;

	sf::String input;
	sf::Text text;

	//Delta time
	sf::Clock dtClock;
	float dt;

	//State
	std::stack<State*> states;
	std::map<std::string, int> supportedKeys;

	//Initialization
	void initVariables();
	void initWindow();
	void initKeys();
	void initStates();

public:
	//Contructors / Destructors
	Game();
	~Game();

	//Functions
	void endApplication();

	//Update
	void updateDt();
	void update(const float& dt);
	//Render
	void render();
	//Core
	void run();
	const sf::RenderWindow& getWindow() const;
};

