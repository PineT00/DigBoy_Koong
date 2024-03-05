#include "pch.h"
#include "AniTest.h"
#include "SceneDev1.h"
#include "TileMap.h"

AniTest::AniTest(const std::string& name)
	: SpriteGo(name)
{
}

AniTest::~AniTest()
{
}

void AniTest::Init()
{
	SpriteGo::Init();

	animator.SetTarget(&sprite);

	{
		AnimationClip clip;
		clip.id = "Idle";
		clip.fps = 2;
		clip.loopTypes = AnimationLoopTypes::Loop;
		clip.frames.push_back({ "graphics/sprite_sheet.png", {0, 0, 120, 120} });
		animator.AddClip(clip);
	}

	{
		AnimationClip clip;
		clip.id = "Run";
		clip.fps = 8;
		clip.loopTypes = AnimationLoopTypes::Loop;

		for (int i = 0; i < 8; ++i)
		{
			clip.frames.push_back({ "graphics/sprite_sheet.png", {i * 120, 120, 120, 120} });
		}
		clip.frames.push_back({ "graphics/sprite_sheet.png", {0, 120, 120, 120} });
		animator.AddClip(clip);
	}

	{
		AnimationClip clip;
		clip.id = "Jump";
		clip.fps = 10;
		clip.loopTypes = AnimationLoopTypes::Single;

		for (int i = 0; i < 7; ++i)
		{
			clip.frames.push_back({"graphics/sprite_sheet.png", {i * 120, 360, 120, 120} });
		}
		clip.frames.push_back({"graphics/sprite_sheet.png", {0, 360, 120, 120} });
		animator.AddClip(clip);
	}

}

void AniTest::Reset()
{
	animator.Play("Idle");
	SetOrigin(Origins::BC);
	SetPosition({ 0.f, 0.f });
	sceneDev1 = dynamic_cast<SceneDev1*>(SCENE_MGR.GetCurrentScene());
}

void AniTest::Update(float dt)
{
	SpriteGo::Update(dt);
	animator.Update(dt);

	float h = InputMgr::GetAxisRaw(Axis::Horizontal);

	if (isGrounded && InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		isGrounded = false;
		animator.Play("Jump");
		velocity.y = -500.f;
	}

	velocity.x = h * speed;
	velocity.y += gravity * dt;

	//position += velocity * dt;

	//if (position.y > 0.f)
	//{
	//	isGrounded = true;
	//	position.y = 0.f;
	//	velocity.y = 0.f;

	//}


	//sf::FloatRect rect = tileMap->GetGlobalBounds();

	//sf::FloatRect rectPlayer = sprite.getGlobalBounds();

	//if (rectPlayer.intersects(rect))
	//{
	//	velocity.y = 0.f;
	//	isGrounded = true;
	//}


	sf::Vector2f pos = position + velocity * dt;

	SetPosition(pos);

	if (h != 0.f)
	{
		SetFlipX(h < 0);
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
	else if (animator.GetCurrentClipId() == "Jump" && isGrounded)
	{
		animator.Play("Idle");
	}

}
