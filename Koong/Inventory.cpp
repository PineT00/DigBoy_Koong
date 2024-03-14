#include "pch.h"
#include "Inventory.h"

Inventory::Inventory(const std::string& name)
	:SpriteGo(name)
{
}

void Inventory::SetInvenItem()
{
}

void Inventory::SetInvenOre()
{
	for (int i = 0; i < invenCount.y; i++) // 6줄
	{
		for (int j = 0; j < invenCount.x; j++) // 6칸
		{
			if (coilNum > 0 && stateList[i * invenCount.x + j] == Empty)
			{
				//광물스프라이트 생성

			}
		}
	}
}

void Inventory::SetInvenMoney()
{
	int unitNumM = money % 10;
	int tensNumM = (money / 10) % 10;
	int hundredsNumM = (money / 100) % 10;
	int thousandsNumM = (money / 1000) % 10;
	int tenThousandsNumM = (money / 10000) % 10;
	int hunThousandsNumM = (money / 100000) % 10;

	moneyUnit.setTexture(*moneyTexture[unitNumM]);
	moneyTens.setTexture(*moneyTexture[tensNumM]);
	moneyHundreds.setTexture(*moneyTexture[hundredsNumM]);
	moneyThousands.setTexture(*moneyTexture[thousandsNumM]);
	moneyTenThousands.setTexture(*moneyTexture[tenThousandsNumM]);
	moneyHunThousands.setTexture(*moneyTexture[hunThousandsNumM]);

}

void Inventory::SetInventory()
{
	invenLists.resize(invenCount.x * invenCount.y);

	for (int i = 0; i < invenCount.y; i++) // 6줄
	{
		for (int j = 0; j < invenCount.x; j++) // 6칸
		{
			if (i >= invenlimit)
			{
				invenLists[i * invenCount.x + j].SetTexture("graphics/ui/FSADIGBOY19-321.png");
			}
			else
			{
				invenLists[i * invenCount.x + j].SetTexture("graphics/ui/FSADIGBOY19-305.png");
			}
			invenLists[i * invenCount.x + j].Init();
			invenLists[i * invenCount.x + j].Reset();
			sf::Vector2f quadPos(invenSize.x * j + 45.f, invenSize.y * i + 185.f);
			invenLists[i * invenCount.x + j].SetPosition(invenClose + quadPos);
		}
	}

	SetInvenMoney();
	SetInvenItem();
	SetInvenOre();

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


	//숫자변수 텍스쳐 할당
	{
		moneyTexture.push_back(&RES_MGR_TEXTURE.Get("graphics/ui/uiNum/FSADIGBOY19-309.png"));
		moneyTexture.push_back(&RES_MGR_TEXTURE.Get("graphics/ui/uiNum/FSADIGBOY19-310.png"));
		moneyTexture.push_back(&RES_MGR_TEXTURE.Get("graphics/ui/uiNum/FSADIGBOY19-311.png"));
		moneyTexture.push_back(&RES_MGR_TEXTURE.Get("graphics/ui/uiNum/FSADIGBOY19-312.png"));
		moneyTexture.push_back(&RES_MGR_TEXTURE.Get("graphics/ui/uiNum/FSADIGBOY19-313.png"));
		moneyTexture.push_back(&RES_MGR_TEXTURE.Get("graphics/ui/uiNum/FSADIGBOY19-314.png"));
		moneyTexture.push_back(&RES_MGR_TEXTURE.Get("graphics/ui/uiNum/FSADIGBOY19-315.png"));
		moneyTexture.push_back(&RES_MGR_TEXTURE.Get("graphics/ui/uiNum/FSADIGBOY19-316.png"));
		moneyTexture.push_back(&RES_MGR_TEXTURE.Get("graphics/ui/uiNum/FSADIGBOY19-317.png"));
		moneyTexture.push_back(&RES_MGR_TEXTURE.Get("graphics/ui/uiNum/FSADIGBOY19-318.png"));
	}

	for (int i = 0; i <= 24; ++i)
	{
		stateList.push_back(Empty);
	}

	invenCoil.SetTexture("graphics/ore/FSADIGBOY19-24.png");

}

void Inventory::Release()
{
	SpriteGo::Release();
}

void Inventory::Reset()
{
	SpriteGo::Reset();

	//인벤토리
	inventory.SetOrigin(Origins::TL);
	inventory.SetPosition(invenClose);

	invenName.SetOrigin({ -90.f, -18.f });
	invenName.SetPosition(inventory.GetPosition());

	moneyMenu.SetOrigin({ -60.f, -160.f });
	moneyMenu.SetPosition(inventory.GetPosition());

	invenKoong.SetOrigin({ -150.f, -65.f });
	invenKoong.SetPosition(inventory.GetPosition());

	//인벤토리 장착슬롯
	invenEquipHead.SetOrigin({ -225.f, -50.f });
	invenEquipHead.SetPosition(inventory.GetPosition());
	invenEquipDrill.SetOrigin({ -225.f, -85.f });
	invenEquipDrill.SetPosition(inventory.GetPosition());
	invenEquipFeet.SetOrigin({ -225.f, -120.f });
	invenEquipFeet.SetPosition(inventory.GetPosition());


	moneyUnit.setOrigin({ -245.f, -158.f });
	moneyUnit.setPosition(inventory.GetPosition());
	moneyTens.setOrigin({ -235.f, -158.f });
	moneyTens.setPosition(inventory.GetPosition());
	moneyHundreds.setOrigin({ -225.f, -158.f });
	moneyHundreds.setPosition(inventory.GetPosition());
	moneyThousands.setOrigin({ -215.f, -158.f });
	moneyThousands.setPosition(inventory.GetPosition());
	moneyTenThousands.setOrigin({ -205.f, -158.f });
	moneyTenThousands.setPosition(inventory.GetPosition());
	moneyHunThousands.setOrigin({ -195.f, -158.f });
	moneyHunThousands.setPosition(inventory.GetPosition());

	SetInventory();
}

void Inventory::Update(float dt)
{
	SpriteGo::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::I))
	{
		if (inventory.GetPosition() == invenClose)
		{
			inventory.SetPosition(invenOpen);
			for (int i = 0; i < invenCount.y; i++) // 6줄
			{
				for (int j = 0; j < invenCount.x; j++) //6칸
				{
					sf::Vector2f quadPos(invenSize.x * j + 45.f, invenSize.y * i + 185.f);
					invenLists[i * invenCount.x + j].SetPosition(invenOpen + quadPos);
				}
			}
		}
		else if (inventory.GetPosition() == invenOpen)
		{
			inventory.SetPosition(invenClose);
			for (int i = 0; i < invenCount.y; i++) // 6줄
			{
				for (int j = 0; j < invenCount.x; j++) //6칸
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

		//돈 숫자 스프라이트
		moneyUnit.setPosition(inventory.GetPosition());
		moneyTens.setPosition(inventory.GetPosition());
		moneyHundreds.setPosition(inventory.GetPosition());
		moneyThousands.setPosition(inventory.GetPosition());
		moneyTenThousands.setPosition(inventory.GetPosition());
		moneyHunThousands.setPosition(inventory.GetPosition());
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

	window.draw(moneyUnit);
	window.draw(moneyTens);
	window.draw(moneyHundreds);
	window.draw(moneyThousands);
	window.draw(moneyTenThousands);
	window.draw(moneyHunThousands);


	for (int a = 0; a < invenLists.size(); ++a)
	{
		invenLists[a].Draw(window);
	}

}
