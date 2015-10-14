#pragma once
#include "GL/freeglut.h"
#include <iostream>
#include <vector>

using namespace std;

class SpaceShip {
public:
	SpaceShip();
	~SpaceShip();
	void drawSquad(bool isLaunch);
	void setSlicesStacks(double numberOf);
	void setDisplayListBoolean(bool weAreInDisplayFuncOne);

private:
	GLUquadric * q;
	double y;
	GLuint* display_list_handle;
	GLuint* displayLists;
	double slices, stacks;
	bool weAreInDisplayFuncNumberOne;

	void drawShip(double x, double y, double z);
	void drawSmoke();
};