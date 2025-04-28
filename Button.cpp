#include "Button.h"

//constructor mit File
Button :: Button(String fileName, String textOfButton, int textSize, float x, float y, float tX, float tY, float lange, float hohe, String colorOfButton, String colorOfText) {
    
    isButtonPressed = false;

    this->tX = tX;
    this->tY = tY;
    this->x = x;
    this->y = y;

    this->lange = lange;
    this->hohe = hohe;

    image.loadFromFile(fileName);
    texture.loadFromImage(image);

    spriteOfButton.setTexture(texture);
    spriteOfButton.setTextureRect(IntRect(0, 0, lange, hohe));
    spriteOfButton.setPosition(x, y);

    font.loadFromFile("E:/projects/ProjectGFS_labyrinth/fonts/Roboto-Black.ttf");
    text.setFont(font);
    text.setString(textOfButton);
    text.setCharacterSize(textSize);
    text.setPosition(tX, tY);

    // farbe von Button
    if (colorOfButton == "Red")
        spriteOfButton.setColor(Color::Red);
    else if (colorOfButton == "Green")
        spriteOfButton.setColor(Color::Green);
    else if (colorOfButton == "Blue")
        spriteOfButton.setColor(Color::Blue);
    else if (colorOfButton == "Yellow")
        spriteOfButton.setColor(Color::Yellow);
    else if (colorOfButton == "White")
        spriteOfButton.setColor(Color::White);
    else if (colorOfButton == "BLack")
        spriteOfButton.setColor(Color::Black);
    else if (colorOfButton == "Purple")
        spriteOfButton.setColor(Color::Magenta);
    else if (colorOfButton == "Cyan")
        spriteOfButton.setColor(Color::Cyan);

    // farbe von Text
    if (colorOfText == "Red")
        text.setFillColor(Color::Red);
    else if (colorOfText == "Green")
        text.setFillColor(Color::Green);
    else if (colorOfText == "Blue")
        text.setFillColor(Color::Blue);
    else if (colorOfText == "Yellow")
        text.setFillColor(Color::Yellow);
    else if (colorOfText == "White")
        text.setFillColor(Color::White);
    else if (colorOfText == "BLack")
        text.setFillColor(Color::Black);
    else if (colorOfText == "Purple")
        text.setFillColor(Color::Magenta);
    else if (colorOfText == "Cyan")
        text.setFillColor(Color::Cyan);

}

//constructor ohne File
Button :: Button(String textOfButton, int textSize, float x, float y, float tX, float tY, float lange, float hohe, String colorOfButton, String colorOfText) {
    isButtonPressed = false;

    this->tX = tX;
    this->tY = tY;
    this->x = x;
    this->y = y;

    this->lange = lange;
    this->hohe = hohe;

    buttonShape.setSize(Vector2f(lange, hohe));
    buttonShape.setPosition(x, y);

    font.loadFromFile("E:/projects/ProjectGFS_labyrinth/fonts/Roboto-Black.ttf");
    text.setFont(font);
    text.setString(textOfButton);
    text.setCharacterSize(textSize);
    text.setPosition(tX, tY);

    // farbe von Button
    if (colorOfButton == "Red")
        buttonShape.setFillColor(Color::Red);
    else if (colorOfButton == "Green")
        buttonShape.setFillColor(Color::Green);
    else if (colorOfButton == "Blue")
        buttonShape.setFillColor(Color::Blue);
    else if (colorOfButton == "Yellow")
        buttonShape.setFillColor(Color::Yellow);
    else if (colorOfButton == "White")
        buttonShape.setFillColor(Color::White);
    else if (colorOfButton == "BLack")
        buttonShape.setFillColor(Color::Black);
    else if (colorOfButton == "Purple")
        buttonShape.setFillColor(Color::Magenta);
    else if (colorOfButton == "Cyan")
        buttonShape.setFillColor(Color::Cyan);

    // farbe von Text
    if (colorOfText == "Red")
        text.setFillColor(Color::Red);
    else if (colorOfText == "Green")
        text.setFillColor(Color::Green);
    else if (colorOfText == "Blue")
        text.setFillColor(Color::Blue);
    else if (colorOfText == "Yellow")
        text.setFillColor(Color::Yellow);
    else if (colorOfText == "White")
        text.setFillColor(Color::White);
    else if (colorOfText == "BLack")
        text.setFillColor(Color::Black);
    else if (colorOfText == "Purple")
        text.setFillColor(Color::Magenta);
    else if (colorOfText == "Cyan")
        text.setFillColor(Color::Cyan);

}

