#include "YSlider.h"

YSlider::YSlider()
{
}


YSlider::~YSlider(void)
{
}

void YSlider::paint(){
	drawSlider();

	XFlush(display);
}


void YSlider::setSlider(double p){
	this->position = p;
	this->cell_bian = kuan;
	this->slider_length = chang;
	this->slider_x1 = x;
	this->slider_y1 = y + cell_bian/2;
	//cout << "this->slider_x1: " << this->slider_x1 << " this->slider_y1: " << this->slider_y1 << endl;
	//cout << "cell_bian: " << cell_bian << endl;
}

void YSlider::drawSlider(){
	int rect_center = slider_x1 + slider_length * position;

	XDrawLine(display, pixmap, gc,
				slider_x1, slider_y1,
				slider_x1 + slider_length, slider_y1);
	XDrawLine(display, pixmap, gc,
				slider_x1, slider_y1 + cell_bian*2/3,
				slider_x1, slider_y1 - cell_bian*2/3);
	XDrawLine(display, pixmap, gc,
				slider_x1 + slider_length, slider_y1 + cell_bian*2/3,
				slider_x1 + slider_length, slider_y1 - cell_bian*2/3);

	this->rec_x1 = rect_center - cell_bian/2;
	this->rec_x2 = rect_center + cell_bian/2;
	this->rec_y1 = slider_y1 - cell_bian/2;
	this->rec_y2 = slider_y1 + cell_bian/2;

	// draw rectangle
	XFillRectangle(display, pixmap, gc, rec_x1, rec_y1, cell_bian, cell_bian);
}


bool YSlider::isSelect(){
	return selected;
}

void YSlider::changePosition(int givenP){

	cout << "givenP: " << givenP << ", this->slider_x1: " <<  this->slider_x1 << endl;
	if (givenP <= slider_x1){
		position = 0;
	}

	else if (givenP >= (slider_x1 + slider_length)){
		position = 1;
	}
	else{
		position = (double)(givenP - slider_x1)  / (double)slider_length;
	}
	cout << "changeposition: " << position << endl;
}

double YSlider::getPosition(){
	return position;
}
void YSlider::cancelSelect(){
	cout << "cancelSelect called ->false" << endl;
	this->selected = false;
}

void YSlider::Select(int givenX, int givenY){
	if ((this->rec_x1 <= givenX && givenX <= this->rec_x2)
		&& (this->rec_y1 <= givenY && givenY <= this->rec_y2)){
		selected = true;
		cout << "Select called ->true" << endl;
	}
	else{
		selected = false;
		cout << "Select called ->false" << endl;
	}
}
