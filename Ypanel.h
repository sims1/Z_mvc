/*
 * YPanel.h
 *
 *  Created on: June 7, 2014
 *      Author: Ling
 */



#ifndef YPANEL_H_
#define YPANEL_H_

#include "Life.h"
#include "YComponent.h"
#include <string>
#include <iostream>
#include <sstream>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

using namespace std;

class YPanel : public YComponent
{
public:
	YPanel();
	virtual ~YPanel(void);
    virtual void paint();

	virtual void setPanel(char type, int gap);
	virtual void add(int given_chang, int given_kuan);
	virtual int getOriginX();
	virtual int getOriginY();

private:
	int x1, y1;
	int x2, y2;
	int interval;
	char layout; // v= vertical, h = horizontal
	int origin_x, origin_y;		// the origin of this next available space
	int next_origin_x, next_origin_y;		// the origin of next available space
};

#endif /* YPANEL_H_ */


