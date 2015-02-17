/*
 * YWindow.cpp
 *
 *  Created on: May 29, 2014
 *      Author: cs349
 */

#include "YWindow.h"

#include <string>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

using namespace std;


YWindow::YWindow(LifeModel* lm){
	this->lm = lm;
	this->init();
	this->eventloop();
}

YWindow::~YWindow(){

}

/**
 * Initialize the window.
 */
void YWindow::init() {

	this->genNum = 0;
	this->playMode = false;
	this->ipf = (MAX_IPF - MIN_IPF) / 2;

    buildWindow(1000, 550);

	buildPixmap();

	manageLayout();

	paint();

	eventloop();

    closeWindow();
}

void YWindow::buildWindow(int w, int h) {
	display = XOpenDisplay("");         
    if (!display) exit (-1);

	// create a window
    int screen = DefaultScreen(display);
	window = XCreateSimpleWindow(display, DefaultRootWindow(display),   
								10, 10, w, h, 2, 
								BlackPixel(display, screen), 
								WhitePixel(display, screen));

	XSelectInput(display, window, 
		Button1MotionMask | ButtonPressMask | ButtonReleaseMask); // select events

	XMapRaised(display, window);
	XFlush(display); 
	sleep(1);           // let server get set up before sending drawing commands
	// drawing demo with graphics context here ...
	GC gc = XCreateGC(display, window, 0, 0);       // create a graphics context
	XSetForeground(display, gc, BlackPixel(display, screen));
	XSetBackground(display, gc, WhitePixel(display, screen));

	// load a larger font
	XFontStruct * font;
	font = XLoadQueryFont (display, "8x16kana");
	XSetFont (display, gc, font->fid);

	this->fillDWGWHS(display, window, gc, w, h, screen);
}

void YWindow::buildPixmap(){
	int depth = DefaultDepth(display, DefaultScreen(display));
	pixmap = XCreatePixmap(display, window, w, h, depth);
}

void YWindow::closePixmap(){
	XFreePixmap(display, pixmap);
}

void YWindow::closeWindow()
{
	cout << "ENTER2exit"; std::cin.get(); // wait for input

    XCloseDisplay(display);
}

/*
 * The loop responding to events from the user.
 */
void YWindow::eventloop() {
	XEvent event; // save the event here
	while( true ) {  // event loop until 'exit'
		if (XPending(display)){
			XNextEvent( this->display, &event ); // wait for next event
			switch( event.type ) {
				case MotionNotify: // mouse movement

					cout << "============MotionNotify" << endl;
				
					if (this->yslider_gen->isSelect()){
						//cout << "yslider_gen isSelect" << endl;
						//cout << event.xmotion.x << "," << event.xmotion.y << endl;

						this->yslider_gen->changePosition(event.xmotion.x);

						if (this->yslider_gen->getPosition() == 1){
							this->genNum = NUM_GENERATIONS - 1;
						}
						else{
							this->genNum = this->yslider_gen->getPosition() * NUM_GENERATIONS;
						}
					}
					else if (this->yslider_speed->isSelect()){
						//cout << "yslider_speed isSelect" << endl;
						//cout << event.xmotion.x << "," << event.xmotion.y << endl;

						this->yslider_speed->changePosition(event.xmotion.x);

						this->ipf = MAX_IPF - this->yslider_speed->getPosition() * (MAX_IPF - MIN_IPF);
						//cout << "MAX_IPF - this->yslider_speed->getPosition() * (MAX_IPF - MIN_IPF);" <<
							// (double)(this->yslider_speed->getPosition()) << endl;
					}

					else{
						//cout << "no MotionNotify" << endl;
					}
				
					break;
				case ButtonPress: // any keypress
					cout << "============ButtonPress" << endl;
					this->yslider_gen->Select(event.xmotion.x, event.xmotion.y);
					this->yslider_speed->Select(event.xmotion.x, event.xmotion.y);

				
					// button trigger
					for(int j = 0; j < BUTTON_SIZE; j++){
						this->ybutton[j]->Select(event.xmotion.x, event.xmotion.y);
					}
					
					if (this->ybutton[0]->isSelect()){
						//cout << "button 0 selected" << endl;
						stopPlayMode();
						this->genNum = 0;
						this->ybutton[0]->cancelSelect();
					}
					
					else if (this->ybutton[4]->isSelect()){
						//cout << "button 4 selected" << endl;
						stopPlayMode();
						this->genNum = NUM_GENERATIONS - 1;
						this->ybutton[4]->cancelSelect();
					}
					
					else if (this->ybutton[1]->isSelect()){
						//cout << "button 1 selected" << endl;
						stopPlayMode();
						if(this->genNum != 0){
							this->genNum--;
						}
						this->ybutton[1]->cancelSelect();
					}
					
					else if (this->ybutton[3]->isSelect()){
						//cout << "button 3 selected" << endl;
						stopPlayMode();
						if(this->genNum != NUM_GENERATIONS - 1){
							this->genNum++;
						}
						this->ybutton[3]->cancelSelect();
					}
					
					else if (this->ybutton[2]->isSelect()){
						//cout << "button 3 selected" << endl;
						//cout << "in flipPlayMode" << endl;
						flipPlayMode();
						if (playMode){
							startTimer();
							lastPaint = 0;
						}
						this->ybutton[2]->cancelSelect();
					}
				
					else{
						//cout << "no ButtonPress" << endl;
					}
					break;
				case ButtonRelease:
					cout << "============ButtonRelease" << endl;
					this->yslider_gen->cancelSelect();
					this->yslider_speed->cancelSelect();
					break;
				//default:
					//cout << "default" <<endl;
			}
		}
		long now = getNow();
		if (now > lastPaint + this->ipf){
			paint();
			lastPaint = now;
			if (playMode){
				if(this->genNum + 1 == NUM_GENERATIONS){
					stopPlayMode();
					paint();
				}
				else{
					this->genNum++;
				}
			}
		}
	}
	
}

