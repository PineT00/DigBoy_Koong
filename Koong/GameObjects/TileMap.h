#pragma once
#include "GameObject.h"
class TileMap :
    public GameObject
{
protected:
    sf::VertexArray va;
	std::string spriteSheetId;
	sf::Texture* texture;
	TileMap* tilemap;

	int rows = 10;
	int cols = 10;

	sf::Vector2i cellCount = { 20, 2 };
	sf::Vector2f cellSize = { 42.f, 42.f }; //��ƴø���

	sf::Transform transform;



public:
	bool isDigging = false;

	TileMap(const std::string& name = "");

	virtual sf::FloatRect GetLocalBounds() override;
	virtual sf::FloatRect GetGlobalBounds() override;

	const sf::Vector2i& GetCellCount() const { return cellCount; }
	const sf::Vector2f& GetCellSize() const { return cellSize; }

	void Set(sf::Vector2i& count, sf::Vector2f& size);

	void SetSpriteSheetId(const std::string& id);
	void UpdateTransform();

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void SetPosition(const sf::Vector2f& pos) override;
	void Translate(const sf::Vector2f& delta) override;
	void SetRotation(float r) override;

	void SetScale(const sf::Vector2f& scale) override;

	void SetFlipX(bool flip) override;
	void SetFlipY(bool flip) override;

	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;


};

