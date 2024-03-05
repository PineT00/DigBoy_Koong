#include "pch.h"
#include "SceneDev1.h"
#include "AniTest.h"
#include "TileMap.h"


SceneDev1::SceneDev1(SceneIds id) : Scene(id)
{
}

SceneDev1::~SceneDev1()
{
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

	player = new AniTest("Player");
	AddGo(player);

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


	tileMap->SetPosition({-400,0});

	Scene::Enter();
}

void SceneDev1::Exit()
{
	Scene::Exit();
}

void SceneDev1::Update(float dt)
{
	Scene::Update(dt);




	sf::FloatRect rect = tileMap->GetGlobalBounds();
	sf::FloatRect rectPlayer = player->GetGlobalBounds();

	if (rectPlayer.intersects(rect))
	{
		player->velocity.y = 0.f;
		player->isGrounded = true;
	}

	t.setSize({ rect.width, rect.height });
	p.setSize({ rectPlayer.width, rectPlayer.height });

}
