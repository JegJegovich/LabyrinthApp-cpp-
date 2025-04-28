#include "textFeld.h"

textFeld::textFeld(string feldText, float x, float y, int zahl)
{
    isZahlEnter = false;
    isOkButtonPressed = false; 
    this->zahl = zahl;

    this->x = x;
    this->y = y;

    //font
    font.loadFromFile("E:/projects/ProjectGFS_labyrinth/fonts/Roboto-Black.ttf");

    if (!font.loadFromFile("E:/projects/ProjectGFS_labyrinth/fonts/Roboto-Black.ttf")) {
        return;
    }

    //text vor dem Textfeld
    textOfFeld.setFont(font);
    textOfFeld.setCharacterSize(40);
    textOfFeld.setFillColor(Color::Blue);
    textOfFeld.setString(feldText);
    textOfFeld.setPosition(x, y);

    image.loadFromFile("E:/projects/ProjectGFS_Labyrinth/images/okButton.png");
    texture.loadFromImage(image);

    tX = x + 150;
    tY = y + 5;

    // Hintergrund hinter dem eingegebenen Text
    textBackground.setSize(Vector2f(80, 40));
    textBackground.setFillColor(Color::White);
    textBackground.setPosition(Vector2f(tX, tY));

    // eingegebene Zahl
    text.setString(to_string(zahl));
    text.setFont(font);
    text.setCharacterSize(40);
    text.setFillColor(Color::Black);
    text.setPosition(tX + 2 , tY - 2);

    //taste OK
    bX = tX + 85;
    bY = tY - 10;

    spriteOfButton.setTexture(texture);
    spriteOfButton.setTextureRect(IntRect(0, 0, 60, 60));
    spriteOfButton.setPosition(Vector2f(bX, bY));
}

void textFeld::draw(RenderWindow& window) {
    window.draw(textOfFeld);
    window.draw(textBackground);
    window.draw(spriteOfButton);
    window.draw(text);
}

void textFeld::setIntText(int zahl) {
    this->zahl = zahl;
    str = to_string(zahl);
}

void textFeld::inputText(Event event, RenderWindow& window) {
    Vector2i mousePos = Mouse::getPosition(window);

    if (event.type == Event::MouseButtonPressed) {
        if (event.key.code == Mouse::Left) {
            if (textBackground.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                textBackground.setPosition(Vector2f(tX - 1.5, tY - 1.5));
                textBackground.setScale(Vector2f(0.95, 0.95));
            }
        }
    }

    if (event.type == Event::MouseButtonReleased) {
        if (event.key.code == Mouse::Left) {
            if (textBackground.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                textBackground.setPosition(Vector2f(tX, tY));
                textBackground.setScale(Vector2f(1, 1));
                str = "";
                text.setString(str);
                isZahlEnter = true;
            }
        }
    }

    if (event.type == Event::TextEntered && isZahlEnter)
    {
        if (event.text.unicode < 128 && str.length() <= 2) {
            if (event.type == Event::KeyReleased) {
                if (event.key.code == Keyboard::BackSpace) {
                   str.pop_back();
                   text.setString(str);
                }
            }
            else {
                str += event.text.unicode;
                text.setString(str);
            }
        }
    }

    if (OkButtonIsPressed()) {
        isZahlEnter = false;
    }
}

void textFeld::okButtonPressing(Event event, RenderWindow& window) {

    Vector2i mousePos = Mouse::getPosition(window);

    if (event.type == Event::MouseButtonPressed) {
        if (event.key.code == Mouse::Left) {
            if (spriteOfButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {

                spriteOfButton.setPosition(bX - 1.5, bY - 1.5);
                spriteOfButton.setScale(0.95, 0.95);

                isOkButtonPressed = true;
            }
        }
    }

    if (event.type == Event::MouseButtonReleased) {
        if (event.key.code == Mouse::Left) {
            if (spriteOfButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {

                spriteOfButton.setPosition(bX, bY);
                spriteOfButton.setScale(1, 1);

                isOkButtonPressed = false;
            }
        }
    }
}
