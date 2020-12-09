#include "stdafx.h"
#include "GameplayState.h"

void GameplayState::initKeybinds()
{
	std::ifstream ifs("config/gamestate_keybinds.ini");

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

void GameplayState::initPlatform()
{
	this->direction.x = 0.f;
	this->direction.y = 0.f;
}

void GameplayState::initVariables()
{
	this->score = 0;
	this->changeColor = 255;

	this->enemyCount = 0;
	this->enemyMax = 20;
	this->spawnRange = sf::Vector2f(1000.f, 1000.f);
	
}

void GameplayState::initBackground()
{
	if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/MapBig.png"))
		std::cout << "ERROR::GAME::Could not load MAPBIG.PNG!" << "\n";
	this->background.setTexture(this->backgroundTexture);
}

void GameplayState::initMusic()
{
}

void GameplayState::initSoundEffects()
{
}

void GameplayState::initTexture()
{
	this->textures["FIREBALL"] = new sf::Texture;
	this->textures["FIREBALL"]->loadFromFile("Resources/Images/Sprites/Bullet/smallFireball.png");
	this->textures["SLIME"] = new sf::Texture;
	this->textures["SLIME"]->loadFromFile("Resources/Images/Sprites/Enemy/slime.png");
}

void GameplayState::initPlayer()
{
	//random player spawn postion
	this->player->setPosition(static_cast<float>(rand() % 2360) + 100.f, static_cast<float>(rand() % 2360) + 100.f);
}

void GameplayState::initItem()
{

}

void GameplayState::initView()
{
	this->view->setSize(this->window->getSize().x, this->window->getSize().y);
	this->view->setCenter(this->player->getPosition());
}

void GameplayState::initGUI()
{
}

GameplayState::GameplayState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, sf::View* view, Player* player)
	: State(window, supportedKeys, states, view, player)
{
	
	this->initTexture();
	this->initVariables();
	this->initPlayer();
	this->initMusic();
	this->initSoundEffects();
	this->initPlatform();
	this->initKeybinds();
	this->initBackground();
	this->initItem();
	this->initView();
	this->initGUI();
}

GameplayState::~GameplayState()
{
	for (auto& i : this->textures)
	{
		delete i.second;
	}

	for (auto* bullet : this->bullets)
	{
		delete bullet;
	}
	//delete Enemies
	for (auto* enemy : this->enemies)
	{
		delete enemy;
	}
}

void GameplayState::endState()
{
	std::cout << "Ending Game State!" << "\n";
}

void GameplayState::spawnEnemies()
{
	//ENEMY SPAWN RANDOM!
	sf::Vector2f enemyPos;
	enemyPos.x = rand() % static_cast<int>(this->background.getGlobalBounds().width - 200) + 100;
	enemyPos.y = rand() % static_cast<int>(this->background.getGlobalBounds().height - 200) + 100;

		//CHECK DISTANCE BETWEEN PLAYER AND ENEMY
	if (abs(this->player->getPosition().x - enemyPos.x) > this->spawnRange.x || abs(this->player->getPosition().y - enemyPos.y) > this->spawnRange.y)
	{
		if (this->enemyCount < this->enemyMax)
		{
			this->enemies.push_back(new Enemy(this->textures["SLIME"], "T_SLIME",
				enemyPos.x,
				enemyPos.y));
			this->enemyCount++;
		}
	}
	
}

void GameplayState::updateView(const float& dt)
{
	//Normal Condition to Set player at Middle of the screen
	this->view->setCenter(this->player->getPosition());

	//Check all border Condition to stop setCenter at playerPosition
	if (this->background.getGlobalBounds().width >= this->view->getSize().x)
	{
		if (this->view->getCenter().x - this->view->getSize().x / 2.f < 0.f)
		{
			this->view->setCenter(0.f + this->view->getSize().x / 2.f, this->view->getCenter().y);
		}
		else if (this->view->getCenter().x + this->view->getSize().x / 2.f > this->background.getGlobalBounds().width)
		{
			this->view->setCenter(this->background.getGlobalBounds().width - this->view->getSize().x / 2.f, this->view->getCenter().y);
		}
	}
	if (this->background.getGlobalBounds().height >= this->view->getSize().y)
	{
		if (this->view->getCenter().y - this->view->getSize().y / 2.f < 0.f)
		{
			this->view->setCenter(this->view->getCenter().x, 0.f + this->view->getSize().y / 2.f);
		}
		else if (this->view->getCenter().y + this->view->getSize().y / 2.f > this->background.getGlobalBounds().height)
		{
			this->view->setCenter(this->view->getCenter().x, this->background.getGlobalBounds().height - this->view->getSize().y / 2.f);
		}
	}
}

