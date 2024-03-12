#pragma once

class SpriteGo;
class TileMap;
class PlayerBody;
class Shop;
class UiHud;

class SceneDev1 : public Scene
{
public:
	enum class Status
	{
		Awake,
		Game,
		GameOver,
		Pause
	};

protected:
	Status currStatus = Status::Awake;

	float tileMapLeftEnd = 0;
	float tileMapRightEnd = 0;

public:
	SpriteGo* mainScreen = nullptr;
	SpriteGo* backGround = nullptr;
	TileMap* tileMap = nullptr;
	PlayerBody* player = nullptr;
	Shop* shop = nullptr;
	UiHud* hud = nullptr;


	SceneDev1(SceneIds id);
	virtual ~SceneDev1();

	bool IsInTileMap(const sf::Vector2f& point);

	sf::Vector2f ClampByTileMap(const sf::Vector2f point);

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;

	void UpdateAwake(float dt);
	void UpdateGame(float dt);
	void UpdateGameOver(float dt);
	void UpdatePause(float dt);

	void SetStatus(Status newStatus);
	Status GetStatus() { return currStatus; }
};