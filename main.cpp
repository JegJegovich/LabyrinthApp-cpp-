#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <string>
#include "Labyrinth.h"
#include "Button.h"
#include "Player.h"
#include "Menu.h"
#include "view.h"
#include "textFeld.h"

using namespace std;
using namespace sf;

int inputRows = 20, inputCols = 20;

float cellSize = 80;

float mapLange = inputCols * cellSize;
float mapHohe = inputRows * cellSize;

int fensterLange = 960;
int fensterHohe = 720;

int spielFensterLange = 960;
int spielFensterHohe = 720;

float xPos = 0;
float yPos = 0;

int schrittenanzahl = 0;

int main() {

    srand(time(0));

    Font font;
    font.loadFromFile("E:/projects/ProjectGFS_labyrinth/fonts/Roboto-Black.ttf");

    // Text vor dem Anzhal der SChritten
    Text schrittenText;
    string strSchrittenText = "Schritten: ";
    schrittenText.setFont(font);
    schrittenText.setString(strSchrittenText);
    schrittenText.setCharacterSize(25);
    schrittenText.setFillColor(Color :: Red);
    schrittenText.setPosition(cellSize - 30, cellSize - 20);

    // Anzahl der Schritten
    Text schritten;
    schritten.setFont(font);
    schritten.setString(to_string(schrittenanzahl));
    schritten.setCharacterSize(25);
    schritten.setFillColor(Color::Red);
    schritten.setPosition(cellSize + 90, cellSize - 20);


    Clock clock;

    RenderWindow MENU(VideoMode(fensterLange, fensterHohe), "Labyrinth Menu");

    Menu menu(MENU.getSize().x, MENU.getSize().y);


    while (MENU.isOpen()) {
        Event menuEvent;

        while (MENU.pollEvent(menuEvent)) {

            if (menuEvent.type == Event::Closed) {
                MENU.close();
            }

            menu.menuButtonPressing(menuEvent, MENU);

            if (menuEvent.type == Event::KeyReleased) {
                if (menuEvent.key.code == Keyboard::Up) {
                    menu.moveUp();
                }

                if (menuEvent.key.code == Keyboard::Down) {
                    menu.moveDown();
                }
            }

            if (menuEvent.key.code == Keyboard::Return || menu.menuButtonIsPressed()) {

                RenderWindow SPIEL(VideoMode(fensterLange, fensterHohe), "Labyrinth Spiel");
                RenderWindow EINSTELLUNGEN(VideoMode(fensterLange, fensterHohe), "Labyrinth Einstellungen");
                RenderWindow UBERSPIEL(VideoMode(fensterLange, fensterHohe), "Labyrinth über Spiel");

                int selectedButton = menu.menuPresed();

                //SPIELEN//
                if (selectedButton == 0) {
                    schrittenanzahl = 0;

                    float pX = 1;
                    float pY = 1;

                    bool losungZeigen = false;

                    Labyrinth labyrinth(inputRows, inputCols, cellSize);

                    Player spieler("images/player.png", cellSize);     

                    view.reset(FloatRect(0, 0, fensterLange, fensterHohe));

                    getPlayerCoordinateForView(spieler.getXPosition(), spieler.getYPosition(), mapLange, mapHohe);

                    while (SPIEL.isOpen()) {
                        float time = clock.getElapsedTime().asMicroseconds();
                        clock.restart();
                        time = time / 1500;

                        Event spielEvent;

                        while (SPIEL.pollEvent(spielEvent)) {
                            //exit
                            if (spielEvent.type == Event::Closed) {
                                SPIEL.close();
                            }
                            if (spielEvent.type == Event::KeyReleased) {
                                if (spielEvent.key.code == Keyboard::Escape) {
                                    SPIEL.close();
                                }
                                //Menu im Spiele
                                if (spielEvent.key.code == Keyboard::M || spielEvent.key.code == Keyboard::Tab) {
                                    RenderWindow MENUImSpiel(VideoMode(960, 720), "Spiel Menu");

                                    textFeld hoheInput("Hohe: ", 50, 100, inputRows);

                                    textFeld langeInput("Lange: ", 400, 100, inputCols);

                                    Button newGeneratingButton("images/Button.png", "New Generating", 23, 70, 170, 85, 190, 200, 75, "Cyan", "White");

                                    Button losungZeigenButton("images/Button.png", "Losung Zeigen", 23, 430, 170, 445, 190, 200, 75, "Red", "White");

                                    Button losungVersteckenButton("images/Button.png", "Losung Verstecken", 21, 430, 300, 435, 320, 200, 75, "Purple", "White");

                                    while (MENUImSpiel.isOpen()) {

                                        Event menuImSpielEvent;

                                        while (MENUImSpiel.pollEvent(menuImSpielEvent)) {
                                          
                                            if (menuImSpielEvent.type == Event::Closed) {
                                                MENUImSpiel.close();
                                            }

                                            if (menuImSpielEvent.type == Event::KeyReleased) {
                                                if (menuImSpielEvent.key.code == Keyboard::Escape) {
                                                    MENUImSpiel.close();
                                                }
                                            }

                                            // eingebung der Hohe
                                            if (hoheInput.OkButtonIsPressed()) {
                                                SPIEL.clear();
                                                schrittenanzahl = 0;
                                                schrittenText.setPosition(cellSize - 30, cellSize - 20); 
                                                schritten.setPosition(cellSize + 90, cellSize - 20);
                                                schritten.setString(to_string(schrittenanzahl));
                                                inputRows = hoheInput.getIntText();
                                                labyrinth.setRows(inputRows);
                                                labyrinth.generateLabyrninth();
                                                losungZeigen = false;
                                                spieler.goToStart();
                                                pX = 1; pY = 1;
                                                SPIEL.display();
                                                MENUImSpiel.close();
                                                mapHohe = inputRows * cellSize;
                                                getPlayerCoordinateForView(spieler.getXPosition(), spieler.getYPosition(), mapLange, mapHohe);
                                            }

                                            // eingebung der lange
                                            if (langeInput.OkButtonIsPressed()) {
                                                SPIEL.clear();
                                                schrittenanzahl = 0;
                                                schrittenText.setPosition(cellSize - 30, cellSize - 20);
                                                schritten.setPosition(cellSize + 90, cellSize - 20);
                                                schritten.setString(to_string(schrittenanzahl));
                                                inputCols = langeInput.getIntText();
                                                labyrinth.setCols(inputCols);
                                                labyrinth.generateLabyrninth();
                                                losungZeigen = false;
                                                spieler.goToStart();
                                                pX = 1; pY = 1;
                                                SPIEL.display();
                                                MENUImSpiel.close();
                                                mapLange = inputCols * cellSize;
                                                getPlayerCoordinateForView(spieler.getXPosition(), spieler.getYPosition(), mapLange, mapHohe);
                                            }

                                            // Tatste fur neue Generation
                                            if (newGeneratingButton.buttonIsPressed()) {
                                                SPIEL.clear();
                                                schrittenanzahl = 0;
                                                schrittenText.setPosition(cellSize - 30, cellSize - 20);
                                                schritten.setPosition(cellSize + 90, cellSize - 20);
                                                schritten.setString(to_string(schrittenanzahl));
                                                labyrinth.generateLabyrninth();
                                                losungZeigen = false;
                                                spieler.goToStart();
                                                pX = 1; pY = 1;
                                                MENUImSpiel.close();
                                                SPIEL.display();
                                                getPlayerCoordinateForView(spieler.getXPosition(), spieler.getYPosition(), mapLange, mapHohe);
                                            }

                                            // Taste, die Labyrinth-Lösung zeigt 
                                            if (losungZeigenButton.buttonIsPressed()) {
                                                losungZeigen = true;
                                                labyrinth.losungFinden();
                                                MENUImSpiel.close();
                                            }

                                            // Taste, die Labyrinth-Lösung versteckt
                                            if (losungVersteckenButton.buttonIsPressed()) {
                                                losungZeigen = false;
                                                MENUImSpiel.close();
                                            }


                                            langeInput.inputText(menuImSpielEvent, MENUImSpiel);
                                            langeInput.okButtonPressing(menuImSpielEvent, MENUImSpiel);

                                            hoheInput.inputText(menuImSpielEvent, MENUImSpiel);
                                            hoheInput.okButtonPressing(menuImSpielEvent, MENUImSpiel);

                                            newGeneratingButton.buttonPressing(menuImSpielEvent, MENUImSpiel);

                                            losungZeigenButton.buttonPressing(menuImSpielEvent, MENUImSpiel);

                                            losungVersteckenButton.buttonPressing(menuImSpielEvent, MENUImSpiel);
                                        }

                                        EINSTELLUNGEN.close();
                                        UBERSPIEL.close();

                                        MENUImSpiel.clear(Color::Black);


                                        hoheInput.draw(MENUImSpiel);
                                        langeInput.draw(MENUImSpiel);

                                        newGeneratingButton.drawButton(MENUImSpiel);
                                        losungZeigenButton.drawButton(MENUImSpiel);
                                        losungVersteckenButton.drawButton(MENUImSpiel);

                                        MENUImSpiel.display();
                                    }
                                }
                            }
                            //bewegung des Spielers
                            if (spielEvent.type == Event::KeyPressed) {
                                if (spielEvent.key.code == Keyboard::W && !labyrinth.isWall(pY - 1, pX)) {
                                    pY -= 1;
                                    schrittenanzahl += 1;
                                    schritten.setString(to_string(schrittenanzahl));
                                    spieler.setPosition(pX * cellSize, pY * cellSize);
                                    schrittenText.setPosition(spieler.getXPosition() - 30, spieler.getYPosition() - 20);
                                    schritten.setPosition(spieler.getXPosition() + 90, spieler.getYPosition() - 20);
                                    getPlayerCoordinateForView(spieler.getXPosition(), spieler.getYPosition(), mapLange, mapHohe);
                                }
                                if (spielEvent.key.code == Keyboard::A && !labyrinth.isWall(pY, pX - 1)) {
                                    pX -= 1;
                                    schrittenanzahl += 1;
                                    schritten.setString(to_string(schrittenanzahl));
                                    spieler.setPosition(pX * cellSize, pY * cellSize);
                                    schrittenText.setPosition(spieler.getXPosition() - 30, spieler.getYPosition() - 20);
                                    schritten.setPosition(spieler.getXPosition() + 90, spieler.getYPosition() - 20);
                                    getPlayerCoordinateForView(spieler.getXPosition(), spieler.getYPosition(), mapLange, mapHohe);
                                }
                                if (spielEvent.key.code == Keyboard::S && !labyrinth.isWall(pY + 1, pX)) {
                                    pY += 1;
                                    schrittenanzahl += 1;
                                    schritten.setString(to_string(schrittenanzahl));
                                    spieler.setPosition(pX * cellSize, pY * cellSize);
                                    schrittenText.setPosition(spieler.getXPosition() - 30, spieler.getYPosition() - 20);
                                    schritten.setPosition(spieler.getXPosition() + 90, spieler.getYPosition() - 20);
                                    getPlayerCoordinateForView(spieler.getXPosition(), spieler.getYPosition(), mapLange, mapHohe);
                                }
                                if (spielEvent.key.code == Keyboard::D && !labyrinth.isWall(pY, pX + 1)) {
                                    pX += 1;
                                    schrittenanzahl += 1;
                                    schritten.setString(to_string(schrittenanzahl));
                                    spieler.setPosition(pX * cellSize, pY * cellSize);
                                    schrittenText.setPosition(spieler.getXPosition() - 30, spieler.getYPosition() - 20);
                                    schritten.setPosition(spieler.getXPosition() + 90, spieler.getYPosition() - 20);
                                    getPlayerCoordinateForView(spieler.getXPosition(), spieler.getYPosition(), mapLange, mapHohe);
                                }
                            }
                            //
                            
                            //view
                            viewMap(time, spielEvent);

                            changeView(spielEvent);    
                            //
                        }

                        // schliessen andere Fenster
                        EINSTELLUNGEN.close();
                        UBERSPIEL.close();


                        SPIEL.setView(view);

                        SPIEL.clear(Color::Cyan);

                        labyrinth.draw(SPIEL, losungZeigen);
                       
                        spieler.draw(SPIEL);

                        SPIEL.draw(schrittenText);
                        
                        SPIEL.draw(schritten);

                        SPIEL.display();
                    }
                }
                //EINSTELLUNGEN//
                if (selectedButton == 1) {
                    textFeld hoheInput("Hohe: ", 50, 100, inputRows);

                    while (EINSTELLUNGEN.isOpen()) {
                        Event einstellungenEvent;

                        while (EINSTELLUNGEN.pollEvent(einstellungenEvent)) {
                            if (einstellungenEvent.type == Event::Closed) {
                                EINSTELLUNGEN.close();
                            }

                            if (einstellungenEvent.type == Event::KeyReleased) {
                                if (einstellungenEvent.key.code == Keyboard::Escape) {
                                    EINSTELLUNGEN.close();
                                }
                            }
                        }
                        SPIEL.close();
                        UBERSPIEL.close();

                        EINSTELLUNGEN.clear(Color::Green);             

                        EINSTELLUNGEN.display();
                    }
                }

                //UBERSPIEL//
                if (selectedButton == 2) {
                    while (UBERSPIEL.isOpen()) {
                        Event event;

                        while (UBERSPIEL.pollEvent(event)) {
                            if (event.type == Event::Closed) {
                                UBERSPIEL.close();
                                break;
                            }

                            if (event.type == Event::KeyReleased) {
                                if (event.key.code == Keyboard::Escape) {
                                    UBERSPIEL.close();
                                    break;
                                }
                            }

                        }
                        SPIEL.close();
                        EINSTELLUNGEN.close();

                        UBERSPIEL.clear();

                        UBERSPIEL.display();
                    }
                }

                //SCHLIESSEN//
                if (selectedButton == 3) {
                    MENU.close();
                    break;
                }
            }
        }
        MENU.clear();

        menu.draw(MENU);

        MENU.display();
    }  
    return 0;
}