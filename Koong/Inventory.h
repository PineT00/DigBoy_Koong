#pragma once
#include "SpriteGo.h"

class Inventory :
    public SpriteGo
{
public:
	enum InvenState
	{
		Blocked = -1,
		Empty,
		Full,

		HealKit,
		AirCap,
		AirCapSuper,
		Bomb,
		Nuclear,
		Dynamite,

		Coil,
		Bronze,
		Silver,
		Gold,
	};

	InvenState state;

	std::vector<InvenState> stateList;
	std::vector<SpriteGo> invenIconList;
	std::vector<SpriteGo> invenNumList;

	//인벤토리
	int healKitNum = 0;
	int airCapNum = 0;
	int airCapSuperNum = 0;
	int bombNum = 0;
	int nuclearNum = 0;
	int dynamiteNum = 0;

	int coilNum = 0;
	int bronzeNum = 0;
	int silverNum = 0;
	int goldNum = 0;

	int invenCoilNum = 0;
	int invenBronzeNum = 0;
	int invenSilverNum = 0;
	int invenGoldNum = 0;

	int money = 0;

protected:

	//인벤토리
	SpriteGo inventory;

	float invenPosX = 0.f;
	sf::Vector2f invenClose = { -300.f, 40.f };
	sf::Vector2f invenOpen = { -10.f, 40.f };

	int invenlimit = 3;

	SpriteGo invenName;
	SpriteGo moneyMenu;

	SpriteGo invenKoong;
	SpriteGo invenEquipHead;
	SpriteGo invenEquipDrill;
	SpriteGo invenEquipFeet;

	sf::Vector2i invenCount = { 6, 6 };
	sf::Vector2f invenSize = { 34, 34 };

	std::vector<SpriteGo> invenLists;


	std::vector<sf::Texture*> moneyTexture;


	sf::Sprite moneyUnit;
	sf::Sprite moneyTens;
	sf::Sprite moneyHundreds;
	sf::Sprite moneyThousands;
	sf::Sprite moneyTenThousands;
	sf::Sprite moneyHunThousands;


public:
	Inventory(const std::string& name = "");
	~Inventory() = default;

	void SetInvenItem(InvenState state, bool Get);
	void SetInvenOre(InvenState state);
	void SetInvenMoney();

	//void SetInventory(); //아이템 획득시마다 호출

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

};

