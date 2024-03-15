#include "pch.h"
#include "OreGo.h"
#include "PlayerBody.h"

OreGo::OreGo(const std::string& name)
	:SpriteGo(name)
{

}

void OreGo::SetOre(sf::Vector2f pos, int ore)
{
	switch (ore)
	{
	case 80:
		type = Types::Coil;
		SetTexture("graphics/ore/FSADIGBOY19-24.png");
		break;

	case 81:
		type = Types::Bronze;
		SetTexture("graphics/ore/FSADIGBOY19-23.png");
		break;

	case 82:
		type = Types::Silver;
		SetTexture("graphics/ore/FSADIGBOY19-22.png");
		break;

	case 83:
		type = Types::Gold;
		SetTexture("graphics/ore/FSADIGBOY19-21.png");
		break;

	default:
		break;
	}
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
		int typeNum = static_cast<int>(type);
		player->OnItem(typeNum, 1);
		SetActive(false);
		SCENE_MGR.GetCurrentScene()->RemoveGo(this);
	}

	SpriteGo::Update(dt);
}
