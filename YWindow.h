/*
 * YWindow.h
 *
 *  Created on: May 29, 2014
 *      Author: cs349
 */

#ifndef YWINDOW_H_
#define YWINDOW_H_

#include "YRectangle.h"
#include "YLabel.h"
#include "Ypanel.h"
#include "LifeModel.h"
#include "YSlider.h"
#include "YPanel.h"
#include "YButton.h"

#include <string>
#include <iostream>
#include <sstream>
#include <list>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#define BUTTON_SIZE 5
#define MIN_IPF 1
#define MAX_IPF 100

using namespace std;

class YWindow {
public:
	YWindow(LifeModel* lm);
	virtual ~YWindow();

    void paint();

private:
	LifeModel* lm;
	Display* display;
	Window window;
	Pixmap pixmap;
	GC gc;
	int w, h, screen;
	bool map[NUM_ROWS][NUM_COLS];
	int genNum;
	bool playMode;	// true if play mode is on, false otherwise
	long startTime1, startTime2;
	int lastPaint;
	int ipf;		// fast 1000 - slow 10

	YRectangle* yrectangle;
	YLabel* ylabel[3];
	YSlider *yslider_gen, *yslider_speed;
	YButton* ybutton[BUTTON_SIZE];

    void init();//
    void eventloop();//
	void playLoop();//

	void buildWindow(int w, int h);//
	void closeWindow();//

	void buildPixmap();//
	void closePixmap();//

	void manageLayout(); //

	void fillDWGWHS(Display* display, Window window, GC gc, int w, int h, int screen);//
	void FillRectangle();//
	void flushEmptyWindow();//
	void getMap(int genNum);//
	void drawRectangle();//
	void drawLabels(int genNum);//
	void drawButtons();//
	void flipPlayMode();//
	void stopPlayMode();//
	void drawSliders(int genNum);//
	void startTimer();//
	long getNow();//

};

#endif /* YWINDOW_H_ */
