#include "pch.h"
#include "SceneDev1.h"
#include "PlayerBody.h"
#include "PlayerHead.h"
#include "TileMap.h"
#include "SpriteGo.h"


SceneDev1::SceneDev1(SceneIds id) : Scene(id)
{
}

SceneDev1::~SceneDev1()
{
}

bool SceneDev1::IsInTileMap(const sf::Vector2f& point)
{
	sf::FloatRect rect = tileMap->GetGlobalBounds();
	rect = Utils::ResizeRect(rect, tileMap->GetCellSize() * -2.f);

	return rect.contains(point);
}

sf::Vector2f SceneDev1::ClampByTileMap(const sf::Vector2f point)
{
	sf::FloatRect rect = tileMap->GetGlobalBounds();
	rect = Utils::ResizeRect(rect, tileMap->GetCellSize() * -2.f);

	return Utils::Clamp(point, rect);
}

void SceneDev1::Init()
{

	backGround = new SpriteGo("BackGround");
	backGround->SetTexture("graphics/FSADIGBOY19-466.jpg");
	backGround->SetOrigin(Origins::MC);
	backGround->SetScale({ 1.5f, 1.5f });
	AddGo(backGround);

	tileMap = new TileMap("Ground");
	AddGo(tileMap, World);

	player = new PlayerBody("Player");
	AddGo(player);

	playerHead = new PlayerHead("Player Head");
	AddGo(playerHead);

	mainScreen = new SpriteGo("MainScreen");
	mainScreen->SetTexture("graphics/FSADIGBOY19-481.jpg");
	mainScreen->SetOrigin(Origins::TL);
	mainScreen->SetScale({ 2.f, 2.f });
	mainScreen->SetPosition({ 0.f, 0.f });
	AddGo(mainScreen, Ui);

	Scene::Init();
}

void SceneDev1::Release()
{
	Scene::Release();
}

void SceneDev1::Enter()
{
	sf::Vector2f windowSize = (sf::Vector2f)FRAMEWORK.GetWindowSize();
	sf::Vector2f centerPos = windowSize * 0.5f;
	worldView.setSize(windowSize);
	worldView.setCenter({ 0.f, 0.f });
	uiView.setSize(windowSize);
	uiView.setCenter(centerPos);

	tileMap->SetPosition({ 0,0 });
	player->SetPosition({ 0,0 });


	tileMapLeftEnd = tileMap->GetPosition().x;
	tileMapRightEnd = tileMapLeftEnd + tileMap->GetCellCount().x * tileMap->GetCellSize().x;

	player->SetActive(false);

	Scene::Enter();
}

void SceneDev1::Exit()
{
	Scene::Exit();
}

void SceneDev1::Update(float dt)
{

	sf::Vector2f worldViewCenter = worldView.getCenter();

	worldViewCenter.y = Utils::Lerp(worldViewCenter.y, player->GetPosition().y, dt * 2.5f);

	if (player->GetPosition().x > tileMapLeftEnd && player->GetPosition().x < tileMapRightEnd)
	{
		worldViewCenter.x = Utils::Lerp(worldViewCenter.x, player->GetPosition().x, dt * 2.5f);
	}
	worldView.setCenter(worldViewCenter);

	backGround->SetPosition(worldViewCenter);

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		sf::Vector2f clickPos = InputMgr::GetMousePos();
	}

	Scene::Update(dt);

	switch (currStatus)
	{
	case Status::Awake:
		UpdateAwake(dt);
		break;
	case Status::Game:
		UpdateGame(dt);
		break;
	case Status::GameOver:
		UpdateGameOver(dt);
		break;
	case Status::Pause:
		UpdatePause(dt);
		break;
	}

}

void SceneDev1::UpdateAwake(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SetStatus(Status::Game);
	}
}

void SceneDev1::UpdateGame(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		SetStatus(Status::Pause);
		return;
	}
}

void SceneDev1::UpdateGameOver(float dt)
{
}

void SceneDev1::UpdatePause(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		SetStatus(Status::Game);
		return;
	}
}

void SceneDev1::SetStatus(Status newStatus)
{
	Status prevStatus = currStatus;
	currStatus = newStatus;

	switch (currStatus)
	{
	case Status::Awake:
		mainScreen->SetActive(true);
		FRAMEWORK.SetTimeScale(0.f);
		break;
	case Status::Game:
		player->SetActive(true);
		mainScreen->SetActive(false);
		SOUND_MGR.PlayBgm("sound/FSADIGBOY19-MainBGM.mp3", false);
		FRAMEWORK.SetTimeScale(1.f);
		break;
	case Status::GameOver:
		FRAMEWORK.SetTimeScale(0.f);
		break;
	case Status::Pause:
		FRAMEWORK.SetTimeScale(0.f);
		break;

	}
}
