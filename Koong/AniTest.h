#pragma once
#include "SpriteGo.h"
#include "Animator.h"

class SceneDev1;
class TileMap;

class AniTest : public SpriteGo
{
protected:
	Animator animator;
	SceneDev1* sceneDev1 = nullptr;
	TileMap* tileMap = nullptr;

	float gravity = 500.f;

	float speed = 300.f;




public:

	AniTest(const std::string& name = "");
	~AniTest();

	sf::Vector2f velocity;
	bool isGrounded = true;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	//void Draw(sf::RenderWindow& window) override;
};

