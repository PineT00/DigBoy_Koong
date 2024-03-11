#include "pch.h"
#include "Shop.h"

Shop::Shop(const std::string& name)
	:SpriteGo(name)
{
}

void Shop::Init()
{
	SpriteGo::Init();

	animator.SetTarget(&sprite);

	{
		AnimationClip clip;
		clip.id = "Idle";
		clip.fps = 6;
		clip.loopTypes = AnimationLoopTypes::Loop;
		clip.frames.push_back({ "graphics/FSADIGBOY19-226.png", {0, 0, 122, 50} });
		clip.frames.push_back({ "graphics/FSADIGBOY19-227.png", {0, 0, 122, 50} });
		clip.frames.push_back({ "graphics/FSADIGBOY19-228.png", {0, 0, 122, 50} });
		clip.frames.push_back({ "graphics/FSADIGBOY19-229.png", {0, 0, 122, 50} });
		clip.frames.push_back({ "graphics/FSADIGBOY19-230.png", {0, 0, 122, 50} });
		clip.frames.push_back({ "graphics/FSADIGBOY19-231.png", {0, 0, 122, 50} });
		animator.AddClip(clip);
	}
}

void Shop::Reset()
{
}

void Shop::Update(float dt)
{
}

void Shop::Draw(sf::RenderWindow& window)
{
}
