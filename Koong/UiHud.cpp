#include "pch.h"
#include "UiHud.h"
#include "PlayerBody.h"

UiHud::UiHud(const std::string& name)
{
}

void UiHud::SetResolution(const sf::Vector2f resolution)
{
}

void UiHud::SetScore(int s)
{
}

void UiHud::SetMessage(const std::string& msg)
{
	textMessage.SetString(msg);
	textMessage.SetOrigin(Origins::MC);
}

void UiHud::SetMessageActive(bool active)
{
	if (active)
		textMessage.SetActive(true);
	else
		textMessage.SetActive(false);
}

void UiHud::SetHpBar(int hp, int max)
{
	float value = (float)hp / max;
	hpBar.SetScale({ hpBarSize.x * value, hpBarSize.y });
}

void UiHud::SetAirBar(int air, int maxair)
{
	float value = (float)air / maxair;

	// 1.0일때 0, 0.0일때 180
	float r = (1.f - value) * 180.0f;

	airBarColor.SetRotation(r);

	if (air > 60.f)
	{
		airBarColor.SetTexture(airBarBlue);
	}
	if (air < 60.f && air > 40.f)
	{
		airBarColor.SetTexture(airBarYellow);
	}
	if (air < 40.f)
	{
		airBarColor.SetTexture(airBarRed);
	}
}

void UiHud::SetInventory(sf::Vector2i& count, sf::Vector2f& size)
{
	invenLists.resize(count.x * count.y);

	for (int i = 0; i < count.y; i++) // 6줄
	{
		for (int j = 0; j < count.x; j++) // 6칸
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

void UiHud::SetInventoryActive()
{
	
}


void UiHud::Init()
{
	hud.SetTexture("graphics/ui/FSADIGBOY19-412.png");

	energy.SetTexture("graphics/ui/FSADIGBOY19-411.png");
	hpBar.SetTexture("graphics/ui/FSADIGBOY19-413.png");

	airText.SetTexture("graphics/ui/FSADIGBOY19-378.png");
	airBarColor.SetTexture("graphics/ui/FSADIGBOY19-375.png");
	airBarFrame1.SetTexture("graphics/ui/FSADIGBOY19-372.png"); //검은 배경
	airBarFrame2.SetTexture("graphics/ui/FSADIGBOY19-377.png"); //눈금

	quickMenu.SetTexture("graphics/ui/FSADIGBOY19-470.png");
	quickItem1.SetTexture("graphics/shop/FSADIGBOY19-48.png");
	quickItem2.SetTexture("graphics/shop/FSADIGBOY19-47.png");
	quickItem3.SetTexture("graphics/shop/FSADIGBOY19-51.png");

	//inventory.SetTexture("graphics/ui/FSADIGBOY19-319.png");

	//invenName.SetTexture("graphics/ui/FSADIGBOY19-320.png");
	//moneyMenu.SetTexture("graphics/ui/FSADIGBOY19-324.png");
	//invenKoong.SetTexture("graphics/ui/FSADIGBOY19-322.png");

	//invenEquipHead.SetTexture("graphics/ui/FSADIGBOY19-307.png");
	//invenEquipDrill.SetTexture("graphics/ui/FSADIGBOY19-307.png");
	//invenEquipFeet.SetTexture("graphics/ui/FSADIGBOY19-307.png");


}

void UiHud::Release()
{
}

void UiHud::Reset()
{
	sf::Vector2f windowSize = (sf::Vector2f)FRAMEWORK.GetWindowSize();

	player = dynamic_cast<PlayerBody*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));

	//체력과 산소게이지
	SetHpBar(player->GetHP(), player->GetMaxHP());
	SetAirBar(player->GetAir(), player->GetMaxAir());

	hud.SetOrigin(Origins::TR);
	hud.SetPosition({ windowSize.x + 10.f, -10.f });

	energy.SetOrigin(Origins::TR);
	energy.SetPosition({ windowSize.x * 0.945f, windowSize.y * 0.28f });

	hpBar.SetOrigin(Origins::TR);
	hpBar.SetPosition({ windowSize.x * 0.955f, windowSize.y * 0.315f });

	airText.SetOrigin(Origins::TR);
	airText.SetPosition({ windowSize.x * 0.926f, windowSize.y * 0.34f });

	airBarFrame1.SetOrigin(Origins::TR);
	airBarFrame1.SetPosition({ windowSize.x * 0.975f, windowSize.y * 0.34f });

	airBarColor.SetOrigin(Origins::TC);
	airBarColor.SetPosition({ windowSize.x * 0.887f, windowSize.y * 0.36f });

	airBarFrame2.SetOrigin(Origins::TR);
	airBarFrame2.SetPosition({ windowSize.x * 0.975f, windowSize.y * 0.34f });

	textMessage.SetW(fontK, L"한글출력테스트", 40, sf::Color::White);
	textMessage.SetPosition({ 0.f, 0.f });

	////인벤토리
	//inventory.SetOrigin(Origins::TL);
	//inventory.SetPosition(invenClose);

	//invenName.SetOrigin({ -90.f, -18.f });
	//invenName.SetPosition(inventory.GetPosition());

	//moneyMenu.SetOrigin({ -60.f, -160.f });
	//moneyMenu.SetPosition(inventory.GetPosition());

	//invenKoong.SetOrigin({ -150.f, -65.f });
	//invenKoong.SetPosition(inventory.GetPosition());

	////인벤토리 장착슬롯
	//invenEquipHead.SetOrigin({ -225.f, -50.f });
	//invenEquipHead.SetPosition(inventory.GetPosition());
	//invenEquipDrill.SetOrigin({ -225.f, -85.f });
	//invenEquipDrill.SetPosition(inventory.GetPosition());
	//invenEquipFeet.SetOrigin({ -225.f, -120.f });
	//invenEquipFeet.SetPosition(inventory.GetPosition());

	//SetInventory(invenCount, invenSize);

	quickMenu.SetOrigin(Origins::TC);
	quickMenu.SetPosition({ windowSize.x * 0.5f, 0.f });

	quickItem1.SetPosition({ windowSize.x * 0.336f, 3.f});
	quickItem2.SetPosition({ windowSize.x * 0.394f, 3.f });
	quickItem3.SetPosition({ windowSize.x * 0.446f, 3.f });
}

