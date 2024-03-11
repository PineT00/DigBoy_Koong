#include "GameObject.h"
#include "SpriteGo.h"
#include "TextGo.h"

class UiHud : public GameObject
{
protected:
	sf::Vector2f referenceResolution = { 1080, 1080 };
	sf::Vector2f resolution = referenceResolution;

	std::string formatScore = "SCORE: ";
	std::string formatFps = "FPS: ";

	TextGo textScore;
	TextGo textFps;

	SpriteGo Main;

public:
	UiHud(const std::string& name = "");
	~UiHud() override = default;

	void SetResolution(const sf::Vector2f resolution);
	void SetScore(int s);

	void SetMessage(const std::string& msg);
	void SetMessageActive(bool active);

	void SetFps(int fps);

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};