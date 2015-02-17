

#include "LifeModel.h"
#include "YWindow.h"


int main ( int argc, char *argv[] ) {

	LifeModel* lm = new LifeModel("gosperglidergun.txt", 2, 2);
	for(int i = 0; i < 30; i++){
		lm->debug(i);
	}

	YWindow *w = new YWindow(lm);

}