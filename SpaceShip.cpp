#include "SpaceShip.h"

SpaceShip::SpaceShip() {
	//display_list_handle = GLuint(-1);
	stacks = slices = 30.0;
	//creates an array of handles to be used for displayFunc and displayFunc2 accordingly
	displayLists = new GLuint[2];
	displayLists[0] = GLuint(-1);
	displayLists[1] = GLuint(-1);
}
SpaceShip::~SpaceShip() {
	delete[] displayLists;
}

void SpaceShip::drawSquad(bool isLaunch) {

	double z = -1.5;
	double x;
	if (isLaunch) {
		y = y+.025;
		//drawSmoke();
	}
	else
	{
		y = 0;
	}

	//Here, we will use a for loop to create the array of ships
	vector<SpaceShip> theSquad;
	for (int a = 0; a < 4; a++) {
		x = -1.5;
		for (int i = 0; i < 4; i++) {
			glPushMatrix();
			glTranslated(x, y, z);
			glScaled(.5, .5, .5);
			drawShip(0, 0, 0);
			glPopMatrix();
			x += 1;
		}
		z += 1;
	}

}

void SpaceShip::drawShip(double x, double y, double z) {

	//LISTS TO REUSE SHAPES
	if (weAreInDisplayFuncNumberOne)
	{
		//if we are here, then we must be within display function 1
		display_list_handle = &displayLists[0];
	}
	else
	{
		//else we are in display function 2
		display_list_handle = &displayLists[1];
	}
	//
	//The reason why there needs to be two different display_list_handles is because
	//different display functions have their own seprate handles and since we have 
	//two display functions, we need two display handles
	//
	if (*display_list_handle == GLuint(-1)) {
		GLUquadric * q = gluNewQuadric();
		*display_list_handle = glGenLists(1);
		glNewList(*display_list_handle, GL_COMPILE);

		glTranslated(0, -1, 0);
		glTranslated(x, y, z);

		//draw the main ship
		glPushMatrix();
		glTranslated(0.0, 1.0, 0.0);
		glScalef(.33f, 1.0f, .33f);
		gluSphere(q, 1.0, slices, stacks);
		glPopMatrix();


		//draw the wings
		for (int a = 0; a < 4; a++) {
			glRotatef(90, 0, 1, 0);
			glPushMatrix();
			glTranslated(0.1, 0.3, 0.0);
			glRotatef(20, 0.0f, 0.0f, -1.0f);
			glRotatef(90, 0.0f, 1.0f, 0.0f);
			glScalef(.33f, 1.0f, 1.0f);
			gluCylinder(q, .25, .15, .5, slices, stacks);
			glPopMatrix();
		}

		for (int i = 0; i < 4; i++) {
			//draw the thrusters
			glRotatef(90, 0, 1, 0);
			glPushMatrix();
			glTranslatef(.55, .4, 0.0);
			glRotatef(90, 1.0f, 0.0f, 0.0f);
			gluCylinder(q, .1, .1, .5, slices, stacks);
			glPopMatrix();

			//draw balls on top
			glPushMatrix();
			glTranslatef(.55, .4, 0.0);
			gluSphere(q, .1, slices, stacks);
			glPopMatrix();

			//draw the flames
			glPushMatrix();
			glTranslatef(.55, -.1, 0.0);
			glScalef(1, 2.5, 1);
			gluSphere(q, .1, slices, stacks);
			glPopMatrix();
		}
		
		glTranslated(-x, -y, -z);
		
		glEndList();
		gluDeleteQuadric(q);
	}

	glCallList(*display_list_handle);
	glTranslated(0, 1, 0);
}

void SpaceShip::setSlicesStacks(double numberOf) {
	stacks = slices = numberOf;
}

void SpaceShip::setDisplayListBoolean(bool weAreInDisplayFuncOne)
{
	weAreInDisplayFuncNumberOne = weAreInDisplayFuncOne;
}

void SpaceShip::drawSmoke() {
	
	int randNum = rand() % 100-200;
	double randX = rand() % 1-4;
	double randZ = rand() % 1-4;
	cout << randX << "   " << randZ << "   " << randNum << "   ";
	for (int i = 0; i < abs(randNum); i++) {
		glPushMatrix();
		glColor3d(0, 1, 0);
		glTranslatef(abs(randX), 0, abs(randZ));
		glScalef(1, 2.5, 1);
		gluSphere(q, .1, slices, stacks);
		glPopMatrix();
	}
}