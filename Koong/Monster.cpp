#include "pch.h"
#include "Monster.h"

Monster::Monster(const std::string& name)
	:SpriteGo(name)
{
}

void Monster::Init()
{
	SpriteGo::Init();

	animator.SetTarget(&sprite);

	{
		AnimationClip clip;
		clip.id = "walk";
		clip.fps = 4;
		clip.loopTypes = AnimationLoopTypes::Loop;
		clip.frames.push_back({ "graphics/spriteSheetHead.png", {0, 0, 40, 33} });
		clip.frames.push_back({ "graphics/spriteSheetHead.png", {0, 32, 40, 33} });
		animator.AddClip(clip);
	}

	{
		AnimationClip clip;
		clip.id = "dead";
		clip.fps = 2;
		clip.loopTypes = AnimationLoopTypes::Loop;

		clip.frames.push_back({ "graphics/spriteSheetHead.png", {0, 132, 40, 33} });
		animator.AddClip(clip);
	}
}

void Monster::Reset()
{
}

void Monster::Update(float dt)
{
}

void Monster::Draw(sf::RenderWindow& window)
{
}
