#pragma once
#include "State.h"
#include "GameplayState.h"
#include "Enemy.h"
#include"Player.h"

class EnterNameState :
	public State
{
private:
	sf::Event nameEvent;
	sf::RectangleShape background;
	sf::Texture backgroundTexture;

	sf::RectangleShape textHolder;
	sf::Text nameEnter;

	sf::Font font;
	sf::String input;
	std::string nameString;
	sf::Text text;

	std::map<std::string, Button*> buttons;

	sf::Music bg_music;

	sf::SoundBuffer enterWord;
	sf::Sound enterWordSound;
	sf::SoundBuffer deleteWord;
	sf::Sound deleteWordSound;
	
	//Add Animation
	std::map<std::string, sf::Texture*> textures;
	std::vector<Enemy*> enemies;
	
	//Decorate

	//Initializer
	void initVariables();
	void initMusic();
	void initBackground();
	void initFont();
	void initText();
	void initKeybinds();
	void initButtons();
	void initDecorates();

public:
	EnterNameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, sf::View* view, Player* player);
	virtual ~EnterNameState();

	//Functions
	void endState();
	void updateButtons();
	void updateInput(const float& dt);
	void update(const float& dt);
	void renderButtons(sf::RenderTarget* target = nullptr);
	void render(sf::RenderTarget* target);
};

