#pragma once
#include "SpriteGo.h"
#include "Player.h"

class Zombie :
    public SpriteGo
{

public:
    enum class Types
    {
        Bloater,
        Chase,
        Crawler,
    };
    static const int TotalTypes = 3;
    static Zombie* Create(Types zombieType);

protected:
    sf::Vector2f direction = { 0.f, 0.f };
    sf::Vector2f look = { 1.0f, 0.f };

    Types type;
    int maxHp;
    float speed;
    int hp;

    Player* player;

public:

    Zombie(const std::string& name = "");
    ~Zombie() override = default;

    void Init() override;
    void Release() override;
    void Reset() override;

    void Update(float dt) override;
    void Draw(sf::RenderWindow& window) override;

};