//constructor ohne Text
Button::Button(String fileName, float x, float y, float lange, float hohe, String colorOfButton) {
    isButtonPressed = false;

    this->x = x;
    this->y = y;

    tX = 0;
    tY = 0;

    this->lange = lange;
    this->hohe = hohe;

    image.loadFromFile(fileName);
    texture.loadFromImage(image);

    spriteOfButton.setTexture(texture);
    spriteOfButton.setTextureRect(IntRect(0, 0, lange, hohe));
    spriteOfButton.setPosition(Vector2f(x , y));

    // farbe von Button
    if (colorOfButton == "Red")
        spriteOfButton.setColor(Color::Red);
    else if (colorOfButton == "Green")
        spriteOfButton.setColor(Color::Green);
    else if (colorOfButton == "Blue")
        spriteOfButton.setColor(Color::Blue);
    else if (colorOfButton == "Yellow")
        spriteOfButton.setColor(Color::Yellow);
    else if (colorOfButton == "White")
        spriteOfButton.setColor(Color::White);
    else if (colorOfButton == "BLack")
        spriteOfButton.setColor(Color::Black);
    else if (colorOfButton == "Purple")
        spriteOfButton.setColor(Color::Magenta);
    else if (colorOfButton == "Cyan")
        spriteOfButton.setColor(Color::Cyan);

}

void Button :: drawButton(RenderWindow& window) {
    window.draw(spriteOfButton);
    window.draw(buttonShape);
    window.draw(text);
}

void Button :: setButtonPosition(float x, float y) {
    this->x = x;
    this->y = y;

    spriteOfButton.setPosition(Vector2f(x, y));
    buttonShape.setPosition(Vector2f(x, y));
}

void Button :: buttonPressing(Event event, RenderWindow& window) {

    Vector2i mousePos = Mouse::getPosition(window);

    if (event.type == Event::MouseButtonPressed) {
        if (event.key.code == Mouse::Left) {
            if (spriteOfButton.getGlobalBounds().contains(mousePos.x, mousePos.y) || buttonShape.getGlobalBounds().contains(mousePos.x, mousePos.y)) {

                buttonShape.setPosition(x + 3, y + 3);
                buttonShape.setScale(0.95, 0.95);

                spriteOfButton.setPosition(x + 3, y + 3);
                spriteOfButton.setScale(0.95, 0.95);

                text.setPosition(tX + 3, tY + 3);
                text.setScale(0.95, 0.95);
            }
        }

    }

    if (event.type == Event::MouseButtonReleased) {
        if (event.key.code == Mouse::Left) {
            if (spriteOfButton.getGlobalBounds().contains(mousePos.x, mousePos.y) || buttonShape.getGlobalBounds().contains(mousePos.x, mousePos.y)) {

                buttonShape.setPosition(x, y);
                buttonShape.setScale(1, 1);

                spriteOfButton.setPosition(x, y);
                spriteOfButton.setScale(1, 1);

                text.setPosition(tX, tY);
                text.setScale(1, 1);

                isButtonPressed = true;
            }
        }
    }
}

void Button :: setTextPosition(float tX, float tY) {
    this->tX = tX;
    this->tY = tY;

    text.setPosition(Vector2f(tX, tY));
}

void Button::setNewText(String textOfButton) {
    text.setString(textOfButton);
}
