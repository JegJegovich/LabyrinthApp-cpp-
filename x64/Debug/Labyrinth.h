#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <stack>

using namespace std;
using namespace sf;



class Labyrinth {
private:
	int Rows, Cols, schritten;
	float cellSize;

	vector<int> losungX;
	vector<int> losungY;

	vector<vector<bool>> maze;
public:

	Labyrinth(int numRows, int numCols, float cellSize);

	vector<vector<bool>>& getLabyrinth()
	{
		return maze;
	}

	float getCellSize() {
		return cellSize;
	}

	void setCellSize(float celllSize);

	void setCols(int Cols);

	void setRows(int Rows);

	void draw(RenderWindow& window, bool losungZeigen);

	void generateLabyrninth();

	bool isWall(int row, int col) {
		return maze[row][col];
	}

	void clearLabyrinth();

	int richtungFurBewegung(int xPos, int yPos, vector<vector<bool>>& array, stack<int>& xStack, stack<int>& yStack);

	bool istBesucht(int xPos, int yPos, stack<int>& xStack, stack<int>& yStack);

	//losung
	void losungFinden();

	int getSchrittenanzahl() {
		return schritten;
	}

	bool istCelleLosung(int xPos, int yPos, vector<int>& losungX, vector<int>& losungY);

	int richtungFurBewegung_Tiefsuchen(int xPos, int yPos, vector<vector<bool>>& array, stack<int>& xStack, stack<int>& yStack);
};
