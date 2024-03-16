#include "pch.h"
#include "PlayerBody.h"
#include "SceneDev1.h"
#include "TileMap.h"
#include "Explosive.h"
#include "Dynamite.h"
#include "Inventory.h"

PlayerBody::PlayerBody(const std::string& name)
	: SpriteGo(name), tileMap(tileMap)
{
}

PlayerBody::~PlayerBody()
{
}


void PlayerBody::OnItem(int type, bool get)
{
	switch (type)
	{
	case 0:
		inventory->coilNum += 1;
		inventory->SetInvenOre(Inventory::InvenState::Coil);
		break;
	case 1:
		inventory->bronzeNum += 1;
		inventory->SetInvenOre(Inventory::InvenState::Bronze);
		break;
	case 2:
		inventory->silverNum += 1;
		inventory->SetInvenOre(Inventory::InvenState::Silver);
		break;
	case 3:
		inventory->goldNum += 1;
		inventory->SetInvenOre(Inventory::InvenState::Gold);
		break;
	case 4:
		inventory->healKitNum += 1;
		inventory->SetInvenItem(Inventory::InvenState::HealKit, get);
		break;
	case 5:
		inventory->airCapNum += 1;
		inventory->SetInvenItem(Inventory::InvenState::AirCap, get);
		break;
	case 6:
		inventory->airCapSuperNum += 1;
		inventory->SetInvenItem(Inventory::InvenState::AirCapSuper, get);
		break;
	case 7:
		inventory->bombNum += 1;
		inventory->SetInvenItem(Inventory::InvenState::Bomb, get);
		break;
	case 8:
		inventory->nuclearNum += 1;
		inventory->SetInvenItem(Inventory::InvenState::Nuclear, get);
		break;
	case 9:
		inventory->dynamiteNum += 1;
		inventory->SetInvenItem(Inventory::InvenState::Dynamite, get);
		break;

	default:
		break;
	}

	std::cout << "광석획득" << std::endl;
	std::cout << "현재광석 수 : " << inventory->coilNum << ", " << inventory->bronzeNum << ", " << inventory->silverNum << ", " << inventory->goldNum << std::endl;


}



void PlayerBody::UseItem(int num)
{
	switch (num)
	{
	case 1:
		inventory->healKitNum -= 1;
		hp += 50;
		if (hp >= hpMax)
		{
			hp = hpMax;
		}
		break;
	case 2:
		inventory->airCapNum -= 1;
		air += 50;
		if (air >= airMax)
		{
			air = airMax;
		}
		break;
	case 3:
		inventory->bombNum -= 1;
	default:
		break;
	}

}

void PlayerBody::OnDamage(float Dmg)
{
	if (!invincible)
	{
		if (Dmg <= armorRate)
		{
			hp -= 0.f;
		}
		else
		{
			hp -= (Dmg - armorRate);
		}
		if (hp <= 0)
		{
			OnDie();
		}

		animator.Play("OnDamage");
		animatorHead.Play("OnDamage");
		velocity.y -= 400.f;
		velocity.x = 0.f;

		invincible = true;
	}


}

void PlayerBody::OnDie()
{
	
	animator.Play("OnDie");
	animatorHead.Play("OnDie");
	gravity = 0.f;
}

