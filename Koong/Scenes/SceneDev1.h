#pragma once

class SpriteGo;
class TileMap;
class PlayerBody;
class Shop;
class UiHud;
class Inventory;

class SceneDev1 : public Scene
{
public:
	enum class Status
	{
		Awake,
		Select,
		Game,
		GameOver,
		Pause
	};

protected:
	Status currStatus = Status::Awake;

	float tileMapLeftEnd = 0;
	float tileMapRightEnd = 0;

public:
	float deadTime = 0.f;
	float deadTimer = 1.f;

	SpriteGo* mainScreen = nullptr;
	SpriteGo* backGround = nullptr;
	TileMap* tileMap = nullptr;
	PlayerBody* player = nullptr;
	Shop* shop = nullptr;
	UiHud* hud = nullptr;
	Inventory* inventory = nullptr;


	SceneDev1(SceneIds id);
	virtual ~SceneDev1();

	bool IsInTileMap(const sf::Vector2f& point);

	sf::Vector2f ClampByTileMap(const sf::Vector2f point);

	void SaveMap(const std::vector<int>& level, const std::string& filename);
	void SaveInventory(const std::string& filename);

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;

	void UpdateAwake(float dt);
	void UpdateSelect(float dt);
	void UpdateGame(float dt);
	void UpdateGameOver(float dt);
	void UpdatePause(float dt);

	void SetStatus(Status newStatus);
	Status GetStatus() { return currStatus; }
};