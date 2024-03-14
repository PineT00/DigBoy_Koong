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

		HealKit,
		Bomb,
		Dynamate,

		Coil,
		Bronze,
		Silver,
		Gold,
	};

	InvenState state;

	std::vector<InvenState> stateList;

	//인벤토리
	int healKitNum = 0;
	int airCapNum = 0;
	int airCapSuperNum = 0;
	int bombNum = 0;
	int dynamite = 0;

	int coilNum = 0;
	int bronzeNum = 0;
	int silverNum = 0;
	int goldNum = 0;

	int money = 0;

	//int unitNumM = money % 10;
	//int tensNumM = (money / 10) % 10;
	//int hundredsNumM = (money / 100) % 10;
	//int thousandsNumM = (money / 1000) % 10;
	//int tenThousandsNumM = (money / 10000) % 10;

protected:

	//인벤토리
	SpriteGo inventory;

	float invenPosX = 0.f;
	sf::Vector2f invenClose = { -300.f, 40.f };
	sf::Vector2f invenOpen = { -10.f, 40.f };

	int invenlimit = 3;

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

	std::vector<sf::Texture*> moneyTexture;


	//어차피 매번 new 해줘야 할텐데 미리 정의하는 의미가 있나
	//SpriteGo itemNum1;
	//SpriteGo itemNum2;
	//SpriteGo itemNum3;
	//SpriteGo itemNum4;
	//SpriteGo itemNum5;

	sf::Sprite moneyUnit;
	sf::Sprite moneyTens;
	sf::Sprite moneyHundreds;
	sf::Sprite moneyThousands;
	sf::Sprite moneyTenThousands;
	sf::Sprite moneyHunThousands;

	SpriteGo invenCoil;
	SpriteGo invenBronze;
	SpriteGo invenSilver;
	SpriteGo invenGold;


public:
	Inventory(const std::string& name = "");
	~Inventory() = default;

	void SetInvenItem();
	void SetInvenOre();
	void SetInvenMoney();
	void SetInventory();

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

};

