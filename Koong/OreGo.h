#pragma once
#include "SpriteGo.h"

class PlayerBody;

class OreGo :
    public SpriteGo
{

protected:
    std::string coilTexture = "graphics/FSADIGBOY19-24.png";

    std::vector<int> oreLevel;

public:
    PlayerBody* player;

    OreGo(const std::string& name = "");
    ~OreGo() = default;

    void SetOre(sf::Vector2f pos);

    void Init() override;
    void Reset() override;
    void Update(float dt) override;

};

