/*
 * 
 * YRectangle.cpp
 *
 *  Created on: May 29, 2014
 *      Author: cs349
 */

#include "YRectangle.h"

YRectangle::YRectangle(){
	
}

YRectangle::~YRectangle()
{
}

void YRectangle::setRectangle(int c, int k){
	this->chang = c;
	this->kuan = k;
}

void YRectangle::paint(bool gen[NUM_ROWS][NUM_COLS]) {

	drawRectangle();

	fillRectangle(gen);

	//XFlush(display);
}

void YRectangle::drawRectangle() {
	XDrawRectangle(display, pixmap, gc, x, y, chang, kuan);
}

void YRectangle::fillRectangle(bool gen[NUM_ROWS][NUM_COLS]){

	int cell_chang = chang / NUM_COLS;
	int cell_kuan = kuan / NUM_ROWS;

	for(int row = 0; row < NUM_ROWS; row++){
		for(int col = 0; col < NUM_COLS; col++){
			if(gen[row][col]){
				XFillRectangle(display, pixmap, gc, 
					x + cell_chang*col, y + cell_kuan*row, 
					cell_chang, cell_kuan);
			}
		}
	}
}