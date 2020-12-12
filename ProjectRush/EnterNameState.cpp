#include "stdafx.h"
#include "EnterNameState.h"
#include "Player.h"

//Initializer
void EnterNameState::initVariables()
{
	this->background.setOrigin(this->window->getSize().x / 2, this->window->getSize().y / 2);
	this->background.setPosition(this->view->getCenter());
	//this->background.setPosition(this->view->getCenter().x - this->window->getSize().x / 2.f, this->view->getCenter().y - this->window->getSize().y / 2.f);
	this->player = new Player();


	this->player->setPosition(20.f, 20.f);

	this->nameEnter.setFont(this->font);
	this->nameEnter.setCharacterSize(100.f);
	this->nameEnter.setLetterSpacing(1.6f);
	this->nameEnter.setOutlineThickness(2.f);
	this->nameEnter.setFillColor(sf::Color::Black);
	this->nameEnter.setOutlineColor(sf::Color::White);
	this->nameEnter.setPosition(430.f, 30.f);
	this->nameEnter.setString("ENTER NAME");

	this->textHolder.setFillColor(sf::Color(255,255,255,100));
	this->textHolder.setSize(sf::Vector2f(200.f, 50.f));
	this->textHolder.setOutlineThickness(1.f);
	this->textHolder.setOutlineColor(sf::Color::Black);
	this->textHolder.setPosition(sf::Vector2f(700,300));

	this->text.setFillColor(sf::Color::Black);
	this->text.setOutlineThickness(1.f);
	this->text.setOutlineColor(sf::Color::White);
}

void EnterNameState::initMusic()
{
	this->bg_music.openFromFile("Resources/Sounds/EnterNameState_Music.ogg");
	this->bg_music.setLoop(true);
	this->bg_music.setVolume(20.f);
	this->bg_music.play();

	//initSound
	if (!this->enterWord.loadFromFile("Resources/Sounds/enterWord.ogg"))
		std::cout << "ERROR::PLAYER::COULD NOT LOAD enterWord" << std::endl;
	this->enterWordSound.setBuffer(this->enterWord);
	this->enterWordSound.setVolume(30.f);

	if (!this->deleteWord.loadFromFile("Resources/Sounds/deleteWord.ogg"))
		std::cout << "ERROR::PLAYER::COULD NOT LOAD delteWord" << std::endl;
	this->deleteWordSound.setBuffer(this->deleteWord);
	this->deleteWordSound.setVolume(30.f);
}

void EnterNameState::initBackground()
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x)
		, static_cast<float>(this->window->getSize().y)));

	if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/enternameBG.png"))
	{
		std::cout << "ERROR::MAIN_MENU_STATE::FAILED TO LOAD BACKGROUND TO TEXTURE" << std::endl;
	}

	this->background.setTexture(&this->backgroundTexture);
}

void EnterNameState::initFont()
{
	if (!this->font.loadFromFile("Fonts/triforce.ttf"))
	{
		std::cout << "ERROR::MAINMENUSTATE::COULD NOT LOAD FONT!" << std::endl;
	}
}

void EnterNameState::initText()
{
	this->input = "";
	this->text.setFont(this->font);
	this->text.setOrigin(this->text.getGlobalBounds().width / 2, 0);
	this->text.setCharacterSize(70.f);
	this->text.setPosition(800,250);
}

