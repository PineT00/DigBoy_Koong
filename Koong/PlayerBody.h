#include "SpriteGo.h"
#include "Animator.h"

class TileMap;

class PlayerBody : public SpriteGo
{
protected:
	Animator animator;

	float gravity = 700.f;
	float speed = 300.f;
	float booster = 500.f;
	float hp = 100.f; //¹Ì±¸Çö

	bool isDrill = false;
	float digTime = 0.f;
	float digTimer = 0.1f;

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
	PlayerBody(const std::string& name = "");
	~PlayerBody();

	sf::Vector2f velocity;
	bool isGrounded = true;

	sf::Vector2i count;
	sf::Vector2f size;

	bool GetIsDrill() { return isDrill; }

	void TextureChange(int x, int y, int rowX, int columnY);
	void changeTile(int x, int y);

	void LocateDrill(float r, float x, float y);

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

