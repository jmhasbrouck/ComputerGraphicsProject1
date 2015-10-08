#include "GL/freeglut.h"
#include <iostream>
#include "SpaceShip.h"
#include "DrawText.h"
#include "DrawCameras.h"
//#include "FirstPersonPerspective.h"

using namespace std;

SpaceShip myLittleRocketShip;
DrawTexts instructions;
DrawCameras camera1;
DrawCameras camera2;

int width = 512;
int height = 512;
int width2 = 1024;
int height2 = 512;
bool wireframe_mode;
GLuint window_1;
GLuint window_2;
GLuint display_list_handle;
GLuint display_list_handle_sphere;
double* longitude = new double(0.0);
double* latitude = new double(0.0);
double* zoom = new double(45);

void ReshapeFunc(int w, int h)
{
	
	width = w;
	height = h;
	glutPostRedisplay();
}
void SpecialFunc(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		*longitude += 1.0;
		camera1.CameraUp();
		camera2.CameraUp();
		break;
	case GLUT_KEY_DOWN:
		*longitude -= 1.0;
		camera1.CameraDown();
		camera2.CameraDown();
		break;
	case GLUT_KEY_LEFT:
		*latitude += 1.0;
		camera1.CameraLeft();
		camera2.CameraLeft();
		break;
	case GLUT_KEY_RIGHT:
		*latitude -= 1.0;
		camera1.CameraRight();
		camera2.CameraRight();
		break;
	case GLUT_KEY_PAGE_UP:
		*zoom -= 0.5;
		camera1.CameraZoomIn();
		camera2.CameraZoomOut();
		break;
	case GLUT_KEY_PAGE_DOWN:
		*zoom += 0.5;
		camera1.CameraZoomOut();
		camera2.CameraZoomOut();
		break;
	default:
		break;
}

	if (*zoom < 1)
	{
		*zoom = 1.0;
	}
	if (*zoom == 90)
	{
		*zoom = 89.5;
	}
}
void SpecialFunc_2(int key, int x, int y)
{
	SpecialFunc(key, x, y);
}

void drawAxes()
{
	glLineWidth(4);

	glBegin(GL_LINES);
	glColor3d(1.0, 0, 0);

	//X axis
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(1.0, 0.0, 0.0);
	//REMEMBER, YOU WILL ALWAYS CHANGE THE SCALING OUTSIDE OF THIS FUNCTION, SO FOR THE LOVE OF GOD JUST MAKE IT IN ONE
	glColor3d(0.0, 1.0, 0.0);
	//Y AXIS
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(0.0, 1.0, 0.0);

	glColor3d(0.0, 0.0, 1.0);
	//Z AXIS
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(0.0, 0.0, 1.0);
	glEnd();

	glLineWidth(1.0);
}

void drawSquare(double r, double g, double b)
{
#ifdef QUADRIC
	drawAxes();
	glColor3d(r, g, b);
	if (display_list_handle == GLuint(-1))
	{

		GLUquadric * q = gluNewQuadric();
		display_list_handle = glGenLists(1);
		glNewList(display_list_handle, GL_COMPILE);
		//gluSphere(q, 1.0, 100, 100); // parameters : (pointer to memory, radius, slices, stacks)
		gluCylinder(q, 1.0, 0.5, 1.0, 100, 100);
		glEndList();
		gluDeleteQuadric(q);
	}
	glCallList(display_list_handle);
#else
	glBegin(GL_QUADS);
	glColor3d(0, 0, 0);
	glVertex2d(-1, 1);
	glColor3d(r, g, b);
	glVertex2d(1, 1);
	glVertex2d(1, -1);
	glVertex2d(-1, -1);
	glEnd();
#endif
}

