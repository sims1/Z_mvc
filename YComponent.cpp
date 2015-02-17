#include "YComponent.h"

YComponent::YComponent()
{
}


YComponent::~YComponent(void)
{
}

void YComponent::set(Display* dis, Pixmap pix, GC gc, int w, int h, int c, int k){
	this->display = dis;
	this->pixmap = pix;
	this->gc = gc;
	this->w = w;
	this->h = h;
	this->chang = c;
	this->kuan = k;
}

void YComponent::setOrigin(int given_x, int given_y){
	this->x = given_x;
	this->y = given_y;
}

int YComponent::getChang(){
	return chang;
}

int YComponent::getKuan(){
	return kuan;
}

void YComponent::paint()
{
}