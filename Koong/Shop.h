#pragma once
#include "SpriteGo.h"
#include "TextGo.h"

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

	TextGo message;
	SpriteGo messageBubble;

	sf::Font fontK = RES_MGR_FONT.Get("fonts/NanumSquareRoundEB.ttf");

	float messageTime = 0.f;
	float messageTimer1 = 1.5f;
	float messageTimer2 = 3.0f;

public:
	Shop(const std::string& name = "");
	~Shop() = default;

	void ShowMessage(sf::Vector2f pos);

	void ShopSetPosition(sf::Vector2f pos);
	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;


};

