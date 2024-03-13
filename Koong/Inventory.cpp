#include "pch.h"
#include "Inventory.h"

Inventory::Inventory(const std::string& name)
	:SpriteGo(name)
{
}

void Inventory::SetInventory(sf::Vector2i& count, sf::Vector2f& size)
{
	invenLists.resize(count.x * count.y);

	for (int i = 0; i < count.y; i++) // 6ÁÙ
	{
		for (int j = 0; j < count.x; j++) // 6Ä­
		{
			if (i >= 3)
			{
				invenLists[i * count.x + j].SetTexture("graphics/ui/FSADIGBOY19-321.png");
			}
			else
			{
				invenLists[i * count.x + j].SetTexture("graphics/ui/FSADIGBOY19-305.png");
			}
			invenLists[i * count.x + j].Init();
			invenLists[i * count.x + j].Reset();
			sf::Vector2f quadPos(invenSize.x * j + 45.f, invenSize.y * i + 185.f);
			invenLists[i * invenCount.x + j].SetPosition(invenClose + quadPos);
		}
	}
}

void Inventory::Init()
{
	SpriteGo::Init();

	inventory.SetTexture("graphics/ui/FSADIGBOY19-319.png");

	invenName.SetTexture("graphics/ui/FSADIGBOY19-320.png");
	moneyMenu.SetTexture("graphics/ui/FSADIGBOY19-324.png");
	invenKoong.SetTexture("graphics/ui/FSADIGBOY19-322.png");

	invenEquipHead.SetTexture("graphics/ui/FSADIGBOY19-307.png");
	invenEquipDrill.SetTexture("graphics/ui/FSADIGBOY19-307.png");
	invenEquipFeet.SetTexture("graphics/ui/FSADIGBOY19-307.png");

}

void Inventory::Release()
{
	SpriteGo::Release();
}

void Inventory::Reset()
{
	SpriteGo::Reset();
}

void Inventory::Update(float dt)
{
	SpriteGo::Update(dt);

}

void Inventory::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}
