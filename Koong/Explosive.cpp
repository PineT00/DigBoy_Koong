#include "pch.h"
#include "Explosive.h"
#include "PlayerBody.h"
#include "TileMap.h"
#include "Monster.h"

Explosive::Explosive(const std::string& name)
{
}

void Explosive::SetBomb(sf::Vector2i pos)
{
	sf::Vector2f quadPos(42.f * pos.x, 42.f * pos.y);
	bomb.setPosition(quadPos);
	//SetPosition(quadPos);
	Init();
	Reset();
}

void Explosive::SetNuke(sf::Vector2i pos)
{
}

void Explosive::SetDynamite(sf::Vector2i pos)
{
}

void Explosive::Init()
{
	SpriteGo::Init();

	animatorBomb.SetTarget(&bomb);
	{
		AnimationClip clip;
		clip.id = "Waiting";
		clip.fps = 2;
		clip.loopTypes = AnimationLoopTypes::Loop;
		clip.frames.push_back({ "graphics/monster/FSADIGBOY19-160.png", {0, 0, 34, 34} });
		clip.frames.push_back({ "graphics/monster/FSADIGBOY19-161.png", {0, 0, 34, 34} });
		animatorBomb.AddClip(clip);
	}

	{
		AnimationClip clip;
		clip.id = "Boom";
		clip.fps = 15;
		clip.loopTypes = AnimationLoopTypes::Single;
		clip.frames.push_back({ "graphics/monster/FSADIGBOY19-127.png", {0, 0, 60, 60} });
		clip.frames.push_back({ "graphics/monster/FSADIGBOY19-128.png", {0, 0, 60, 60} });
		clip.frames.push_back({ "graphics/monster/FSADIGBOY19-129.png", {0, 0, 60, 60} });
		clip.frames.push_back({ "graphics/monster/FSADIGBOY19-130.png", {0, 0, 60, 60} });
		clip.frames.push_back({ "graphics/monster/FSADIGBOY19-131.png", {0, 0, 60, 60} });
		clip.frames.push_back({ "graphics/monster/FSADIGBOY19-132.png", {0, 0, 60, 60} });
		clip.frames.push_back({ "graphics/monster/FSADIGBOY19-133.png", {0, 0, 60, 60} });
		clip.frames.push_back({ "graphics/monster/FSADIGBOY19-134.png", {0, 0, 60, 60} });
		clip.frames.push_back({ "graphics/monster/FSADIGBOY19-135.png", {0, 0, 60, 60} });
		clip.frames.push_back({ "graphics/monster/FSADIGBOY19-136.png", {0, 0, 60, 60} });
		clip.frames.push_back({ "graphics/monster/FSADIGBOY19-137.png", {0, 0, 60, 60} });
		clip.frames.push_back({ "graphics/monster/FSADIGBOY19-138.png", {0, 0, 60, 60} });
		clip.frames.push_back({ "graphics/monster/FSADIGBOY19-139.png", {0, 0, 60, 60} });
		clip.frames.push_back({ "graphics/monster/FSADIGBOY19-140.png", {0, 0, 60, 60} });
		clip.frames.push_back({ "graphics/monster/FSADIGBOY19-141.png", {0, 0, 60, 60} });
		clip.frames.push_back({ "graphics/monster/FSADIGBOY19-142.png", {0, 0, 60, 60} });
		clip.frames.push_back({ "graphics/monster/FSADIGBOY19-143.png", {0, 0, 60, 60} });
		clip.frames.push_back({ "graphics/monster/FSADIGBOY19-144.png", {0, 0, 60, 60} });
		clip.frames.push_back({ "graphics/monster/FSADIGBOY19-145.png", {0, 0, 60, 60} });
		clip.frames.push_back({ "graphics/monster/FSADIGBOY19-146.png", {0, 0, 60, 60} });
		clip.frames.push_back({ "graphics/monster/FSADIGBOY19-147.png", {0, 0, 60, 60} });
		clip.frames.push_back({ "graphics/monster/FSADIGBOY19-148.png", {0, 0, 60, 60} });
		clip.frames.push_back({ "graphics/monster/FSADIGBOY19-149.png", {0, 0, 60, 60} });
		clip.frames.push_back({ "graphics/monster/FSADIGBOY19-150.png", {0, 0, 60, 60} });
		clip.frames.push_back({ "graphics/monster/FSADIGBOY19-151.png", {0, 0, 60, 60} });
		clip.frames.push_back({ "graphics/monster/FSADIGBOY19-152.png", {0, 0, 60, 60} });
		clip.frames.push_back({ "graphics/monster/FSADIGBOY19-153.png", {0, 0, 60, 60} });
		clip.frames.push_back({ "graphics/monster/FSADIGBOY19-154.png", {0, 0, 60, 60} });
		clip.frames.push_back({ "graphics/monster/FSADIGBOY19-155.png", {0, 0, 60, 60} });
		clip.frames.push_back({ "graphics/monster/FSADIGBOY19-156.png", {0, 0, 60, 60} });
		clip.frames.push_back({ "graphics/monster/FSADIGBOY19-157.png", {0, 0, 60, 60} });
		clip.frames.push_back({ "graphics/monster/FSADIGBOY19-158.png", {0, 0, 60, 60} });
		animatorBomb.AddClip(clip);
	}

}

void Explosive::Reset()
{
	SpriteGo::Reset();
	animatorBomb.Play("Waiting");
	bomb.setOrigin({ -5.f, -5.f });
}

void Explosive::Update(float dt)
{
	SpriteGo::Update(dt);
	animatorBomb.Update(dt);

	bombTime += dt;
	if (bombTime > bombTimer)
	{
		animatorBomb.Play("Boom");
		bombTime = 0.f;
		animatorBomb.PlayQueue("Waiting");
	}
}

void Explosive::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);

	window.draw(bomb);
}
