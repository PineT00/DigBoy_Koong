#include "pch.h"
#include "Inventory.h"
#include "PlayerBody.h"

Inventory::Inventory(const std::string& name)
	:SpriteGo(name)
{
}

void Inventory::SetPlayerInfo()
{
	hpWstring = std::to_wstring(player->GetHP());
	decimalPos = hpWstring.find(L".");
	hpWstring = hpWstring.substr(0, decimalPos); // 소수점 직전까지만 출력

	hpMaxWstring = std::to_wstring(player->GetMaxHP());
	decimalPos = hpMaxWstring.find(L".");
	hpMaxWstring = hpMaxWstring.substr(0, decimalPos);

	airWstring = std::to_wstring(player->GetAir());
	decimalPos = airWstring.find(L".");
	airWstring = airWstring.substr(0, decimalPos);

	airMaxWstring = std::to_wstring(player->GetMaxAir());
	decimalPos = airMaxWstring.find(L".");
	airMaxWstring = airMaxWstring.substr(0, decimalPos);

	drillWstring = std::to_wstring(player->GetDrillPower());
	decimalPos = drillWstring.find(L".");
	drillWstring = drillWstring.substr(0, decimalPos);

	boosterWstring = std::to_wstring(player->GetBooster());
	decimalPos = boosterWstring.find(L".");
	boosterWstring = boosterWstring.substr(0, decimalPos);

	armorWstring = std::to_wstring(player->GetArmor());
	decimalPos = armorWstring.find(L".");
	armorWstring = armorWstring.substr(0, decimalPos);

	energyText.SetW(fontK, L"ENERGY  " + hpWstring + L"/" + hpMaxWstring, 11, sf::Color::Red);
	airText.SetW(fontK, L"AIR  " + airWstring + L"/" + airMaxWstring, 11, sf::Color::Cyan);
	digPowerText.SetW(fontK, L"굴착력 :   " + drillWstring, 15, sf::Color::White);
	boosterText.SetW(fontK, L"부스터 :   " + boosterWstring, 15, sf::Color::White);
	armorText.SetW(fontK, L"방어력 :   " + armorWstring, 15, sf::Color::White);
}

void Inventory::OpenInven()
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
				invenIconList[i * invenCount.x + j].SetPosition(invenOpen + quadPos);
				invenNumList[i * invenCount.x + j].SetPosition(invenOpen + quadPos);
			}
		}
		SetPlayerInfo();
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
				invenIconList[i * invenCount.x + j].SetPosition(invenClose + quadPos);
				invenNumList[i * invenCount.x + j].SetPosition(invenClose + quadPos);
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

	//플레이어 정보
	textBack.SetPosition(inventory.GetPosition());
	energyText.SetPosition(inventory.GetPosition());
	airText.SetPosition(inventory.GetPosition());
	digPowerText.SetPosition(inventory.GetPosition());
	boosterText.SetPosition(inventory.GetPosition());
	armorText.SetPosition(inventory.GetPosition());
}

void Inventory::SellAll()
{
	std::cout << "광석정산" << std::endl;
	SetInvenMoney((coilNum * coilPrice), 1);
	coilNum = 0;

	SetInvenMoney((bronzeNum * bronzePrice), 1);
	bronzeNum = 0;

	SetInvenMoney((silverNum * silverPrice), 1);
	silverNum = 0;

	SetInvenMoney((goldNum * goldPrice), 1);
	goldNum = 0;

	SetInvenOre(Empty);
	std::cout << "현재 보유금 : " << money << std::endl;
}


