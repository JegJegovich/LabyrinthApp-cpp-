#include "Labyrinth.h"

Labyrinth::Labyrinth(int numRows, int numCols, float cellSize) {
	setRows(numRows);
	setCols(numCols);
	setCellSize(cellSize);
    generateLabyrninth();
}

void Labyrinth::setCellSize(float celllSize) {
	this->cellSize = celllSize;
}

void Labyrinth::draw(RenderWindow& window, bool losungZeigen) {

	for (int i = 0; i < Rows; ++i) {
		for (int j = 0; j < Cols; ++j) {
			RectangleShape cell(Vector2f(cellSize, cellSize));
			cell.setPosition(j * cellSize, i * cellSize);
			if (maze[i][j]) {
				cell.setFillColor(Color::Black);
			}
			else if (i == Rows - 2 && j == Cols - 2) {
				cell.setFillColor(Color::Green);
			}
			else if (!maze[i][j] && istCelleLosung(j ,i, losungX, losungY) && losungZeigen) {
				cell.setFillColor(Color::Yellow);
			}
			else {
				cell.setFillColor(Color::White);
			}
			window.draw(cell);
		}
	}
}

void Labyrinth::setRows(int Rows) {
	if (Rows % 2  == 0) {
		Rows -= 1;
	}
	this->Rows = Rows;
}

void Labyrinth::setCols(int Cols) {
	if (Cols % 2 == 0) {
		Cols -= 1;
	}
	this->Cols = Cols;
}

void Labyrinth::clearLabyrinth() {
	losungX.resize(0);
	losungY.resize(0);

	if (Rows % 2 == 0) {
		Rows -= 1;
	}
	if (Cols % 2 == 0) {
		Cols -= 1;
	}
	
	maze.resize(Rows, vector<bool>(Cols));
	
	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < Cols; j++)
		{
			maze[i][j] = true;
		}
	}
	
	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < Cols; j++)
		{
			if ((i % 2 == 1 && j % 2 == 1) && (i < Rows - 1 && j < Cols - 1)) {
				maze[i][j] = false;
			}
		}
	}
}

int Labyrinth::richtungFurBewegung(int xPos, int yPos, vector<vector<bool>>& array, stack<int>& xStack, stack<int>& yStack) {
	vector<int> richtungen;

	int size = 0;

	if (xPos + 2 < Cols - 1) {
		if (!array[yPos][xPos + 2] && !istBesucht(xPos + 2, yPos, xStack, yStack)) {
			richtungen.push_back(1);
			size += 1;
		}
	}

	if (xPos - 2 > 0) {
		if (!array[yPos][xPos - 2] && !istBesucht(xPos - 2, yPos, xStack, yStack)) {
			richtungen.push_back(2);
			size += 1;
		}
	}

	if (yPos + 2 < Rows - 1) {
		if (!array[yPos + 2][xPos] && !istBesucht(xPos, yPos + 2, xStack, yStack)) {
			richtungen.push_back(3);
			size += 1;
		}
	}

	if (yPos - 2 > 0) {
		if (!array[yPos - 2][xPos] && !istBesucht(xPos, yPos - 2, xStack, yStack)) {
			richtungen.push_back(4);
			size += 1;
		}
	}

	if (size == 0) {
		return 0;
	}
	else if (size == 1) {
		return richtungen[0];
	}
	else {
		return richtungen[rand() % size];
	}
}

bool Labyrinth::istBesucht(int xPos, int yPos, stack<int>& xStack, stack<int>& yStack) {
	stack<int> tempX = xStack;
	stack<int> tempY = yStack;

	bool result = false;

	while (!tempX.empty() && !tempY.empty()) {
		if (tempX.top() == xPos && tempY.top() == yPos) {
			return true;
			break;
		}
		tempX.pop();
		tempY.pop();
	}
	return false;
}

