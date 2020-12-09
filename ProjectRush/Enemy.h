#pragma once

#include "stdafx.h"
#include "Bullet.h"
#include "Collider.h"
#include "Collision.h"
#include "Player.h"
#include "AnimationComponent.h"

enum ENEMY_ANIMATION_STATE { SLIME_IDLE = 0, SLIME_MOVING_LEFT, SLIME_MOVING_RIGHT, SLIME_MOVING_UP, SLIME_MOVING_DOWN, };

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

	//Modifiers
	void takeDmg(int dmg);
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

