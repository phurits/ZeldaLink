#pragma once
#include "Player.h"
#include "Bullet.h"
//#include "Enemy.h"
#include "Platform.h"
#include "MainMenuState.h"
//#include "GameOverState.h"
#include "Item.h"
//#include "BossFightState.h"
#include "State.h"

class GameplayState :
    public State
{
private:
    sf::Event gameEvent;

    //GUI
    sf::RectangleShape hpBarOutline;
    sf::RectangleShape hpBar;
    sf::RectangleShape BonusItemIcon;
    sf::Text playerName;
    int changeColor;
    sf::Font scoreFont;
    sf::Text scoreText;
    int score;

    //Background
    sf::Sprite background;
    sf::Texture backgroundTexture;

    //View
    sf::Vector2f viewPos;
    float currentCamera;
    bool moveCamera;
    float nextViewPos;

    //Enemy
    //std::vector<Enemy*> enemies;
   // sf::Vector2f enemyDirection;

    //Pos at mouse for bullet
    sf::Vector2f aimDir;
    sf::Vector2f aimDirNorm;

    //Bullets
    std::map<std::string, sf::Texture*> textures;
    std::vector<Bullet*> bullets;
    sf::Clock shootTimer;
    Bullet b1;

    //Platform
    std::vector<Platform*> platforms;
    sf::Vector2f direction;

    //Initialization
    void initKeybinds();
    void initPlatform();
    void initVariables();
    void initBackground();
    void initMusic();
    void initSoundEffects();
    void initTexture();
    void initPlayer();
    void initItem();
    void initView();
    void initGUI();

public:
    //Constructure & Destructure
    GameplayState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, sf::View* view, Player* player);
    virtual ~GameplayState();

    //Functions
    void endState();
    void spawnEnemies();

    //Update
    void updateView(const float& dt);
    void updateInput(const float& dt);
    void updatePlayer(const float& dt);
    void updateEnemy(const float& dt);
    void updateCollision(const float& dt);
    void updateItemsCollision(const float& dt);
    void updateBullet(const float& dt);
    void updateGUI(const float& dt);
    void update(const float& dt);

    //Render
    void renderPlayer();

    void renderGUI();
    void render(sf::RenderTarget* target = nullptr);
};

