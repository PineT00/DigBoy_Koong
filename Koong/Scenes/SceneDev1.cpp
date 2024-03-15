#include "pch.h"
#include "SceneDev1.h"
#include "PlayerBody.h"
#include "TileMap.h"
#include "SpriteGo.h"
#include "Shop.h"
#include "UiHud.h"
#include "Inventory.h"


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

void SceneDev1::SaveMap(const std::vector<int>& level, const std::string& filename)
{
	std::ofstream file(filename);

	if (file.is_open()) 
	{
		for (size_t i = 0; i < level.size(); ++i) 
		{
			file << level[i];

			// 마지막 열이 아니라면 쉼표를 추가
			if ((i + 1) % 60 == 0) {
				file << "\n";
			}
			else {
				file << ",";
			}
		}

		file.close();
		std::cout << "Level saved to " << filename << std::endl;
	}
	else 
	{
		std::cout << "Failed to open file for writing: " << filename << std::endl;
	}
	
}

void SceneDev1::SaveInventory(const std::string& filename)
{
	std::ofstream file(filename);

	if (file.is_open())
	{
		//file << "\n";
		file << "healKitNum";
		file << ",";
		file << "airCapNum";
		file << ",";
		file << "airCapSuperNum";
		file << ",";
		file << "bombNum";
		file << ",";
		file << "nuclearNum";
		file << ",";
		file << "dynamiteNum";
		file << ",";
		file << "coilNum";
		file << ",";
		file << "bronzeNum";
		file << ",";
		file << "silverNum";
		file << ",";
		file << "goldNum";
		file << ",";
		file << "money";
		file << "\n";
		file << inventory->healKitNum;
		file << ",";
		file << inventory->airCapNum;
		file << ",";
		file << inventory->airCapSuperNum;
		file << ",";
		file << inventory->bombNum;
		file << ",";
		file << inventory->nuclearNum;
		file << ",";
		file << inventory->dynamiteNum;
		file << ",";
		file << inventory->coilNum;
		file << ",";
		file << inventory->bronzeNum;
		file << ",";
		file << inventory->silverNum;
		file << ",";
		file << inventory->goldNum;
		file << ",";
		file << inventory->money;


		file.close();
		std::cout << "Inventory saved to " << filename << std::endl;
	}
	else
	{
		std::cout << "Failed to open file for writing: " << filename << std::endl;
	}
}

void SceneDev1::Init()
{
	inventory = new Inventory("Inventory");
	AddGo(inventory, Ui);

	hud = new UiHud("Hud");
	AddGo(hud, Ui);

	mainScreen = new SpriteGo("MainScreen");
	mainScreen->SetTexture("graphics/FSADIGBOY19-481.jpg");
	mainScreen->SetOrigin(Origins::TL);
	mainScreen->SetPosition({ 0.f, 0.f });
	AddGo(mainScreen, Ui);

	backGround = new SpriteGo("BackGround");
	backGround->SetTexture("graphics/FSADIGBOY19-466.jpg");
	backGround->SetOrigin(Origins::MC);
	AddGo(backGround);

	tileMap = new TileMap("Ground");
	AddGo(tileMap, World);
	
	shop = new Shop("Shop");
	AddGo(shop);

	player = new PlayerBody("Player");
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

	tileMap->SetPosition({ 0,0 });
	player->SetPosition({ 0,0 });

	tileMapLeftEnd = tileMap->GetPosition().x;
	tileMapRightEnd = tileMapLeftEnd + tileMap->GetCellCount().x * tileMap->GetCellSize().x;

	shop->ShopSetPosition({ 1200.f, 45.f });

	player->SetPosition({ 1400.f, -50.f });

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


	if (player->GetPosition().x >= (tileMapLeftEnd + 300.f) && player->GetPosition().x <= (tileMapRightEnd - 300.f))
	{

		worldViewCenter.x = Utils::Lerp(worldViewCenter.x, player->GetPosition().x, dt * 2.5f);

	}
	else
	{
		if (player->GetPosition().x < 1000.f)
		{
			worldViewCenter.x = Utils::Lerp(worldViewCenter.x, tileMapLeftEnd + 330.f, dt * 2.5f);
		}
		else if (player->GetPosition().x > 1000.f)
		{
			worldViewCenter.x = Utils::Lerp(worldViewCenter.x, tileMapRightEnd - 330.f, dt * 2.5f);
		}
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
	case Status::Select:
		UpdateSelect(dt);
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
		SetStatus(Status::Select);
	}
}

void SceneDev1::UpdateSelect(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SetStatus(Status::Game);

		inventory->LoadInventory("tables/save/Inventory.csv");
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
	else if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SaveMap(tileMap->level, "tables/save/MapTableSave.csv");
		SaveInventory("tables/save/Inventory.csv");
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
	case Status::Select:
		mainScreen->SetActive(false);
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
