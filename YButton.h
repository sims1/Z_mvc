/*
 * YButton.h
 *
 *  Created on: June 7, 2014
 *      Author: Ling
 */

#ifndef YBUTTON_H_
#define YBUTTON_H_

#include "Life.h"
#include "YComponent.h"
#include <string>
#include <iostream>
#include <sstream>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

using namespace std;

class YButton : public YComponent
{
public:
	YButton();
	virtual ~YButton();
	virtual void setButton(string content);
	virtual void paint();

	virtual bool isSelect();
	virtual void cancelSelect();
	virtual void Select(int positionX, int positionY);

private:
	string label;
	int cell_bian;
	int rec_x1, rec_x2, rec_y1, rec_y2;

	bool selected;
};

#endif /* YBUTTON_H_ */
