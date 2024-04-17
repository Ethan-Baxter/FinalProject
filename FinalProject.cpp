#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;
using namespace sf;

bool isCellAlive[50][50]{};
vector<vector<RectangleShape>> grid(50, vector<RectangleShape>(50));

void createGrid() {
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			if (((i % 2) == 1)  && ((j%3)==0)) {
				isCellAlive[i][j] = { true };
			}
			else {
				isCellAlive[i][j] = { false };
			}
		}
	}
}

/*void drawGrid() {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 50; j++) {
			if (isCellAlive[i][j] == true) {
				cout << "*";
			}
			else {
				cout << ".";
			}
		}
		cout << endl;
	}
}*/

int main() {
	RenderWindow window(VideoMode(600, 600), "squares");
	createGrid();
	window.display();
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		for (int i = 0; i < 50; i++) {
			for (int j = 0; j < 50; j++) {
				if (isCellAlive[i][j] == true) {
					grid[i][j].setFillColor(Color(255,255,255));
				}
				else {
					grid[i][j].setFillColor(Color(0, 0, 0));
				}
				grid[i][j].setSize(Vector2f(10, 10));
				grid[i][j].setPosition(Vector2f(i*12,j*12));
				window.draw(grid[i][j]);
			}
		}
		window.display();
	}
}