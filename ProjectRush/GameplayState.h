#pragma once
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Platform.h"
#include "MainMenuState.h"
#include "Item.h"
#include "GameOverState.h"
#include "State.h"

class GameplayState :
    public State
{
private:
    sf::Event gameEvent;

    //Sound
    sf::Music bg_music;

    sf::SoundBuffer pShoot;
    sf::Sound pShootSound;
    sf::SoundBuffer eDeath;
    sf::Sound eDeathSound;
    sf::SoundBuffer eHit;
    sf::Sound eHitSound;
    sf::SoundBuffer pDeath;
    sf::Sound pDeathSound;
    sf::SoundBuffer coin;
    sf::Sound coinSound;
    

    //GUI
    sf::RectangleShape hpBarOutline;
    sf::RectangleShape hpBar;
    sf::RectangleShape BonusItemIcon;
    sf::Text playerName;
    std::string stHealth;
    sf::Text health;
    int changeColor;
    sf::Font font;
    sf::Text scoreText;
    int score;

    //Background
    sf::Sprite background;
    sf::Texture backgroundTexture;

    //Enemy
    std::vector<Enemy*> enemies;
    sf::Vector2f enemyDirection;
    sf::Vector2f spawnRange;
    sf::Vector2f enemyPos;

    int enemyKillCount;
    int blueAmount;
    int blueMax;
    int pinkAmount;
    int pinkMax;
    int yellowAmount;
    int yellowMax;

    //GEMS
    int greenGemAmount;
    int greenGemMax;
    int greenGemPoint;
    int blueGemAmount;
    int blueGemMax;
    int blueGemPoint;
    int redGemAmount;
    int redGemMax;
    int redGemPoint;
   
    //Bullets
    std::map<std::string, sf::Texture*> textures;
    std::vector<Bullet*> bullets;
    sf::Clock shootTimer;

    //Item
    int numberItems;
    std::vector<Item*> items;
    std::map<std::string, sf::SoundBuffer*> soundEffects;

    sf::SoundBuffer pickUpItem;
    sf::Sound pickUpItemSound;

    //Initialization
    void initKeybinds();
    void initFont();
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

    //Accessors
    sf::Text getScoreText();

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
    void updateToNextState(const float& dt);
    void cheat(const float& dt);
    void update(const float& dt);

    //Render
    void renderPlayer();

    void renderGUI();
    void render(sf::RenderTarget* target = nullptr);
};

