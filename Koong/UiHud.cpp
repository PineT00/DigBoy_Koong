#include "pch.h"
#include "UiHud.h"
#include "PlayerBody.h"
#include "Inventory.h"
#include "Shop.h"

UiHud::UiHud(const std::string& name)
{
}

void UiHud::SetResolution(const sf::Vector2f resolution)
{
}

void UiHud::SetScore(int s)
{
}

void UiHud::SetMessage(const std::wstring& msg)
{
	textMessage.SetW(fontK, msg, 20, sf::Color::Black);
}

void UiHud::SetMessageActive(bool active)
{
	if (active)
	{
		bubble.SetActive(true);
		textMessage.SetActive(true);
	}
	else
	{
		bubble.SetActive(false);
		textMessage.SetActive(false);
	}
}

void UiHud::SetHpBar(int hp, int max)
{
	float value = (float)hp / max;
	hpBar.SetScale({ hpBarSize.x * value, hpBarSize.y });
}

void UiHud::SetAirBar(int air, int maxair)
{
	float value = (float)air / maxair;

	// 1.0¿œ∂ß 0, 0.0¿œ∂ß 180
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

void UiHud::OpenShop()
{
	if (shopHud.GetPosition() == shopClose)
	{
		shopHud.SetPosition(shopOpen);
		shopBack.SetPosition(shopOpen);
		for (int i = 0; i < shopCount.y; i++) // 7¡Ÿ
		{
			for (int j = 0; j < shopCount.x; j++) //3ƒ≠
			{
				sf::Vector2f quadPos(shopSize.x * j + 52.f, shopSize.y * i + 180.f);
				shopList[i * shopCount.x + j].SetPosition(shopOpen + quadPos);

				quadPos = { shopSize.x * j + 55.f, shopSize.y * i + 182.f };
				shopIconList[i * shopCount.x + j].SetPosition(shopOpen + quadPos);

				quadPos = { shopSize.x * j + 92.f, shopSize.y * i + 185.f };
				shopNameList[i * shopCount.x + j].SetPosition(shopOpen + quadPos);

				quadPos = { shopSize.x * j + 90.f, shopSize.y * i + 200.f };
				shopPriceList[i * shopCount.x + j].SetPosition(shopOpen + quadPos);
			}
		}

	}
	else if (shopHud.GetPosition() == shopOpen)
	{
		SetMessageActive(false);
		shopHud.SetPosition(shopClose);
		shopBack.SetPosition(shopClose);
		for (int i = 0; i < shopCount.y; i++) // 7¡Ÿ
		{
			for (int j = 0; j < shopCount.x; j++) //3ƒ≠
			{
				sf::Vector2f quadPos(shopSize.x * j + 52.f, shopSize.y * i + 180.f);
				shopList[i * shopCount.x + j].SetPosition(shopClose + quadPos);

				quadPos = { shopSize.x * j + 55.f, shopSize.y * i + 182.f };
				shopIconList[i * shopCount.x + j].SetPosition(shopClose + quadPos);

				quadPos = { shopSize.x * j + 92.f, shopSize.y * i + 185.f };
				shopNameList[i * shopCount.x + j].SetPosition(shopClose + quadPos);

				quadPos = { shopSize.x * j + 90.f, shopSize.y * i + 200.f };
				shopPriceList[i * shopCount.x + j].SetPosition(shopClose + quadPos);
			}
		}
	}

	buttonSell.SetPosition(shopHud.GetPosition());
	phd.SetPosition(shopHud.GetPosition());
	phdGlass.SetPosition(shopHud.GetPosition());

	upScroll.SetPosition(shopHud.GetPosition());
	downScroll.SetPosition(shopHud.GetPosition());



}


void UiHud::ShopScrollUp()
{
	for (int i = 0; i < shopCount.y; i++) // 7¡Ÿ
	{
		for (int j = 0; j < shopCount.x; j++) //3ƒ≠
		{
			sf::Vector2f quadPos(shopSize.x * j + 52.f, shopSize.y * i + 180.f);
			shopList[i * shopCount.x + j].SetPosition(shopOpenUp + quadPos);

			quadPos = { shopSize.x * j + 55.f, shopSize.y * i + 182.f };
			shopIconList[i * shopCount.x + j].SetPosition(shopOpenUp + quadPos);

			quadPos = { shopSize.x * j + 92.f, shopSize.y * i + 185.f };
			shopNameList[i * shopCount.x + j].SetPosition(shopOpenUp + quadPos);

			quadPos = { shopSize.x * j + 90.f, shopSize.y * i + 200.f };
			shopPriceList[i * shopCount.x + j].SetPosition(shopOpenUp + quadPos);
		}
	}
}

void UiHud::ShopScrollDown()
{
	for (int i = 0; i < shopCount.y; i++) // 7¡Ÿ
	{
		for (int j = 0; j < shopCount.x; j++) //3ƒ≠
		{
			sf::Vector2f quadPos(shopSize.x * j + 52.f, shopSize.y * i + 180.f);
			shopList[i * shopCount.x + j].SetPosition(shopOpenDown + quadPos);

			quadPos = { shopSize.x * j + 55.f, shopSize.y * i + 182.f };
			shopIconList[i * shopCount.x + j].SetPosition(shopOpenDown + quadPos);

			quadPos = { shopSize.x * j + 92.f, shopSize.y * i + 185.f };
			shopNameList[i * shopCount.x + j].SetPosition(shopOpenDown + quadPos);

			quadPos = { shopSize.x * j + 90.f, shopSize.y * i + 200.f };
			shopPriceList[i * shopCount.x + j].SetPosition(shopOpenDown + quadPos);
		}
	}
}

void UiHud::BuyItem(int num)
{
	if (priceList[num] > inventory->money)
	{
		SetMessageActive(true);
		return;
	}

	switch (num)
	{
	case 0: 
		inventory->SetInvenItem(Inventory::InvenState::HealKit, 1);
		inventory->SetInvenMoney(priceList[0], -1);
		break;
	case 1:
		inventory->SetInvenItem(Inventory::InvenState::AirCap, 1);
		inventory->SetInvenMoney(priceList[1], -1);
		break;
	case 2:
		inventory->SetInvenItem(Inventory::InvenState::AirCapSuper, 1);
		inventory->SetInvenMoney(priceList[2], -1);
		break;
	case 3:
		inventory->SetInvenItem(Inventory::InvenState::Bomb, 1);
		inventory->SetInvenMoney(priceList[3], -1);
		break;
	case 4:
		inventory->SetInvenItem(Inventory::InvenState::Nuclear, 1);
		inventory->SetInvenMoney(priceList[4], -1);
		break;
	case 5:
		inventory->SetInvenItem(Inventory::InvenState::Dynamite, 1);
		inventory->SetInvenMoney(priceList[5], -1);
		break;
	case 6:
		inventory->SetInvenMoney(priceList[6], -1);
		inventory->cap1 = 1;
		break;
	case 7:
		inventory->SetInvenMoney(priceList[7], -1);
		inventory->cap2 = 1;
		break;
	case 8:
		inventory->SetInvenMoney(priceList[8], -1);
		inventory->cap3 = 1;
		break;
	case 9:
		inventory->SetInvenMoney(priceList[9], -1);
		inventory->cap4 = 1;
		break;
	case 10:
		inventory->SetInvenMoney(priceList[10], -1);
		inventory->cap5 = 1;
		break;
	case 11:
		inventory->SetInvenMoney(priceList[11], -1);
		inventory->drill1 = 1;
		break;
	case 12:
		inventory->SetInvenMoney(priceList[12], -1);
		inventory->drill2 = 1;
		break;
	case 13:
		inventory->SetInvenMoney(priceList[13], -1);
		inventory->drill3 = 1;
		break;
	case 14:
		inventory->SetInvenMoney(priceList[14], -1);
		inventory->drill4 = 1;
		break;
	case 15:
		inventory->SetInvenMoney(priceList[15], -1);
		inventory->drill5 = 1;
		break;
	case 16:
		inventory->SetInvenMoney(priceList[16], -1);
		inventory->shoe1 = 1;
		break;
	case 17:
		inventory->SetInvenMoney(priceList[17], -1);
		inventory->shoe2 = 1;
		break;
	case 18:
		inventory->SetInvenMoney(priceList[18], -1);
		inventory->shoe3 = 1;
		break;
	case 19:
		inventory->SetInvenMoney(priceList[19], -1);
		inventory->shoe4 = 1;
		break;
	case 20:
		inventory->SetInvenMoney(priceList[20], -1);
		inventory->shoe5 = 1;
		break;
	}

	player->SetCap();
	player->SetDrillPower();
	player->SetShoes();
	inventory->SetPlayerInfo();

}

void UiHud::Init()
{
	//bill.setTexture(RES_MGR_TEXTURE.Get("graphics/shop/FSADIGBOY19-292.png"));
	animator.SetTarget(&bill);
	{
		AnimationClip clip;
		clip.id = "Billing";
		clip.fps = 12;
		clip.loopTypes = AnimationLoopTypes::Single;
		clip.frames.push_back({ "graphics/shop/FSADIGBOY19-292.png", {0, 0, 330, 450} });
		clip.frames.push_back({ "graphics/shop/FSADIGBOY19-302.png", {0, 0, 330, 450} });
		clip.frames.push_back({ "graphics/shop/FSADIGBOY19-303.png", {0, 0, 330, 450} });
		animator.AddClip(clip);
	}

	hud.SetTexture("graphics/ui/FSADIGBOY19-412.png");

	energy.SetTexture("graphics/ui/FSADIGBOY19-411.png");
	hpBar.SetTexture("graphics/ui/FSADIGBOY19-413.png");

	airText.SetTexture("graphics/ui/FSADIGBOY19-378.png");
	airBarColor.SetTexture("graphics/ui/FSADIGBOY19-375.png");
	airBarFrame1.SetTexture("graphics/ui/FSADIGBOY19-372.png"); //∞À¿∫ πË∞Ê
	airBarFrame2.SetTexture("graphics/ui/FSADIGBOY19-377.png"); //¥´±›

	quickMenu.SetTexture("graphics/ui/FSADIGBOY19-470.png");
	quickItem1.SetTexture("graphics/shop/item/FSADIGBOY19-item1.png");
	quickItem2.SetTexture("graphics/shop/item/FSADIGBOY19-item2.png");
	quickItem3.SetTexture("graphics/shop/item/FSADIGBOY19-item4.png");
	quickItem4.SetTexture("graphics/shop/item/FSADIGBOY19-item6.png");

	pointer.setFillColor(sf::Color::Red);
	pointer.setOrigin({ 0.5f, 0.5f });
	pointer.setSize({ 1.f,1.f });
	pointer.setPosition({ 0.f, 0.f });

	//ªÛ¡°∏ﬁ¥∫
	shopHud.SetTexture("graphics/shop/FSADIGBOY19-shopMenuF.png");
	shopBack.SetTexture("graphics/shop/FSADIGBOY19-shopMenuB.png");
	buttonSell.SetTexture("graphics/ui/FSADIGBOY19-sell.png");

	phd.SetTexture("graphics/shop/FSADIGBOY19-phd.png");
	phdGlass.SetTexture("graphics/shop/FSADIGBOY19-phdGlass.png");

	upScroll.SetTexture("graphics/shop/FSADIGBOY19-367.png");
	downScroll.SetTexture("graphics/shop/FSADIGBOY19-369.png");

	bubble.SetTexture("graphics/bubble/FSADIGBOY19-277.png");
}

void UiHud::Release()
{
}

void UiHud::Reset()
{
	sf::Vector2f windowSize = (sf::Vector2f)FRAMEWORK.GetWindowSize();

	player = dynamic_cast<PlayerBody*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));
	inventory = dynamic_cast<Inventory*>(SCENE_MGR.GetCurrentScene()->FindGo("Inventory"));
	shop = dynamic_cast<Shop*>(SCENE_MGR.GetCurrentScene()->FindGo("Shop"));

	//√º∑¬∞˙ ªÍº“∞‘¿Ã¡ˆ
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

	quickMenu.SetOrigin(Origins::TC);
	quickMenu.SetPosition({ windowSize.x * 0.5f, 0.f });

	quickItem1.SetPosition({ windowSize.x * 0.336f, 3.f});
	quickItem2.SetPosition({ windowSize.x * 0.394f, 3.f });
	quickItem3.SetPosition({ windowSize.x * 0.446f, 3.f });
	quickItem4.SetPosition({ windowSize.x * 0.500f, 3.f });

	bill.setPosition({-10.f, 50.f});

	//ªÛ¡°∏ﬁ¥∫
	shopHud.SetOrigin(Origins::TL);
	shopHud.SetPosition(shopClose);
	shopBack.SetOrigin(Origins::TL);
	shopBack.SetPosition(shopClose);

	buttonSell.SetOrigin({-10,-45});
	buttonSell.SetPosition(shopClose);

	phd.SetOrigin({-200.f,-30.f});
	phd.SetPosition(shopClose);
	phdGlass.SetOrigin({ -200.f,-30.f });
	phdGlass.SetPosition(shopClose);

	bubble.SetOrigin({ -60.f, -35.f });
	bubble.SetPosition(shopOpen);
	textMessage.SetOrigin({ -90.f, -75.f });
	textMessage.SetPosition(shopOpen);

	SetMessage(L"µ∑¿Ã ∫Œ¡∑«ÿ!"); 
	SetMessageActive(false);

	shopList.resize(shopCount.x * shopCount.y);
	shopIconList.resize(shopCount.x * shopCount.y);
	shopNameList.resize(shopCount.x * shopCount.y);
	shopPriceList.resize(shopCount.x * shopCount.y);

	for (int i = 0; i < shopCount.y; i++) // 7¡Ÿ
	{
		for (int j = 0; j < shopCount.x; j++) //3ƒ≠
		{
			shopList[i * shopCount.x + j].SetTexture("graphics/shop/FSADIGBOY19-214.png");
			shopIconList[i * shopCount.x + j].SetTexture("graphics/shop/item/FSADIGBOY19-item1.png");
			shopNameList[i * shopCount.x + j].SetW(fontK, L"«Ÿ∆¯≈∫", menuStringSize, sf::Color::White);
			shopPriceList[i * shopCount.x + j].SetW(fontK, L"\\1000", menuStringSize, sf::Color::Yellow);

			sf::Vector2f quadPos(shopSize.x * j + 45.f, shopSize.y * i + 185.f);
			shopList[i * shopCount.x + j].SetPosition(shopClose + quadPos);
			quadPos = { shopSize.x * j + 55.f, shopSize.y * i + 182.f };
			shopIconList[i * shopCount.x + j].SetPosition(shopClose + quadPos);
			quadPos = { shopSize.x * j + 88.f, shopSize.y * i + 195.f };
			shopNameList[i * shopCount.x + j].SetPosition(shopClose + quadPos);
			quadPos = { shopSize.x * j + 85.f, shopSize.y * i + 205.f };
			shopPriceList[i * shopCount.x + j].SetPosition(shopClose + quadPos);

		}
	}

	for(int i = 0; i <= 20; ++i)
	{
		shopIconList[i].SetTexture("graphics/shop/item/FSADIGBOY19-item" + std::to_string(i+1) + ".png");
	}

	//æ∆¿Ã≈€¿Ã∏ß
	{
		shopNameList[0].SetW(fontK, L"±∏±ﬁªÛ¿⁄", menuStringSize, sf::Color::White);
		shopNameList[1].SetW(fontK, L"ªÍº“ƒ∏Ω∂(º“)", menuStringSize, sf::Color::White);
		shopNameList[2].SetW(fontK, L"ªÍº“ƒ∏Ω∂(¥Î)", menuStringSize, sf::Color::White);
		shopNameList[3].SetW(fontK, L"∆¯≈∫", menuStringSize, sf::Color::White);
		shopNameList[4].SetW(fontK, L"øÔ∆Æ∂Û∆¯≈∫", menuStringSize, sf::Color::White);
		shopNameList[5].SetW(fontK, L"¥Ÿ¿Ã≥™∏∂¿Ã∆Æ", menuStringSize, sf::Color::White);
		shopNameList[6].SetW(fontK, L"≥™¿ÃΩ∫ƒ∏", menuStringSize, sf::Color::White);
		shopNameList[7].SetW(fontK, L"Ω¥∆€ƒ∏", menuStringSize, sf::Color::White);
		shopNameList[8].SetW(fontK, L"∏ﬁ∞°ƒ∏", menuStringSize, sf::Color::White);
		shopNameList[9].SetW(fontK, L"øÔ∆Æ∂Ûƒ∏", menuStringSize, sf::Color::White);
		shopNameList[10].SetW(fontK, L"∑πæÓƒ∏", menuStringSize, sf::Color::White);
		shopNameList[11].SetW(fontK, L"≥™¿ÃΩ∫µÂ∏±", menuStringSize, sf::Color::White);
		shopNameList[12].SetW(fontK, L"Ω¥∆€µÂ∏±", menuStringSize, sf::Color::White);
		shopNameList[13].SetW(fontK, L"∏ﬁ∞°µÂ∏±", menuStringSize, sf::Color::White);
		shopNameList[14].SetW(fontK, L"∞ÒµÂµÂ∏±", menuStringSize, sf::Color::White);
		shopNameList[15].SetW(fontK, L"∑πæÓµÂ∏±", menuStringSize, sf::Color::White);
		shopNameList[16].SetW(fontK, L"≥™¿ÃΩ∫Ω¥¡Ó", menuStringSize, sf::Color::White);
		shopNameList[17].SetW(fontK, L"Ω¥∆€Ω¥¡Ó", menuStringSize, sf::Color::White);
		shopNameList[18].SetW(fontK, L"∏ﬁ∞°Ω¥¡Ó", menuStringSize, sf::Color::White);
		shopNameList[19].SetW(fontK, L"øÔ∆Æ∂ÛΩ¥¡Ó", menuStringSize, sf::Color::White);
		shopNameList[20].SetW(fontK, L"∑πæÓΩ¥¡Ó", menuStringSize, sf::Color::White);
	}

	//æ∆¿Ã≈€∞°∞›∏ÆΩ∫∆Æ
	{
		priceList.push_back(1000);
		priceList.push_back(500);
		priceList.push_back(2000);
		priceList.push_back(100);
		priceList.push_back(300);
		priceList.push_back(1000);
		priceList.push_back(5000);
		priceList.push_back(10000);
		priceList.push_back(20000);
		priceList.push_back(50000);
		priceList.push_back(10000);
		priceList.push_back(5000);
		priceList.push_back(10000);
		priceList.push_back(20000);
		priceList.push_back(50000);
		priceList.push_back(10000);
		priceList.push_back(5000);
		priceList.push_back(10000);
		priceList.push_back(20000);
		priceList.push_back(50000);
		priceList.push_back(10000);
	}


	//æ∆¿Ã≈€∞°∞›
	for (int i = 0; i < 21; ++i)
	{
		shopPriceList[i].SetW(fontK, std::to_wstring(priceList[i]), 13, sf::Color::Yellow);
	}

	upScroll.SetOrigin({ -347.f,-179.f });
	downScroll.SetOrigin({ -347.f,-376.f });
	upScroll.SetPosition(shopClose);
	downScroll.SetPosition(shopClose);
}

