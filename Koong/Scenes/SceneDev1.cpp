#include "pch.h"
#include "SceneDev1.h"
#include "PlayerBody.h"
#include "PlayerHead.h"
#include "TileMap.h"


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

	tileMap = new TileMap("Ground");
	AddGo(tileMap);

	player = new PlayerBody("Player");
	AddGo(player);

	playerHead = new PlayerHead("Player Head");
	AddGo(playerHead);

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

	tileMap->SetPosition({-400,100});
	player->SetPosition({ 0,0 });


	Scene::Enter();
}

void SceneDev1::Exit()
{
	Scene::Exit();
}

void SceneDev1::Update(float dt)
{
	sf::Vector2f worldViewCenter = worldView.getCenter();
	worldViewCenter = Utils::Lerp(worldViewCenter, player->GetPosition(), dt * 2.5f);
	worldView.setCenter(worldViewCenter);


	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		sf::Vector2f clickPos = InputMgr::GetMousePos();
	}

	Scene::Update(dt);

}
