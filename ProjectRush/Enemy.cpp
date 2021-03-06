#include "stdafx.h"
#include "Enemy.h"

void Enemy::initVariables()
{
	this->hpMax = 3;
	this->hp = hpMax;
	this->damage = 1;
	this->points = 5;
	this->dropChance = 20;
	this->isDeath = false;

	this->enemyVision = sf::Vector2f(800, 800);

	this->speed = 1.f;
	this->xAxis = 0;
	this->yAxis = 0;
}

void Enemy::initSoundEffects()
{
	if (!this->takeDmgsfx.loadFromFile("Resources/Sounds/LTTP_Enemy_Hit.wav"))
	{
		std::cout << "ERROR::ENEMY::COULD NOT LOAD SOUND EFFECTS ENEMY TAKE DMG" << std::endl;
	}
	this->takeDmgSound.setBuffer(this->takeDmgsfx);
	this->takeDmgSound.setVolume(30.f);
}

void Enemy::initSprite()
{
	this->sprite.setScale(1.f,1.f);
}

void Enemy::initAnimationComponent()
{
	this->createAnimationComponent();
}

Enemy::Enemy(sf::Texture* texture, std::string type, float pos_x, float pos_y)
	:type(type)
{
	this->sprite.setTexture(*texture);
	this->sprite.setPosition(pos_x, pos_y);
	this->texture = *texture;

	this->initPos.x = pos_x;
	this->initPos.y = pos_y;

	this->initVariables();
	this->initSprite();
	this->initSoundEffects();
	this->initAnimationComponent();
	this->randomItem();

	//Add animations
	if (this->type == "BLUE_SLIME")
	{
		this->enemyVision = sf::Vector2f(1000, 1000);
		this->sprite.setScale(1.5f, 1.5f);
		this->hitbox = new Hitbox(this->sprite, 5, 5, 44, 30);
		this->hpMax = 3;
		this->hp = hpMax;
		this->points = 300;
		this->animationComponent->addAnimation("IDLE", 10.f, 0, 0, 2, 0, 36, 27);
		this->animationComponent->addAnimation("MOVE_LEFT", 10.f, 0, 1, 2, 1, 36, 27);
		this->animationComponent->addAnimation("MOVE_RIGHT", 10.f, 0, 2, 2, 2, 36, 27);
		this->animationComponent->addAnimation("MOVE_UP", 10.f, 0, 3, 2, 3, 36, 27);
		this->animationComponent->addAnimation("MOVE_DOWN", 10.f, 0, 0, 2, 0, 36, 27);
	}
	if (this->type == "PINK_SLIME")
	{
		this->enemyVision = sf::Vector2f(1000, 1000);
		this->sprite.setScale(2.5f, 2.5f);
		this->hitbox = new Hitbox(this->sprite, 5, 5, 80, 57);
		this->hpMax = 5;
		this->hp = hpMax;
		this->points = 500;
		this->animationComponent->addAnimation("IDLE", 10.f, 0, 0, 2, 0, 36, 27);
		this->animationComponent->addAnimation("MOVE_LEFT", 10.f, 0, 1, 2, 1, 36, 27);
		this->animationComponent->addAnimation("MOVE_RIGHT", 10.f, 0, 2, 2, 2, 36, 27);
		this->animationComponent->addAnimation("MOVE_UP", 10.f, 0, 3, 2, 3, 36, 27);
		this->animationComponent->addAnimation("MOVE_DOWN", 10.f, 0, 0, 2, 0, 36, 27);
	}
	if (this->type == "YELLOW_SLIME")
	{
		this->enemyVision = sf::Vector2f(1380, 1380);
		this->sprite.setScale(1.f,1.f);
		this->hitbox = new Hitbox(this->sprite, 0, 0, 36, 27);
		this->hpMax = 1;
		this->hp = hpMax;
		this->points = 1000;
		this->animationComponent->addAnimation("IDLE", 10.f, 0, 0, 2, 0, 36, 27);
		this->animationComponent->addAnimation("MOVE_LEFT", 10.f, 0, 1, 2, 1, 36, 27);
		this->animationComponent->addAnimation("MOVE_RIGHT", 10.f, 0, 2, 2, 2, 36, 27);
		this->animationComponent->addAnimation("MOVE_UP", 10.f, 0, 3, 2, 3, 36, 27);
		this->animationComponent->addAnimation("MOVE_DOWN", 10.f, 0, 0, 2, 0, 36, 27);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (this->type == "ZELDA_U")
	{
		this->sprite.setScale(0.7, 0.7);
		this->hitbox = new Hitbox(this->sprite, 0, 0, 36, 27);
		this->animationComponent->addAnimation("WALK_UP", 11.f, 0, 0, 5, 0, 126, 126);
	}
	if (this->type == "ZELDA_D")
	{
		this->sprite.setScale(0.7, 0.7);
		this->hitbox = new Hitbox(this->sprite, 0, 0, 36, 27);
		this->animationComponent->addAnimation("WALK_DOWN", 11.f, 0, 2, 5, 2, 126, 126);
	}
	if (this->type == "ZELDA_L")
	{
		this->sprite.setScale(0.7, 0.7);
		this->hitbox = new Hitbox(this->sprite, 0, 0, 36, 27);
		this->animationComponent->addAnimation("WALK_LEFT", 11.f, 0, 1, 5, 1, 126, 126);
		
	}
	if (this->type == "ZELDA_R")
	{
		this->sprite.setScale(0.7, 0.7);
		this->hitbox = new Hitbox(this->sprite, 0, 0, 36, 27);
		this->animationComponent->addAnimation("WALK_RIGHT", 11.f, 0, 3, 5, 3, 126, 126);
	}
	if (this->type == "ENS_BSLIME")
	{
		this->sprite.setScale(3.5, 3.5);
		this->hitbox = new Hitbox(this->sprite, 0, 0, 36, 27);
		this->animationComponent->addAnimation("IDLE", 10.f, 0, 0, 2, 0, 36, 27);
	}
	if (this->type == "ENS_PSLIME")
	{
		this->sprite.setScale(3.5, 3.5);
		this->hitbox = new Hitbox(this->sprite, 0, 0, 36, 27);
		this->animationComponent->addAnimation("IDLE", 10.f, 0, 0, 2, 0, 36, 27);
	}
	if (this->type == "ENS_YSLIME")
	{
		this->sprite.setScale(3.5, 3.5);
		this->hitbox = new Hitbox(this->sprite, 0, 0, 36, 27);
		this->animationComponent->addAnimation("IDLE", 10.f, 0, 0, 2, 0, 36, 27);
	}
}

Enemy::~Enemy()
{
	
}

short Enemy::getAnimationState()
{
	return this->animationState;
}

const sf::FloatRect Enemy::getHitbox() const
{
	return sf::FloatRect(this->hitbox->getGlobalBounds());
}

//Accessors
int Enemy::getHp()
{
	return this->hp;
}

int& Enemy::getPoint()
{
	return this->points;
}

sf::Vector2f Enemy::getPosition()
{
	return this->sprite.getPosition();
}

sf::FloatRect Enemy::getGlobalBounds()
{
	return this->hitbox->getGlobalBounds();
}

bool Enemy::getIsDrop()
{
	return this->isDrop;
}

bool Enemy::getIsDeath()
{
	return this->isDeath;
}

std::string Enemy::getType()
{
	return this->type;
}

int Enemy::getMaxHp()
{
	return this->hpMax;
}

sf::Vector2f Enemy::getCenter()
{
	return sf::Vector2f(this->sprite.getGlobalBounds().left + (this->sprite.getGlobalBounds().width / 2), this->sprite.getGlobalBounds().top + (this->sprite.getGlobalBounds().height / 2));
}

float Enemy::getSpeed()
{
	return this->speed;
}

//Modifiers
void Enemy::takeDmg(int dmg)
{
	this->takeDmgSound.play();
	this->sprite.setColor(sf::Color(255, 0, 0, 127));
	this->hp -= dmg;
	this->takeDmgTimer.restart();
}

void Enemy::setSpeed(float speed)
{
	this->speed = speed;
}

void Enemy::setPosition(float pos_x, float pos_y)
{
	this->sprite.setPosition(pos_x, pos_y);
}


void Enemy::createAnimationComponent()
{
	this->animationComponent = new AnimationComponent(this->sprite, this->texture);
}

void Enemy::deathAnimation(const float& dt)
{
	if (this->hp <= 0 && !this->isDeath)
	{
		this->isDeath = true;
	}
}

void Enemy::randomItem()
{
	if (rand() % 100 <= this->dropChance)
	{
		this->isDrop = true;
	}
	else this->isDrop = false;
}

//Functions =================================================================================================================================================

Collider Enemy::getCollider()
{
	return Collider(this->body);
}

void Enemy::updateMovement(Player* player, const float& dt)
{

	if (this->type == "BLUE_SLIME" && !this->isDeath)
	{
		if (abs(player->getPosition().x - this->getCenter().x) < this->enemyVision.x && abs(player->getPosition().y - this->getCenter().y) < this->enemyVision.y)
		{
			this->speed = 1;
			if (this->getCenter().y - (player->getPosition().y + (player->getGlobalBounds().height / 2.f)) > 0.f)
			{
				this->sprite.move(0.f, -speed);
				this->xAxis = 0;
				this->yAxis = -1;
			}
			else if ((player->getPosition().y + (player->getGlobalBounds().height / 2.f)) - this->getCenter().y > 0.f)
			{
				this->sprite.move(0.f, speed);
				this->xAxis = 0;
				this->yAxis = 1;
			}
			if (this->getCenter().x - (player->getPosition().x + (player->getGlobalBounds().width / 2.f)) > 0.f)
			{
				this->sprite.move(-speed, 0.f);
				this->xAxis = -1;
				this->yAxis = 0;
			}
			else if ((player->getPosition().x + (player->getGlobalBounds().width / 2.f)) - this->getCenter().x > 0.f)
			{
				this->sprite.move(speed, 0.f);
				this->xAxis = 1;
				this->yAxis = 0;
			}
		}
		else
		{
			this->xAxis = 0;
			this->yAxis = 0;
		}
	}
	if (this->type == "PINK_SLIME" && !this->isDeath)
	{
		if (abs(player->getPosition().x - this->getCenter().x) < this->enemyVision.x && abs(player->getPosition().y - this->getCenter().y) < this->enemyVision.y)
		{
			this->speed = 0.5;
			if (this->getCenter().y - (player->getPosition().y + (player->getGlobalBounds().height / 2.f)) > 0.f)
			{
				this->sprite.move(0.f, -speed);
				this->xAxis = 0;
				this->yAxis = -1;
			}
			else if ((player->getPosition().y + (player->getGlobalBounds().height / 2.f)) - this->getCenter().y > 0.f)
			{
				this->sprite.move(0.f, speed);
				this->xAxis = 0;
				this->yAxis = 1;
			}
			if (this->getCenter().x - (player->getPosition().x + (player->getGlobalBounds().width / 2.f)) > 0.f)
			{
				this->sprite.move(-speed, 0.f);
				this->xAxis = -1;
				this->yAxis = 0;
			}
			else if ((player->getPosition().x + (player->getGlobalBounds().width / 2.f)) - this->getCenter().x > 0.f)
			{
				this->sprite.move(speed, 0.f);
				this->xAxis = 1;
				this->yAxis = 0;
			}
		}
		else
		{
			this->xAxis = 0;
			this->yAxis = 0;
		}
	}
	if (this->type == "YELLOW_SLIME" && !this->isDeath)
	{
		if (abs(player->getPosition().x - this->getCenter().x) < this->enemyVision.x && abs(player->getPosition().y - this->getCenter().y) < this->enemyVision.y)
		{
			this->speed = 1.5;
			if (this->getCenter().y - (player->getPosition().y + (player->getGlobalBounds().height / 2.f)) > 0.f)
			{
				this->sprite.move(0.f, -speed);
				this->xAxis = 0;
				this->yAxis = -1;
			}
			else if ((player->getPosition().y + (player->getGlobalBounds().height / 2.f)) - this->getCenter().y > 0.f)
			{
				this->sprite.move(0.f, speed);
				this->xAxis = 0;
				this->yAxis = 1;
			}
			if (this->getCenter().x - (player->getPosition().x + (player->getGlobalBounds().width / 2.f)) > 0.f)
			{
				this->sprite.move(-speed, 0.f);
				this->xAxis = -1;
				this->yAxis = 0;
			}
			else if ((player->getPosition().x + (player->getGlobalBounds().width / 2.f)) - this->getCenter().x > 0.f)
			{
				this->sprite.move(speed, 0.f);
				this->xAxis = 1;
				this->yAxis = 0;
			}
		}
		else
		{
			this->xAxis = 0;
			this->yAxis = 0;
		}
	}
	
}

void Enemy::updateHitbox()
{
	this->hitbox->update();

}

void Enemy::updateAnimation(const float& dt)
{
	if (this->type == "BLUE_SLIME")
	{
		if (this->xAxis == -1 && this->yAxis == 0)	//LEFT
		{
			this->animationComponent->play("MOVE_LEFT", dt);
		}
		else if (this->xAxis == 1 && this->yAxis == 0)	//RIGHT
		{
			this->animationComponent->play("MOVE_RIGHT", dt);
		}
		else if (this->xAxis == 0 && this->yAxis == -1)	//UP
		{
			this->animationComponent->play("MOVE_UP", dt);
		}
		else if (this->xAxis == 0 && this->yAxis == 1)	//DOWN
		{
			this->animationComponent->play("MOVE_DOWN", dt);
		}
		if (this->xAxis == 0 && this->yAxis == 0)
		{
			this->animationComponent->play("IDLE", dt);
		}
	}
	if (this->type == "PINK_SLIME")
	{
		if (this->xAxis == -1 && this->yAxis == 0)	//LEFT
		{
			this->animationComponent->play("MOVE_LEFT", dt);
		}
		else if (this->xAxis == 1 && this->yAxis == 0)	//RIGHT
		{
			this->animationComponent->play("MOVE_RIGHT", dt);
		}
		else if (this->xAxis == 0 && this->yAxis == -1)	//UP
		{
			this->animationComponent->play("MOVE_UP", dt);
		}
		else if (this->xAxis == 0 && this->yAxis == 1)	//DOWN
		{
			this->animationComponent->play("MOVE_DOWN", dt);
		}
		if (this->xAxis == 0 && this->yAxis == 0)
		{
			this->animationComponent->play("IDLE", dt);
		}
	}
	if (this->type == "YELLOW_SLIME")
	{
		if (this->xAxis == -1 && this->yAxis == 0)	//LEFT
		{
			this->animationComponent->play("MOVE_LEFT", dt);
		}
		else if (this->xAxis == 1 && this->yAxis == 0)	//RIGHT
		{
			this->animationComponent->play("MOVE_RIGHT", dt);
		}
		else if (this->xAxis == 0 && this->yAxis == -1)	//UP
		{
			this->animationComponent->play("MOVE_UP", dt);
		}
		else if (this->xAxis == 0 && this->yAxis == 1)	//DOWN
		{
			this->animationComponent->play("MOVE_DOWN", dt);
		}
		if (this->xAxis == 0 && this->yAxis == 0)
		{
			this->animationComponent->play("IDLE", dt);
		}
	}
	if (this->type == "ZELDA_U")
	{
		this->animationComponent->play("WALK_UP", dt, true);
	}
	if (this->type == "ZELDA_D")
	{
		this->animationComponent->play("WALK_DOWN", dt, true);
	}
	if (this->type == "ZELDA_L")
	{
		this->animationComponent->play("WALK_LEFT", dt, true);
	}
	if (this->type == "ZELDA_R")
	{
		this->animationComponent->play("WALK_RIGHT", dt,true);
	}
	if (this->type == "ENS_BSLIME")
	{
		this->animationComponent->play("IDLE", dt,true);
	}
	if (this->type == "ENS_PSLIME")
	{
		this->animationComponent->play("IDLE", dt, true);
	}
	if (this->type == "ENS_YSLIME")
	{
		this->animationComponent->play("IDLE", dt, true);
	}
}

void Enemy::updateColor()
{
	if (this->takeDmgTimer.getElapsedTime().asSeconds() >= 0.15f)
	{
		this->sprite.setColor(sf::Color(255, 255, 255, 255));
	}

}

//Functions
void Enemy::update(Player* player, const float& dt)
{
	this->updateMovement(player, dt);
	this->updateColor();
	this->updateAnimation(dt);
	this->deathAnimation(dt);
	this->updateHitbox();
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);

	//this->hitbox->render(*target);
}