void PlayerBody::Init()
{
	SpriteGo::Init();


	//head.setTexture(RES_MGR_TEXTURE.Get("graphics/spriteSheetBody.png"));

	animator.SetTarget(&sprite);

	{
		AnimationClip clip;
		clip.id = "Idle";
		clip.fps = 2;
		clip.loopTypes = AnimationLoopTypes::Loop;
		clip.frames.push_back({ "graphics/spriteSheetBody.png", {0, 0, 33, 24} });
		animator.AddClip(clip);
	}

	{
		AnimationClip clip;
		clip.id = "Run";
		clip.fps = 8;
		clip.loopTypes = AnimationLoopTypes::Loop;

		clip.frames.push_back({ "graphics/spriteSheetBody.png", {0, 24, 33, 24} });
		clip.frames.push_back({ "graphics/spriteSheetBody.png", {0, 48, 33, 24} });
		animator.AddClip(clip);
	}

	{
		AnimationClip clip; //상승하는 효과가 추가되야 함
		clip.id = "Boost";
		clip.fps = 2;
		clip.loopTypes = AnimationLoopTypes::Single;

		clip.frames.push_back({ "graphics/spriteSheetBody.png", {0, 0, 33, 24} });

		animator.AddClip(clip);
	}

	{
		AnimationClip clip;
		clip.id = "OnDamage";
		clip.fps = 3;
		clip.loopTypes = AnimationLoopTypes::Single;

		clip.frames.push_back({ "graphics/OnDamage/FSADIGBOY19-Empty.png", {0, 0, 33, 24} });

		animator.AddClip(clip);
	}

	{
		AnimationClip clip;
		clip.id = "OnDie";
		clip.fps = 3;
		clip.loopTypes = AnimationLoopTypes::Single;

		clip.frames.push_back({ "graphics/OnDamage/FSADIGBOY19-Empty.png", {0, 0, 0, 0} });

		animator.AddClip(clip);
	}

	animatorHead.SetTarget(&head);
	{
		AnimationClip clip;
		clip.id = "Idle";
		clip.fps = 4;
		clip.loopTypes = AnimationLoopTypes::Loop;
		clip.frames.push_back({ "graphics/spriteSheetHead.png", {0, 0, 40, 33} });
		clip.frames.push_back({ "graphics/spriteSheetHead.png", {0, 32, 40, 33} });
		animatorHead.AddClip(clip);
	}

	{
		AnimationClip clip;
		clip.id = "Run";
		clip.fps = 2;
		clip.loopTypes = AnimationLoopTypes::Loop;

		clip.frames.push_back({ "graphics/spriteSheetHead.png", {0, 132, 40, 33} });
		animatorHead.AddClip(clip);
	}

	{
		AnimationClip clip; //상승하는 효과가 추가되야 함
		clip.id = "Boost";
		clip.fps = 2;
		clip.loopTypes = AnimationLoopTypes::Loop;

		clip.frames.push_back({ "graphics/spriteSheetHead.png", {0, 0, 40, 33} });
		animatorHead.AddClip(clip);
	}

	{
		AnimationClip clip;
		clip.id = "Drill";
		clip.fps = 2;
		clip.loopTypes = AnimationLoopTypes::Loop;

		clip.frames.push_back({ "graphics/spriteSheetHead.png", {0, 66, 40, 33} });
		animatorHead.AddClip(clip);
	}

	{
		AnimationClip clip;
		clip.id = "OnDamage";
		clip.fps = 3;
		clip.loopTypes = AnimationLoopTypes::Single;

		clip.frames.push_back({ "graphics/OnDamage/FSADIGBOY19-202.png", {0, 0, 47, 55} });

		animatorHead.AddClip(clip);
	}
	{
		AnimationClip clip;
		clip.id = "OnDie";
		clip.fps = 3;
		clip.loopTypes = AnimationLoopTypes::Single;

		clip.frames.push_back({ "graphics/OnDamage/FSADIGBOY19-dead.png", {0, 0, 64, 64} });

		animatorHead.AddClip(clip);
	}


	leftCheck.setFillColor(sf::Color::Transparent);
	leftCheck.setOrigin({ 17.f, 2.5f });
	leftCheck.setSize(hCheckerSize);
	leftCheck.setPosition({ 0.f, 0.f });

	rightCheck.setFillColor(sf::Color::Transparent);
	rightCheck.setOrigin({ -12.f, 2.5f });
	rightCheck.setSize(hCheckerSize);
	rightCheck.setPosition({ 0.f, 0.f });

	topCheck.setFillColor(sf::Color::Transparent);
	topCheck.setOrigin({ 5.f, 35.f });
	topCheck.setSize(vCheckerSize);
	topCheck.setPosition({ 0.f, 0.f });

	buttomCheck.setFillColor(sf::Color::Transparent);
	buttomCheck.setOrigin({ 5.f, 2.5f });
	buttomCheck.setSize(vCheckerSize);
	buttomCheck.setPosition({ 0.f, 0.f });

	drill.SetTexture("graphics/FSADIGBOY19-33.png");
	drill.SetOrigin(Origins::MC);
	drill.SetPosition({ 0.f, 0.f });

	flame.SetTexture("graphics/FSADIGBOY19-fire.png");
	flame.SetOrigin(Origins::TC);
	flame.SetPosition({ 0.f, 0.f });
	flame.SetActive(false);
}

void PlayerBody::Reset()
{
	animator.Play("Idle");
	SetOrigin(Origins::BC);

	animatorHead.Play("Idle");

	head.setOrigin({20, 50});
	head.setPosition(position);

	tileMap = dynamic_cast<TileMap*>(SCENE_MGR.GetCurrentScene()->FindGo("Ground"));
	inventory = dynamic_cast<Inventory*>(SCENE_MGR.GetCurrentScene()->FindGo("Inventory"));

	//타일맵 숫자, 사이즈 가져오기
	count = tileMap->GetCellCount();
	size = tileMap->GetCellSize();

	tileMapLeftEnd = tileMap->GetPosition().x;
	tileMapRightEnd = tileMapLeftEnd + count.x * size.x;

	flame.SetPosition(GetPosition());
}

