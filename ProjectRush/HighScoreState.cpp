#include "stdafx.h"
#include "HighScoreState.h"

void HighScoreState::initVariables()
{
	
}

void HighScoreState::initMusic()
{
	this->bg_music.openFromFile("Resources/Sounds/Highscore_Music.ogg");
	this->bg_music.setLoop(true);
	this->bg_music.setVolume(20.f);
	this->bg_music.play();
}

void HighScoreState::initBackground()
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x),
		static_cast<float>(this->window->getSize().y)));
	if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/leaderboardBG.png"))
	{
		std::cout << "ERROR::MAIN_MENU_STATE::FAILED TO LOAD BACKGROUND TO TEXTURE" << std::endl;
	}
	this->background.setTexture(&this->backgroundTexture);
	this->background.setOrigin(this->window->getSize().x / 2, this->window->getSize().y / 2);
	this->background.setPosition(this->view->getCenter());
	//this->background.setPosition(this->view->getCenter().x - this->window->getSize().x / 2.f, this->view->getCenter().y - this->window->getSize().y / 2.f);
}

void HighScoreState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/triforce.ttf"))
	{
		std::cout << "ERROR::MAINMENUSTATE::COULD NOT LOAD FONT!" << std::endl;
	}
}

void HighScoreState::initText()
{
	this->scoreBoardText.setFont(this->font);
	this->scoreBoardText.setCharacterSize(40.f);
	this->scoreBoardText.setFillColor(sf::Color::White);
	this->scoreBoardText.setString("\\=SCOREBOARD=/");
	this->scoreBoardText.setPosition(this->background.getPosition().x - 160, this->background.getPosition().y - 416);

	for (int i = 0; i < 5; i++)
	{
		this->playerName[i].setFont(this->font);
		this->playerName[i].setCharacterSize(30.f);
		this->playerName[i].setFillColor(sf::Color::White);
		this->playerName[i].setPosition(this->background.getPosition().x - 180, this->background.getPosition().y - 316 + (100 * i));
		this->playerScore[i].setFont(this->font);
		this->playerScore[i].setCharacterSize(30.f);
		this->playerScore[i].setFillColor(sf::Color::White);
		this->playerScore[i].setPosition(this->background.getPosition().x +120, this->background.getPosition().y - 316 + (100 * i));
	}
}

void HighScoreState::initKeybinds()
{
	std::ifstream ifs("config/highscorestate_keybinds.ini");

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

void HighScoreState::initHighScore()
{
	this->fp = fopen("./highscore.txt", "r");
	for (int i = 0; i < 5; i++)
	{
		fscanf(this->fp, "%s", &this->temp);
		this->name[i] = this->temp;
		this->playerName[i].setString(this->name[i]);
		fscanf(this->fp, "%d", &this->score[i]);
		this->playerScore[i].setString(std::to_string(this->score[i]));
		this->userScore.push_back(std::make_pair(this->score[i], this->name[i]));
	}

}

void HighScoreState::initButtons()
{
	this->buttons["MAIN_MENU"] = new Button(this->background.getPosition().x - 100, this->background.getPosition().y + 200, 220, 50, &this->font, "MAINMENU", 30,
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}

HighScoreState::HighScoreState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, sf::View* view, Player* player)
	:State(window, supportedKeys, states, view, player)
{
	this->initMusic();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initHighScore();
	this->initText();
	this->initButtons();
}

HighScoreState::~HighScoreState()
{
	auto i = this->buttons.begin();
	for (i = this->buttons.begin(); i != this->buttons.end(); ++i)
	{
		delete i->second;
	}
}

void HighScoreState::endState()
{
	std::cout << "Ending Score Board State" << std::endl;
}

void HighScoreState::updateButtons()
{
	/*Update all the buttons and handle the functionality*/
	for (auto& i : this->buttons)
	{
		i.second->update(this->mousePosView);
	}

	//BACK TO MAIN MENU
	if (this->buttons["MAIN_MENU"]->isPressed())
	{
		//this->bg_music.pause();
		this->bg_music.stop();
		this->endState();
		this->states->push(new MainMenuState(this->window, this->supportedKeys, this->states, this->view, this->player));
	}
}

void HighScoreState::updateInput(const float& dt)
{
	this->checkForQuit();
}

void HighScoreState::update(const float& dt)
{
	this->updateMousePosition();
	this->updateInput(dt);
	this->updateButtons();
}

void HighScoreState::renderButtons(sf::RenderTarget* target)
{
	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}
}

void HighScoreState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderButtons(target);

	target->draw(this->scoreBoardText);

	for (int i = 0; i < 5; i++)
	{
		target->draw(this->playerName[i]);
		target->draw(this->playerScore[i]);
	}
}
