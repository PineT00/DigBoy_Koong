#include "pch.h"
#include "Shop.h"
#include "PlayerBody.h"

Shop::Shop(const std::string& name)
	:SpriteGo(name)
{
}

void Shop::ShowMessage(sf::Vector2f pos)
{
	message.SetOrigin(Origins::MC);

	messageBubble.SetTexture("graphics/bubble/FSADIGBOY19-bubble.png");
	messageBubble.SetOrigin({ 90,52 });
	message.SetPosition(pos);
	messageBubble.SetPosition(pos);

}

void Shop::ShopSetPosition(sf::Vector2f pos)
{
	shop.SetOrigin(Origins::BC);

	shop.SetPosition(pos);

	propeller.setPosition(shop.GetPosition());

	NPC.SetPosition(shop.GetPosition());

	portal.setPosition(shop.GetPosition());

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

	shop.SetOrigin(Origins::BC);
	//shop.SetPosition({ 640.f, 45.f });

	propeller.setOrigin({ 65.f, 276.f });
	propeller.setPosition(shop.GetPosition());

	NPC.SetOrigin({27.f, 116.f});
	NPC.SetPosition(shop.GetPosition());

	portal.setOrigin({ 45.f, 125.f }); //스프라이트 크기의 가운데
	portal.setPosition(shop.GetPosition());

	animator1.Play("rotate");

	animator2.Play("portal");

	player = dynamic_cast<PlayerBody*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));


}

void Shop::Update(float dt)
{
	SpriteGo::Update(dt);
	animator1.Update(dt);
	animator2.Update(dt);

}

void Shop::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);

	shop.Draw(window);
	NPC.Draw(window);
	window.draw(propeller);
	window.draw(portal);


}
