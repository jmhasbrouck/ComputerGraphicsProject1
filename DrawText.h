#pragma once

#include "GL/freeglut.h"
#include <string>

using namespace std;

class DrawTexts {
public:
	DrawTexts();
	
	void DrawIt(const char *text, int length, int x, int y);
	void DrawPanel();
};