void YWindow::startTimer(){
	struct timeval start;

    long mtime, seconds, useconds;    

    gettimeofday(&start, NULL);

    startTime1 = start.tv_sec;
    startTime2 = start.tv_usec;
}

long YWindow::getNow(){
	struct timeval end;

    long mtime, seconds, useconds;    

    gettimeofday(&end, NULL);

    seconds  = end.tv_sec  - startTime1;
    useconds = end.tv_usec - startTime2;

    mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;

    //printf("Elapsed time: %ld milliseconds\n", mtime);
	return mtime;
}

void YWindow::manageLayout() {
	int input_chang, input_kuan;
	int input_interval = w/22;

	YPanel* panel1 = new YPanel();
	panel1->set(display, pixmap, gc, w, h, w/2, h);
	panel1->setOrigin(0, 0);
	panel1->setPanel('v', w/30);

	this->yrectangle = new YRectangle();
	input_chang = w*2/5;
	input_kuan = input_chang / NUM_COLS * NUM_ROWS;
	this->yrectangle->set(display, pixmap, gc, w, h, input_chang, input_kuan);
	panel1->add(input_chang, input_kuan);
	this->yrectangle->setOrigin(panel1->getOriginX(), panel1->getOriginY());

	this->ylabel[0] = new YLabel();
	input_chang = w/10;
	input_kuan = w/50;
	this->ylabel[0]->set(display, pixmap, gc, w, h, input_chang, input_kuan);
	panel1->add(input_chang, input_kuan);
	this->ylabel[0]->setOrigin(panel1->getOriginX(), panel1->getOriginY());

	//
	YPanel* panel2 = new YPanel();
	panel2->set(display, pixmap, gc, w, h, w/2, h*2/3);
	panel2->setOrigin(w/2, h/6);
	panel2->setPanel('v', 0);

	YPanel* panel_button = new YPanel();
	input_chang = w/3;
	input_kuan = h/8;
	panel_button->set(display, pixmap, gc, w, h, input_chang, input_kuan);
	panel2->add(input_chang, input_kuan);
	panel_button->setOrigin(panel2->getOriginX(), panel2->getOriginY());
	panel_button->setPanel('h', w/100);

	input_chang = w/20;
	input_kuan = input_chang;
	for(int k = 0; k < BUTTON_SIZE; k++){
		ybutton[k] = new YButton();
		this->ybutton[k]->set(display, pixmap, gc, w, h, input_chang, input_kuan);
		panel_button->add(input_chang, input_kuan);
		this->ybutton[k]->setOrigin(panel_button->getOriginX(), panel_button->getOriginY());
	}
	this->ybutton[0]->setButton("  |<");
	this->ybutton[1]->setButton("  <<");
	this->ybutton[2]->setButton("   >");
	this->ybutton[3]->setButton("  >>");
	this->ybutton[4]->setButton("  >|");

	YPanel* panel_gen = new YPanel();
	input_chang = w/2;
	input_kuan = h/6;
	panel_gen->set(display, pixmap, gc, w, h, input_chang, input_kuan);
	panel2->add(input_chang, input_kuan);
	panel_gen->setOrigin(panel2->getOriginX(), panel2->getOriginY());
	panel_gen->setPanel('h', w/100);

	this->ylabel[1] = new YLabel();
	input_chang = w/20;
	input_kuan = w/50;
	this->ylabel[1]->set(display, pixmap, gc, w, h, input_chang, input_kuan);
	panel_gen->add(input_chang, input_kuan);
	this->ylabel[1]->setOrigin(panel_gen->getOriginX(), panel_gen->getOriginY());

	this->yslider_gen = new YSlider();
	input_chang = w/3;
	input_kuan = w/40;
	this->yslider_gen->set(display, pixmap, gc, w, h, input_chang, input_kuan);
	panel_gen->add(input_chang, input_kuan);
	this->yslider_gen->setOrigin(panel_gen->getOriginX(), panel_gen->getOriginY());

	YPanel* panel_speed = new YPanel();
	input_chang = w/2;
	input_kuan = h/6;
	panel_speed->set(display, pixmap, gc, w, h, input_chang, input_kuan);
	panel2->add(input_chang, input_kuan);
	panel_speed->setOrigin(panel2->getOriginX(), panel2->getOriginY());
	panel_speed->setPanel('h', w/100);

	this->ylabel[2] = new YLabel();
	input_chang = w/20;
	input_kuan = w/50;
	this->ylabel[2]->set(display, pixmap, gc, w, h, input_chang, input_kuan);
	panel_speed->add(input_chang, input_kuan);
	this->ylabel[2]->setOrigin(panel_speed->getOriginX(), panel_speed->getOriginY());

	this->yslider_speed = new YSlider();
	input_chang = w/3;
	input_kuan = w/40;
	this->yslider_speed->set(display, pixmap, gc, w, h, input_chang, input_kuan);
	panel_speed->add(input_chang, input_kuan);
	this->yslider_speed->setOrigin(panel_speed->getOriginX(), panel_speed->getOriginY());

}

