#include "pch.h"
#include "SpriteGo.h"

SpriteGo::SpriteGo(const std::string& name)
	: GameObject(name)
{
}

void SpriteGo::SetTexture(const std::string& textureId)
{
	this->texturId = textureId;

	sprite.setTexture(RES_MGR_TEXTURE.Get(textureId));
}

void SpriteGo::SetPosition(const sf::Vector2f& pos)
{
	//GameObject::SetPosition(pos);
	position = pos;
	sprite.setPosition(pos);
}

void SpriteGo::Translate(const sf::Vector2f& delta)
{
	position += delta;
	sprite.setPosition(position);
}

void SpriteGo::SetRotation(float r)
{
	rotation = r;
	sprite.setRotation(rotation);
}

void SpriteGo::SetOrigin(Origins preset)
{
	if (preset == Origins::Custom)
	{
		preset = Origins::TL;
	}
	originPreset = preset;
	origin = Utils::SetOrigin(sprite, originPreset);
}

void SpriteGo::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	sprite.setOrigin(newOrigin);
}

void SpriteGo::SetScale(const sf::Vector2f& s)
{
	sf::Vector2f spriteScale = scale = s;
	if (isFlipX)
	{
		spriteScale.x = -scale.x;
	}
	if (isFlipY)
	{
		spriteScale.y = -scale.y;
	}
	sprite.setScale(spriteScale);
}

void SpriteGo::SetFlipX(bool filp)
{
	if (isFlipX == filp)
		return;

	isFlipX = filp;
	SetScale(scale);
}

void SpriteGo::SetFlipY(bool filp)
{
	if (isFlipY == filp)
		return;

	isFlipY = filp;
	SetScale(scale);
}

void SpriteGo::Reset()
{
	sprite.setTexture(RES_MGR_TEXTURE.Get(texturId));
}

void SpriteGo::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);

	if (SCENE_MGR.GetDeveloperMode())
	{
		sf::RectangleShape globalHitBox;
		sf::FloatRect globalBound = sprite.getGlobalBounds();

		globalHitBox.setPosition(globalBound.left, globalBound.top);
		globalHitBox.setSize({ globalBound.width, globalBound.height });
		globalHitBox.setOutlineColor(sf::Color::Red);
		globalHitBox.setOutlineThickness(1.f);
		globalHitBox.setFillColor(sf::Color::Transparent);

		window.draw(globalHitBox);
	}

}
