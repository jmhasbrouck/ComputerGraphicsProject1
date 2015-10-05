/*#include "FirstPersonPerspective.h"
#include "GL/freeglut.h"
#include <iostream>

FirstPersonPerspective::FirstPersonPerspective(int& hght, int& wdth, double* latitude_P, double* longitude_P, double* zoom_P)
{
	height = hght;
	width = wdth;
	latitude = latitude_P;
	longitude = longitude_P;
	zoom = zoom_P;
}


FirstPersonPerspective::~FirstPersonPerspective()
{
}

void FirstPersonPerspective::drawAxes()
{
	glLineWidth(4.0);

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
#define QUADRIC
void FirstPersonPerspective::drawSquare(double r, double g, double b)
{
#ifdef QUADRIC
	/*drawAxes();
	glColor3d(r, g, b);
	/*if (display_list_handle == GLuint(-1))
	{

		GLUquadric * q = gluNewQuadric();
		display_list_handle = glGenLists(1);
		//RECORD	
		glNewList(display_list_handle, GL_COMPILE);
		//gluSphere(q, 1.0, 100, 100); // parameters : (pointer to memory, radius, slices, stacks)
		gluCylinder(q, 1.0, 0.5, 1.0, 100, 100);
		//STOP RECORDING		
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


void FirstPersonPerspective::DisplayFunc()
{
	int elapsed_time = glutGet(GLUT_ELAPSED_TIME);

	GLReturnedError("Entering DisplayFunc");

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
	//glRotated(elapsed_time / 5.0, 0, 1, 0);
	glScaled(0.5, 1.0, 1.0);
	drawSquare(0.1, 0.3, 0.6);
	glPopMatrix();

	glutSwapBuffers();
}

void FirstPersonPerspective::KeyboardFunc(unsigned char c, int x, int y)
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
void FirstPersonPerspective::ReshapeFunc(int w, int h)
{
	width = w;
	height = h;
	glutPostRedisplay();
}
void FirstPersonPerspective::SpecialFunc(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		*longitude += 1.0;
		break;
	case GLUT_KEY_DOWN:
		*longitude -= 1.0;
		break;
	case GLUT_KEY_LEFT:
		*latitude += 1.0;
		break;
	case GLUT_KEY_RIGHT:
		*latitude -= 1.0;
		break;
	case GLUT_KEY_PAGE_UP:
		*zoom -= 0.5;
		break;
	case GLUT_KEY_PAGE_DOWN:
		*zoom += 0.5;
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
}*/