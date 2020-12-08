#include "stdafx.h"
#include "EnterNameState.h"

//Initializer
void EnterNameState::initVariables()
{
	this->player = new Player();
	this->player->setPosition(20.f, 20.f);

	this->nameEnter.setFont(this->font);
	this->nameEnter.setCharacterSize(50.f);
	//this->nameEnter.setLetterSpacing(1.6f);
	this->nameEnter.setOutlineThickness(1.5f);
	this->nameEnter.setOutlineColor(sf::Color::Black);
	this->nameEnter.setPosition(630.f, 200.f);
	this->nameEnter.setString("ENTER NAME");

	this->textHolder.setFillColor(sf::Color(255,255,255,100));
	this->textHolder.setSize(sf::Vector2f(200.f, 50.f));
	this->textHolder.setOutlineThickness(1.f);
	this->textHolder.setOutlineColor(sf::Color::Black);
	this->textHolder.setPosition(sf::Vector2f(700, 300.f));

	this->text.setFillColor(sf::Color::Black);
}

void EnterNameState::initMusic()
{
	//this->bg_music.openFromFile("Resources/Sound Effects/intro.ogg");
	//this->bg_music.setLoop(true);
	//this->bg_music.setVolume(10.f);
	//this->bg_music.play();
}

void EnterNameState::initBackground()
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x)
		, static_cast<float>(this->window->getSize().y)));

	if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/wallpaper.jpg"))
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
	this->text.setCharacterSize(25.f);
	this->text.setPosition(sf::Vector2f(this->view->getCenter().x - 100, 310.f));
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
	this->buttons["GAME_STATE"] = new Button(700 ,400, 200, 50, &this->font, "START", 40,
		sf::Color(255, 255, 255, 0), sf::Color(255, 255, 255, 0), sf::Color(255, 255, 255, 0));
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

}

EnterNameState::~EnterNameState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
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
				}
				else
				{
					if (this->input.getSize() < 13 && this->nameEvent.text.unicode != 13)
					{
						if (this->nameEvent.text.unicode >= 97 && this->nameEvent.text.unicode <= 122)
						{
							this->nameEvent.text.unicode -= 32;
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


	this->text.setString(this->input);
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

	target->draw(this->nameEnter);
	target->draw(this->textHolder);
	target->draw(this->text);
}
