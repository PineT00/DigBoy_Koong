#pragma once
#include "SpriteGo.h"

class PlayerBody;

class Shop :
    public SpriteGo

{
protected:
	Animator animator1;
	sf::Sprite propeller;

	Animator animator2;
	sf::Sprite portal;

	PlayerBody* player;
	SpriteGo shop;
	SpriteGo NPC;


public:
	Shop(const std::string& name = "");
	~Shop() = default;

	void ShopSetPosition(sf::Vector2f pos);
	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;


};

