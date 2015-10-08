#include "DrawText.h"

DrawTexts::DrawTexts() {
	int a = 0;
}

void DrawTexts::DrawIt(const char *text, int length, int x, int y) {
	
	glMatrixMode(GL_PROJECTION);
	double *matrix = new double[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	gluOrtho2D(0.0, GLUT_WINDOW_WIDTH, 0.0, GLUT_WINDOW_HEIGHT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2i(x, y);

	for (int i = 0; i < length; i++) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]);
	}

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);
	delete[] matrix;
}

void DrawTexts::DrawPanel() {
	string welcome = "Welcome to Project 1!!";
	string arrowKeys = "Use the arrow keys to navigate around the graphic.";
	string zoom = "Use Page UP and Page Down to zoom in or out.";
	string wireFrame = "Use W to enter and exit wireframe mode.";
	string quit = "Use ESC or X to quit the program.";

	DrawIt(welcome.data(), welcome.size(), 0, 13);
	DrawIt(arrowKeys.data(), arrowKeys.length(), 0, 10);
	DrawIt(wireFrame.data(), wireFrame.length(), 0, 7);
	DrawIt(zoom.data(), zoom.length(), 0, 4);
	DrawIt(quit.data(), arrowKeys.length(), 0, 1);
}