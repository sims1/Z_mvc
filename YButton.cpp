#include "YButton.h"

YButton::YButton()
{
}


YButton::~YButton()
{
}

void YButton::setButton(string content)
{
	this->label = content;
	this->cell_bian = chang;
	this->rec_x1 = x;
	this->rec_y1 = y;
	this->rec_x2 = rec_x1 + cell_bian;
	this->rec_y2 = rec_y1 + cell_bian;
	this->selected = false;
}

void YButton::paint() {
	XDrawImageString(display, pixmap, gc, x, y + w/31, (this->label).c_str(), (this->label).length());
	XDrawRectangle(display, pixmap, gc, x, y, chang, kuan);

	
	//XFlush(display);
}

bool YButton::isSelect(){
	return selected;
}

void YButton::cancelSelect(){
	selected = false;
}

void YButton::Select(int positionX, int positionY){
	if (rec_x1 < positionX && positionX < rec_x2 && rec_y1 < positionY && positionY < rec_y2){
		selected = true;
		cout << "selected: " << positionX << " " << positionY << endl;
	}
	else{
		selected = false;
	}
}