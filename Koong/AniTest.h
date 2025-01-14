#pragma once
#include "SpriteGo.h"
#include "Animator.h"

class TileMap;

class AniTest : public SpriteGo
{
protected:
	Animator animator;
	Animator animatorH;

	float gravity = 700.f;
	float speed = 300.f;
	float booster = 500.f;

	TileMap* tileMap;

public:

	AniTest(const std::string& name = "");
	~AniTest();

	sf::Vector2f velocity;
	bool isGrounded = true;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

