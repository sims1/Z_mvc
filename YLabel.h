/*
 * YLabel.h
 *
 *  Created on: June 5, 2014
 *      Author: Ling
 */

#ifndef YLABEL_H_
#define YLABEL_H_

#include "YComponent.h"
#include <string>
#include <iostream>
#include <sstream>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

using namespace std;

class YLabel : public YComponent
{
public:
	YLabel();
	virtual ~YLabel();

	virtual void setLabelText(string label_text);
    virtual void paint();

private:
	string label_text;
};

#endif /* YLABEL_H_ */
