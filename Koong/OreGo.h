#pragma once
#include "SpriteGo.h"
class OreGo :
    public SpriteGo
{

protected:

public:
    SpriteGo* coil = new SpriteGo;
    SpriteGo* coper = new SpriteGo;
    SpriteGo* silver = new SpriteGo;
    SpriteGo* gold = new SpriteGo;

    OreGo(const std::string& name = "");
    ~OreGo() = default;

    void ShowOre();

	void SetTexture(const std::string& textureId);
	void Reset() override;
	void Draw(sf::RenderWindow& window) override;

};

