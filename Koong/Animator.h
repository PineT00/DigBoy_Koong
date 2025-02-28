#pragma once

enum class AnimationLoopTypes
{
	Single,
	Loop,
	PingPong,
};

struct AnimationFrame
{
	std::string textureId;
	sf::IntRect texCoord;

	AnimationFrame(const std::string& id, const sf::IntRect& coord)
		: textureId(id), texCoord(coord)
	{

	}
	const sf::Texture& GetTexture() const
	{
		return RES_MGR_TEXTURE.Get(textureId);
	}
};

struct AnimationClip
{
	std::string id;
	std::vector<AnimationFrame> frames;
	AnimationLoopTypes loopTypes = AnimationLoopTypes::Single;
	int fps = 30;

	int GetTotalFrame() const
	{
		return frames.size();
	}
};

class Animator
{
protected:
	std::unordered_map<std::string, AnimationClip> clips;
	std::queue<std::string> queue;

	float speed = 1.f; //애니메이션 재생속도

	bool isPlaying = false;
	AnimationClip* currentClip = nullptr;
	int totalFrame = 0;
	int currentFrame = -1;
	int addFrame = 1;

	float clipDuration = 0.f;

	float accumTime = 0.f;

	sf::Sprite* target = nullptr;

public:
	Animator();
	~Animator();

	void AddClip(const AnimationClip& clip);

	bool IsPlaying() const { return isPlaying; }
	const std::string& GetCurrentClipId() { return currentClip->id; }

	sf::Sprite* GetTarget() const { return target; }
	void SetTarget(sf::Sprite* t) { target = t; }

	float GetSpeed() const { return speed; }
	float SetSpeed(float s) { speed = s; }

	void Update(float dt);

	void Play(const std::string& clipId, bool clearQueue = true);
	void PlayQueue(const std::string& clipId);
	void Stop();
	void SetFrame(const AnimationFrame& frame);

};

