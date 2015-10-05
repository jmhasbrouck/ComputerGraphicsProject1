#pragma once
#include "GL\freeglut.h"
class FirstPersonPerspective
{
public:
	FirstPersonPerspective(int& hght, int& wdth, double* latitude_P, double* longitude_P, double* zoom_P);
	static bool GLReturnedError(char * s);
	~FirstPersonPerspective();
	static void drawAxes();
	static void drawSquare(double r, double g, double b);
	void DisplayFunc();
	void KeyboardFunc(unsigned char c, int x, int y);
	void ReshapeFunc(int w, int h);
	void SpecialFunc(int key, int x, int y);
	void TimerFunc(int period);
private:
	bool wireframe_mode;
	GLuint window;
	GLuint display_list_handle;
	int height;
	int width;
	double* zoom;
	double* latitude;
	double* longitude;
};

