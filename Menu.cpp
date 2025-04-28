#include "Menu.h"

Menu::Menu(float lange, float hohe) {

	if (!font.loadFromFile("E:/projects/ProjectGFS_labyrinth/fonts/Roboto-Black.ttf")) {
		cout << "Font is not hier!";
	}

	buttonPressed = false;

	//Spielen
	menuText[0].setFont(font);
	menuText[0].setFillColor(Color::Yellow);
	menuText[0].setString("Spielen");
	menuText[0].setCharacterSize(fontSize);
	menuText[0].setPosition(lange / 3, 100);
	//Einstellungen
	menuText[1].setFont(font);
	menuText[1].setFillColor(Color::Yellow);
	menuText[1].setString("Einstellungen");
	menuText[1].setCharacterSize(fontSize);
	menuText[1].setPosition(lange / 3, 250);

	//über Spiel
	menuText[2].setFont(font);
	menuText[2].setFillColor(Color::Yellow);
	menuText[2].setString("über Spiel");
	menuText[2].setCharacterSize(fontSize);
	menuText[2].setPosition(lange / 3, 400);

	//Exit
	menuText[3].setFont(font);
	menuText[3].setFillColor(Color::Yellow);
	menuText[3].setString("Exit");
	menuText[3].setCharacterSize(fontSize);
	menuText[3].setPosition(lange / 3, 550);

	menuSelected = -1;
}

//MoveUp
void Menu::moveUp() {
	menuSelected--;

	if (menuSelected >=  0) {
		menuText[menuSelected].setFillColor(Color::Red);
		menuText[menuSelected + 1].setFillColor(Color::Yellow);
	}
	else {
		menuText[0].setFillColor(Color::Yellow);
		menuSelected = 3;
		menuText[menuSelected].setFillColor(Color::Red);
	}
}


//MoveDown
void Menu::moveDown() {
	menuSelected++;

	if (menuSelected < 4) {
		menuText[menuSelected - 1].setFillColor(Color::Yellow);
		menuText[menuSelected].setFillColor(Color::Red);
	}
	else {
		menuText[3].setFillColor(Color::Yellow);
		menuSelected = 0;
		menuText[menuSelected].setFillColor(Color::Red);
	}
}

void Menu::menuButtonPressing(Event event, RenderWindow& window) {

	Vector2i mousePos = Mouse::getPosition(window);

	if (menuText[0].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
		menuSelected = 0;
		menuText[menuSelected].setFillColor(Color::Red);
		if (event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left) {
			buttonPressed = true;
		}
	}
	else if (menuText[1].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
		menuSelected = 1;
		menuText[menuSelected].setFillColor(Color::Red);
		if (event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left) {
			buttonPressed = true;
		}
	}
	else if (menuText[2].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
		menuSelected = 2;
		menuText[menuSelected].setFillColor(Color::Red);
		if (event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left) {
			buttonPressed = true;
		}
	}
	else if (menuText[3].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
		menuSelected = 3;
		menuText[menuSelected].setFillColor(Color::Red);
		if (event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left) {
			buttonPressed = true;
		}
	}
	else {
		menuText[menuSelected].setFillColor(Color::Yellow);
		buttonPressed = false;
	}
}

//MainWindow malen
void Menu::draw(RenderWindow& window) {
	for (int i = 0; i < 4; i++) {
		window.draw(menuText[i]);
	}
}