#include <SFML/Graphics.hpp>

using namespace sf;

View view;

float viewX, viewY;

View getPlayerCoordinateForView(float x, float y,float mapLange, float mapHohe) {

	float tempX = x; float tempY = y;

	if (x < 480) {
		tempX = 480;
	}
	if (y < 360) {
		tempY = 360;
	}
	if (y > (mapHohe - 720) + 360) {
		tempY = (mapHohe - 720) + 360;
	}
	if (x > (mapLange - 960) + 480) {
		tempX = (mapLange - 960) + 480;
	}

	viewX = tempX, viewY = tempY;
	view.setCenter(tempX, tempY);
	return view;
}

View viewMap(float time, Event event) {
	if (event.type == Event::KeyReleased)
	{
		if (event.key.code == Keyboard::Right) {
			view.move(50*time, 0);
		}
		if (event.key.code == Keyboard::Left) {
			view.move(-50* time, 0);
		}
		if (event.key.code == Keyboard::Down) {
			view.move(0, 50*time);
		}
		if (event.key.code == Keyboard::Up) {
			view.move(0, -50*time);
		}
	}
	return view;
}

View changeView(Event event) {
	if (event.key.code == Keyboard::Q) {
		view.zoom(1.0100f);
	}
	if (event.key.code == Keyboard::E) {
		view.zoom(0.9900f);
	}
	if (event.key.code == Keyboard::F) {
		view.setSize(960, 720);
	}

	return view;
}

float getViewPositionX() {
	return viewX + 400;
}

float getViewPositionY() {
	return viewY - 300;
}