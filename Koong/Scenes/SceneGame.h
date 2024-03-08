#pragma once
#include "Scene.h"

class TileMap;

class SceneGame : public Scene
{
protected:
	TileMap* tileMap = nullptr;

public:
	SceneGame(SceneIds id);
	~SceneGame() override = default;
	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

