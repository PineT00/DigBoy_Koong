#include "pch.h"
#include "Dynamite.h"
#include "TileMap.h"


Dynamite::Dynamite(const std::string& name)
{
}

void Dynamite::SetDynamite(sf::Vector2i pos)
{
	Init();
	Reset();
	aim = pos;
	sf::Vector2f quadPos(42.f * pos.y, 42.f * pos.x);
	SetOrigin({ -5.f, -5.f });
	SetPosition(quadPos);


}

void Dynamite::Init()
{
	SpriteGo::Init();
	SetTexture("graphics/monster/FSADIGBOY19-125.png");

	animator.SetTarget(&sprite);
	{
		AnimationClip clip;
		clip.id = "Waiting";
		clip.fps = 2;
		clip.loopTypes = AnimationLoopTypes::Loop;
		clip.frames.push_back({ "graphics/monster/FSADIGBOY19-125.png", {0, 0, 29, 19} });
		animator.AddClip(clip);
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
		animator.AddClip(clip);
	}
}

void Dynamite::Reset()
{
	SpriteGo::Reset();
	tileMap = dynamic_cast<TileMap*>(SCENE_MGR.GetCurrentScene()->FindGo("Ground"));

	animator.Play("Waiting");
}

void Dynamite::Update(float dt)
{
	SpriteGo::Update(dt);
	animator.Update(dt);

	bombTime += dt;

	if (bombTime > bombTimer && !explode)
	{
		SetOrigin({ 10.f, 10.f });
		animator.Play("Boom");
		bombTime = 0.f;
		explode = true;

	}
	if (bombTime > bombTimer && explode)
	{
		SetActive(false);
	}

	if (explode)
	{
		tileMap->destroyTile(aim.x, aim.y);
		//std::cout << aim.x << "," << aim.y << std::endl;
	}
}

void Dynamite::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}
