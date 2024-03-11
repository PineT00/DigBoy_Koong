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
		clip.id = "rotate";
		clip.fps = 12;
		clip.loopTypes = AnimationLoopTypes::Loop;
		clip.frames.push_back({ "graphics/shop/FSADIGBOY19-propeller.png", {0, 0, 122, 50} });
		clip.frames.push_back({ "graphics/shop/FSADIGBOY19-propeller.png", {0, 50, 122, 50} });
		clip.frames.push_back({ "graphics/shop/FSADIGBOY19-propeller.png", {0, 100, 122, 50} });
		clip.frames.push_back({ "graphics/shop/FSADIGBOY19-propeller.png", {0, 150, 122, 50} });
		clip.frames.push_back({ "graphics/shop/FSADIGBOY19-propeller.png", {0, 200, 122, 50} });
		clip.frames.push_back({ "graphics/shop/FSADIGBOY19-propeller.png", {0, 250, 122, 50} });
		animator.AddClip(clip);
	}

	shop.SetTexture("graphics/shop/FSADIGBOY19-shop.png");

}

void Shop::Reset()
{
	SpriteGo::Reset();

	SetOrigin(Origins::BC);
	SetPosition({ 100.f, -240.f });

	shop.SetOrigin(Origins::TC);
	shop.SetPosition({ 160.f, -260.f });
	animator.Play("rotate");

}

void Shop::Update(float dt)
{
	SpriteGo::Update(dt);
	animator.Update(dt);

	if (InputMgr::GetMouseButton(sf::Mouse::Left))
	{
		animator.Play("rotate");
	}

}

void Shop::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
	shop.Draw(window);
}
