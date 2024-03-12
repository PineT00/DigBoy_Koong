#pragma once
#include "SpriteGo.h"
class Monster :
    public SpriteGo
{
private:
	Animator animator;

	float speed = 30.f;
	float hp = 10.f;

	sf::Vector2f velocity = { 0.f,0.f };

public:
	Monster(const std::string& name = "");
	~Monster() = default;

	void SetMonster(sf::Vector2f pos);

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

