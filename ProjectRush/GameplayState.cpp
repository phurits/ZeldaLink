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

void GameplayState::initFont()
{
	if (!this->font.loadFromFile("Fonts/triforce.ttf"))
	{
		std::cout << "ERROR::MAINMENUSTATE::COULD NOT LOAD FONT!" << std::endl;
	}
}

void GameplayState::initVariables()
{
	this->score = 0;
	this->changeColor = 255;

	this->spawnRange = sf::Vector2f(800.f, 800.f);

	//Enemy Kill Total
	this->enemyKillCount = 0;

	//init Blue Slime Amount;
	this->blueAmount = 0;
	this->blueMax = 15;

	//init Pink Slime Amount;
	this->pinkAmount = 0;
	this->pinkMax = 10;

	//init Yellow Slime Amount;
	this->yellowAmount = 0;
	this->yellowMax = 5;

	//GEMS
	this->greenGemAmount = 0;
	this->greenGemMax = 30;
	this->greenGemPoint = 50;

	this->blueGemAmount = 0;
	this->blueGemMax = 20;
	this->blueGemPoint = 100;

	this->redGemAmount = 0;
	this->redGemMax = 10;
	this->redGemPoint = 200;

	this->numberItems = 3;
	

}

void GameplayState::initBackground()
{
	if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/MapBig.png"))
		std::cout << "ERROR::GAME::Could not load MAPBIG.PNG!" << "\n";
	this->background.setTexture(this->backgroundTexture);
}

void GameplayState::initMusic()
{
	this->bg_music.openFromFile("Resources/Sounds/GameState_Music.ogg");
	this->bg_music.setLoop(true);
	this->bg_music.setVolume(20.f);
	this->bg_music.play();
}

void GameplayState::initSoundEffects()
{
	if (!this->pShoot.loadFromFile("Resources/Sounds/LTTP_Cane_Magic.wav"))
		std::cout << "ERROR::PLAYER::COULD NOT LOAD pSHOOT" << std::endl;
	this->pShootSound.setBuffer(pShoot);
	this->pShootSound.setVolume(20.f);

	if (!this->eDeath.loadFromFile("Resources/Sounds/LTTP_Enemy_Kill.wav"))
		std::cout << "ERROR::PLAYER::COULD NOT LOAD eDEATH" << std::endl;
	this->eDeathSound.setBuffer(eDeath);
	this->eDeathSound.setVolume(20.f);

	if (!this->eHit.loadFromFile("Resources/Sounds/LTTP_Enemy_Hit.wav"))
		std::cout << "ERROR::PLAYER::COULD NOT LOAD eHIT" << std::endl;
	this->eHitSound.setBuffer(eHit);
	this->eHitSound.setVolume(20.f);

	if(!this->pDeath.loadFromFile("Resources/Sounds/LTTP_Link_Fall.wav"))
		std::cout << "ERROR::PLAYER::COULD NOT LOAD pDEATH" << std::endl;
	this->pDeathSound.setBuffer(pDeath);
	this->pDeathSound.setVolume(30.f);

	if (!this->pickUpItem.loadFromFile("Resources/Sounds/LTTP_Rupee1.wav"))
		std::cout << "ERROR::PLAYER::COULD NOT LOAD pickItem" << std::endl;
	this->pickUpItemSound.setBuffer(pickUpItem);
	this->pickUpItemSound.setVolume(20.f);

	if (!this->coin.loadFromFile("Resources/Sounds/coin.ogg"))
		std::cout << "ERROR::PLAYER::COULD NOT LOAD pick Coin" << std::endl;
	this->coinSound.setBuffer(coin);
	this->coinSound.setVolume(20.f);


}

