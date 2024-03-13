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
	SetOrigin({ -4.2f, -4.2f });
	SetPosition(pos);
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