void UiHud::Update(float dt)
{
	SetHpBar(player->GetHP(), player->GetMaxHP());
	SetAirBar(player->GetAir(), player->GetMaxAir());

	//if (InputMgr::GetKeyDown(sf::Keyboard::I))
	//{
	//	if (inventory.GetPosition() == invenClose)
	//	{
	//		inventory.SetPosition(invenOpen);
	//		for (int i = 0; i < invenCount.y; i++) // 4줄
	//		{
	//			for (int j = 0; j < invenCount.x; j++) //6칸
	//			{
	//				sf::Vector2f quadPos(invenSize.x * j + 45.f, invenSize.y * i + 185.f);
	//				invenLists[i * invenCount.x + j].SetPosition(invenOpen + quadPos);
	//			}
	//		}
	//	}
	//	else if (inventory.GetPosition() == invenOpen)
	//	{
	//		inventory.SetPosition(invenClose);
	//		for (int i = 0; i < invenCount.y; i++) // 4줄
	//		{
	//			for (int j = 0; j < invenCount.x; j++) //6칸
	//			{
	//				sf::Vector2f quadPos(invenSize.x * j + 45.f, invenSize.y * i + 185.f);
	//				invenLists[i * invenCount.x + j].SetPosition(invenClose + quadPos);
	//			}
	//		}
	//	}
	//	invenName.SetPosition(inventory.GetPosition());
	//	invenKoong.SetPosition(inventory.GetPosition());
	//	moneyMenu.SetPosition(inventory.GetPosition());
	//	invenEquipHead.SetPosition(inventory.GetPosition());
	//	invenEquipDrill.SetPosition(inventory.GetPosition());
	//	invenEquipFeet.SetPosition(inventory.GetPosition());
	//}

	if (InputMgr::GetKeyDown(sf::Keyboard::Num1))
	{
		player->UseItem(1);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Num2))
	{
		player->UseItem(2);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Num3))
	{
		player->UseItem(3);
	}
}

void UiHud::Draw(sf::RenderWindow& window)
{
	
	airBarFrame1.Draw(window);
	airBarColor.Draw(window);

	airBarFrame2.Draw(window);

	hud.Draw(window);

	airText.Draw(window);

	hpBar.Draw(window);
	energy.Draw(window);

	/*inventory.Draw(window);
	invenName.Draw(window);
	moneyMenu.Draw(window);

	invenKoong.Draw(window);
	invenEquipHead.Draw(window);
	invenEquipDrill.Draw(window);
	invenEquipFeet.Draw(window);

	for (int a = 0; a < invenLists.size(); ++a)
	{
		invenLists[a].Draw(window);
	}*/

	//inven1.Draw(window);

	//textMessage.Draw(window);

	quickMenu.Draw(window);
	quickItem1.Draw(window);
	quickItem2.Draw(window);
	quickItem3.Draw(window);
}