void EnterNameState::initKeybinds()
{
	std::ifstream ifs("config/enternamestate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}
	ifs.close();
}

void EnterNameState::initButtons()
{
	this->buttons["GAME_STATE"] = new Button(this->view->getCenter().x - this->window->getSize().x / 2.f + 630 , this->view->getCenter().y - this->window->getSize().y / 2.f + 420, 350, 100, &this->font, "START", 80,
		sf::Color(255, 255, 255, 0), sf::Color(255, 255, 255, 0), sf::Color(255, 255, 255, 0));
}

void EnterNameState::initDecorates()
{
	this->textures["ZELDA"] = new sf::Texture;
	this->textures["ZELDA"]->loadFromFile("Resources/Images/Sprites/Player/Full_Movement.png");

	this->textures["BLUE_SLIME"] = new sf::Texture;
	this->textures["BLUE_SLIME"]->loadFromFile("Resources/Images/Sprites/Enemy/blue_slime.png");
	this->textures["PINK_SLIME"] = new sf::Texture;
	this->textures["PINK_SLIME"]->loadFromFile("Resources/Images/Sprites/Enemy/pink_slime.png");
	this->textures["YELLOW_SLIME"] = new sf::Texture;
	this->textures["YELLOW_SLIME"]->loadFromFile("Resources/Images/Sprites/Enemy/yellow_slime.png");

	//Spawn all Zelda Left Side
	this->enemies.push_back(new Enemy(this->textures["ZELDA"], "ZELDA_U", 225, 190));
	this->enemies.push_back(new Enemy(this->textures["ZELDA"], "ZELDA_D", 235, 300));
	this->enemies.push_back(new Enemy(this->textures["ZELDA"], "ZELDA_L", 110, 300));
	this->enemies.push_back(new Enemy(this->textures["ZELDA"], "ZELDA_R", 363, 300));

	this->enemies.push_back(new Enemy(this->textures["BLUE_SLIME"], "ENS_BSLIME", 20, 700));
	this->enemies.push_back(new Enemy(this->textures["PINK_SLIME"], "ENS_PSLIME", 240, 700));
	this->enemies.push_back(new Enemy(this->textures["YELLOW_SLIME"], "ENS_YSLIME", 480, 700));

}

EnterNameState::EnterNameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, sf::View* view, Player* player)
	: State(window, supportedKeys, states, view, player)
{
	this->initVariables();
	this->initMusic();
	this->initBackground();
	this->initFont();
	this->initText();
	this->initKeybinds();
	this->initButtons();
	this->initDecorates();
	

}

EnterNameState::~EnterNameState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
	for (auto& i : this->textures)
	{
		delete i.second;
	}
	for (auto* enemy : this->enemies)
	{
		delete enemy;
	}
}

void EnterNameState::endState()
{
	std::cout << "Ending EnterNameState" << std::endl;
}

void EnterNameState::updateButtons()
{
	for (auto& i : this->buttons)
	{
		i.second->update(this->mousePosView);
	}

	//Start
	if (this->buttons["GAME_STATE"]->isPressed() && !this->nameString.empty())
	{
		this->player->setName(this->nameString);
		if (!this->states->empty())
			this->states->pop();
		this->states->push(new GameplayState(this->window, this->supportedKeys, this->states, this->view, this->player)); //Switch push state btw Gamestate & GameplayState
		this->bg_music.stop();
	}
}

void EnterNameState::updateInput(const float& dt)
{
	this->checkForQuit();
}

void EnterNameState::update(const float& dt)
{
	while (this->window->pollEvent(this->nameEvent))
	{
		if (this->nameEvent.type == sf::Event::TextEntered)
		{
			if (this->nameEvent.text.unicode < 128)
			{
				std::cout << "Text entered: " << (this->nameEvent.text.unicode) << std::endl;
				if (this->nameEvent.text.unicode == static_cast<sf::Uint32>(8) && this->input.getSize() > 0)
				{
					this->input.erase(this->input.getSize() - 1);
					this->nameString.erase(this->nameString.size() - 1);
					this->deleteWordSound.play();
				}
				else
				{
					if (this->input.getSize() < 8 && this->nameEvent.text.unicode != 13)
					{
						if (this->nameEvent.text.unicode >= 97 && this->nameEvent.text.unicode <= 122)
						{
							this->nameEvent.text.unicode -= 32;
							this->enterWordSound.play();
						}
						this->input += this->nameEvent.text.unicode;
						this->nameString += this->nameEvent.text.unicode;
					}
				}

			}
		}
	}
	this->updateMousePosition();
	this->updateInput(dt);
	this->updateButtons();

	for (auto* enemy : this->enemies)
	{
		enemy->update(this->player, dt);
	}

	this->text.setString(this->input);
	this->text.setOrigin(this->text.getGlobalBounds().width / 2.f, 0.f);
}

void EnterNameState::renderButtons(sf::RenderTarget* target)
{
	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}
}

void EnterNameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);
	this->renderButtons(target);

	for (auto* enemy : this->enemies)
	{
		enemy->render(target);
	}

	target->draw(this->nameEnter);
	//target->draw(this->textHolder);
	target->draw(this->text);
	
}
