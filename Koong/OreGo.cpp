#include "pch.h"
#include "OreGo.h"
#include "PlayerBody.h"

OreGo::OreGo(const std::string& name)
	:SpriteGo(name)
{

}

void OreGo::SetOre(sf::Vector2f pos)
{
	SetTexture("graphics/FSADIGBOY19-24.png");
	SetOrigin(Origins::MC);
	SetPosition({ pos.x + 20.f, pos.y + 20.f });
}

void OreGo::Init()
{
	SpriteGo::Init();
}

void OreGo::Reset()
{
	player = dynamic_cast<PlayerBody*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));
	SpriteGo::Reset();
}

void OreGo::Update(float dt)
{
	sf::FloatRect bound = sprite.getGlobalBounds();
	sf::FloatRect playerBound = player->GetSpriteGlobalBound();

	if (bound.intersects(playerBound))
	{
		player->OnItem();
		SetActive(false);
		//SCENE_MGR.GetCurrentScene()->RemoveGo(this);
	}

	SpriteGo::Update(dt);
}
