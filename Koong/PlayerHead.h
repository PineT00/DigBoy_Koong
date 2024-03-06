#pragma once
#include "SpriteGo.h"

class PlayerBody;

class PlayerHead :
    public SpriteGo
{

protected:
	Animator animator;
    PlayerBody* player;

public:
	PlayerHead(const std::string& name = "");
	~PlayerHead() = default;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;


};

