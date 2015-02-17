/*
 * YRectangle.h
 *
 *  Created on: May 29, 2014
 *      Author: cs349
 */

#ifndef YRECTANGLE_H_
#define YRECTANGLE_H_

#include "Life.h"
#include "YComponent.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>

using namespace std;

class YRectangle : public YComponent
{
public:
	YRectangle();
	virtual ~YRectangle();

	virtual void setRectangle(int c, int k);
    virtual void paint(bool gen[NUM_ROWS][NUM_COLS]);

private:
	void drawRectangle();
	void fillRectangle(bool gen[NUM_ROWS][NUM_COLS]);
};

#endif /* YRECTANGLE_H_ */

