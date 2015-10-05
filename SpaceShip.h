#pragma once
#include "GL/freeglut.h"
#include <vector>

using namespace std;

class SpaceShip {
public:
	SpaceShip();
	~SpaceShip();
	vector<SpaceShip> drawSquad();
	void drawShip();
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