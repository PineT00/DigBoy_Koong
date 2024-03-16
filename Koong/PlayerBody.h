#include "SpriteGo.h"
#include "Animator.h"

class TileMap;
class Inventory;

class PlayerBody : public SpriteGo
{
protected:
	Animator animator;

	sf::Sprite head;
	Animator animatorHead;

	Inventory* inventory;

	float speed = 300.f;


	float hpMax = 100.f; 
	float airMax = 100.f; //에어 최대용량
	float hp = hpMax;
	float air = airMax;

	float booster = 300.f; //부스터파워

	float fallDmg = 30.f;
	float armorRate = 0.f; //방어력

	bool isDrill = false;
	float digTime = 0.f;
	float digTimer = 0.5f; 
	float drillPower = 5.f;  //드릴파워

	bool invincible = false;
	float invincTimer = 1.5f;
	float invincTime = 0.f;

	TileMap* tileMap;

	sf::RectangleShape leftCheck;
	sf::RectangleShape rightCheck;
	sf::RectangleShape topCheck;
	sf::RectangleShape buttomCheck;

	sf::Vector2f vCheckerSize = { 10.f, 5.f };
	sf::Vector2f hCheckerSize = { 5.f, 5.f };

	int playerCellX;
	int playerCellY;

	SpriteGo drill;
	float drillDown = 0;

	SpriteGo flame;

public:
	float gravity = 900.f;

	sf::Vector2f velocity;

	bool isGrounded = true;


	float tileMapLeftEnd = 0.f;
	float tileMapRightEnd = 0.f;
	sf::Vector2i count;
	sf::Vector2f size;

	bool GetIsDrill() { return isDrill; }

	sf::FloatRect GetSpriteGlobalBound() { return sprite.getGlobalBounds(); }
	sf::Vector2i GetPlayerCellCount() { return sf::Vector2i{ playerCellX, playerCellY }; }

	float GetMaxHP() { return hpMax; }
	float GetMaxAir() { return airMax; }
	float GetHP() { return hp; }
	float GetAir() { return air; }


	void SetCap();
	void SetDrillPower();
	void SetShoes();

	float GetDrillPower() const { return drillPower; }
	float GetBooster() { return booster; }
	float GetArmor() { return armorRate; }

	PlayerBody(const std::string& name = "");
	~PlayerBody();

	void OnItem(int type, bool get);

	void UseItem(int num);

	void OnDamage(float Dmg);
	void OnDie();

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;


};

