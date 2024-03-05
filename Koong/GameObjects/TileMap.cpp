#include "pch.h"
#include "TileMap.h"

TileMap::TileMap(const std::string& name)
    :GameObject(name)
{
}

sf::FloatRect TileMap::GetLocalBounds()
{
    sf::FloatRect bounds = va.getBounds();
    bounds.left = origin.x;
    bounds.top = origin.y;
    return bounds;
}

sf::FloatRect TileMap::GetGlobalBounds()
{
    sf::FloatRect bounds = va.getBounds();
    return transform.transformRect(bounds);
}

void TileMap::Set(sf::Vector2i& count, sf::Vector2f& size)
{
    cellCount = count;
    cellSize = size;

    va.clear();
    va.setPrimitiveType(sf::Quads);
    va.resize(count.x * count.y * 4);

    sf::Vector2f posOffset[4] = {
        { 0, 0 },
        { size.x, 0 },
        { size.x, size.y },
        { 0, size.y },
    };

    sf::Vector2f texCoord0[4] = {
        { 0, 0 },
        { 42.f, 0 },
        { 42.f, 42.f },
        { 0, 42.f },
    };

    int level[] =
    {
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,30,30,1,1,1,30,30,1,1,1,1,1,1,1,1,
        1,1,1,1,1,30,30,1,1,1,30,30,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,10,1,1,1,1,1,10,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,5,5,5,5,5,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    };

    for (int i = 0; i < count.y; ++i)
    {
        for (int j = 0; j < count.x; ++j)
        {

            int texIndexY = level[i * count.x + j];
            int texIndexX = 0;

            if (texIndexY > 5)
            {
                if(texIndexY % 5 == 0)
                {
                    texIndexX = (texIndexY / 5) - 1;
                    texIndexY = 5;
                }
                else
                {
                    texIndexX = texIndexY / 5;
                    texIndexY = texIndexY % 5;
                }
            }

            int quadIndex = i * count.x + j;
            sf::Vector2f quadPos(size.x * j, size.y * i);

            for (int k = 0; k < 4; k++)
            {
                int vertexIndex = ((quadIndex * 4) + k);
                va[vertexIndex].position = quadPos + posOffset[k];
                va[vertexIndex].texCoords = texCoord0[k] ;

                va[vertexIndex].texCoords.x += texIndexX * 42.f;
                va[vertexIndex].texCoords.y += texIndexY * 42.f;
            }

        }

    }
}

void TileMap::SetSpriteSheetId(const std::string& id)
{
    spriteSheetId = id;
    texture = &RES_MGR_TEXTURE.Get(spriteSheetId);
}

void TileMap::UpdateTransform()
{
    transform = sf::Transform::Identity;
    float scaleX = isFlipX ? -scale.x : scale.x;
    float scaleY = isFlipY ? -scale.y : scale.y;
    transform.scale(scaleX, scaleY, position.x, position.y);
    transform.rotate(rotation, position.x, position.y);
    transform.translate(position - origin);
}

void TileMap::SetOrigin(Origins preset)
{
    if (preset == Origins::Custom)
        return;

    originPreset = preset;
    sf::FloatRect bound = va.getBounds();
    origin.x = bound.width * ((int)originPreset % 3) * 0.5f;
    origin.y = bound.height * ((int)originPreset / 3) * 0.5f;
    UpdateTransform();

}

void TileMap::SetOrigin(const sf::Vector2f& newOrigin)
{
    originPreset = Origins::Custom;
    origin = newOrigin;
    UpdateTransform();
}

void TileMap::SetPosition(const sf::Vector2f& pos)
{

    GameObject::SetPosition(pos);
    transform.translate(position);
    UpdateTransform();
}

void TileMap::Translate(const sf::Vector2f& delta)
{
    GameObject::Translate(delta);
    transform.translate(position);
    UpdateTransform();
}

void TileMap::SetRotation(float r)
{
    GameObject::SetRotation(r);
    UpdateTransform();
}

void TileMap::SetScale(const sf::Vector2f& scale)
{
    GameObject::SetScale(scale);
    transform.scale(this->scale);
    UpdateTransform();
}

void TileMap::SetFlipX(bool flip)
{
    GameObject::SetFlipX(flip);
    UpdateTransform();
}

void TileMap::SetFlipY(bool flip)
{
    GameObject::SetFlipY(flip);
    UpdateTransform();
}

void TileMap::Init()
{
    GameObject::Init();
    SetSpriteSheetId("graphics/FSADIGBOY19-9.png");
    Set(cellCount, cellSize);
    //SetOrigin(Origins::MC);
}

void TileMap::Release()
{
    GameObject::Release();
}

void TileMap::Reset()
{
    GameObject::Reset();
}

void TileMap::Update(float dt)
{
    GameObject::Update(dt);
}

void TileMap::Draw(sf::RenderWindow& window)
{
    //GameObject::Draw(window);
    sf::RenderStates state;
    state.texture = texture;
    state.transform = transform;

    window.draw(va, state);

}
