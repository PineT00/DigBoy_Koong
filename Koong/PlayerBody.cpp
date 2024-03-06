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
	SpriteGo::Update(dt);
	animator.Update(dt);

	float h = InputMgr::GetAxisRaw(Axis::Horizontal);

	velocity.x = h * speed;

	if (InputMgr::GetKey(sf::Keyboard::Space))
	{
		isGrounded = false;
		animator.Play("Boost");
		velocity.y += -booster * dt;
		std::cout << velocity.y << std::endl;

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
			auto count = tileMap->GetCellCount();
			for (int i = 0; i < count.y; ++i)
			{
				for (int j = 0; j < count.x; ++j)
				{
					if (tileMap->level[i * count.x + j] == 3)
						continue;

					if (tileMap->GetTileBound(j, i).intersects(playerBounds))
					{
						if (tileMap->GetTileBound(j, i).top > playerBounds.height)
						{
							pos.y = tileMap->GetTileBound(j, i).top;
							velocity.y = 0.f;
						}
						/*if (tileMap->GetTileBound(j, i).height < playerBounds.top)
						{
							pos.y = tileMap->GetTileBound(j, i).height;
						}
						if (tileMap->GetTileBound(j, i).left >= playerBounds.width)
						{
							pos.x = tileMap->GetTileBound(j, i).left;
						}
						if (tileMap->GetTileBound(j, i).width <= playerBounds.left)
						{
							pos.x = tileMap->GetTileBound(j, i).width;
						}*/
						std::cout << j << ", " << i << std::endl;

						/*pos.y = tileMap->GetTileBound(j, i).top;
						velocity.y = 0.f;*/

						SetPosition(pos);
						isGrounded = true;
					}
				}
			}
		}
	}
}

void PlayerBody::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);

}