void UiHud::Update(float dt)
{
	animator.Update(dt);

	sf::Vector2i mousePos = (sf::Vector2i)InputMgr::GetMousePos();
	sf::Vector2f mouseUiPos = SCENE_MGR.GetCurrentScene()->ScreenToUi(mousePos);
	
	pointer.setPosition(mouseUiPos);

	SetHpBar(player->GetHP(), player->GetMaxHP());
	SetAirBar(player->GetAir(), player->GetMaxAir());

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
	
	
	sf::FloatRect bound = shop->NPC.GetGlobalBounds();
	sf::FloatRect playerBound = player->GetSpriteGlobalBound();

	if (bound.intersects(playerBound) && InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		inventory->OpenInven();
		OpenShop();
	}

	if (buttonSell.GetGlobalBounds().intersects(pointer.getGlobalBounds()))
	{
		if (!billOn && InputMgr::GetMouseButtonDown(sf::Mouse::Left))
		{
			billOn = true;
			inventory->SellAll();
			bill.setPosition({ -10.f, 50.f });
			animator.Play("Billing");
		}
		
	}

	if (shopHud.GetPosition() == shopOpen)
	{
		for (int i = 0; i < shopCount.y; i++) // 7¡Ÿ
		{
			for (int j = 0; j < shopCount.x; j++) //3ƒ≠
			{
				if (shopList[i * shopCount.x + j].GetGlobalBounds().intersects(pointer.getGlobalBounds()))
				{
					//«ÿ¥Áƒ≠¿« º≥∏Ì ∏ﬁº“µÂ
					if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
					{
						BuyItem(i * shopCount.x + j);
					}

				}

			}
		}
	}

	if (buttonSell.GetGlobalBounds().intersects(pointer.getGlobalBounds()))
	{
		if (!billOn && InputMgr::GetMouseButtonDown(sf::Mouse::Left))
		{
			billOn = true;
			inventory->SellAll();
			bill.setPosition({ -10.f, 50.f });
			animator.Play("Billing");
		}
	}

	if (billOn && InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		billOn = false;
	}

	if (upScroll.GetGlobalBounds().intersects(pointer.getGlobalBounds()))
	{
		if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
		{
			ShopScrollUp();
		}
	}
	else if (downScroll.GetGlobalBounds().intersects(pointer.getGlobalBounds()))
	{
		if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
		{
			ShopScrollDown();
		}
	}

	//∏ﬁΩ√¡ˆ√¢¿Ã ∂∞¿÷¥¬ Ω√∞£
	if (textMessage.GetActive())
	{
		textTime += dt;
		if (textTimer < textTime)
		{
			SetMessageActive(false);
			textTime = 0.f;
		}
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


	quickMenu.Draw(window);
	quickItem1.Draw(window);
	quickItem2.Draw(window);
	quickItem3.Draw(window);
	quickItem4.Draw(window);


	//ªÛ¡°∏ﬁ¥∫

	shopBack.Draw(window);

	for (int a = 0; a < shopList.size(); ++a)
	{
		shopList[a].Draw(window);
	}

	for (int a = 0; a < shopIconList.size(); ++a)
	{
		shopIconList[a].Draw(window);
	}
	for (int a = 0; a < shopNameList.size(); ++a)
	{
		shopNameList[a].Draw(window);
	}
	for (int a = 0; a < shopNameList.size(); ++a)
	{
		shopPriceList[a].Draw(window);
	}

	shopHud.Draw(window);
	buttonSell.Draw(window); 

	phd.Draw(window);
	phdGlass.Draw(window);


	if (textMessage.GetActive())
	{
		bubble.Draw(window);
		textMessage.Draw(window);
	}
	
	upScroll.Draw(window);
	downScroll.Draw(window);

	if(billOn)
	{
		window.draw(bill);
	}

	window.draw(pointer);
	
}