void Inventory::SetInvenItem(InvenState state, bool Get)
{
	bool set = false;

	if (Get)
	{
		for (int i = 0; i < invenCount.y; i++) // 6줄
		{
			for (int j = 0; j < invenCount.x; j++) // 6칸
			{
				if (stateList[i * invenCount.x + j] == Empty)
				{
					switch (state)
					{
					case HealKit:
						invenIconList[i * invenCount.x + j].SetTexture("graphics/shop/item/FSADIGBOY19-item1.png");
						stateList[i * invenCount.x + j] = HealKit;
						set = true;
						break;
					case AirCap:
						invenIconList[i * invenCount.x + j].SetTexture("graphics/shop/item/FSADIGBOY19-item2.png");
						stateList[i * invenCount.x + j] = AirCap;
						set = true;
						break;
					case AirCapSuper:
						invenIconList[i * invenCount.x + j].SetTexture("graphics/shop/item/FSADIGBOY19-item3.png");
						stateList[i * invenCount.x + j] = AirCapSuper;
						set = true;
						break;
					case Bomb:
						invenIconList[i * invenCount.x + j].SetTexture("graphics/shop/item/FSADIGBOY19-item4.png");
						stateList[i * invenCount.x + j] = Bomb;
						set = true;
						break;

					case Nuclear:
						invenIconList[i * invenCount.x + j].SetTexture("graphics/shop/item/FSADIGBOY19-item5.png");
						stateList[i * invenCount.x + j] = Nuclear;
						set = true;
						break;

					case Dynamite:
						invenIconList[i * invenCount.x + j].SetTexture("graphics/shop/item/FSADIGBOY19-item6.png");
						stateList[i * invenCount.x + j] = Dynamite;
						set = true;
						break;
					default:
						break;
					}
					break;
				}

				if (set)
				{
					break;
				}

			}
			if (set)
			{
				break;
			}
		}
	}
	else
	{
		for (int i = 0; i < invenCount.y; i++) // 6줄
		{
			for (int j = 0; j < invenCount.x; j++) // 6칸
			{
				if (stateList[i * invenCount.x + j] == state)
				{
					switch (state)
					{
					case HealKit:
						invenIconList[i * invenCount.x + j].SetTexture("graphics/ore/FSADIGBOY19-empty.png");
						stateList[i * invenCount.x + j] = Empty;
						set = true;
						break;
					case AirCap:
						invenIconList[i * invenCount.x + j].SetTexture("graphics/ore/FSADIGBOY19-empty.png");
						stateList[i * invenCount.x + j] = Empty;
						set = true;
						break;
					case AirCapSuper:
						invenIconList[i * invenCount.x + j].SetTexture("graphics/ore/FSADIGBOY19-empty.png");
						stateList[i * invenCount.x + j] = Empty;
						set = true;
						break;
					case Bomb:
						invenIconList[i * invenCount.x + j].SetTexture("graphics/ore/FSADIGBOY19-empty.png");
						stateList[i * invenCount.x + j] = Empty;
						set = true;
						break;

					case Nuclear:
						invenIconList[i * invenCount.x + j].SetTexture("graphics/ore/FSADIGBOY19-empty.png");
						stateList[i * invenCount.x + j] = Empty;
						set = true;
						break;

					case Dynamite:
						invenIconList[i * invenCount.x + j].SetTexture("graphics/ore/FSADIGBOY19-empty.png");
						stateList[i * invenCount.x + j] = Empty;
						set = true;
						break;
					default:
						break;
					}
					break;
				}

				if (set)
				{
					break;
				}

			}
			if (set)
			{
				break;
			}
		}
	}
	
}

