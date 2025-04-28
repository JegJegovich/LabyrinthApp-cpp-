#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <random>

using namespace std;
using namespace sf;

class Menu{
private:
	float hohe, lange, x, y, schritte;
	int menuSelected;
	Font font;
	Text menuText[4];
	bool buttonPressed = false;
	int fontSize = 70;
public:
	Menu(float lange, float hohe);

    void draw(RenderWindow& window);

	void moveUp();

	void moveDown();

	int menuPresed() {
		return  menuSelected;
	}

	bool menuButtonIsPressed() {
		return buttonPressed;
	}

	void menuButtonPressing(Event event, RenderWindow& window);
};

