#pragma once
#include "SpriteGo.h"
class Monster :
    public SpriteGo
{
private:
	Animator animator;

public:
	Monster(const std::string& name = "");
	~Monster() = default;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

