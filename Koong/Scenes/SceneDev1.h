#pragma once

class TileMap;
class AniTest;

class SceneDev1 : public Scene
{
protected:


public:
	TileMap* tileMap = nullptr;
	AniTest* player = nullptr;

	SceneDev1(SceneIds id);
	virtual ~SceneDev1();

	sf::Vector2f ClampByTileMap(const sf::Vector2f point);

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
};