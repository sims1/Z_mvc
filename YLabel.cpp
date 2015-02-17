#include "YLabel.h"

YLabel::YLabel()
{
}


YLabel::~YLabel()
{
}

void YLabel::setLabelText(string label_text){
	this->label_text = label_text;
}

void YLabel::paint(){
	XDrawImageString(display, pixmap, gc, x, y+w/55, label_text.c_str(), label_text.length());

	//XFlush(display);
}