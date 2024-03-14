#include "GameObject.h"
#include "SpriteGo.h"
#include "TextGo.h"

class PlayerBody;
class TileMap;
class Inventory;

class UiHud : public GameObject
{
protected:
	sf::Vector2f referenceResolution = { 1280, 960 };
	sf::Vector2f resolution = referenceResolution;

	Inventory* inventory = nullptr;

	TextGo textMessage;

	SpriteGo hud;

	SpriteGo energy;
	SpriteGo hpBar;

	SpriteGo airText;
	SpriteGo airBarColor;
	SpriteGo airBarFrame1;
	SpriteGo airBarFrame2;

	//Äü¸Þ´º
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

public:
	UiHud(const std::string& name = "");
	~UiHud() override = default;

	void SetResolution(const sf::Vector2f resolution);
	void SetScore(int s);

	void SetMessage(const std::string& msg);
	void SetMessageActive(bool active);

	void SetHpBar(int hp, int max);
	void SetAirBar(int air, int maxair);

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};