#include "pch.h"
#include "Monster.h"
#include "TileMap.h"
#include "PlayerBody.h"

Monster::Monster(const std::string& name)
	:SpriteGo(name)
{
}

void Monster::SetMonster(sf::Vector2f pos)
{
	animator.Play("walk");
	SetOrigin(Origins::BC);
	SetPosition(pos);
}

void Monster::Init()
{
	SpriteGo::Init();

	animator.SetTarget(&sprite);

	{
		AnimationClip clip;
		clip.id = "walk";
		clip.fps = 4;
		clip.loopTypes = AnimationLoopTypes::Loop;
		clip.frames.push_back({ "graphics/monster/FSADIGBOY19-121.png", {0, 0, 38, 40} });
		clip.frames.push_back({ "graphics/monster/FSADIGBOY19-122.png", {0, 0, 38, 40} });
		clip.frames.push_back({ "graphics/monster/FSADIGBOY19-123.png", {0, 0, 38, 40} });
		clip.frames.push_back({ "graphics/monster/FSADIGBOY19-122.png", {0, 0, 38, 40} });
		animator.AddClip(clip);
	}

	{
		AnimationClip clip;
		clip.id = "dead";
		clip.fps = 1;
		clip.loopTypes = AnimationLoopTypes::Single;

		clip.frames.push_back({ "graphics/monster/FSADIGBOY19-124.png", {0, 0, 38, 40} });
		animator.AddClip(clip);
	}

	leftCheck.setFillColor(sf::Color::Transparent);
	Utils::SetOrigin(leftCheck, Origins::MC);
	leftCheck.setSize(CheckerSize);

	rightCheck.setFillColor(sf::Color::Transparent);
	Utils::SetOrigin(rightCheck, Origins::MC);
	rightCheck.setSize(CheckerSize);

	leftButtomCheck.setFillColor(sf::Color::Transparent);
	Utils::SetOrigin(leftButtomCheck, Origins::TL);
	leftButtomCheck.setSize(CheckerSize);

	rightButtomCheck.setFillColor(sf::Color::Transparent);
	Utils::SetOrigin(rightButtomCheck, Origins::TR);
	rightButtomCheck.setSize(CheckerSize);


	SetPosition({ 0.f, 0.f });
}

void Monster::Reset()
{
	SpriteGo::Reset();
	animator.Play("walk");
	SetOrigin(Origins::BC);
	tileMap = dynamic_cast<TileMap*>(SCENE_MGR.GetCurrentScene()->FindGo("Ground"));
	player = dynamic_cast<PlayerBody*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));

	SetPosition({ 200.f, 0.f });

}

void Monster::Update(float dt)
{
	SpriteGo::Update(dt);
	animator.Update(dt);

	velocity.x = dir * speed;
	sf::Vector2f pos = position + velocity * dt;
	SetPosition(pos);

	sf::Vector2f CheckPos = sprite.getPosition();

	leftCheck.setPosition({ CheckPos.x - 22.f, CheckPos.y - 20.f });
	rightCheck.setPosition({ CheckPos.x + 19.f, CheckPos.y - 20.f});

	leftButtomCheck.setPosition({ CheckPos.x - 14.f, CheckPos.y + 1.2f });
	rightButtomCheck.setPosition({ CheckPos.x + 11.f, CheckPos.y + 1.2f });

	if (tileMap != nullptr)
	{
		const sf::FloatRect& monsterBounds = sprite.getGlobalBounds();

		const sf::FloatRect& groundBounds = tileMap->GetGlobalBounds();

		if (monsterBounds.intersects(player->GetSpriteGlobalBound()))
		{
			player->OnDamage(attack);
		}


		// 몬스터가 속한 셀의 인덱스
		int monsterCellX = static_cast<int>(GetPosition().x / tileMap->GetCellSize().x);
		int monsterCellY = static_cast<int>(GetPosition().y / tileMap->GetCellSize().y) -1;

		std::cout << monsterCellX << ", " << monsterCellY << std::endl;

		// 주변 6개의 인접한 셀에 대해서만 충돌 체크
		for (int i = monsterCellY; i <= monsterCellY + 1; ++i)
		{
			for (int j = monsterCellX - 1; j <= monsterCellX + 1; ++j)
			{
				sf::FloatRect tileBounds = tileMap->GetTileBound(j, i);

				if (i >= 0 && i < tileMap->GetCellCount().y && j >= 0 && j < tileMap->GetCellCount().x)
				{
					if ((dir == 1 && tileBounds.intersects(rightCheck.getGlobalBounds())) || (dir == -1 && tileBounds.intersects(leftCheck.getGlobalBounds())))
					{
						if (tileMap->level[i * tileMap->GetCellCount().x + j] == 16 || tileMap->level[i * tileMap->GetCellCount().x + j] == 56)
						{
							if (isFlipX)
							{
								SetFlipX(false);
							}
							else
							{
								SetFlipX(true);
							}
							dir *= -1;
						}
					}

					if ((dir == 1 && tileBounds.intersects(rightButtomCheck.getGlobalBounds())) || (dir == -1 && tileBounds.intersects(leftButtomCheck.getGlobalBounds())))
					{
						if (tileMap->level[i * tileMap->GetCellCount().x + j] == 0 || tileMap->level[i * tileMap->GetCellCount().x + j] == 32)
						{
							if (isFlipX)
							{
								SetFlipX(false);
							}
							else
							{
								SetFlipX(true);
							}
							dir *= -1;
						}
					}
				}
				
			}
		}
		
	}

	//time += dt;
	//if (time > timer)
	//{
	//	if (isFlipX)
	//	{
	//		SetFlipX(false);
	//	}
	//	else 
	//	{
	//		SetFlipX(true);
	//	}
	//	time = 0.f;
	//	dir *= -1.f;
	//}


}

void Monster::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
	window.draw(leftCheck);
	window.draw(rightCheck);
	window.draw(leftButtomCheck);
	window.draw(rightButtomCheck);

	if (SCENE_MGR.GetDeveloperMode())
	{
		leftCheck.setFillColor(sf::Color::Red);
		rightCheck.setFillColor(sf::Color::Red);
		leftButtomCheck.setFillColor(sf::Color::Red);
		rightButtomCheck.setFillColor(sf::Color::Red);
	}
	else
	{
		leftCheck.setFillColor(sf::Color::Transparent);
		rightCheck.setFillColor(sf::Color::Transparent);
		leftButtomCheck.setFillColor(sf::Color::Transparent);
		rightButtomCheck.setFillColor(sf::Color::Transparent);
	}
}
