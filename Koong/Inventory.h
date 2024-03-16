#pragma once
#include "SpriteGo.h"
#include "TextGo.h"

class PlayerBody;

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
	std::vector<SpriteGo> invenLists;
	std::vector<SpriteGo> invenIconList;
	std::vector<SpriteGo> invenNumList;

	std::vector<int> invenSaveList;

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

	int coilPrice = 100;
	int bronzePrice = 300;
	int silverPrice = 500;
	int goldPrice = 1000;

	int money = 0;

	bool cap1 = 0;
	bool cap2 = 0;
	bool cap3 = 0;
	bool cap4 = 0;
	bool cap5 = 0;

	bool drill1 = 0;
	bool drill2 = 0;
	bool drill3 = 0;
	bool drill4 = 0;
	bool drill5 = 0;

	bool shoe1 = 0;
	bool shoe2 = 0;
	bool shoe3 = 0;
	bool shoe4 = 0;
	bool shoe5 = 0;

protected:

	PlayerBody* player;

	//인벤토리
	SpriteGo inventory;

	float invenPosX = 0.f;
	sf::Vector2f invenClose = { -300.f, 40.f };
	sf::Vector2f invenOpen = { -10.f, 40.f };

	int invenlimit = 3;

	SpriteGo invenName;
	SpriteGo moneyMenu;

	SpriteGo getOut;
	SpriteGo getOutLight;

	SpriteGo invenKoong;

	SpriteGo invenHead;
	SpriteGo invenDrill;
	SpriteGo invenFeet;

	SpriteGo invenEquipHead;
	SpriteGo invenEquipDrill;
	SpriteGo invenEquipFeet;


	sf::Vector2i invenCount = { 6, 6 };
	sf::Vector2f invenSize = { 34, 34 };



	std::vector<sf::Texture*> moneyTexture;


	sf::Sprite moneyUnit;
	sf::Sprite moneyTens;
	sf::Sprite moneyHundreds;
	sf::Sprite moneyThousands;
	sf::Sprite moneyTenThousands;
	sf::Sprite moneyHunThousands;

	SpriteGo textBack;
	TextGo energyText;
	TextGo airText;
	TextGo digPowerText;
	TextGo boosterText;
	TextGo armorText;

	sf::Font fontK = RES_MGR_FONT.Get("fonts/NanumSquareRoundEB.ttf");

	std::wstring hpWstring;
	std::wstring hpMaxWstring;
	std::wstring airWstring;
	std::wstring airMaxWstring;
	std::wstring drillWstring;
	std::wstring boosterWstring;
	std::wstring armorWstring;

	size_t decimalPos;

public:
	Inventory(const std::string& name = "");
	~Inventory() = default;

	void SetPlayerInfo();

	void SetInvenItem(InvenState state, bool Get);
	void SetInvenOre(InvenState state);
	void SetInvenMoney(int money, int state);

	void LoadInventory(const std::string& filename); //세이브파일 로드

	void OpenInven();

	void SellAll();

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

};

