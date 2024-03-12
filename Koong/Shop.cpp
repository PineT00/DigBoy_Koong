#include "pch.h"
#include "Shop.h"
#include "PlayerBody.h"

Shop::Shop(const std::string& name)
	:SpriteGo(name)
{
}

void Shop::Init()
{
	SpriteGo::Init();

	animator1.SetTarget(&propeller);
	
	{
		AnimationClip clip;
		clip.id = "rotate";
		clip.fps = 10;
		clip.loopTypes = AnimationLoopTypes::Loop;
		clip.frames.push_back({ "graphics/shop/FSADIGBOY19-propeller.png", {0, 0, 122, 50} });
		clip.frames.push_back({ "graphics/shop/FSADIGBOY19-propeller.png", {0, 50, 122, 50} });
		clip.frames.push_back({ "graphics/shop/FSADIGBOY19-propeller.png", {0, 100, 122, 50} });
		clip.frames.push_back({ "graphics/shop/FSADIGBOY19-propeller.png", {0, 150, 122, 50} });
		clip.frames.push_back({ "graphics/shop/FSADIGBOY19-propeller.png", {0, 200, 122, 50} });
		clip.frames.push_back({ "graphics/shop/FSADIGBOY19-propeller.png", {0, 250, 122, 50} });
		animator1.AddClip(clip);
	}

	animator2.SetTarget(&portal);
	{
		AnimationClip clip;
		clip.id = "portal";
		clip.fps = 8;
		clip.loopTypes = AnimationLoopTypes::Loop;
		clip.frames.push_back({ "graphics/shop/FSADIGBOY19-232.png", {0, 0, 87, 93} });
		clip.frames.push_back({ "graphics/shop/FSADIGBOY19-233.png", {0, 0, 87, 93} });
		clip.frames.push_back({ "graphics/shop/FSADIGBOY19-234.png", {0, 0, 87, 93} });
		clip.frames.push_back({ "graphics/shop/FSADIGBOY19-235.png", {0, 0, 87, 93} });
		clip.frames.push_back({ "graphics/shop/FSADIGBOY19-236.png", {0, 0, 87, 93} });
		clip.frames.push_back({ "graphics/shop/FSADIGBOY19-237.png", {0, 0, 87, 93} });
		clip.frames.push_back({ "graphics/shop/FSADIGBOY19-238.png", {0, 0, 87, 93} });
		clip.frames.push_back({ "graphics/shop/FSADIGBOY19-239.png", {0, 0, 87, 93} });
		animator2.AddClip(clip);
	}

	NPC.SetTexture("graphics/shop/FSADIGBOY19-220.png");
	shop.SetTexture("graphics/shop/FSADIGBOY19-shop.png");


}

void Shop::Reset()
{
	SpriteGo::Reset();

	propeller.setPosition({ 95.f, -235.f });
	portal.setPosition({ 115.f, -80.f });

	shop.SetOrigin(Origins::TC);
	shop.SetPosition({ 160.f, -255.f });

	NPC.SetOrigin(Origins::TC);
	NPC.SetPosition({ 155.f, -70.f });

	animator1.Play("rotate");

	animator2.Play("portal");

	player = dynamic_cast<PlayerBody*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));

}

void Shop::Update(float dt)
{
	SpriteGo::Update(dt);
	animator1.Update(dt);
	animator2.Update(dt);

	sf::FloatRect bound = NPC.GetGlobalBounds();
	sf::FloatRect playerBound = player->GetSpriteGlobalBound();

	if (bound.intersects(playerBound) && InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		player->SellAll();
	}

}

void Shop::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);

	shop.Draw(window);
	NPC.Draw(window);
	window.draw(propeller);
	window.draw(portal);

}
