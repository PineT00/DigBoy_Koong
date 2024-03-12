#include "SpriteGo.h"
#include "Animator.h"

class TileMap;

class PlayerBody : public SpriteGo
{
protected:
	Animator animator;

	float speed = 300.f;
	float booster = 500.f;

	float hpMax = 100.f;
	float airMax = 100.f;
	float hp = hpMax;
	float air = airMax;

	bool isDrill = false;
	float digTime = 0.f;
	float digTimer = 0.1f;

	//인벤토리
	int healKitNum = 0;
	int airCapNum = 0;
	int airCapMaxNum = 0;
	int bombNum = 0;
	int dynamite = 0;

	int coilNum = 0;
	int silverNum = 0;
	int goldNum = 0;
	int money = 0;

	TileMap* tileMap;

	sf::RectangleShape leftCheck;
	sf::RectangleShape rightCheck;
	sf::RectangleShape topCheck;
	sf::RectangleShape buttomCheck;

	sf::Vector2f vCheckerSize = { 10.f, 5.f };
	sf::Vector2f hCheckerSize = { 5.f, 5.f };

	SpriteGo drill;
	float drillDown = 0;

	SpriteGo* coil = new SpriteGo;

public:
	float gravity = 700.f;

	sf::Vector2f velocity;

	bool isGrounded = true;

	sf::Vector2i count;
	sf::Vector2f size;

	bool GetIsDrill() { return isDrill; }

	sf::FloatRect GetSpriteGlobalBound() { return sprite.getGlobalBounds(); }

	float GetMaxHP() { return hpMax; }
	float GetMaxAir() { return airMax; }
	float GetHP() { return hp; }
	float GetAir() { return air; }

	PlayerBody(const std::string& name = "");
	~PlayerBody();

	void OnItem();
	void SellAll();

	void UseItem(int num);

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;


};

