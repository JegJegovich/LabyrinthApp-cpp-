#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <random>


using namespace std;
using namespace sf;

class Button {
private:
    Font font;
    Text text;
    Texture texture;
    Image image;
    Sprite spriteOfButton;
    RectangleShape buttonShape;
    Vector2f position;
    float x, y, lange, hohe, tX, tY;
    bool isButtonPressed;

public:
    //constructor mit File
    Button(String fileName, String textOfButton, int textSize, float x, float y, float tX, float tY, float lange, float hohe, String colorOfButton, String colorOfText);

    //constructor ohne File
    Button(String textOfButton, int textSize, float x, float y, float tX, float tY, float lange, float hohe, String colorOfButton, String colorOfText);

    //constructor ohne Text
    Button(String fileName, float x, float y, float lange, float hohe, String colorOfButton);

    void drawButton(RenderWindow& window);

    bool buttonIsPressed() {
        return isButtonPressed;
    }

    void setButtonPosition(float x, float y);

    void setTextPosition(float tX, float tY);

    void setNewText(String text);

    void buttonPressing(Event event, RenderWindow& window);
};