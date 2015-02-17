#include "YPanel.h"

YPanel::YPanel()
{
}

YPanel::~YPanel(void)
{
}

void YPanel::paint() {

}

void YPanel::setPanel(char type, int gap){
	this->x1 = x;
	this->y1 = y;
	this->x2 = x + chang;
	this->y2 = y + kuan;
	this->interval = gap;
	if (!(type == 'v' || type == 'h')){
		cout << "ERROR: wrong layout type when adding to panel, expecting v or c" << endl;
		return;
	}
	this->layout = type;

	this->next_origin_x = x1 + interval;
	this->next_origin_y = y1 + interval;
	//XDrawRectangle(display, pixmap, gc, x, y, chang, kuan);
	//cout << "x: " << x << " y: " << y << " chang: " << chang << " kuan: " << kuan << endl;
	//XFlush(display);
}

void YPanel::add(int given_chang, int given_kuan){
	if (!((next_origin_y < y2 - interval) && (next_origin_x < x2 - interval))){
		cout << "ERROR: fail adding, the panel is full" << endl;
		cout << next_origin_y << " " << y2 << " " << interval << endl;
		cout << next_origin_x << " " <<  x2 << " " << interval << endl;;
		return;
	}

	if (layout == 'v'){
		origin_x = next_origin_x + (chang - given_chang)/2 - interval;
		origin_y = next_origin_y;
		next_origin_y += interval + given_kuan;
	}
	else if (layout == 'h'){
		//cout << "origin_y: " << origin_y << " (kuan - given_kuan)/2: " << (kuan - given_kuan)/2 << endl;
		origin_x = next_origin_x;
		origin_y = next_origin_y + (kuan - given_kuan)/2 - interval;
		next_origin_x += interval + given_chang;

		//cout << "origin_x: " << origin_x << " origin_y: " << origin_y << endl;
	}
	else{
		cout << "ERROR: impossible to have layout other than v or h" << endl;
	}
}

int YPanel::getOriginX(){
	return origin_x;
}

int YPanel::getOriginY(){
	return origin_y;
}