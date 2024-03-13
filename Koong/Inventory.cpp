#include "pch.h"
#include "Inventory.h"

Inventory::Inventory(const std::string& name)
	:SpriteGo(name)
{
}

void Inventory::SetInventory(sf::Vector2i& count, sf::Vector2f& size)
{
	invenLists.resize(count.x * count.y);

	for (int i = 0; i < count.y; i++) // 6¡Ÿ
	{
		for (int j = 0; j < count.x; j++) // 6ƒ≠
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

	//¿Œ∫•≈‰∏Æ
	inventory.SetOrigin(Origins::TL);
	inventory.SetPosition(invenClose);

	invenName.SetOrigin({ -90.f, -18.f });
	invenName.SetPosition(inventory.GetPosition());

	moneyMenu.SetOrigin({ -60.f, -160.f });
	moneyMenu.SetPosition(inventory.GetPosition());

	invenKoong.SetOrigin({ -150.f, -65.f });
	invenKoong.SetPosition(inventory.GetPosition());

	//¿Œ∫•≈‰∏Æ ¿Â¬¯ΩΩ∑‘
	invenEquipHead.SetOrigin({ -225.f, -50.f });
	invenEquipHead.SetPosition(inventory.GetPosition());
	invenEquipDrill.SetOrigin({ -225.f, -85.f });
	invenEquipDrill.SetPosition(inventory.GetPosition());
	invenEquipFeet.SetOrigin({ -225.f, -120.f });
	invenEquipFeet.SetPosition(inventory.GetPosition());

	SetInventory(invenCount, invenSize);
}

void Inventory::Update(float dt)
{
	SpriteGo::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::I))
	{
		if (inventory.GetPosition() == invenClose)
		{
			inventory.SetPosition(invenOpen);
			for (int i = 0; i < invenCount.y; i++) // 6¡Ÿ
			{
				for (int j = 0; j < invenCount.x; j++) //6ƒ≠
				{
					sf::Vector2f quadPos(invenSize.x * j + 45.f, invenSize.y * i + 185.f);
					invenLists[i * invenCount.x + j].SetPosition(invenOpen + quadPos);
				}
			}
		}
		else if (inventory.GetPosition() == invenOpen)
		{
			inventory.SetPosition(invenClose);
			for (int i = 0; i < invenCount.y; i++) // 6¡Ÿ
			{
				for (int j = 0; j < invenCount.x; j++) //6ƒ≠
				{
					sf::Vector2f quadPos(invenSize.x * j + 45.f, invenSize.y * i + 185.f);
					invenLists[i * invenCount.x + j].SetPosition(invenClose + quadPos);
				}
			}
		}
		invenName.SetPosition(inventory.GetPosition());
		invenKoong.SetPosition(inventory.GetPosition());
		moneyMenu.SetPosition(inventory.GetPosition());
		invenEquipHead.SetPosition(inventory.GetPosition());
		invenEquipDrill.SetPosition(inventory.GetPosition());
		invenEquipFeet.SetPosition(inventory.GetPosition());
	}
}

void Inventory::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);

	inventory.Draw(window);
	invenName.Draw(window);
	moneyMenu.Draw(window);

	invenKoong.Draw(window);
	invenEquipHead.Draw(window);
	invenEquipDrill.Draw(window);
	invenEquipFeet.Draw(window);

	for (int a = 0; a < invenLists.size(); ++a)
	{
		invenLists[a].Draw(window);
	}

}
