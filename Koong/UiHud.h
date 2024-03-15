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

	//���޴�
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

	//�����޴�
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

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};