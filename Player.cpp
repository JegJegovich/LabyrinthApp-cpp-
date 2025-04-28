#include "Player.h"

Player::Player(String fileName, float cellSize) {
	image.loadFromFile(fileName);

	texture.loadFromImage(image);
	this->spieler.setTexture(texture);
	this->spieler.setTextureRect(IntRect(0, 0, cellSize, cellSize));

	xP = cellSize; yP = cellSize;
	this->spieler.setPosition(yP, xP);

	this->cellSize = cellSize;
}

void Player::bewegen(float  moveX, float moveY) {
	xP += moveX;
	yP += moveY;
	spieler.setPosition(xP, yP);
}

void Player::goToStart() {
	xP = cellSize;
	yP = cellSize;
	spieler.setPosition(xP, yP);
}

void Player::setPosition(float x, float y) {
	xP = x;
	yP = y;
	spieler.setPosition(xP, yP);
}

void Player::draw(RenderWindow& window) const {
	window.draw(spieler);
}