void PlayerBody::Update(float dt)
{
	sf::Vector2f CheckPos = sprite.getPosition();

	buttomCheck.setPosition(CheckPos);
	topCheck.setPosition(CheckPos);
	CheckPos.y += -15.f;
	leftCheck.setPosition(CheckPos);

	CheckPos = sprite.getPosition();
	CheckPos.y += -15.f;
	rightCheck.setPosition(CheckPos);

	sf::Vector2f drillPosDown = sprite.getPosition();
	sf::Vector2f drillPosLeft = { drillPosDown.x - 15 , drillPosDown.y - 15};
	sf::Vector2f drillPosRight = { drillPosDown.x + 15 , drillPosDown.y - 15 };

	drill.SetPosition(drillPosDown);
	drill.SetActive(false);

	SpriteGo::Update(dt);
	animator.Update(dt);

	float h = InputMgr::GetAxisRaw(Axis::Horizontal);

	velocity.x = h * speed;

	if (InputMgr::GetKey(sf::Keyboard::Up))
	{
		flame.SetActive(true);
		animator.Play("Boost");
		velocity.y += -booster * dt;

		if (velocity.y <= -500.f)
		{
			velocity.y = -500.f;
		}
	}
	else
	{
		flame.SetActive(false);
		velocity.y += gravity * dt;

		if (velocity.y >= 800.f)
		{
			velocity.y = 800.f;
		}
	}

	sf::Vector2f pos = position + velocity * dt;

	if (pos.x <= tileMapLeftEnd)
	{
		pos.x = tileMapLeftEnd;
	}
	if (pos.x >= tileMapRightEnd)
	{
		pos.x = tileMapRightEnd;
	}

	SetPosition(pos);
	flame.SetPosition({ pos.x, pos.y - 2.f });

	if (h != 0.f)
	{
		SetFlipX(h > 0);
		head.setScale(-h, 1.f);
	}

	if (animator.GetCurrentClipId() == "Idle")
	{
		if (h != 0.f)
		{
			animator.Play("Run");
			animatorHead.Play("Run");
		}
	}
	else if (animator.GetCurrentClipId() == "Run")
	{
		if (h == 0.f)
		{
			animator.Play("Idle");
			animatorHead.Play("Idle");
		}
	}
	else if (animator.GetCurrentClipId() == "Boost" && isGrounded)
	{
		animator.Play("Idle");
		animatorHead.Play("Idle");
	}

	if (animator.GetCurrentClipId() == "Idle" && isDrill)
	{
		animatorHead.Play("Drill");
	}
	if (animator.GetCurrentClipId() == "Idle" && !isDrill)
	{
		animatorHead.Play("Idle");
	}

	if (tileMap != nullptr)
	{
		const sf::FloatRect& playerBounds = sprite.getGlobalBounds();
		const sf::FloatRect& groundBounds = tileMap->GetGlobalBounds();

		if (playerBounds.intersects(groundBounds))
		{
			// 플레이어가 속한 셀의 인덱스
			playerCellX = static_cast<int>(GetPosition().x / tileMap->GetCellSize().x);
			playerCellY = static_cast<int>(GetPosition().y / tileMap->GetCellSize().y) - 1;

			if (playerCellY > 0)
			{
				air -= 1.f * dt;
				if (air <= 0.f)
				{
					air = 0.f;
					hp -= 1.5f * dt;
				}
			}
			else
			{
				air = airMax;
			}
			//std::cout << playerCellX << ", " << playerCellY << std::endl;


			// 주변 8개의 인접한 셀에 대해서만 충돌 체크
			for (int i = playerCellY - 1; i <= playerCellY + 1; ++i)
			{
				for (int j = playerCellX - 1; j <= playerCellX + 1; ++j)
				{
					if (i >= 0 && i < count.y && j >= 0 && j < count.x)
					{
						sf::FloatRect tileBounds = tileMap->GetTileBound(j, i);

						if (tileMap->level[i * count.x + j] == 0 || tileMap->level[i * count.x + j] == 32 || tileMap->level[i * count.x + j] == -1)
							continue; //통과처리할 타일 종류

						if (tileBounds.intersects(playerBounds))
						{

							if (buttomCheck.getGlobalBounds().intersects(tileBounds) && velocity.y >= 0)
							{
								if (velocity.y > 600.f)
								{
									if (fallDmg <= armorRate)
									{
										hp -= 0.f;
									}
									else
									{
										hp -= (fallDmg - armorRate);
									}
									std::cout << "으악!" << std::endl;
								}

								pos.y = tileBounds.top;
								velocity.y = 0.f;
								isGrounded = true;

								if (isGrounded && InputMgr::GetKeyDown(sf::Keyboard::Down))
								{
									SOUND_MGR.PlaySfx("sound/FSADIGBOY19-Drill.mp3", false);
								}
								if (isGrounded && InputMgr::GetKey(sf::Keyboard::Down))
								{
									
									isDrill = true;
									drill.SetRotation(0.f);
									drill.SetPosition(drillPosDown);
									drill.SetActive(true);
									digTime += dt * drillPower;
									if (digTime >= digTimer)
									{
										tileMap->changeTile(i, j);
										digTime = 0.f;
									}
									//std::cout << digTime << std::endl;
								}
								else
								{
									isDrill = false;
								}

								if (InputMgr::GetKeyDown(sf::Keyboard::Num4))
								{
									Dynamite* dynamite = new Dynamite;
									dynamite->SetDynamite({ i, j });
									SCENE_MGR.GetCurrentScene()->AddGo(dynamite);
								}
							}
						

							if (topCheck.getGlobalBounds().intersects(tileBounds) && velocity.y < 0)
							{
								pos.y = tileBounds.top + tileBounds.height + 25.f;
								velocity.y = -0.5f;
							}

							if (h == -1 && leftCheck.getGlobalBounds().intersects(tileBounds))
							{
								if (isGrounded)
								{
									isDrill = true;
									drill.SetRotation(90);
									drill.SetPosition(drillPosLeft);
									drill.SetActive(true);
									digTime += dt * drillPower;
									if (digTime >= digTimer)
									{
										tileMap->changeTile(i, j);
										digTime = 0.f;
									}
								}
								pos.x = tileBounds.left + tileBounds.width + 16.f;
							}
							if (h == 1 && rightCheck.getGlobalBounds().intersects(tileBounds))
							{
								if (isGrounded)
								{
									isDrill = true;
									drill.SetRotation(270);
									drill.SetPosition(drillPosRight);
									drill.SetActive(true);
									digTime += dt * drillPower;
									if (digTime >= digTimer)
									{
										tileMap->changeTile(i, j);
										digTime = 0.f;
									}
								}
								pos.x = tileBounds.left - 16.f;
							}

							SetPosition(pos);
							
							
						}
					}
				}
			}
		}
	}

	head.setPosition(position);


	if (abs(velocity.y) < 0.1f)
	{
		isGrounded = true;
	}
	else
	{
		isGrounded = false;
	}

	if (invincible)
	{
		invincTime += dt;
		if (invincTime > invincTimer)
		{
			invincible = false;
			invincTime = 0.f;
			animator.Play("Idle");
			animatorHead.Play("Idle");
		}
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Num3))
	{
		Explosive* explosive = new Explosive;
		explosive->SetBomb({ playerCellX, playerCellY });
		SCENE_MGR.GetCurrentScene()->AddGo(explosive);
	}


	//아이템 획득 테스트용
	if (InputMgr::GetKeyDown(sf::Keyboard::Num6))
	{
		OnItem(5, 1);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Num7))
	{
		OnItem(5, 0);
	}

}

void PlayerBody::Draw(sf::RenderWindow& window)
{
	if (flame.GetActive())
	{
		flame.Draw(window);
	}

	SpriteGo::Draw(window);
	window.draw(head);
	window.draw(leftCheck);
	window.draw(rightCheck);
	window.draw(topCheck);
	window.draw(buttomCheck);
	//coil->Draw(window);


	if (drill.GetActive())
	{
		drill.Draw(window);
	}


	if (SCENE_MGR.GetDeveloperMode())
	{
		leftCheck.setFillColor(sf::Color::Red);
		rightCheck.setFillColor(sf::Color::Red);
		topCheck.setFillColor(sf::Color::Red);
		buttomCheck.setFillColor(sf::Color::Red);
	}
	else
	{
		leftCheck.setFillColor(sf::Color::Transparent);
		rightCheck.setFillColor(sf::Color::Transparent);
		topCheck.setFillColor(sf::Color::Transparent);
		buttomCheck.setFillColor(sf::Color::Transparent);
	}

	//말풍선으로 플레이어 좌표 띄우기
}
