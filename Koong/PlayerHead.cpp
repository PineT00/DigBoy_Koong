#include "pch.h"
#include "PlayerHead.h"
#include "PlayerBody.h"

PlayerHead::PlayerHead(const std::string& name)
	:SpriteGo(name), player(player)
{
}

void PlayerHead::Init()
{
	SpriteGo::Init();

	animator.SetTarget(&sprite);

	{
		AnimationClip clip;
		clip.id = "Idle";
		clip.fps = 4;
		clip.loopTypes = AnimationLoopTypes::Loop;
		clip.frames.push_back({ "graphics/spriteSheetHead.png", {0, 0, 40, 33} });
		clip.frames.push_back({ "graphics/spriteSheetHead.png", {0, 32, 40, 33} });
		animator.AddClip(clip);
	}

	{
		AnimationClip clip;
		clip.id = "Run";
		clip.fps = 2;
		clip.loopTypes = AnimationLoopTypes::Loop;

		clip.frames.push_back({ "graphics/spriteSheetHead.png", {0, 132, 40, 33} });
		animator.AddClip(clip);
	}

	{
		AnimationClip clip; //상승하는 효과가 추가되야 함
		clip.id = "Boost";
		clip.fps = 2;
		clip.loopTypes = AnimationLoopTypes::Loop;

		clip.frames.push_back({ "graphics/spriteSheetHead.png", {0, 0, 40, 33} });
		animator.AddClip(clip);
	}
}

void PlayerHead::Reset()
{
	animator.Play("Idle");
	SetOrigin(Origins::BC);
	SetPosition({ 0.f, 10.f });

	player = dynamic_cast<PlayerBody*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));
}

void PlayerHead::Update(float dt)
{
	sf::Vector2f pos = player->GetPosition();
	pos.y -= 20.f;
	SetPosition(pos);

	float h = InputMgr::GetAxisRaw(Axis::Horizontal);

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
	else if (animator.GetCurrentClipId() == "Boost" && player->isGrounded)
	{
		animator.Play("Idle");
	}

}

void PlayerHead::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}
