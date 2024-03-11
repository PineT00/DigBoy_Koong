#include "pch.h"
#include "PlayerBody.h"
#include "SceneDev1.h"
#include "TileMap.h"

PlayerBody::PlayerBody(const std::string& name)
	: SpriteGo(name), tileMap(tileMap)
{
}

PlayerBody::~PlayerBody()
{
}

void PlayerBody::LocateDrill(float r, float x, float y)
{
	
}

void PlayerBody::OnItem()
{
	std::cout << "광석획득" << std::endl;
	coilNum += 1;
	std::cout << "현재광석 수 : " << coilNum << std::endl;
}

void PlayerBody::Init()
{
	SpriteGo::Init();

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
		clip.id = "Drill";
		clip.fps = 2;
		clip.loopTypes = AnimationLoopTypes::Loop;

		clip.frames.push_back({ "graphics/FSADIGBOY19-33.png", {0, 0, 33, 24} });

		animator.AddClip(clip);
	}

	leftCheck.setFillColor(sf::Color::Transparent);
	Utils::SetOrigin(leftCheck, Origins::MC);
	leftCheck.setSize(hCheckerSize);
	leftCheck.setPosition({ 0.f, 0.f });

	rightCheck.setFillColor(sf::Color::Transparent);
	Utils::SetOrigin(rightCheck, Origins::MC);
	rightCheck.setSize(hCheckerSize);
	rightCheck.setPosition({ 0.f, 0.f });

	topCheck.setFillColor(sf::Color::Transparent);
	Utils::SetOrigin(topCheck, Origins::MC);
	topCheck.setSize(vCheckerSize);
	topCheck.setPosition({ 0.f, 0.f });

	buttomCheck.setFillColor(sf::Color::Transparent);
	Utils::SetOrigin(buttomCheck, Origins::MC);
	buttomCheck.setSize(vCheckerSize);
	buttomCheck.setPosition({ 0.f, 0.f });

	drill.SetTexture("graphics/FSADIGBOY19-33.png");
	drill.SetOrigin(Origins::MC);
	drill.SetPosition({ 0.f, 0.f });

}

void PlayerBody::Reset()
{
	animator.Play("Idle");
	SetOrigin(Origins::BC);
	SetPosition({ 400.f, -200.f });


	tileMap = dynamic_cast<TileMap*>(SCENE_MGR.GetCurrentScene()->FindGo("Ground"));

	//타일맵 숫자, 사이즈 가져오기
	count = tileMap->GetCellCount();
	size = tileMap->GetCellSize();
}

void PlayerBody::Update(float dt)
{
	sf::Vector2f CheckPos = sprite.getPosition();
	CheckPos.x += -5.f;
	CheckPos.y += -2.f;
	buttomCheck.setPosition(CheckPos);

	CheckPos = sprite.getPosition();
	CheckPos.x += -5.f;
	CheckPos.y += -40.f;
	topCheck.setPosition(CheckPos);

	CheckPos = sprite.getPosition();
	CheckPos.x += -20.f;
	CheckPos.y += -15.f;
	leftCheck.setPosition(CheckPos);

	CheckPos = sprite.getPosition();
	CheckPos.x += 15.f;
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
		animator.Play("Boost");
		velocity.y += -booster * dt;


		if (velocity.y <= -500.f)
		{
			velocity.y = -500.f;
		}
	}
	else
	{
		velocity.y += gravity * dt;

		if (velocity.y >= 800.f)
		{
			velocity.y = 800.f;
		}
	}

	sf::Vector2f pos = position + velocity * dt;

	SetPosition(pos);

	if (h != 0.f)
	{
		SetFlipX(h > 0);
	}

	if (animator.GetCurrentClipId() == "Idle")
	{
		if (h != 0.f)
		{
			animator.Play("Run");
		}
	}
	else if (animator.GetCurrentClipId() == "Run")
	{
		if (h == 0.f)
		{
			animator.Play("Idle");
		}
	}
	else if (animator.GetCurrentClipId() == "Boost" && isGrounded)
	{
		animator.Play("Idle");
	}

	if (tileMap != nullptr)
	{
		const sf::FloatRect& playerBounds = sprite.getGlobalBounds();
		const sf::FloatRect& groundBounds = tileMap->GetGlobalBounds();

		if (playerBounds.intersects(groundBounds))
		{
			// 플레이어가 속한 셀의 인덱스
			int playerCellX = static_cast<int>(GetPosition().x / tileMap->GetCellSize().x);
			int playerCellY = static_cast<int>(GetPosition().y / tileMap->GetCellSize().y) - 1;

			//std::cout << playerCellX << ", " << playerCellY << std::endl;


			// 주변 8개의 인접한 셀에 대해서만 충돌 체크
			for (int i = playerCellY - 1; i <= playerCellY + 1; ++i)
			{
				for (int j = playerCellX - 1; j <= playerCellX + 1; ++j)
				{
					if (i >= 0 && i < count.y && j >= 0 && j < count.x)
					{
						sf::FloatRect tileBounds = tileMap->GetTileBound(j, i);

						if (tileMap->level[i * count.x + j] == 0 || tileMap->level[i * count.x + j] == 32)
							continue; //통과처리할 타일 종류

						if (tileBounds.intersects(playerBounds))
						{
							if (buttomCheck.getGlobalBounds().intersects(tileBounds) && velocity.y >= 0)
							{
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
									digTime += dt;
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
									digTime += dt;
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
									digTime += dt;
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

	if (abs(velocity.y) < 0.1f)
	{
		isGrounded = true;
	}
	else
	{
		isGrounded = false;
	}

}

void PlayerBody::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
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
}