void Inventory::SetInvenOre(InvenState state)
{
	bool set = false;

	for (int i = 0; i < invenCount.y; i++) // 6줄
	{
		for (int j = 0; j < invenCount.x; j++) // 6칸
		{
			//중복부터 찾기(있으면 숫자만 올리기)
			if (stateList[i * invenCount.x + j] == state) 
			{
				switch (state) //5개되면 full상태로 만들고 인벤넘버 초기화
				{
				case Coil:
					invenCoilNum += 1;
					invenNumList[i * invenCount.x + j].SetTexture("graphics/ui/uiNum/mini" + std::to_string(invenCoilNum) + ".png"); //숫자바꾸기
					set = true;

					if (invenCoilNum >= 5)
					{
						stateList[i * invenCount.x + j] = Full;
						invenCoilNum = 0;
					}

					break;
				case Bronze:
					invenBronzeNum += 1;
					invenNumList[i * invenCount.x + j].SetTexture("graphics/ui/uiNum/mini" + std::to_string(invenBronzeNum) + ".png"); //숫자바꾸기
					set = true;

					if (invenBronzeNum >= 5)
					{
						stateList[i * invenCount.x + j] = Full;
						invenBronzeNum = 0;
					}

					break;
				case Silver:
					invenSilverNum += 1;
					invenNumList[i * invenCount.x + j].SetTexture("graphics/ui/uiNum/mini" + std::to_string(invenSilverNum) + ".png"); //숫자바꾸기
					set = true;

					if (invenSilverNum >= 5)
					{
						stateList[i * invenCount.x + j] = Full;
						invenSilverNum = 0;
					}
					break;
				case Gold:
					invenGoldNum += 1;
					invenNumList[i * invenCount.x + j].SetTexture("graphics/ui/uiNum/mini" + std::to_string(invenGoldNum) + ".png"); //숫자바꾸기
					set = true;

					if (invenGoldNum >= 5)
					{
						stateList[i * invenCount.x + j] = Full;
						invenGoldNum = 0;
					}
					break;
				default:
					break;
				}

				if (set)
				{
					return;
				}
			}
		}
	}




	for (int i = 0; i < invenCount.y; i++) // 6줄
	{
		for (int j = 0; j < invenCount.x; j++) // 6칸
		{

			if (state == Empty) //광물 모두비우기(정산)
			{
				switch (stateList[i * invenCount.x + j])
				{
				case Coil:
					invenCoilNum = 0;
					invenNumList[i * invenCount.x + j].SetTexture("graphics/ore/FSADIGBOY19-empty.png");
					invenIconList[i * invenCount.x + j].SetTexture("graphics/ore/FSADIGBOY19-empty.png");
					stateList[i * invenCount.x + j] = Empty;
					break;
				case Bronze:
					invenBronzeNum = 0;
					invenNumList[i * invenCount.x + j].SetTexture("graphics/ore/FSADIGBOY19-empty.png");
					invenIconList[i * invenCount.x + j].SetTexture("graphics/ore/FSADIGBOY19-empty.png");
					stateList[i * invenCount.x + j] = Empty;
					break;
				case Silver:
					invenSilverNum = 0;
					invenNumList[i * invenCount.x + j].SetTexture("graphics/ore/FSADIGBOY19-empty.png");
					invenIconList[i * invenCount.x + j].SetTexture("graphics/ore/FSADIGBOY19-empty.png");
					stateList[i * invenCount.x + j] = Empty;
					break;
				case Gold:
					invenGoldNum = 0;
					invenNumList[i * invenCount.x + j].SetTexture("graphics/ore/FSADIGBOY19-empty.png");
					invenIconList[i * invenCount.x + j].SetTexture("graphics/ore/FSADIGBOY19-empty.png");
					stateList[i * invenCount.x + j] = Empty;
					break;
				case Full:
					invenNumList[i * invenCount.x + j].SetTexture("graphics/ore/FSADIGBOY19-empty.png");
					invenIconList[i * invenCount.x + j].SetTexture("graphics/ore/FSADIGBOY19-empty.png");
					stateList[i * invenCount.x + j] = Empty;

				default:
					break;
				}
			}

			//빈칸에 광물채우기
			else if (stateList[i * invenCount.x + j] == Empty)
			{
				switch (state)
				{
				case Coil:
					invenCoilNum += 1;
					invenIconList[i * invenCount.x + j].SetTexture("graphics/ore/FSADIGBOY19-24.png");
					invenNumList[i * invenCount.x + j].SetTexture("graphics/ui/uiNum/mini" + std::to_string(invenCoilNum) + ".png");
					stateList[i * invenCount.x + j] = Coil;
					set = true;
					break;
				case Bronze:
					invenBronzeNum += 1;
					invenIconList[i * invenCount.x + j].SetTexture("graphics/ore/FSADIGBOY19-23.png");
					invenNumList[i * invenCount.x + j].SetTexture("graphics/ui/uiNum/mini" + std::to_string(invenBronzeNum) + ".png");
					stateList[i * invenCount.x + j] = Bronze;
					set = true;
					break;
				case Silver:
					invenSilverNum += 1;
					invenIconList[i * invenCount.x + j].SetTexture("graphics/ore/FSADIGBOY19-22.png");
					invenNumList[i * invenCount.x + j].SetTexture("graphics/ui/uiNum/mini" + std::to_string(invenSilverNum) + ".png");
					stateList[i * invenCount.x + j] = Silver;
					set = true;
					break;
				case Gold:
					invenGoldNum += 1;
					invenIconList[i * invenCount.x + j].SetTexture("graphics/ore/FSADIGBOY19-21.png");
					invenNumList[i * invenCount.x + j].SetTexture("graphics/ui/uiNum/mini" + std::to_string(invenGoldNum) + ".png");
					stateList[i * invenCount.x + j] = Gold;
					set = true;
					break;
				default:
					break;
				}
				break;
			}

			if (set)
			{
				break;
			}
		}	
		if (set)
		{
			break;
		}

	}
}

