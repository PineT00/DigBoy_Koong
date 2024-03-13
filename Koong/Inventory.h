#pragma once
#include "SpriteGo.h"
class Inventory :
    public SpriteGo
{

protected:
	//인벤토리
	SpriteGo inventory;
	float invenPosX = 0.f;
	sf::Vector2f invenClose = { -300.f, 40.f };
	sf::Vector2f invenOpen = { -10.f, 40.f };

	//SpriteGo invenSprite;
	//SpriteGo invenEmpty;
	//SpriteGo invenBlocked;

	SpriteGo invenName;
	SpriteGo moneyMenu;

	SpriteGo invenKoong;
	SpriteGo invenEquipHead;
	SpriteGo invenEquipDrill;
	SpriteGo invenEquipFeet;


	sf::Vector2i invenCount = { 6, 6 };
	sf::Vector2f invenSize = { 34, 34 };
	std::vector<SpriteGo> invenLists;

public:
	Inventory(const std::string& name = "");
	~Inventory() = default;

	void SetInventory(sf::Vector2i& count, sf::Vector2f& size);

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;


};

