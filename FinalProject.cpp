#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;
using namespace sf;

bool isCellAlive[50][50]{};
bool isCellAliveNextGeneration[50][50]{};
vector<vector<RectangleShape>> cells(50, vector<RectangleShape>(50));
vector<RectangleShape> grid(vector<RectangleShape>(98));

void gridStartRandom() {
	srand(time(NULL));
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			int random = rand() % 5;
			if (random == 0) {
				isCellAlive[i][j] = true;
			}
			else {
				isCellAlive[i][j] = false;
			}
		}
	}
}

void cellGeneration() {
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			int liveNeighbors = 0;
			//underpopulation & overpopulation rule (note: cells outside the grid are considered dead)
			if (isCellAlive[i][j] == true) {
				if (i == 0 && j == 0) {
					for (int a = 0; a < 2; a++) {
						for (int b = 0; b < 2; b++) {
							if (isCellAlive[i + a][j + b] == true && !((a == 0) && (b == 0))) {
								liveNeighbors+=1;
							}
						}
					}
				}
				else if (i == 49 && j == 0) {
					for (int a = -1; a < 1; a++) {
						for (int b = 0; b < 2; b++) {
							if (isCellAlive[i + a][j + b] == true && !((a == 0) && (b == 0))) {
								liveNeighbors += 1;
							}
						}
					}
				}
				else if (i == 0 && j == 49) {
					for (int a = 0; a < 2; a++) {
						for (int b = -1; b < 1; b++) {
							if (isCellAlive[i + a][j + b] == true && !((a == 0) && (b == 0))) {
								liveNeighbors += 1;
							}
						}
					}
				}
				else if (i == 49 && j == 49) {
					for (int a = -1; a < 1; a++) {
						for (int b = -1; b < 1; b++) {
							if (isCellAlive[i + a][j + b] == true && !((a == 0) && (b == 0))) {
								liveNeighbors += 1;
							}
						}
					}
				}
				else if ((i > 0 && i < 49) && j == 0) {
					for (int a = -1; a < 2; a++) {
						for (int b = 0; b < 2; b++) {
							if (isCellAlive[i + a][j + b] == true && !((a == 0) && (b == 0))) {
								liveNeighbors += 1;
							}
						}
					}
				}
				else if ((i > 0 && i < 49) && j == 49) {
					for (int a = -1; a < 2; a++) {
						for (int b = -1; b < 1; b++) {
							if (isCellAlive[i + a][j + b] == true && !((a == 0) && (b == 0))) {
								liveNeighbors += 1;
							}
						}
					}
				}
				else if ((j > 0 && j < 49) && i == 0) {
					for (int a = 0; a < 2; a++) {
						for (int b = -1; b < 2; b++) {
							if (isCellAlive[i + a][j + b] == true && !((a == 0) && (b == 0))) {
								liveNeighbors += 1;
							}
						}
					}
				}
				else if ((j > 0 && j < 49) && i == 49) {
					for (int a = -1; a < 1; a++) {
						for (int b = -1; b < 2; b++) {
							if (isCellAlive[i + a][j + b] == true && !((a == 0) && (b == 0))) {
								liveNeighbors += 1;
							}
						}
					}
				}
				else {
					for (int a = -1; a < 2; a++) {
						for (int b = -1; b < 2; b++) {
							if (isCellAlive[i + a][j + b] == true && !((a == 0) && (b == 0))) {
								liveNeighbors += 1;
							}
						}
					}
				}
				if (liveNeighbors < 2 || liveNeighbors > 3) {
					isCellAliveNextGeneration[i][j] = false;
				}
				else {
					isCellAliveNextGeneration[i][j] = true;
				}
			}

		}
	}
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			isCellAlive[i][j] = isCellAliveNextGeneration[i][j];
		}
	}
}

int main() {
	RenderWindow window(VideoMode(600, 600), "squares");
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			cells[i][j].setSize(Vector2f(10, 10));
			cells[i][j].setPosition(Vector2f((i * 12)+1, (j * 12)+1));
		}
	}
	for (int i = 0; i < 98; i++) {
		if (i % 2 == 0) {
			int y = (i * 6) + 11;
			grid[i].setSize(Vector2f(600,2));
			grid[i].setPosition(0, y);
			grid[i].setFillColor(Color(128, 128, 128));
		}
		else {
			int x = ((i-1) * 6) + 11;
			grid[i].setSize(Vector2f(2, 600));
			grid[i].setPosition(x,0);
			grid[i].setFillColor(Color(128, 128, 128));
		}
		}
	gridStartRandom();
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event))
		{
		}
		for (int i = 0; i < 50; i++) {
			for (int j = 0; j < 50; j++) {
				if (isCellAlive[i][j] == true) {
					cells[i][j].setFillColor(Color(255,255,255));
				}
				else {
					cells[i][j].setFillColor(Color(0, 0, 0));
				}
				window.draw(cells[i][j]);
			}
			for (int i = 0; i < 98; i++) {
				window.draw(grid[i]);
			}
		}
		window.display();
		std::this_thread::sleep_for(2000ms);
		cellGeneration();
	}
}