void Labyrinth::generateLabyrninth() {
	int x, y;

	if (Rows % 2 == 0) {
		Rows -= 1;
	}
	if (Cols % 2 == 0) {
		Cols -= 1;
	}

	maze.resize(Rows, vector<bool>(Cols, true));

	clearLabyrinth();

	maze[1][1] = false;
	x = 1;
	y = 1;

	stack<int> besuchteX;
	stack<int> besuchteY;

	besuchteX.push(x);
	besuchteY.push(y);

	bool generierungsVerlauf = true;

	while (generierungsVerlauf) {
		int richtung = richtungFurBewegung(x, y, maze, besuchteX, besuchteY);

		switch (richtung) {
		case 1:
			maze[y][x + 1] = false;
			x += 2;
			besuchteX.push(x);
			besuchteY.push(y);
			break;
		case 2:
			maze[y][x - 1] = false;
			x -= 2;
			besuchteX.push(x);
			besuchteY.push(y);
			break;
		case 3:
			maze[y + 1][x] = false;
			y += 2;
			besuchteX.push(x);
			besuchteY.push(y);
			break;
		case 4:
			maze[y - 1][x] = false;
			y -= 2;
			besuchteX.push(x);
			besuchteY.push(y);
			break;
		case 0:
			besuchteX.pop();
			besuchteY.pop();
			if (!besuchteX.empty() && !besuchteY.empty()) {
				int tempX = besuchteX.top();
				int tempY = besuchteY.top();
				besuchteX.push(x);
				besuchteY.push(y);
				x = tempX;
				y = tempY;
				stack<int> stackX = besuchteX;
				stack<int> stackY = besuchteY;
				while (richtungFurBewegung(x, y, maze, besuchteX, besuchteY) == 0) {
					stackX.pop();
					stackY.pop();
					if (stackX.empty() && stackY.empty()) {
						generierungsVerlauf = false;
						break;
					}
					x = stackX.top();
					y = stackY.top();
					if (x == 1 && y == 1) {
						generierungsVerlauf = false;
						break;
					}
				}
			}
			else {
				generierungsVerlauf = false;
			}
			break;
		}
	}

	while (besuchteX.empty() && besuchteY.empty()) {
		besuchteX.pop();
		besuchteY.pop();
	}
}

// losung
int Labyrinth::richtungFurBewegung_Tiefsuchen(int xPos, int yPos, vector<vector<bool>>& maze, stack<int>& xStack, stack<int>& yStack) {
	vector<int> richtungen;

	int size = 0;

	if (xPos + 1 < Cols - 1) {
		if (!maze[yPos][xPos + 1] &&!istBesucht(xPos + 1, yPos, xStack, yStack)) {
			richtungen.push_back(1);
			size += 1;
		}
	}

	if (xPos - 1 > 0) {
		if (!maze[yPos][xPos - 1] && !istBesucht(xPos - 1, yPos, xStack, yStack)) {
			richtungen.push_back(2);
			size += 1;
		}
	}

	if (yPos + 1 < Rows - 1) {
		if (!maze[yPos + 1][xPos] && !istBesucht(xPos, yPos + 1, xStack, yStack)) {
			richtungen.push_back(3);
			size += 1;
		}
	}

	if (yPos - 1 > 0) {
		if (!maze[yPos - 1][xPos] && !istBesucht(xPos, yPos - 1, xStack, yStack)) {
			richtungen.push_back(4);
			size += 1;
		}
	}

	if (size == 0) {
		return 0;
	}
	else if (size == 1) {
		return richtungen[0];
	}
	else {
		return richtungen[rand() % size];
	}
}

