#include "pch.h"
#include "SceneGame.h"
#include "TileMap.h"

SceneGame::SceneGame(SceneIds id)
    :Scene(id)
{
}

void SceneGame::Init()
{


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

}

void SceneGame::Exit()
{
    Scene::Exit();
}

void SceneGame::Update(float dt)
{
    Scene::Update(dt);
}

void SceneGame::Draw(sf::RenderWindow& window)
{
    Scene::Draw(window);
}
