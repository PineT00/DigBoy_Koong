#pragma once
#include "GameObject.h"

//class OreGo;

class TileMap :
    public GameObject
{

public:
	std::vector<int> level; //甘鸥老 加己

protected:
	std::string spriteSheetId;
	sf::Texture* texture;
	TileMap* tilemap;

	int rows = 10;
	int cols = 10;

	//sf::Vector2i cellCount = { 20,10 };
	sf::Vector2i cellCount = { 60, 412 };
	sf::Vector2f cellSize = { 42.f, 42.f }; //棱酒疵府扁

	sf::Transform transform;

public:
	sf::VertexArray va;
	sf::Vector2f posOffset[4];
	sf::Vector2f texCoord0[4];

	int blockedTile[14] = {16, 56, 60, 72, 73, 74, 75, 76, 77, 78, 80, 81, 82, 83};
	int openTile[3] = {-1, 0, 32};
	int oreTile[4] = { 80, 81, 82, 83 };


	sf::FloatRect GetTileBound(int x, int y);

	TileMap(const std::string& name = "");

	virtual sf::FloatRect GetLocalBounds() override;
	virtual sf::FloatRect GetGlobalBounds() override;

	const sf::Vector2i& GetCellCount() const { return cellCount; }
	const sf::Vector2f& GetCellSize() const { return cellSize; }

	void SetLevel(const std::string& filename);

	void TextureChange(int x, int y, int rowX, int columnY);
	void changeTile(int x, int y);


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