void drawSphere(double r)
{
	if (display_list_handle_sphere == GLuint(-1))
	{
		glColor3d(0.5f, 0.5f, 0.5f);
		GLUquadric * q = gluNewQuadric();
		display_list_handle = glGenLists(1);
		glNewList(display_list_handle, GL_COMPILE);
		gluSphere(q, r, 30, 30); // parameters : (pointer to memory, radius, slices, stacks)
		glEndList();
		gluDeleteQuadric(q);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	glCallList(display_list_handle);
}

void KeyboardFunc(unsigned char c, int x, int y)
{
	switch (c)
	{
	case 27:
	case 'x':
		glutLeaveMainLoop();
		break;

	case 'w':
		glPolygonMode(GL_FRONT_AND_BACK, wireframe_mode ? GL_LINE : GL_FILL);
		wireframe_mode = !wireframe_mode;
		break;
	default:
		break;
	}
}
void KeyboardFunc_2(unsigned char c, int x, int y)
{
	KeyboardFunc(c, x, y);
}
void DisplayFunc()
{
	//Lets the SpaceShip object know that we are in DisplayFunc
	myLittleRocketShip.setDisplayListBoolean(true);
	int elapsed_time = glutGet(GLUT_ELAPSED_TIME);

	//GLReturnedError("Entering DisplayFunc");
	glClearColor(0.0, 0.0, 0.0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//MAKE SURE IT IS BIT AND not GL_COLOR_BUFFER
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(*zoom, width / double(height), 1.0, 10.0);
	glViewport(0.0, 0.0, width, height);


	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 4.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0);
	glRotated(*longitude, 1, 0, 0);
	glRotated(*latitude, 0, 1, 0);
	
	glPushMatrix();
	glScaled(2,2,2);
	drawAxes();
	glPopMatrix();

	glPushMatrix();
	glScaled(1, 1, 1);
	myLittleRocketShip.drawSquad();
	glPopMatrix();

	glPushMatrix();
	instructions.DrawPanel();
	glPopMatrix();

	glutSwapBuffers();
}
void DisplayFunc_2()
{
	//Lets the SpaceShip object know that we are in DisplayFunc_2
	myLittleRocketShip.setDisplayListBoolean(false);
	int elapsed_time = glutGet(GLUT_ELAPSED_TIME);

	//GLReturnedError("Entering DisplayFunc");
	glClearColor(0.0, 0.0, 0.0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//MAKE SURE IT IS BIT AND not GL_COLOR_BUFFER
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5, 5, -5, 5.0f, 0.0f, 10.0f);
	glViewport(0.0, 0.0, width2/2.0, height);

	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	gluLookAt(0.0, 0.0, 4.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0);
	glScaled(.5, .5, .5);
	

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);
	glPushMatrix();
	drawSphere(6);
	glPopMatrix();
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	glTranslated(0, 0, 7.5);
	myLittleRocketShip.drawSquad();
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5, 5, -5, 5.0f, 0.0f, 10.0f);
	glViewport(width2 / 2.0, 0.0, width2 / 2.0, height);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 4.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0);
	glScaled(.5, .5, .5);
	glRotated(90, 0, 1, 0);

	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);
	glPushMatrix();
	drawSphere(6);
	glPopMatrix();
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	glTranslated(-7.5, 0, 0);
	myLittleRocketShip.drawSquad();

	
	

	glutSwapBuffers();
}
void TimerFunc(int period)
{
	glutTimerFunc(period, TimerFunc, period);
	glutPostRedisplay();
}

int main(int argc, char * argv[])
{
	

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	//FirstPersonPerspective * fp =  new FirstPersonPerspective(height, width, latitude, longitude, zoom);
	wireframe_mode = true;
	display_list_handle = GLuint(-1);
	display_list_handle_sphere = GLuint(-1);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(width, height);
	window_1 = glutCreateWindow("First Person");
	glutDisplayFunc(DisplayFunc);
	glutKeyboardFunc(KeyboardFunc);
	glutSpecialFunc(SpecialFunc);
	glutReshapeFunc(ReshapeFunc);
	glutTimerFunc(1000/60, TimerFunc, 1000/60);


	glutInitWindowSize(width2, height2);
	window_2 = glutCreateWindow("Third Person");
	glutDisplayFunc(DisplayFunc_2);
	glutKeyboardFunc(KeyboardFunc_2);
	glutSpecialFunc(SpecialFunc_2);
	//glutReshapeFunc(ReshapeFunc_2);
	glutTimerFunc(1000 / 60, TimerFunc, 1000 / 60);

	glutMainLoop();
	



	delete latitude;
	delete longitude;
	delete zoom;
}

/*
how to do pointer to a function example
*********************************
this goes in main

void (* function_ptr)(int) = Foo;

PrintingFunction(Foo, 8);
PrintingFunction(Fee, 9);
cout << "Enter to continue . . . ";
char b;
cin >> b;
****************************************
functions

void Foo(int argument)
{
cout << "Here's your argument: " << argument << endl;
}

void PrintingFunction(void (* function_ptr)(int), int argument)
{
function_ptr(argument);
}

void Fee(int argument)
{
cout << "Your argument this is: " << argument << endl;
}*/