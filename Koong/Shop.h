#pragma once
#include "SpriteGo.h"

class Shop :
    public SpriteGo
{

protected:
	Animator animator;

	SpriteGo propeller;
	SpriteGo shop;
	SpriteGo board;

public:
	Shop(const std::string& name = "");
	~Shop() = default;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;


};

