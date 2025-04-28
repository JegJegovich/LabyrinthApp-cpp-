#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

using namespace std;
using namespace sf;

class textFeld
{
private:
	Font font;
	Text textOfFeld, text;
	Texture texture;
	Image image;
	Sprite spriteOfButton;
	string str;
	RectangleShape textBackground;
	bool isZahlEnter, isOkButtonPressed;
	int zahl;
	float x, y, bX, bY, tX, tY;

	string getStrText() {
		return str;
	}
public: 

	textFeld(string textFeld, float x, float y, int zahl);

	void draw(RenderWindow& window);

	int getIntText() {
		zahl = stoi(getStrText());
		return zahl;
	}

	void setIntText(int zahl);

	bool OkButtonIsPressed() {
		return isOkButtonPressed;
	}

	void inputText(Event event, RenderWindow& window);

	void okButtonPressing(Event event, RenderWindow& window);
};

