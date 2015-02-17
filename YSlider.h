/*
 * YSlider.h
 *
 *  Created on: June 7, 2014
 *      Author: Ling
 */

#ifndef YSLIDER_H_
#define YSLIDER_H_

#include "Life.h"
#include "YComponent.h"
#include <string>
#include <iostream>
#include <sstream>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

using namespace std;

class YSlider : public YComponent
{
public:
	YSlider();
	virtual ~YSlider();
	virtual void setSlider(double p);
	
	virtual void paint();

	virtual bool isSelect();
	virtual void changePosition(int givenP);
	virtual double getPosition();
	virtual void cancelSelect();
	virtual void Select(int givenX, int givenY);

private:
	int cell_bian;
	int slider_length;
	int slider_x1, slider_y1;
	int rec_x1, rec_x2, rec_y1, rec_y2;

	bool selected;
	double position;

	virtual void drawSlider();
	
};

#endif /* YSLIDER_H_ */
