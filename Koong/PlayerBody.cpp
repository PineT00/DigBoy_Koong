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
		AnimationClip clip; //����ϴ� ȿ���� �߰��Ǿ� ��
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
			pos.y = tileMap->GetGlobalBounds().top;
			velocity.y = 0.f;
			SetPosition(pos);
			isGrounded = true;
		}
	}
}

void PlayerBody::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);

}
