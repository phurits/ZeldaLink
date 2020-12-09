#pragma once

#include "stdafx.h"
#include "Player.h"

class State
{
private:


protected:
	std::stack<State*>* states;
	sf::RenderWindow* window;
	Player* player;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	bool quit;

	sf::View* view;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	std::vector<sf::Texture> textures;
	


	//Functions
	virtual void initKeybinds() = 0;

public:
	State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, sf::View* view, Player* player);
	virtual ~State();

	//Accessors
	const bool& getQuit() const;

	virtual void checkForQuit();

	virtual void endState() = 0;
	virtual void updateMousePosition();
	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

