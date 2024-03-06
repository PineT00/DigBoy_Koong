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

	TileMap* tileMap;

public:
	PlayerBody(const std::string& name = "");
	~PlayerBody();

	sf::Vector2f velocity;
	bool isGrounded = true;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

