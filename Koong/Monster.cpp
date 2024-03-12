#include "pch.h"
#include "Monster.h"

Monster::Monster(const std::string& name)
	:SpriteGo(name)
{
}

void Monster::SetMonster(sf::Vector2f pos)
{
	animator.Play("walk");
	SetOrigin(Origins::BC);
	SetPosition(pos);
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
		clip.frames.push_back({ "graphics/monster/FSADIGBOY19-121.png", {0, 0, 38, 40} });
		clip.frames.push_back({ "graphics/monster/FSADIGBOY19-122.png", {0, 0, 38, 40} });
		clip.frames.push_back({ "graphics/monster/FSADIGBOY19-123.png", {0, 0, 38, 40} });
		clip.frames.push_back({ "graphics/monster/FSADIGBOY19-122.png", {0, 0, 38, 40} });
		animator.AddClip(clip);
	}

	{
		AnimationClip clip;
		clip.id = "dead";
		clip.fps = 1;
		clip.loopTypes = AnimationLoopTypes::Single;

		clip.frames.push_back({ "graphics/monster/FSADIGBOY19-124.png", {0, 0, 38, 40} });
		animator.AddClip(clip);
	}
}

void Monster::Reset()
{
	SpriteGo::Reset();
	animator.Play("walk");
	SetOrigin(Origins::BC);
	SetPosition({ 0.f, 0.f });
}

void Monster::Update(float dt)
{
	SpriteGo::Update(dt);
	animator.Update(dt);

	float dir = 1.f;

	velocity.x = dir * speed;
	sf::Vector2f pos = position + velocity * dt;
	SetPosition(pos);
}

void Monster::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}
