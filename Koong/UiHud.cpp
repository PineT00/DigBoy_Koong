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
}

void UiHud::SetMessageActive(bool active)
{
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
	cellCount = count;
	cellSize = size;

	invenVa.clear();
	invenVa.setPrimitiveType(sf::Quads);
	invenVa.resize(count.x * count.y * 4);

	posOffset[0] = { 0, 0 };
	posOffset[1] = { size.x, 0 };
	posOffset[2] = { size.x, size.y };
	posOffset[3] = { 0, size.y };

	texCoord0[0] = { 0, 0 };
	texCoord0[1] = { 42.f, 0 };
	texCoord0[2] = { 42.f, 42.f };
	texCoord0[3] = { 0, 42.f };


	invenMap =
	{
	    1,1,1,1,1,1,
		1,1,1,1,1,1,
		1,1,1,1,1,1,
		1,1,1,1,1,1,
		1,1,1,1,1,1,
		1,1,1,1,1,1,
	};

	for (int i = 0; i < count.y; ++i)
	{
		for (int j = 0; j < count.x; ++j)
		{

			int texIndexX = invenMap[i * count.x + j];
			int texIndexY = 0;

			int quadIndex = i * count.x + j;
			sf::Vector2f quadPos(size.x * j, size.y * i);

			for (int k = 0; k < 4; k++)
			{
				int vertexIndex = ((quadIndex * 4) + k);
				invenVa[vertexIndex].position = quadPos + posOffset[k];
				invenVa[vertexIndex].texCoords = texCoord0[k];

				invenVa[vertexIndex].texCoords.x += texIndexX * 42.f;
				invenVa[vertexIndex].texCoords.y += texIndexY * 42.f;
			}

		}
	}
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

	inventory.SetTexture("graphics/ui/FSADIGBOY19-319.png");
	invenSprite.SetTexture("graphics/ui/FSADIGBOY19-322.png");
	invenEmpty.SetTexture("graphics/ui/FSADIGBOY19-305.png");
	invenBlocked.SetTexture("graphics/ui/FSADIGBOY19-321.png");


	test.setFont(RES_MGR_FONT.Get("NanumSquareRoundEB.ttf"));
	test.setString("SFML!");
	test.setCharacterSize(34);
	test.setFillColor(sf::Color::White);
}

void UiHud::Release()
{
}

void UiHud::Reset()
{
	player = dynamic_cast<PlayerBody*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));

	//체력과 산소게이지
	SetHpBar(player->GetHP(), player->GetMaxHP());
	SetAirBar(player->GetAir(), player->GetMaxAir());

	hud.SetOrigin(Origins::TR);
	hud.SetPosition({ 1280.f, 0.f });

	energy.SetOrigin(Origins::TR);
	energy.SetPosition({ 1238.f, 140.f });

	hpBar.SetOrigin(Origins::TR);
	hpBar.SetPosition({ 1242.f, 160.f });

	airText.SetOrigin(Origins::TR);
	airText.SetPosition({ 1223.f, 170.f });

	airBarFrame1.SetOrigin(Origins::TR);
	airBarFrame1.SetPosition({ 1255.f, 173.f });

	airBarColor.SetOrigin(Origins::TC);
	airBarColor.SetPosition({ 1198.f, 184.f });

	airBarFrame2.SetOrigin(Origins::TR);
	airBarFrame2.SetPosition({ 1253.f, 173.f });


	//인벤토리
	inventory.SetOrigin(Origins::TL);
	inventory.SetPosition(invenClose);
}

void UiHud::Update(float dt)
{
	SetHpBar(player->GetHP(), player->GetMaxHP());
	SetAirBar(player->GetAir(), player->GetMaxAir());

	if (InputMgr::GetKeyDown(sf::Keyboard::I))
	{
		if (inventory.GetPosition() == invenClose)
		{
			inventory.SetPosition(invenOpen);

		}
		else if (inventory.GetPosition() == invenOpen)
		{
			inventory.SetPosition(invenClose);
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

	inventory.Draw(window);

	window.draw(test);

}
