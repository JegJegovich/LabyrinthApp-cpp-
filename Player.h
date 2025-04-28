#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <random>

using namespace std;
using namespace sf;

class Player {
private:

	float cellSize;
	float xP, yP;
	int richtung;
	Sprite spieler;
	Texture texture;
	Image image;

public:

	Player(String fileName, float cellSize);

	Sprite getSprite() {
		return spieler;
	}

	void bewegen( float  moveX, float moveY);

	void setPosition(float  x, float y);

	void goToStart();

	float getXPosition() {
		return xP;
	}

	float getYPosition() {
		return yP;
	}

	void draw(RenderWindow& window) const;
};