void GameplayState::initTexture()
{
	//BULLET
	this->textures["FIREBALL"] = new sf::Texture;
	this->textures["FIREBALL"]->loadFromFile("Resources/Images/Sprites/Bullet/smallFireball.png");
	//ENEMY
	this->textures["BLUE_SLIME"] = new sf::Texture;
	this->textures["BLUE_SLIME"]->loadFromFile("Resources/Images/Sprites/Enemy/blue_slime.png");
	this->textures["PINK_SLIME"] = new sf::Texture;
	this->textures["PINK_SLIME"]->loadFromFile("Resources/Images/Sprites/Enemy/pink_slime.png");
	this->textures["YELLOW_SLIME"] = new sf::Texture;
	this->textures["YELLOW_SLIME"]->loadFromFile("Resources/Images/Sprites/Enemy/yellow_slime.png");
	//HEATH
	this->textures["HEART"] = new sf::Texture;
	this->textures["HEART"]->loadFromFile("Resources/Images/Items/Heart.png");
	//ITEM DROP
	this->textures["RED_POTION"] = new sf::Texture;
	this->textures["RED_POTION"]->loadFromFile("Resources/Images/Items/red_potion.png");
	this->textures["PURPLE_POTION"] = new sf::Texture;
	this->textures["PURPLE_POTION"]->loadFromFile("Resources/Images/Items/purple_potion.png");
	this->textures["YELLOW_POTION"] = new sf::Texture;
	this->textures["YELLOW_POTION"]->loadFromFile("Resources/Images/Items/yellow_potion.png");
	//COIN
	this->textures["GREEN_GEM"] = new sf::Texture;
	this->textures["GREEN_GEM"]->loadFromFile("Resources/Images/Items/green_rupee.png");
	this->textures["BLUE_GEM"] = new sf::Texture;
	this->textures["BLUE_GEM"]->loadFromFile("Resources/Images/Items/blue_rupee.png");
	this->textures["RED_GEM"] = new sf::Texture;
	this->textures["RED_GEM"]->loadFromFile("Resources/Images/Items/red_rupee.png");
}

void GameplayState::initPlayer()
{
	//random player spawn postion
	this->player->setPosition(static_cast<float>(rand() % 2800) + 100.f, static_cast<float>(rand() % 2800) + 100.f);
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
	//HEALTHBAR
	this->hpBar.setPosition(10.f, 35.f);
	this->hpBar.setSize(sf::Vector2f(20.f * this->player->getHp(), 30.f));
	this->hpBar.setFillColor(sf::Color::Red);
		//health holder box
	this->hpBarOutline.setPosition(10.f, 35.f);
	this->hpBarOutline.setSize(sf::Vector2f(20.f * this->player->getMaxHp(), 30.f));
	this->hpBarOutline.setOutlineThickness(1.f);
	this->hpBarOutline.setOutlineColor(sf::Color::Black);
	this->hpBarOutline.setFillColor(sf::Color(0,0,0,255));
		//health font
	this->health.setFont(this->font);
	this->health.setPosition((20.f * this->player->getMaxHp()) / 2, 40.f);
	this->health.setString(std::to_string(this->player->getHp()) + " / " + std::to_string(this->player->getMaxHp()));
	this->health.setCharacterSize(20.f);
	this->health.setFillColor(sf::Color::White);
	this->health.setOutlineThickness(1.f);

	//SCORE
	this->scoreText.setFont(this->font);
	this->scoreText.setLetterSpacing(2.f);
	this->scoreText.setString(std::to_string(this->player->getScore()));
	this->scoreText.setCharacterSize(30);
	this->scoreText.setFillColor(sf::Color::Yellow);
	this->scoreText.setOutlineThickness(2.f);
	this->scoreText.setOutlineColor(sf::Color::Black);
	this->scoreText.setPosition(this->view->getCenter().x + this->window->getSize().x / 2.f - this->scoreText.getGlobalBounds().width - 20.f, this->view->getCenter().y - (this->window->getSize().y) / 2.f + 10.f);
}

GameplayState::GameplayState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, sf::View* view, Player* player)
	: State(window, supportedKeys, states, view, player)
{
	
	this->initView();
	this->initTexture();
	this->initFont();
	this->initVariables();
	this->initPlayer();
	this->initMusic();
	this->initSoundEffects();
	this->initKeybinds();
	this->initBackground();
	this->initItem();
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
	for (auto* item : this->items)
	{
		delete item;
	}
	for (auto& i : this->soundEffects)
	{
		delete i.second;
	}
}

sf::Text GameplayState::getScoreText()
{
	return this->scoreText;
}

void GameplayState::endState()
{
	std::cout << "Ending Game State!" << "\n";
}

