#include "stdafx.h"
#include "Player.h"

//Initialize Functions
void Player::initVariables()
{
	this->sprite = new sf::Sprite;
	this->animationState = P_IDLE;
	this->maxHp = 10.f;
	this->hp = maxHp;
	this->shootCD = 0.4f;
	this->name = "";
	
}

void Player::initTexture()
{
	if (!this->textureSheet.loadFromFile("Resources/Images/Sprites/Player/Full_Movement.png"))
		std::cout << "ERROR::PLAYER::Could not load the player sheet!" << "\n";
}

void Player::initSprite()
{
	this->sprite->setTexture(this->textureSheet);
}

void Player::initAnimationComponent()
{
	this->creatAnimationComponent();
}

void Player::initSoundEffects()
{
	if (!this->takeDmgsfx.loadFromFile("Resources/Sounds/LTTP_Link_Hurt.wav"))
		std::cout << "ERROR::PLAYER::COULD NOT LOAD FROM FILE PLAYER_TAKE_DMG" << std::endl;
	this->takeDmgSound.setBuffer(this->takeDmgsfx);
	this->takeDmgSound.setVolume(50.f);
}

//Constructors / Destructors
Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initSoundEffects();
	this->initAnimationComponent();

	this->createHitbox(30.f,15.f,66.f,90.f);
	this->animationComponent->addAnimation("IDLE", 11.f, 0, 4 , 5, 4, 126, 126);
	this->animationComponent->addAnimation("WALK_LEFT", 11.f, 0, 1 , 5, 1, 126, 126);
	this->animationComponent->addAnimation("WALK_RIGHT", 11.f, 0, 3 , 5, 3, 126, 126);
	this->animationComponent->addAnimation("WALK_UP", 11.f, 0, 0 , 5, 0, 126, 126);
	this->animationComponent->addAnimation("WALK_DOWN", 11.f, 0, 2 , 5, 2, 126, 126);
}

Player::~Player()
{
	delete this->animationComponent;
	delete this->hitbox;
}

//Accessors

const sf::Vector2f Player::getPosition() const
{
	return this->sprite->getPosition();
}

const sf::FloatRect Player::getGlobalBounds() const
{
	return this->sprite->getGlobalBounds();
}

sf::Sprite& Player::getSprite()
{
	return *this->sprite;
}

const sf::FloatRect Player::getHitbox() const
{
	return sf::FloatRect(this->hitbox->getGlobalBounds());
}

short Player::getAnimationState()
{
	return this->animationState;
}
int Player::getHp()
{
	return this->hp;
}

const int& Player::getMaxHp() const
{
	return this->maxHp;
}

const float& Player::getShootCD() const
{
	return this->shootCD;
}

const bool& Player::getBonusState() const
{
	return this->BonusState;
}

const int& Player::getScore() const
{
	return this->score;
}

std::string Player::getName()
{
	return this->name;
}


//Modifiers
void Player::setPosition(const float x, const float y)
{
	this->sprite->setPosition(x, y);
}

void Player::takeDmg(int dmg)
{
	this->sprite->setColor(sf::Color(255, 0, 0, 127));
	this->takeDmgSound.play();
	this->hp -= dmg;
	this->takeDmgTimer.restart();
}

void Player::heal(int x)
{
	this->hp += x;
}

void Player::reduceShootCD()
{
	this->shootCD = 0.2f;
	//this->BonusState = true;
	this->shootCDTimer.restart();
}

void Player::addScore(int x)
{
	this->score += x;
}

void Player::setName(std::string name)
{
	this->name.assign(name);
}

void Player::creatAnimationComponent()
{
	this->animationComponent = new AnimationComponent(*this->sprite, this->textureSheet);
}

void Player::createHitbox(float offset_x, float offset_y, float width, float height)
{
	this->hitbox = new Hitbox(*this->sprite, offset_x, offset_y, width, height);
}
//Functions

void Player::move(const float& dt, const float dir_x, const float dir_y)
{
}

void Player::resetToNormal(const float& dt)
{
	if (this->takeDmgTimer.getElapsedTime().asSeconds() >= 0.3f)
	{
		this->sprite->setColor(sf::Color(255, 255, 255, 255));
	}
}

void Player::updateMovement(const float& dt)
{
	this->animationState = P_IDLE;
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) //LEFT
	{
		
		this->sprite->move(-2.f, 0.f);
		this->animationState = P_MOVING_LEFT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) //RIGHT
	{
		
		this->sprite->move(2.f, 0.f);
		this->animationState = P_MOVING_RIGHT;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) //UP
	{
		
		this->sprite->move( 0.f, -2.f); // NOT USING ACC
		this->animationState = P_MOVING_UP;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) //DOWN
	{
		
		this->sprite->move(0.f, 2.f);
		this->animationState = P_MOVING_DOWN;
	}
}

void Player::updateAnimation(const float& dt)
{
	if (this->animationState == P_IDLE)
	{
		this->animationComponent->play("IDLE", dt);
	}
	if (this->animationState == P_MOVING_RIGHT)
	{
		this->animationComponent->play("WALK_RIGHT", dt);
	}
	if (this->animationState == P_MOVING_LEFT)
	{
		this->animationComponent->play("WALK_LEFT", dt);
	}
	if (this->animationState == P_MOVING_UP)
	{
		this->animationComponent->play("WALK_UP", dt);
	}
	if (this->animationState == P_MOVING_DOWN)
	{
		this->animationComponent->play("WALK_DOWN", dt);
	}
}

Collider Player::getCollider()
{
	return Collider(this->hitbox->getHitbox());
}

void Player::update(const float& dt)
{
	this->updateMovement(dt);	//Update Position of player	//-
	this->updateAnimation(dt);	//Movement Animation
	this->hitbox->update();		//Update hitbox
	this->resetToNormal(dt);

	//std::cout << this->sprite.getPosition().x << " " << this->sprite.getPosition().y << std::endl;
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(*this->sprite);

	//this->hitbox->render(*target);
}