void YWindow::paint() {
	flushEmptyWindow();

	drawRectangle();
	drawLabels(genNum);

	drawButtons();

	drawSliders(genNum);

	XCopyArea(display, pixmap, window, gc, 
		0, 0, w, h,  // region of pixmap to copy
		0, 0); // position to put top left corner of pixmap in window
	XFlush(display);
}

void YWindow::fillDWGWHS(Display* display, Window window, GC gc, int w, int h, int screen){
	this->display = display;
	this->window = window;
	this->gc = gc;
	this->w = w;
	this->h = h;
	this->screen = screen;
}

void YWindow::flushEmptyWindow(){

	XSetForeground(display, gc, WhitePixel(this->display, screen));

	XFillRectangle(display, pixmap, gc, 0, 0, w, h);

	XSetForeground(display, gc, BlackPixel(this->display, screen));

	XFlush(display);
}

void YWindow::drawRectangle(){
	getMap(this->genNum);
	this->yrectangle->paint(this->map);
}

void YWindow::drawLabels(int genNum){
	ostringstream o1, o2;
	string str1, str2;
	o1 << genNum + 1;
	o2 << NUM_GENERATIONS;
	str1 = o1.str();
	str2 = o2.str();

	string label_text = "Gen: " + str1 + " / " + str2;

	this->ylabel[0]->setLabelText(label_text);
	this->ylabel[1]->setLabelText("Gen");
	this->ylabel[2]->setLabelText("Speed");

	for(int j = 0; j < 3; j++){
		this->ylabel[j]->paint();
	}
}

void YWindow::getMap(int genNum){
	for(int row = 0; row < NUM_ROWS; row++){
		for(int col = 0; col < NUM_COLS; col++){
			this->map[row][col] = this->lm->getMapEntry(genNum, row, col);
		}
	}
}

void YWindow::drawSliders(int genNum){
	this->yslider_gen->setSlider((double)genNum / (double)NUM_GENERATIONS);
	this->yslider_gen->paint();

	this->yslider_speed->setSlider((double)(MAX_IPF - ipf) / (double)(MAX_IPF - MIN_IPF));
	this->yslider_speed->paint();

}

void YWindow::drawButtons(){
	for(int i = 0; i < BUTTON_SIZE; i++)
		this->ybutton[i]->paint();
}

void YWindow::flipPlayMode(){
	if (playMode){
		playMode = false;
	}
	else{
		playMode = true;
	}
	if (playMode){
		this->ybutton[2]->setButton("  ||");
	}
	else{
		this->ybutton[2]->setButton("   >");
	}
}

void YWindow::stopPlayMode(){
	playMode = false;
	this->ybutton[2]->setButton("   >");
}