#pragma once
#include "SpriteGo.h"

class TileMap;

class Dynamite :
    public SpriteGo
{
protected:
    TileMap* tileMap;

    Animator animator;

    float bombTime = 0.f;
    float bombTimer = 1.5f;

    bool explode = false;

    sf::Vector2i aim;
public:

    Dynamite(const std::string& name = "");
    ~Dynamite() = default;

    void SetDynamite(sf::Vector2i pos);

    void Init() override;
    void Reset() override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow& window) override;


};

