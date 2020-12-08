#pragma once

#include "State.h"
#include "Button.h"
#include "EnterNameState.h"


class MainMenuState :
	public State
{
private:
	sf::Event menuEvent;

	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;
	sf::Font gameTitleFont;
	sf::Text gameTitle;

	std::map<std::string, Button*> buttons;

	sf::Music bg_music;

	//Initializer
	void initVariables();
	void initMusic();
	void initBackground();
	void initFonts();
	void initText();
	void initKeybinds();
	void initButtons();
public:
	MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, sf::View* view, Player* player);
	virtual ~MainMenuState();

	//Functions
	void endState();
	void updateButtons();
	void updateInput(const float& dt);
	void update(const float& dt);
	void renderButtons(sf::RenderTarget* target = nullptr);
	void render(sf::RenderTarget* target = nullptr);

};

