#include <iostream>
#include <conio.h>
#include <thread>
#include <chrono>
using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;

int headX, headY, fruitX, fruitY, score;
int tailX[100], tailY[100], nTail;

enum eDirection { STOP = 0, LEFT, UP, RIGHT, DOWN };
eDirection dir;

void Setup() {
	gameOver = false;
	dir = STOP;

	// init head in centre
	headX = width / 2;
	headY = height / 2;
	nTail = 0;

	// init fruit
	fruitX = rand() % width;
	fruitY = rand() % height;

	// init score
	score = 0;

}

void Draw() {
	// clear screen
	system("cls");

	cout << "SCORE: " << score << endl;

	// top border
	for (int i = 0; i < width + 1; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width + 1; j++) {
			if (j == 0)
				cout << "#";
			else if (j == width)
				cout << "#";
			else {
				if (j == headX && i == headY)
					cout << "o";
				else if (j == fruitX && i == fruitY)
					cout << "@";
				else {
					bool p = false;
					for (int k = 0; k < nTail; k++) {
						if (j == tailX[k] && i == tailY[k]) {
							cout << "o";
							p = true;
						}
					}
					if (!p)
						cout << " ";
				}
			}
		}
		cout << endl;
	}

	// bottom border
	for (int i = 0; i < width + 1; i++)
		cout << "#";
	cout << endl;
}

void Input() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
				break;
		case 'q':
			gameOver = true;
			break;
		default:
			break;
		}
	}
}

void Logic() {

	int prevX = tailX[0];
	tailX[0] = headX;
	int prevY = tailY[0];
	tailY[0] = headY;
	int tempX, tempY;
	for (int i = 1; i < nTail; i++) {
		tempX = tailX[i];
		tempY = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = tempX;
		prevY = tempY;
	}

	switch (dir) {
	case LEFT:
		headX -= 1;
		break;
	case RIGHT:
		headX += 1;
		break;
	case UP:
		headY -= 1;
		break;
	case DOWN:
		headY += 1;
		break;
	}

	// check if fruit has been caught
	if (headX == fruitX && headY == fruitY) {
		score += 10;
		nTail++;
		fruitX = rand() % width;
		fruitY = rand() % height;
	}

	// check if snake leaves game boundary
	if (headX == 0 || headX == width || headY == -1 || headY == height)
		gameOver = true;
	else {
		for (int i = 0; i < nTail; i++) {
			if (headX == tailX[i] && headY == tailY[i])
				gameOver = true;
		}
	}
}

int main() {
	Setup();

	while (!gameOver) {
		Draw();
		Input();
		Logic();
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}

	return 0;
}