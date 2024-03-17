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
		file << "cap1";
		file << ",";
		file << "cap2";
		file << ",";
		file << "cap3";
		file << ",";
		file << "cap4";
		file << ",";
		file << "cap5";
		file << ",";
		file << "drill1";
		file << ",";
		file << "drill2";
		file << ",";
		file << "drill3";
		file << ",";
		file << "drill4";
		file << ",";
		file << "drill5";
		file << ",";
		file << "shoe1";
		file << ",";
		file << "shoe2";
		file << ",";
		file << "shoe3";
		file << ",";
		file << "shoe4";
		file << ",";
		file << "shoe5";
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
		file << inventory->cap1;
		file << ",";
		file << inventory->cap2;
		file << ",";
		file << inventory->cap3;
		file << ",";
		file << inventory->cap4;
		file << ",";
		file << inventory->cap5;
		file << ",";
		file << inventory->drill1;
		file << ",";
		file << inventory->drill2;
		file << ",";
		file << inventory->drill3;
		file << ",";
		file << inventory->drill4;
		file << ",";
		file << inventory->drill5;
		file << ",";
		file << inventory->shoe1;
		file << ",";
		file << inventory->shoe2;
		file << ",";
		file << inventory->shoe3;
		file << ",";
		file << inventory->shoe4;
		file << ",";
		file << inventory->shoe5;
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

void SceneDev1::SetSelect(int select)
{
	switch (select)
	{
	case 1:
		selectNew->SetActive(true);
		selectLoad->SetActive(false);
		selectHowTo->SetActive(false);
		break;
	case 2:
		selectNew->SetActive(false);
		selectLoad->SetActive(true);
		selectHowTo->SetActive(false);
		break;
	case 3:
		selectNew->SetActive(false);
		selectLoad->SetActive(false);
		selectHowTo->SetActive(true);
		break;

	default:
		break;
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
	tileMap->SetLevel("tables/save/MapTableSave.csv");
	AddGo(tileMap, World);
	
	shop = new Shop("Shop");
	AddGo(shop);

	player = new PlayerBody("Player");
	AddGo(player);

	selectScreen = new SpriteGo("SelectScreen");
	selectScreen->SetTexture("graphics/FSADIGBOY19-Select.png");
	selectScreen->SetOrigin(Origins::TL);
	selectScreen->SetPosition({ 0.f, 0.f });
	AddGo(selectScreen, Ui);

	selectNew = new SpriteGo("SelectNew");
	selectNew->SetTexture("graphics/FSADIGBOY19-272.png");
	selectNew->SetOrigin(Origins::TL);
	selectNew->SetPosition({ 0.f, 0.f });
	AddGo(selectNew, Ui);

	selectLoad = new SpriteGo("SelectLoad");
	selectLoad->SetTexture("graphics/FSADIGBOY19-273.png");
	selectLoad->SetOrigin(Origins::TL);
	selectLoad->SetPosition({ 0.f, 0.f });
	AddGo(selectLoad, Ui);

	selectHowTo = new SpriteGo("SelectHowTo");
	selectHowTo->SetTexture("graphics/FSADIGBOY19-271.png");
	selectHowTo->SetOrigin(Origins::TL);
	selectHowTo->SetPosition({ 0.f, 0.f });
	AddGo(selectHowTo, Ui);

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

	selectNew->SetOrigin(Origins::MC);
	selectNew->SetPosition({302.f, 265.f});
	selectLoad->SetOrigin(Origins::MC);
	selectLoad->SetPosition({ 302.f, 295.f });
	selectHowTo->SetOrigin(Origins::MC);
	selectHowTo->SetPosition({ 302.f, 325.f });

	selectScreen->SetActive(false);
	selectNew->SetActive(false);
	selectLoad->SetActive(false);
	selectHowTo->SetActive(false);

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
	if (InputMgr::GetKeyDown(sf::Keyboard::Down))
	{
		select += 1;

		if (select > 3)
		{
			select = 1;
		}
	}
	SetSelect(select);
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))

	{
		if (select == 1)
		{
			//tileMap->SetLevel("tables/MapTable60200.csv");
			SetStatus(Status::Game);
		}
		else if (select == 2)
		{
			//tileMap->SetLevel("tables/save/MapTableSave.csv");
			//tileMap->Set(tileMap->GetCellCount(),tileMap->GetCellSize());
			inventory->LoadInventory("tables/save/Inventory.csv");
			SetStatus(Status::Game);

		}
	}



}

void SceneDev1::UpdateGame(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		SetStatus(Status::Pause);
		return;
	}
	if (player->GetHP() <= 0)
	{
		deadTime += dt;
		if (deadTime >= deadTimer)
		{
			SetStatus(Status::GameOver);
		}
	}
	if (hud->save)
	{
		SaveMap(tileMap->level, "tables/save/MapTableSave.csv");
		SaveInventory("tables/save/Inventory.csv");
		hud->save = false;
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
		selectScreen->SetActive(false);
		FRAMEWORK.SetTimeScale(0.f);
		break;
	case Status::Select:
		mainScreen->SetActive(false);
		selectScreen->SetActive(true);
		FRAMEWORK.SetTimeScale(0.f);
		break;
	case Status::Game:
		mainScreen->SetActive(false);
		selectScreen->SetActive(false);
		selectNew->SetActive(false);
		selectLoad->SetActive(false);
		selectHowTo->SetActive(false);

		player->SetActive(true);
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
