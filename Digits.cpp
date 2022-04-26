#include "Digits.h"
void Digits::setTexture() {
	this->texture = TextureManager::GetTexture("digits");
}
sf::Sprite Digits::getSprite() {
	return this->sprite;
}
void Digits::getDigit(int number) {
	this->sprite = sf::Sprite(this->texture);
	this->sprite.setTextureRect(sf::IntRect(number*21,0,21,32));
}
void Digits::setPosition(float x, float y) {
	this->sprite.setPosition(x,y);
}