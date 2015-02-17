/*
 * Generation.cpp  Represent one generation of the Life simulation.
 *
 */

#include "Generation.h"

#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>


using namespace std;

/**
 * Read the first generation from a file in the patterns/ directory.
 */
Generation::Generation(string filename, int top, int left) {
	this->genNum = 0;

	// Initialize the map to all dead life-forms.
	for(int r=0; r<NUM_ROWS; r++) {
		for(int c=0; c<NUM_COLS; c++) {
			this->map[r][c] = false;
		}
	}

	// Initialize the map with the live life-forms.
	ifstream fs;
	string path = "patterns/" + filename;
	fs.open(path.c_str());

	string line;

	if (fs.is_open()) {
		int r = 0;
		while (getline (fs, line) && r < NUM_ROWS) {
			if (line[0] != '!') {
				if (left + line.length() > NUM_COLS) {
					cerr << "pattern won't fit in grid";
					exit(0);
				}
				for(int c = 0; c<line.length(); c++) {
					if (line[c] == '.') {
						this->map[r+top][c+left] = false;
					} else if (line[c] == 'O') {
						this->map[r+top][c+left] = true;
					} else {
						cerr << "unrecognized character " << line[c] << "(" << r << "," << c << ")";
					}
				}
				r++;
			}
		}
	} else {
		cerr << "Unable to open file " + path;
	}
}

/**
 * Create a new generation with all dead life-forms.
 */
Generation::Generation(int genNum) {
	this->genNum = genNum;
	for(int r=0; r<NUM_ROWS; r++) {
		for(int c=0; c<NUM_COLS; c++) {
			this->map[r][c] = false;
		}
	}
}


Generation::~Generation() {
}

/**
 * Generate the next generation of the simulation.
 */
Generation* Generation::nextGeneration() {
	Generation* next = new Generation(this->genNum+1);

	for(int r = 0; r < NUM_ROWS; r++) {
		for(int c=0; c < NUM_COLS; c++) {
			int numNeighbours = countNeighbours(r, c);
			bool isAlive = this->map[r][c];
			if (isAlive && (numNeighbours < 2 || numNeighbours > 3)) {
				next->map[r][c] = false;
			} else if (!isAlive && numNeighbours == 3) {
				next->map[r][c] = true;
			} else {
				next->map[r][c] = isAlive;
			}
		}
	}

	return next;
}


/**
 * Count the live cells neighbouring the life-form at (row, col).
 */
int Generation::countNeighbours(int row, int col) {
	int count = 0;
	for(int r = max(0, row-1); r <= min(row+1, NUM_ROWS-1); r++) {
		for(int c = max(0, col-1); c <= min(col+1, NUM_COLS-1); c++) {
			if (this->map[r][c] && (r != row || c != col)) {
				count++;
			}
		}
	}
	return count;
}


/**
 * Print out this generation.
 */
void Generation::debug() {
	cout << "Gen: " << this->genNum << '\n';
	for(int r=0; r<NUM_ROWS; r++) {
		for(int c=0; c<NUM_COLS; c++) {
			if (this->map[r][c]) {
				cout << 'O';
			} else {
				cout << '.';
			}
		}
		cout << '\n';
	}
}

bool Generation::getMapEntry(int row, int col) {
	return this->map[row][col];
}