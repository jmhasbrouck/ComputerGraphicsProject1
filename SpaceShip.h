#pragma once
#include "GL/freeglut.h"
#include <vector>

using namespace std;

class SpaceShip {
public:
	SpaceShip();
	~SpaceShip();
	void drawSquad();
	void drawShip(double x, double y, double z);
	void setSlicesStacks(double numberOf);
	void colorShip(double r, double g, double b);
	void setDisplayListBoolean(bool weAreInDisplayFuncOne);
private:
	GLUquadric * q;

	GLuint* display_list_handle;
	GLuint* displayLists;
	double slices, stacks;
	bool weAreInDisplayFuncNumberOne;
	double xc, yc, zc;
	double red, green, blue;
};