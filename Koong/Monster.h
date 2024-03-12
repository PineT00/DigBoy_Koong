#pragma once
#include "SpriteGo.h"

class TileMap;
class PlayerBody;

class Monster :
    public SpriteGo
{
private:
	TileMap* tileMap;
	PlayerBody* player;

	Animator animator;

	float gravity = 700.f;
	float speed = 100.f;
	float hp = 10.f;
	float attack = 30.f;

	sf::Vector2f velocity = { 0.f,0.f };

	sf::RectangleShape leftCheck;
	sf::RectangleShape rightCheck;

	sf::RectangleShape leftButtomCheck;
	sf::RectangleShape rightButtomCheck;

	sf::Vector2f CheckerSize = { 5.f, 5.f };

	int dir = 1;
	float timer = 3.f;
	float time = 0.f;

	sf::Vector2f monsterPos = { 0.f,0.f };

public:
	Monster(const std::string& name = "");
	~Monster() = default;

	void SetMonster(sf::Vector2f pos);

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

