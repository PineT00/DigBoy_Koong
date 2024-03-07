#pragma once
#include "GameObject.h"
class TileMap :
    public GameObject
{

public:
	std::vector<int> level;
	sf::Vector2i cellCount = { 15, 6 };

protected:

	std::string spriteSheetId;
	sf::Texture* texture;
	TileMap* tilemap;

	int rows = 10;
	int cols = 10;


	sf::Vector2f cellSize = { 42.f, 42.f }; //��ƴø���

	sf::Transform transform;

public:
	sf::VertexArray va;

	sf::Vector2f posOffset[4];
	sf::Vector2f texCoord0[4];


	sf::FloatRect GetTileBound(int x, int y);

	TileMap(const std::string& name = "");

	virtual sf::FloatRect GetLocalBounds() override;
	virtual sf::FloatRect GetGlobalBounds() override;

	const sf::Vector2i& GetCellCount() const { return cellCount; }
	const sf::Vector2f& GetCellSize() const { return cellSize; }

	void SetLevel(const std::string& filename);

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