void Labyrinth::losungFinden() {

	if (Rows % 2 == 0) {
		Rows -= 1;
	}
	if (Cols % 2 == 0) {
		Cols -= 1;
	}

	vector<vector<bool>> gelösteLabyrinth;

	gelösteLabyrinth.resize(Rows, vector<bool>(Cols));

	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < Cols; j++)
		{
			gelösteLabyrinth[i][j] = maze[i][j];
		}
	}

	vector<int> tempLosungX; // temporäres Array für x-Lösung
	vector<int> tempLosungY; // temporäres Array für y-Lösung

	vector<vector<int>> losungWegX;  // array mit möglichen x-Lösungen
	vector<vector<int>> losungWegY;  // array mit möglichen y-Lösungen

	stack<int> besuchteX;    // stapel mit besuchten x-Werten
	stack<int> besuchteY;    // stapel mit besuchten y-Werten

	int schritten = 0;   // schrittenanzahl

	vector<int> losungenSchritte; // array mit möglichen Schrittenanzählen

	int x = 1; // aktuelle x-Position
	int y = 1; // aktuelle y-Position

	besuchteX.push(x);
	besuchteY.push(y);

	tempLosungX.push_back(1);   // hinzufügen x-Position der ersten Zelle im x-Lösung-Array 
	tempLosungY.push_back(1);   // hinzufügen y-Position der ersten Zelle im y-Lösung-Array 


	bool generationsverlauf = true; // generationsverlauf

	while (generationsverlauf) { // suchen Lösung

		int richtung = richtungFurBewegung_Tiefsuchen(x, y, gelösteLabyrinth, besuchteX, besuchteY);  // mögliche zufällige Richtung für Bewegung 

		switch (richtung) {
		case 1: // bewegung nach rechts
			x += 1;

			besuchteX.push(x);    // hinzufügen der besuchten Zelle zum x-Stapel
			besuchteY.push(y);    // hinzufügen der besuchten Zelle zum y-Stapel

			// stellen die Zellen im temporären x-Losung-Array 
			tempLosungX.push_back(x);

			// stellen die Zellen im temporären y-Losung-Array 
			tempLosungY.push_back(y);

			schritten += 1;    // schrittenanzahl vergrößern

			if (x == Cols - 2 && y == Rows - 2) {  // wir prüfen, ob aktuelle Zelle das Finish ist

				losungenSchritte.push_back(schritten);  // hinzufügen aktuelle Schrittenanzahl im Array mit möglichen Schrittenanzählen
				losungWegX.push_back(tempLosungX);      // hinzufügen aktuell temporäres Array für x-Lösung im Array mit möglichen x-Lösungen
				losungWegY.push_back(tempLosungY);      // hinzufügen aktuell temporäres Array für y-Lösung im Array mit möglichen y-Lösungen
			}
			break;
		case 2:      // bewegung nach links
			x -= 1;

			besuchteX.push(x);    // hinzufügen der besuchten Zelle zum x-Stapel
			besuchteY.push(y);    // hinzufügen der besuchten Zelle zum y-Stapel

			// stellen die Zellen im temporären x-Losung-Array
			tempLosungX.push_back(x);

			// stellen die Zellen im temporären y-Losung-Array 
			tempLosungY.push_back(y);

			schritten += 1;   // vergrößern Schrittenanzahl 

			if (x == Cols - 2 && y == Rows - 2) {  // wir prüfen, ob aktuelle Zelle das Finish ist

				losungenSchritte.push_back(schritten);    // hinzufügen aktuelle Schrittenanzahl im Array mit möglichen Schrittenanzählen
				losungWegX.push_back(tempLosungX);        // hinzufügen aktuell temporäres Array für x-Lösung im Array mit möglichen x-Lösungen
				losungWegY.push_back(tempLosungY);        // hinzufügen aktuell temporäres Array für y-Lösung im Array mit möglichen y-Lösungen
			}
			break;
		case 3:     // Bewegung nach unten
			y += 1;

			besuchteX.push(x);  // hinzufügen der besuchten Zelle zum x-Stapel  
			besuchteY.push(y);  // hinzufügen der besuchten Zelle zum y-Stapel  

			// stellen die Zellen im temporären x-Losung-Array 
			tempLosungX.push_back(x);

			// stellen die Zellen im temporären y-Losung-Array 
			tempLosungY.push_back(y);

			schritten += 1;    // vergrößern Schrittenanzahl 

			if (x == Cols - 2 && y == Rows - 2) {  // wir prüfen, ob aktuelle Zelle das Finish ist

				losungenSchritte.push_back(schritten);    // hinzufügen aktuelle Schrittenanzahl im Array mit möglichen Schrittenanzählen
				losungWegX.push_back(tempLosungX);        // hinzufügen aktuell temporäres Array für x-Lösung im Array mit möglichen x-Lösungen
				losungWegY.push_back(tempLosungY);        // hinzufügen aktuell temporäres Array für y-Lösung im Array mit möglichen y-Lösungen
			}
			break;
		case 4:     // Bewegung nach oben
			y -= 1;

			besuchteX.push(x);    // hinzufügen der besuchten Zelle zum x-Stapel
			besuchteY.push(y);    // hinzufügen der besuchten Zelle zum y-Stapel

			// die Zellen im x-Losung-Array stellen 
			tempLosungX.push_back(x);

			// die Zellen im y-Losung-Array  stellen
			tempLosungY.push_back(y);

			schritten += 1;    // vergrößern Schrittenanzahl 

			if (x == Cols - 2 && y == Rows - 2) {   // wir prüfen, ob aktuelle Zelle das Finish ist

				losungenSchritte.push_back(schritten);    // hinzufügen aktuelle Schrittenanzahl im Array mit möglichen Schrittenanzählen
				losungWegX.push_back(tempLosungX);        // hinzufügen aktuell temporäres Array für x-Lösung im Array mit möglichen x-Lösungen
				losungWegY.push_back(tempLosungY);        // hinzufügen aktuell temporäres Array für y-Lösung im Array mit möglichen y-Lösungen
			}
			break;

		case 0:    // aktuelle Zelle hat keine mögliche Richtungen für Bewegung
			stack<int> stackX = besuchteX;    // schaffen einen neuen Stapel und kopieren dorthin aktuellen x-Stapel mit besuchten Zellen
			stack<int> stackY = besuchteY;    // schaffen einen neuen Stapel und kopieren dorthin aktuellen y-Stapel mit besuchten Zellen

			stackX.pop();    // löschen die aktuelle x-Position
			stackY.pop();    // löschen die aktuelle y-Position

			if (!stackX.empty() && !stackY.empty()) { // wenn die Stapel nicht leer sind

				x = stackX.top(); // machen die letzte x-Postion aktuell
				y = stackY.top(); // machen die letzte y-Postion aktuell

				tempLosungX.pop_back(); // löschung der letzten x-Positionen aus dem temporären Array mit x-Lösung

				tempLosungY.pop_back(); // löschung der letzten y-Positionen aus dem temporären Array mit y-Lösung

				schritten -= 1; // löschen die letzen 2 Schrittenanzahl

				while (richtungFurBewegung_Tiefsuchen(x, y, gelösteLabyrinth, besuchteX, besuchteY) == 0) { // entlang des Stapels zurückgehen( bis dann hat die aktuelle Zelle keine Variante für Bewegung)

					stackX.pop();   // löschen die aktuelle x-Position
					stackY.pop();   // löschen die aktuellee y-Position

					if (stackX.empty() && stackY.empty()) { // aufhören Generationsverlauf, wenn die Stapel mit besuchten x- und y-Positionen leer ist 
						generationsverlauf = false;
						break;
					}

					x = stackX.top(); // machen die letzte Variable des x-Stapels akltuel 
					y = stackY.top(); // machen die letzte Variable des y-Stapels akltuel

					tempLosungX.pop_back();  // löschen die letzten x-Positionen aus dem temporären Array mit x-Lösung

					tempLosungY.pop_back();  // löschen die letzten y-Positionen aus dem temporären Array mit y-Lösung

					schritten -= 1;  // reduzieren Schrittenanzahl 

					if (schritten == 0) {
						generationsverlauf = false;
						break;
					}
				}
			}
			break;
		}
	}


	losungX = losungWegX[0];	 // x-Werte der Losung 

	if (losungWegX.size() > 1) {
		for (int i = 1; i < losungWegX.size(); i++) { //hier wir prüfen, ob andere variante besser sind

			if (losungWegX[i].size() < losungX.size()) {
				losungX = losungWegX[i];
			}
		}
	}


	losungY = losungWegY[0];	 // y-Werte der Losung 

	if (losungWegY.size() > 1) {
		for (int i = 1; i < losungWegY.size(); i++) {   // hier wir prüfen, ob andere variante besser sind

			if (losungWegY[i].size() < losungY.size()) {
				losungY = losungWegY[i];
			}
		}
	}

	schritten = losungenSchritte[0];   // schritten, die Man braucht, um den Labyrinth zu lösen

	if (losungenSchritte.size() > 1) {
		for (int i = 1; i < losungenSchritte.size(); i++) // hier wir prüfen, ob andere variante besser sind
		{
			if (losungenSchritte[i] < schritten) {
				schritten = losungenSchritte[i];
			}
		}
	}

	// löschen die x- und y-Stapel
	while (besuchteX.empty() && besuchteY.empty()) {
		besuchteX.pop();
		besuchteY.pop();
	}

}

bool Labyrinth::istCelleLosung(int xPos, int yPos, vector<int>& losungX, vector<int>& losungY) {
	for (int i = 0; i < losungX.size(); i++)
	{
		if (losungX[i] == xPos && losungY[i] == yPos) {
			return true;
			break;
		}
	}
	return false;
}