void GameplayState::spawnEnemies()
{
	//ENEMY SPAWN RANDOM!
	enemyPos.x = rand() % static_cast<int>(this->background.getGlobalBounds().width - 200) + 100;
	enemyPos.y = rand() % static_cast<int>(this->background.getGlobalBounds().height - 200) + 100;

	int randomItem = rand();

		//CHECK DISTANCE BETWEEN PLAYER AND ENEMY
	if (abs(this->player->getPosition().x - enemyPos.x) > this->spawnRange.x || abs(this->player->getPosition().y - enemyPos.y) > this->spawnRange.y)
	{
		//Coins
		if (this->greenGemAmount < this->greenGemMax)
		{
			this->items.push_back(new Item(this->textures["GREEN_GEM"], "GREEN_GEM", enemyPos.x, enemyPos.y));
			this->greenGemAmount++;
		}
		else if (this->blueGemAmount < this->blueGemMax)
		{
			this->items.push_back(new Item(this->textures["BLUE_GEM"], "BLUE_GEM", enemyPos.x, enemyPos.y));
			this->blueGemAmount++;
		}
		else if (this->redGemAmount < this->redGemMax)
		{
			this->items.push_back(new Item(this->textures["RED_GEM"], "RED_GEM", enemyPos.x, enemyPos.y));
			this->redGemAmount++;
		}
		//ENEMIES
		if (this->blueAmount < this->blueMax)
		{
			this->enemies.push_back(new Enemy(this->textures["BLUE_SLIME"], "BLUE_SLIME", enemyPos.x, enemyPos.y));
			this->blueAmount++;
		}
		else if (this->pinkAmount < this->pinkMax)
		{
			this->enemies.push_back(new Enemy(this->textures["PINK_SLIME"], "PINK_SLIME", enemyPos.x, enemyPos.y));
			this->pinkAmount++;
		}
		else if (this->yellowAmount < this->yellowMax)
		{
			this->enemies.push_back(new Enemy(this->textures["YELLOW_SLIME"], "YELLOW_SLIME", enemyPos.x, enemyPos.y));
			this->yellowAmount++;
		}
		//ITEM DROP EVERY 20 ENEMY DIE
		
		if (this->enemyKillCount == 20)
		{
			if (randomItem % this->numberItems == 0)
			{
				this->items.push_back(new Item(this->textures["PURPLE_POTION"], "FIRE_RATE", enemyPos.x, enemyPos.y));
			}
			else if(randomItem % this->numberItems == 1)
			{
				this->items.push_back(new Item(this->textures["RED_POTION"], "DMG_BOOST", enemyPos.x, enemyPos.y));
			}
			else if (randomItem % this->numberItems == 2)
			{
				this->items.push_back(new Item(this->textures["YELLOW_POTION"], "SPEED_BOOST", enemyPos.x, enemyPos.y));
			}
			this->enemyKillCount = 0;
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
		if (this->shootTimer.getElapsedTime().asSeconds() >= this->player->getFirerate())
		{
			this->pShootSound.play();
			this->bullets.push_back(new Bullet(this->textures["FIREBALL"], 
				(this->player->getPosition().x + (this->player->getGlobalBounds().width / 3.f)) + rand() % static_cast<int>(this->player->getGlobalBounds().width / 3.f),
				this->player->getPosition().y + (this->player->getGlobalBounds().height / 2.f), 
				0.f, -1.f, 5.f));
			this->shootTimer.restart();
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (this->shootTimer.getElapsedTime().asSeconds() >= this->player->getFirerate())
		{
			this->pShootSound.play();
			this->bullets.push_back(new Bullet(this->textures["FIREBALL"],
				(this->player->getPosition().x + (this->player->getGlobalBounds().width / 3.f)) + rand() % static_cast<int>(this->player->getGlobalBounds().width / 3.f),
				this->player->getPosition().y + (this->player->getGlobalBounds().height / 2.f),
				0.f, 1.f, 5.f));
			this->shootTimer.restart();
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (this->shootTimer.getElapsedTime().asSeconds() >= this->player->getFirerate())
		{
			this->pShootSound.play();
			this->bullets.push_back(new Bullet(this->textures["FIREBALL"],
				this->player->getPosition().x + (this->player->getGlobalBounds().width / 2.f),
				(this->player->getPosition().y + (this->player->getGlobalBounds().height / 3.f)) + rand() % static_cast<int>(this->player->getGlobalBounds().height / 3.f), 
				-1.f, 0.f, 5.f));
			this->shootTimer.restart();
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (this->shootTimer.getElapsedTime().asSeconds() >= this->player->getFirerate())
		{
			this->pShootSound.play();
			this->bullets.push_back(new Bullet(this->textures["FIREBALL"],
				this->player->getPosition().x + (this->player->getGlobalBounds().width / 2.f),
				(this->player->getPosition().y + (this->player->getGlobalBounds().height / 3.f)) + rand() % static_cast<int>(this->player->getGlobalBounds().height / 3.f),
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
				if (enemy->getType() == "BLUE_SLIME")
					this->blueAmount--;
				else if (enemy->getType() == "PINK_SLIME")
					this->pinkAmount--;
				else if (enemy->getType() == "YELLOW_SLIME")
					this->yellowAmount--;
				this->enemyKillCount++;
				delete this->enemies.at(temp);
				this->enemies.erase(this->enemies.begin() + temp);
				temp--;
				
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

	//Check collistion btw player & enemy
	for (auto* enemy : this->enemies)
	{
		if (this->player->getHitbox().intersects(enemy->getHitbox()) && enemy->getHp() > 0)
		{
			this->player->takeDmg(1);
			if (enemy->getHp() <= 0)
			{
				this->player->addScore(enemy->getPoint());
			}
			enemy->takeDmg(999);
		}
	}

	//DEBUG PLAYER POSITION
	//std::cout << this->player->getPosition().x << " " << this->player->getPosition().y << "\n";
	
}

void GameplayState::updateItemsCollision(const float& dt)
{
	unsigned itemCounter = 0;
	for (auto* item : this->items)
	{
		//HEART
		if (item->getGlobalBounds().intersects(this->player->getHitbox()) && this->player->getHp() < this->player->getMaxHp() && item->getType() == "HEART")
		{
			delete this->items.at(itemCounter);
			this->player->heal(1);
			this->items.erase(this->items.begin() + itemCounter);
			this->pickUpItemSound.play();
			--itemCounter;
		}
		//RED POTIONS = DMG BOOST
		if (item->getGlobalBounds().intersects(this->player->getHitbox()) && item->getType() == "DMG_BOOST")
		{
			delete this->items.at(itemCounter);
			this->player->boostDMG();
			this->items.erase(this->items.begin() + itemCounter);
			this->pickUpItemSound.play();
			--itemCounter;
		}
		//BLUE POTION = FIRERATE BOOST
		if (item->getGlobalBounds().intersects(this->player->getHitbox()) && item->getType() == "FIRE_RATE" )
		{
			delete this->items.at(itemCounter);
			this->player->reduceFirerateCDR();
			this->items.erase(this->items.begin() + itemCounter);
			this->pickUpItemSound.play();
			--itemCounter;
		}
		//YELLOW POTION = SPEED BOOST
		if (item->getGlobalBounds().intersects(this->player->getHitbox()) && item->getType() == "SPEED_BOOST")
		{
			delete this->items.at(itemCounter);
			this->player->speedBoost();
			this->items.erase(this->items.begin() + itemCounter);
			this->pickUpItemSound.play();
			--itemCounter;
		}
		//GEM
		if (item->getGlobalBounds().intersects(this->player->getHitbox()) && item->getType() == "GREEN_GEM")
		{
			delete this->items.at(itemCounter);
			this->player->addScore(this->greenGemPoint);
			this->items.erase(this->items.begin() + itemCounter);
			this->coinSound.play();
			--itemCounter;
		}
		if (item->getGlobalBounds().intersects(this->player->getHitbox()) && item->getType() == "BLUE_GEM")
		{
			delete this->items.at(itemCounter);
			this->player->addScore(this->blueGemPoint);
			this->items.erase(this->items.begin() + itemCounter);
			this->coinSound.play();
			--itemCounter;
		}
		if (item->getGlobalBounds().intersects(this->player->getHitbox()) && item->getType() == "RED_GEM")
		{
			delete this->items.at(itemCounter);
			this->player->addScore(this->redGemPoint);
			this->items.erase(this->items.begin() + itemCounter);
			this->coinSound.play();
			--itemCounter;
		}
		++itemCounter;
	}
}

void GameplayState::updateBullet(const float& dt)
{
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
			if (bullet->getBounds().intersects(enemy->getHitbox()) && enemy->getHp() > 0)
			{
				this->eHitSound.play();
				//std::cout << enemy->getHp() << std::endl;
				enemy->takeDmg(this->player->getPlayerDmg());
				////if enemy's hp is 0
				if (enemy->getHp() <= 0)
				{
					this->eDeathSound.play();
					this->player->addScore(enemy->getPoint());
					if (enemy->getIsDrop())
						this->items.push_back(new Item(this->textures["HEART"], "HEART", enemy->getPosition().x, enemy->getPosition().y));
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
			temp++;
		}
		++counter;
	}
}

void GameplayState::updateGUI(const float& dt)
{
	this->hpBarOutline.setPosition(this->view->getCenter().x - (this->window->getSize().x / 2.f) + 10.f, this->view->getCenter().y - (this->window->getSize().y) / 2.f + 35.f);
	this->hpBar.setPosition(this->view->getCenter().x - (this->window->getSize().x / 2.f) + 10.f, this->view->getCenter().y - (this->window->getSize().y / 2.f) + 35.f);
	this->hpBar.setSize(sf::Vector2f(this->player->getHp() * 20.f, 30.f)); //HP CURRENT BAR

	this->health.setString(std::to_string(this->player->getHp()) + " / " + std::to_string(this->player->getMaxHp()));
	this->health.setPosition((this->view->getCenter().x - (this->window->getSize().x / 2.f)) + 20.f, this->view->getCenter().y - (this->window->getSize().y / 2.f) + 35.f);

	this->scoreText.setString(std::to_string(this->player->getScore()));
	this->scoreText.setPosition(this->view->getCenter().x + this->window->getSize().x / 2.f - this->scoreText.getGlobalBounds().width - 20.f, this->view->getCenter().y - (this->window->getSize().y) / 2.f + 10.f);

}

void GameplayState::updateToNextState(const float& dt)
{
	
	if (this->player->getHp() <= 0)
	{
		this->player->setPosition(0, 0);
		this->pDeathSound.play();
		this->bg_music.pause();
		if (!this->states->empty())
			this->states->pop();
		this->states->push(new GameOverState(this->window, this->supportedKeys, this->states, this->view, this->player));
	}
}

void GameplayState::cheat(const float& dt)
{
	//GAME OVER
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal) && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
	{
		this->player->takeDmg(999);
	}
	//SPAWN PURPLE_POTION
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		this->items.push_back(new Item(this->textures["PURPLE_POTION"], "FIRE_RATE", enemyPos.x, enemyPos.y));
	}
	//SPAWN RED_POTION
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		this->items.push_back(new Item(this->textures["RED_POTION"], "DMG_BOOST", enemyPos.x, enemyPos.y));
	}
	//SPAWN YELLOW_POTION
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		this->items.push_back(new Item(this->textures["YELLOW_POTION"], "SPEED_BOOST", enemyPos.x, enemyPos.y));
	}
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

	this->cheat(dt);

	this->updateToNextState(dt);

	

	//std::cout << this->view->getCenter().x << " " << this->view->getCenter().y << "\n";
}

void GameplayState::renderPlayer()
{
	this->player->render(this->window);
}

void GameplayState::renderGUI()
{
	this->window->draw(this->hpBarOutline);
	this->window->draw(this->hpBar);
	this->window->draw(this->health);

	this->window->draw(this->scoreText);
}

void GameplayState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	this->window->draw(this->background);	//Render Background

	for (auto* item : this->items)
	{
		item->render(this->window);
	}
	for (auto* bullet : this->bullets)
	{
		bullet->render(this->window);
	}
	for (auto* enemy : this->enemies)
	{
		enemy->render(this->window);
	}


	this->renderPlayer();					//Render Player

	this->renderGUI();
}