void GameplayState::updateInput(const float& dt)
{
	this->checkForQuit();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (this->shootTimer.getElapsedTime().asSeconds() >= this->player->getShootCD())
		{
			this->bullets.push_back(new Bullet(this->textures["FIREBALL"], 
				this->player->getPosition().x + (this->player->getGlobalBounds().width / 2.f),
				this->player->getPosition().y + (this->player->getGlobalBounds().height / 2.f), 
				0.f, -1.f, 5.f));
			this->shootTimer.restart();
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (this->shootTimer.getElapsedTime().asSeconds() >= this->player->getShootCD())
		{
			this->bullets.push_back(new Bullet(this->textures["FIREBALL"],
				this->player->getPosition().x + (this->player->getGlobalBounds().width / 2.f),
				this->player->getPosition().y + (this->player->getGlobalBounds().height / 2.f),
				0.f, 1.f, 5.f));
			this->shootTimer.restart();
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (this->shootTimer.getElapsedTime().asSeconds() >= this->player->getShootCD())
		{
			this->bullets.push_back(new Bullet(this->textures["FIREBALL"],
				this->player->getPosition().x + (this->player->getGlobalBounds().width / 2.f),
				this->player->getPosition().y + (this->player->getGlobalBounds().height / 2.f),
				-1.f, 0.f, 5.f));
			this->shootTimer.restart();
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (this->shootTimer.getElapsedTime().asSeconds() >= this->player->getShootCD())
		{
			this->bullets.push_back(new Bullet(this->textures["FIREBALL"],
				this->player->getPosition().x + (this->player->getGlobalBounds().width / 2.f),
				this->player->getPosition().y + (this->player->getGlobalBounds().height / 2.f),
				1.f,0.f, 5.f));
			this->shootTimer.restart();
		}
	}
}

void GameplayState::updatePlayer(const float& dt)
{
	this->player->update(dt);
}

void GameplayState::updateEnemy(const float& dt)
{
	int temp = 0;
	for (auto* enemy : this->enemies)
	{
		enemy->update(this->player, dt);
		if (enemy->getHp() <= 0)
		{
			if (enemy->getIsDeath())
			{
				delete this->enemies.at(temp);
				this->enemies.erase(this->enemies.begin() + temp);
				temp--;
				this->enemyCount--;
			}
		}
		temp++;
	}
}

void GameplayState::updateCollision(const float& dt)
{
	//Check collistion between player & Map Border
	if (this->player->getPosition().x < 0)
	{
		this->player->setPosition(0, this->player->getPosition().y);
	}
	if (this->player->getPosition().x + this->player->getGlobalBounds().width > this->background.getGlobalBounds().width)
	{
		this->player->setPosition(this->background.getGlobalBounds().width - this->player->getGlobalBounds().width, this->player->getPosition().y);
	}
	if (this->player->getPosition().y < 0)
	{
		this->player->setPosition(this->player->getPosition().x, 0.f);
	}
	if (this->player->getPosition().y + this->player->getGlobalBounds().width > this->background.getGlobalBounds().height)
	{
		this->player->setPosition(this->player->getPosition().x, this->background.getGlobalBounds().height - this->player->getGlobalBounds().height);
	}

	for (auto* enemy : this->enemies)
	{
		if (this->player->getHitbox().intersects(enemy->getHitbox()) && enemy->getHp() > 0)
		{
			this->player->takeDmg(1);
			if (enemy->getHp() <= 0)
			{
				this->player->addScore(enemy->getPoint());
			}
			
		}
	}
	//DEBUG PLAYER POSITION
	//std::cout << this->player->getPosition().x << " " << this->player->getPosition().y << "\n";
	
}

void GameplayState::updateItemsCollision(const float& dt)
{

}

void GameplayState::updateBullet(const float& dt)
{

	this->aimDir = sf::Vector2f(this->mousePosView.x - (this->player->getPosition().x + (this->player->getGlobalBounds().width / 2.f)), this->mousePosView.y - (this->player->getPosition().y + (this->player->getGlobalBounds().height / 2.f)));
	this->aimDirNorm = this->aimDir / sqrt(pow(this->aimDir.x, 2) + pow(this->aimDir.y, 2));

	//DEBUG
	//std::cout << this->mousePosView.x << " " << this->mousePosView.y << " "  << this->aimDir.x << " " << this->aimDir.y << " X = " << this->aimDirNorm.x << " Y = " << this->aimDirNorm.y << "\n";

	int counter = 0;
	for (auto* bullet : this->bullets)
	{
		bullet->update();

		//DELETE BULLET AT RIGHT 
		if (bullet->getBounds().left + bullet->getBounds().width > this->view->getCenter().x + this->window->getSize().x / 2.f + 100.f)
		{
			//delete bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
			std::cout << this->bullets.size() << " RIGHT" << "\n";
		}
		//DELETE BULLET AT LEFT 
		else if (bullet->getBounds().left < this->view->getCenter().x - this->window->getSize().x / 2.f - 100.f)
		{
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
			std::cout << this->bullets.size() << " LEFT" << "\n";
		}
		//DELETE BULLET AT BOTTOM 
		else if (bullet->getBounds().top + bullet->getBounds().height > this->view->getCenter().y + (this->window->getSize().y / 2.f) + 100.f)
		{
			//delete bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
			std::cout << this->bullets.size() << " BOTTOM" << "\n";
		}
		//DELETE BULLET AT TOP 
		else if (bullet->getBounds().top < this->view->getCenter().y - (this->window->getSize().y / 2.f) - 100.f)
		{
			//delete bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
			std::cout << this->bullets.size() << " TOP" << "\n";
		}

		int temp = 0;
		//check if bullet hit the enemy(ies)
		for (auto* enemy : this->enemies)
		{
			if (bullet->getBounds().intersects(enemy->getGlobalBounds()) && enemy->getHp() > 0)
			{
				//std::cout << enemy->getHp() << std::endl;
				enemy->takeDmg(1);
				////if enemy's hp is 0
				if (enemy->getHp() == 0)
				{
					this->player->addScore(enemy->getPoint());
					//if (enemy->getIsDrop())
					//	this->items.push_back(new Item(this->textures["HEALTH"], "HEAL", enemy->getPosition().x, enemy->getPosition().y + enemy->getGlobalBounds().height - 40.f));
						if (enemy->getIsDeath())
						{
							delete this->enemies.at(temp);
							this->enemies.erase(this->enemies.begin() + temp);
							temp--;
						}
				}
				delete this->bullets.at(counter);
				this->bullets.erase(this->bullets.begin() + counter);
				--counter;
			}
			//temp++;
		}
		++counter;
	}
}

void GameplayState::updateGUI(const float& dt)
{
}

void GameplayState::update(const float& dt)
{
	this->updateMousePosition();
	this->spawnEnemies();
	
	this->window->setView(*this->view);
	this->updateInput(dt);
	this->updateCollision(dt);
	this->updateItemsCollision(dt);
	this->updateBullet(dt);
	this->updatePlayer(dt);

	this->updateEnemy(dt);

	this->updateView(dt);
	this->updateGUI(dt);

	
}

void GameplayState::renderPlayer()
{
	this->player->render(this->window);
}

void GameplayState::renderGUI()
{
}

void GameplayState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	this->window->draw(this->background);	//Render Background

	for (auto* bullet : this->bullets)
	{
		bullet->render(this->window);
	}
	for (auto* enemy : this->enemies)
	{
		enemy->render(this->window);
	}

	this->renderPlayer();					//Render Player
}
