#include "GameObject.h"
#include "SpriteGo.h"
#include "TextGo.h"

class Animator;
class PlayerBody;
class TileMap;
class Inventory;
class Shop;

class UiHud : public GameObject
{

public:

	int healKitPrice = 1000;
	int airCapPrice = 500;
	int airCapSuperPrice = 2000;
	int bombPrice = 100;
	int nuclearPrice = 300;
	int dynamitePrice = 1000;

	int cap1Price = 5000;
	int cap2Price = 10000;
	int cap3Price = 20000;
	int cap4Price = 50000;
	int cap5Price = 100000;

	int drill1Price = 5000;
	int drill2Price = 10000;
	int drill3Price = 20000;
	int drill4Price = 50000;
	int drill5Price = 100000;

	int shoe1Price = 5000;
	int shoe2Price = 10000;
	int shoe3Price = 20000;
	int shoe4Price = 50000;
	int shoe5Price = 100000;

protected:

	Animator animator;
	sf::Sprite bill;

	bool billOn = false;

	sf::Vector2f referenceResolution = { 1280, 960 };
	sf::Vector2f resolution = referenceResolution;

	Inventory* inventory = nullptr;
	Shop* shop = nullptr;

	TextGo textMessage;

	SpriteGo hud;

	SpriteGo energy;
	SpriteGo hpBar;

	SpriteGo airText;
	SpriteGo airBarColor;
	SpriteGo airBarFrame1;
	SpriteGo airBarFrame2;

	//퀵메뉴
	SpriteGo quickMenu;
	SpriteGo quickItem1;
	SpriteGo quickItem2;
	SpriteGo quickItem3;
	SpriteGo quickItem4;

	float fadeTime = 0.5f;

	sf::Vector2f hpBarSize = { 1.f, 1.f };

	PlayerBody* player;

	sf::String airBarBlue = "graphics/ui/FSADIGBOY19-375.png";
	sf::String airBarYellow = "graphics/ui/FSADIGBOY19-374.png";
	sf::String airBarRed = "graphics/ui/FSADIGBOY19-373.png";

	sf::Font fontK = RES_MGR_FONT.Get("fonts/NanumSquareRoundEB.ttf");

	sf::RectangleShape pointer;

	//상점메뉴
	std::vector<SpriteGo> shopList;
	std::vector<SpriteGo> shopIconList;
	std::vector<TextGo> shopNameList;
	std::vector<TextGo> shopPriceList;

	SpriteGo phd;
	SpriteGo phdGlass;

	SpriteGo shopHud;
	SpriteGo shopBack;
	SpriteGo buttonSell;

	sf::Vector2f shopOpen = { 260.f, 42.f };
	sf::Vector2f shopClose = { 640.f, 42.f };

	sf::Vector2i shopCount = { 3, 7 };
	sf::Vector2f shopSize = { 98, 37 };

	int menuStringSize = 11;

public:
	UiHud(const std::string& name = "");
	~UiHud() override = default;

	void SetResolution(const sf::Vector2f resolution);
	void SetScore(int s);

	void SetMessage(const std::string& msg);
	void SetMessageActive(bool active);

	void SetHpBar(int hp, int max);
	void SetAirBar(int air, int maxair);

	void OpenShop();
	void BuyItem(int num);


	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};