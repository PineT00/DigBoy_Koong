#pragma once
#include "Singleton.h"

class Scene;

enum class SceneIds
{
	None = -1, SceneGame, SceneDev1, SceneDev2, Count,
};

class SceneMgr : public Singleton<SceneMgr>
{
	friend class Singleton<SceneMgr>;

protected:
	std::vector<Scene*> scenes;

	SceneIds startScene = SceneIds::SceneDev1;
	SceneIds currentScene = startScene;

	bool isDeveloperMode = false;

	SceneMgr() = default;
	virtual ~SceneMgr();

public:
	void Init();
	void Release();

	void ChangeScene(SceneIds id);

	Scene* GetCurrentScene() { return scenes[(int)currentScene]; }
	bool GetDeveloperMode() { return isDeveloperMode; }

	void Update(float dt);
	void Draw(sf::RenderWindow& window);

	SceneMgr(const SceneMgr&) = delete;
	SceneMgr(SceneMgr&&) = delete;
	SceneMgr& operator=(const SceneMgr&) = delete;
	SceneMgr& operator=(SceneMgr&&) = delete;
};

#define SCENE_MGR (SceneMgr::Instance())