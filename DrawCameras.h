#pragma once

#include "GL\freeglut.h"

using namespace std;

class DrawCameras {
public:
	DrawCameras(double x, double y);

	void CameraUp();
	void CameraDown();
	void CameraLeft();
	void CameraRight();
	void CameraZoomIn();
	void CameraZoomOut();

private:
	void drawThem(double x, double y);
	void getPosition();
	double xCoord;
	double yCoord;
};