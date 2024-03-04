#include "pch.h"
#include "SceneGame.h"
#include "Player.h"
#include "TileMap.h"
#include "Zombie.h"

SceneGame::SceneGame(SceneIds id)
    :Scene(id)
{
}

void SceneGame::Init()
{
    tileMap = new TileMap("Background");
    AddGo(tileMap);

    player = new Player("Player");
    AddGo(player);

    //zombie = new Zombie("Zombie");

    Scene::Init();
}

void SceneGame::Release()
{
    Scene::Release();
}

void SceneGame::Enter()
{
    Scene::Enter();

    sf::Vector2f windowSize = (sf::Vector2f)FRAMEWORK.GetWindowSize();
    sf::Vector2f centerPos = (sf::Vector2f)FRAMEWORK.GetWindowSize() * 0.5f;
    //sf::Vector2f centerPos = windowSize * 0.5f;
    worldView.setSize(windowSize);
    worldView.setCenter({ 0.f, 0.f });
    uiView.setSize(windowSize);
    uiView.setCenter(centerPos);

    

    TileMap* tileMap = dynamic_cast<TileMap*>(FindGo("Background"));

    tileMap->SetPosition({ 0.f, 0.f });
    tileMap->SetScale({ 1, 1 });
    tileMap->SetRotation(0);
    tileMap->SetOrigin(Origins::MC);

    player->SetPosition({ 0.f, 0.f });
}

void SceneGame::Exit()
{
    Scene::Exit();
}

void SceneGame::Update(float dt)
{
    Scene::Update(dt);

    worldView.setCenter(player->GetPosition());
    if (InputMgr::GetKeyDown(sf::Keyboard::Space))
    {
        Zombie::Types zombieType = (Zombie::Types)Utils::RandomRange(0, Zombie::TotalTypes);
        Zombie* zombie = Zombie::Create(zombieType);
        zombie->Init();
        zombie->Reset();
        zombie->SetPosition(Utils::RandomInUnitCircle() * 500.f + player->GetPosition());
        AddGo(zombie);
    }
}

void SceneGame::Draw(sf::RenderWindow& window)
{
    Scene::Draw(window);
}