void Inventory::SetInvenMoney(int coin, int state)
{


	if (state == 1)
	{
		money += coin;
	}
	else if (state == -1)
	{
		money -= coin;
	}
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

void Inventory::LoadInventory(const std::string& filename)
{
	std::ifstream file(filename);
	std::string line;


	if (file.is_open())
	{
		std::getline(file, line);

		if (std::getline(file, line))
		{
			std::istringstream iss(line);
			std::string token;

			while (std::getline(iss, token, ','))
			{
				int value = std::stoi(token);
				invenSaveList.push_back(value);
			}
		}

		file.close();
	}
	else
	{
		std::cout << "파일을 열 수 없습니다." << std::endl;
	}

	money = invenSaveList[10];
	coilNum = invenSaveList[6];
	bronzeNum = invenSaveList[7];
	silverNum = invenSaveList[8];
	goldNum = invenSaveList[9];

	SetInvenMoney(0, 0);

	for (int i = 0; i < coilNum; ++i)
	{
		SetInvenOre(Inventory::InvenState::Coil);
	}
	for (int i = 0; i < bronzeNum; ++i)
	{
		SetInvenOre(Inventory::InvenState::Bronze);
	}
	for (int i = 0; i < silverNum; ++i)
	{
		SetInvenOre(Inventory::InvenState::Silver);
	}
	for (int i = 0; i < goldNum; ++i)
	{
		SetInvenOre(Inventory::InvenState::Gold);
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

	textBack.SetTexture("graphics/ui/FSADIGBOY19-323.png");
	getOut.SetTexture("graphics/ui/FSADIGBOY19-getout.png");
	getOutLight.SetTexture("graphics/ui/FSADIGBOY19-getoutLight.png");

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



}

void Inventory::Release()
{
	SpriteGo::Release();
}

void Inventory::Reset()
{
	SpriteGo::Reset();

	player = dynamic_cast<PlayerBody*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));

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


	invenLists.resize(invenCount.x * invenCount.y);
	invenIconList.resize(invenCount.x * invenCount.y);
	invenNumList.resize(invenCount.x * invenCount.y);

	//invenSaveList.resize(11);


	for (int i = 0; i < invenCount.y; i++) // 6줄
	{
		for (int j = 0; j < invenCount.x; j++) // 6칸
		{
			invenLists[i * invenCount.x + j].SetTexture("graphics/ui/FSADIGBOY19-305.png");
			invenIconList[i * invenCount.x + j].SetTexture("graphics/ore/FSADIGBOY19-empty.png");
			invenNumList[i * invenCount.x + j].SetTexture("graphics/ore/FSADIGBOY19-empty.png");

			sf::Vector2f quadPos(invenSize.x * j + 45.f, invenSize.y * i + 185.f);
			invenLists[i * invenCount.x + j].SetPosition(invenClose + quadPos);
			invenIconList[i * invenCount.x + j].SetPosition(invenClose + quadPos);
			invenNumList[i * invenCount.x + j].SetPosition(invenClose + quadPos);
		}
	}

	for (int i = 0; i < invenCount.x * invenCount.y; ++i)
	{
		stateList.push_back(Empty);
	}

	SetInvenMoney(0, 0);

	textBack.SetOrigin({ -48.f, -49.f });
	energyText.SetOrigin({ -50.f, -48.f });
	airText.SetOrigin({ -50.f, -65.f });;
	digPowerText.SetOrigin({ -50.f, -90.f });;
	boosterText.SetOrigin({ -50.f, -110.f });;
	armorText.SetOrigin({ -50.f, -130.f });;

	textBack.SetPosition(inventory.GetPosition());
	energyText.SetPosition(inventory.GetPosition());
	airText.SetPosition(inventory.GetPosition());
	digPowerText.SetPosition(inventory.GetPosition());
	boosterText.SetPosition(inventory.GetPosition());
	armorText.SetPosition(inventory.GetPosition());

}

void Inventory::Update(float dt)
{
	SpriteGo::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::I))
	{
		OpenInven();
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

	textBack.Draw(window);
	energyText.Draw(window);
	airText.Draw(window);
	digPowerText.Draw(window);
	boosterText.Draw(window);
	armorText.Draw(window);

	for (int a = 0; a < invenLists.size(); ++a)
	{
		invenLists[a].Draw(window);
	}

	for (int a = 0; a < invenIconList.size(); ++a)
	{
		invenIconList[a].Draw(window);
	}

	for (int a = 0; a < invenNumList.size(); ++a)
	{
		invenNumList[a].Draw(window);
	}

}

