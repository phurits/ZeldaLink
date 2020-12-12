#pragma once

#include "stdafx.h"
#include "Collider.h"
#include "AnimationComponent.h"
#include "Hitbox.h"

enum PLAYER_ANIMATION_STATE { P_IDLE = 0, P_MOVING_LEFT, P_MOVING_RIGHT, P_MOVING_UP, P_MOVING_DOWN};

class Player
{
private:
	sf::Sprite* sprite;
	sf::Texture textureSheet;
	sf::Clock animationTimer;
	std::string name;

	//Status
	int maxHp;
	int hp;
	sf::Clock takeDmgTimer;
	float takeDmgTime;
	int score;

	//Event stuff (when pick up items)
	float firerate;
	bool firerateState;
	sf::Clock firerateCDRTimer;

	int playerDmg;
	bool DmgBoostState;
	sf::Clock dmgBoostTimer;

	//Hitbox
	Hitbox* hitbox;

	//Animation
	AnimationComponent* animationComponent;
	short animationState;
	sf::Clock shootCooldown;
	bool isShooting;

	//sound effects
	
	sf::SoundBuffer takeDmgsfx;
	sf::Sound takeDmgSound;

	//Initializations
	void initVariables();
	void initTexture();
	void initSprite();
	void initAnimationComponent();
	void initSoundEffects();

public:
	//Constructors / Destructors
	Player();
	virtual ~Player();

	//Accessors
	const sf::Vector2f getPosition() const;
	const sf::FloatRect getGlobalBounds() const;
	sf::Sprite& getSprite();
	const sf::FloatRect getHitbox() const;
	short getAnimationState();
	int getHp();
	const int& getMaxHp() const;
	const int& getScore() const;
	Collider getCollider();
	std::string getName();

	//FIRERATE REDUCTION
	const float& getFirerate() const;
	const bool& getFirerateState() const;
	void reduceFirerateCDR();

	const int& getPlayerDmg() const;
	const bool& getDmgBoostState() const;
	void boostDMG();

	//Modifiers
	void setPosition(const float x, const float y);
	void takeDmg(int dmg);
	void heal(int x);
	void addScore(int x);
	void setName(std::string name);

	//Components
	void creatAnimationComponent();
	void createHitbox(float offset_x, float offset_y, float width, float height);

	//Functions
	void move(const float& dt, const float dir_x, const float dir_y);
	void resetToNormal(const float& dt);
	void updateMovement(const float& dt);
	void updateAnimation(const float& dt);
	void update(const float& dt);
	//Render
	void render(sf::RenderTarget* target);
};

