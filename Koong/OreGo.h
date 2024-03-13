#pragma once
#include "SpriteGo.h"

class PlayerBody;

class OreGo :
    public SpriteGo
{

public:
    enum class Types
    {
        Coil,
        Bronze,
        Silver,
        Gold,
    };

protected:
    Types type;

    std::string coilTexture = "graphics/FSADIGBOY19-24.png";

public:
    PlayerBody* player;

    OreGo(const std::string& name = "");
    ~OreGo() = default;

    void SetOre(sf::Vector2f pos, int ore);

    void Init() override;
    void Reset() override;
    void Update(float dt) override;

};

