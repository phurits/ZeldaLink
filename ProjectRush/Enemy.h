#pragma once

#include "stdafx.h"
#include "Bullet.h"
#include "Collider.h"
#include "Collision.h"
#include "Player.h"
#include "AnimationComponent.h"

class Enemy
{
private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::RectangleShape body;
	std::string type;
	int hp;
	int hpMax;
	int damage;
	int points;
	float dropChance;
	bool isDrop;
	bool isDeath;

	float speed;
	short xAxis;
	short yAxis;

	sf::Vector2f enemyVision;

	//Animations
	AnimationComponent* animationComponent;
	short animationState;

	//Hitbox
	Hitbox* hitbox;

	sf::Clock takeDmgTimer;

	sf::Vector2f initPos;

	//Sounds
	sf::SoundBuffer takeDmgsfx;
	sf::Sound takeDmgSound;

	void initVariables();
	void initSoundEffects();
	void initSprite();
	void initAnimationComponent();

public:
	//Constructure & Destructure
	Enemy(sf::Texture* texture, std::string type, float pos_x, float pos_y);
	~Enemy();

	//Accessors
	short getAnimationState();
	const sf::FloatRect getHitbox() const;
	int getHp();
	int& getPoint();
	sf::Vector2f getPosition();
	sf::FloatRect getGlobalBounds();
	bool getIsDrop();
	bool getIsDeath();
	std::string getType();
	int getMaxHp();
	sf::Vector2f getCenter();
	float getSpeed();

	const bool& getConfusedState() const;
	void enemyConfused();

	//Modifiers
	void takeDmg(int dmg);
	void setSpeed(float speed);
	void setPosition(float pos_x, float pos_y);

	//Components
	void createAnimationComponent();

	//Functions
	void deathAnimation(const float& dt);
	void randomItem();
	Collider getCollider();
	void updateMovement(Player* player, const float& dt);
	void updateHitbox();
	void updateAnimation(const float& dt);
	void updateColor();
	void update(Player* player, const float& dt);
	void render(sf::RenderTarget* target);
};

