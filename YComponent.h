/*
 * YComponent.h
 *
 *  Created on: May 29, 2014
 *      Author: cs349
 */

#ifndef YCOMPONENT_H_
#define YCOMPONENT_H_

#include "Life.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>

using namespace std;

class YComponent {
public:
	YComponent();
	virtual void set(Display* display, Pixmap pixmap, GC gc, int w, int h, int c, int k);
	virtual void setOrigin(int given_x, int given_y);
	virtual ~YComponent();
    virtual void paint();

	Display* display;
	Pixmap pixmap;
	GC gc;
	int w, h;
	int x, y;
	int chang, kuan;

	virtual int getChang();
	virtual int getKuan();
};

#endif /* YCOMPONENT_H_ */

