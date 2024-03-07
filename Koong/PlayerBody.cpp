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

	leftCheck.setFillColor(sf::Color::Red);
	Utils::SetOrigin(leftCheck, Origins::MC);
	leftCheck.setSize(hCheckerSize);
	leftCheck.setPosition({ 0.f, 0.f });

	rightCheck.setFillColor(sf::Color::Red);
	Utils::SetOrigin(rightCheck, Origins::MC);
	rightCheck.setSize(hCheckerSize);
	rightCheck.setPosition({ 0.f, 0.f });

	topCheck.setFillColor(sf::Color::Red);
	Utils::SetOrigin(topCheck, Origins::MC);
	topCheck.setSize(vCheckerSize);
	topCheck.setPosition({ 0.f, 0.f });

	buttomCheck.setFillColor(sf::Color::Red);
	Utils::SetOrigin(buttomCheck, Origins::MC);
	buttomCheck.setSize(vCheckerSize);
	buttomCheck.setPosition({ 0.f, 0.f });

}

void PlayerBody::Reset()
{
	animator.Play("Idle");
	SetOrigin(Origins::BC);
	SetPosition({ 0.f, 0.f });


	tileMap = dynamic_cast<TileMap*>(SCENE_MGR.GetCurrentScene()->FindGo("Ground"));
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

	SpriteGo::Update(dt);
	animator.Update(dt);

	float h = InputMgr::GetAxisRaw(Axis::Horizontal);

	velocity.x = h * speed;

	if (InputMgr::GetKey(sf::Keyboard::Up))
	{
		isGrounded = false;
		animator.Play("Boost");
		velocity.y += -booster * dt;
		//std::cout << velocity.y << std::endl;

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

			std::cout << playerCellX << ", " << playerCellY << std::endl;

			auto count = tileMap->GetCellCount();
			auto size = tileMap->GetCellSize();

			// 주변 8개의 인접한 셀에 대해서만 충돌 체크

			for (int i = playerCellY - 1; i <= playerCellY + 1; ++i)
			{
				for (int j = playerCellX - 1; j <= playerCellX + 1; ++j)
				{
					if (i >= 0 && i < count.y && j >= 0 && j < count.x)
					{
						sf::FloatRect tileBounds = tileMap->GetTileBound(j, i);

						if (tileMap->level[i * count.x + j] == 0 || tileMap->level[i * count.x + j] == 3)
							continue;

						if (tileBounds.intersects(playerBounds))
						{
							if (buttomCheck.getGlobalBounds().intersects(tileBounds) && velocity.y >= 0)
							{
								pos.y = tileBounds.top;
								velocity.y = 0.f;

								//통과 가능한 타일로 변경.(텍스쳐변경은 없음)
								if (InputMgr::GetKeyDown(sf::Keyboard::Space))
								{
									tileMap->level[i * count.x + j] = 3;

									int quadIndex = i * count.x + j;
									sf::Vector2f quadPos(size.x * j, size.y * i);

									//텍스쳐 변경. 타일맵에 있는 오프셋과 코드를 불러와야..
									for (int k = 0; k < 4; k++)
									{				
										
										int vertexIndex = ((quadIndex * 4) + k);
										tileMap->va[vertexIndex].position = quadPos + tileMap->posOffset[k];
										tileMap->va[vertexIndex].texCoords = tileMap->texCoord0[k];

										tileMap->va[vertexIndex].texCoords.x += 0 * 42.f;
										tileMap->va[vertexIndex].texCoords.y += 3 * 42.f;
									}
								}
							}
							if (topCheck.getGlobalBounds().intersects(tileBounds) && velocity.y < 0)
							{
								pos.y = tileBounds.top + tileBounds.height + 30.f;
								velocity.y = -0.5f;
							}

							if (h == -1 && leftCheck.getGlobalBounds().intersects(tileBounds))
							{
								
								if (InputMgr::GetKeyDown(sf::Keyboard::Left))
								{
									tileMap->level[i * count.x + j] = 3;
								}
								pos.x = tileBounds.left + tileBounds.width + 20.f;
							}
							if (h == 1 && rightCheck.getGlobalBounds().intersects(tileBounds))
							{
								pos.x = tileBounds.left - 20.f;
								

							}

							//std::cout << j << ", " << i << std::endl;

							SetPosition(pos);
							isGrounded = true;
						}
					}
				}
			}
		}
	}
}

void PlayerBody::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
	window.draw(leftCheck);
	window.draw(rightCheck);
	window.draw(topCheck);
	window.draw(buttomCheck);
}
