#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include <vector>
using std::vector;
class Digits
{
	sf::Texture texture;
	sf::Sprite sprite;
public:
	void setTexture(), getDigit(int number), setPosition(float x, float y);
	sf::Sprite getSprite();
};