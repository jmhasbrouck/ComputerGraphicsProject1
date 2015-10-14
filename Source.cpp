#include "GL/freeglut.h"
#include <iostream>
#include "SpaceShip.h"
#include "DrawText.h"
#include "DrawCameras.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

using namespace std;

//DrawCameras camera1;
//DrawCameras camera2;
SpaceShip myLittleRocketShip;
DrawTexts instructions;
int width = 512;
int height = 512;
int width2 = 1024;
int height2 = 512;
bool wireframe_mode;
bool rapid_fire, is_launch = false;
double red, green, blue = 100.5;
GLuint window_1;
GLuint window_2;
GLuint display_list_handle;
GLuint display_list_handle_sphere;
double* longitude = new double(-45.0);//rotation angle for camera
double* latitude = new double(0.0);//rotation angle for camera
double* zoom = new double(45);//angle of zoom
double farPlane = 5;
double nearPlane = .5;
double radius = ((farPlane + nearPlane)/2) + nearPlane;//calculation for the radius

//******************************************************
vec3 cameraPosition;
//******************************************************

void ReshapeFunc(int w, int h)
{	
	width = w;
	height = h;
	glutPostRedisplay();
}
void ReshapeFunc_2(int w, int h)
{
	width2 = w;
	height2 = h;
	glutPostRedisplay();
}
void SpecialFunc(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		*latitude -= 1.0;
		break;
	case GLUT_KEY_DOWN:
		*latitude += 1.0;
		break;
	case GLUT_KEY_LEFT:
		*longitude -= 1.0;
		break;
	case GLUT_KEY_RIGHT:
		*longitude += 1.0;
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
	if (*latitude == -90)
	{
		*latitude = -89;
	}
	if (*latitude == 90)
	{
		*latitude = 89;
	}
}
//Function that returns camera position. Used in DisplayFunc
vec3 ComputeCameraPosition()
{
	mat4 m;
	vec4 p(0, 0, radius, 1);
	m = rotate(m, radians(float(*longitude)), vec3(0.0f,1.0f,0.0f));
	m = rotate(m, radians(float(*latitude)), vec3(1.0f, 0.0f, 0.0f));
	return vec3(m*p);
}

void drawAxes()
{
	glLineWidth(4);

	glBegin(GL_LINES);
	glColor3d(1.0, 0, 0);

	//X axis - red
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(1.0, 0.0, 0.0);
	//REMEMBER, YOU WILL ALWAYS CHANGE THE SCALING OUTSIDE OF THIS FUNCTION, SO FOR THE LOVE OF GOD JUST MAKE IT IN ONE
	glColor3d(0.0, 1.0, 0.0);
	//Y AXIS - blue
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(0.0, 1.0, 0.0);

	glColor3d(0.0, 0.0, 1.0);
	//Z AXIS - green
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(0.0, 0.0, 1.0);
	glEnd();

	glLineWidth(1.0);
}

void drawSphere()
{
	
	glColor3d(0.5f, 0.5f, 0.5f);
	glutWireSphere(radius, 40, 35); // parameters : (pointer to memory, radius, slices, stacks)
	
}

void changetheColor() {
	double randNum;

	randNum = (rand() % 255 - 1) / 255.0f;
	red = randNum;
	randNum = (rand() % 255 - 1) / 255.0f;
	blue = randNum;
	randNum = (rand() % 255 - 1) / 255.0f;
	green = randNum;

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
		wireframe_mode = !wireframe_mode;
		break;
	case 'c':
		changetheColor();
		break;
	case 'r':
		if (rapid_fire) {
			rapid_fire = false;
		}
		else {
			rapid_fire = true;
		}
		break;
	case 'l':
		if (is_launch) {
			is_launch = false;
		}
		else {
			is_launch = true;
		}
	default:
		break;
	}
}

void DisplayFunc()
{
	if (rapid_fire) {
		changetheColor();
	}
	//Lets the SpaceShip object know that we are in DisplayFunc
	myLittleRocketShip.setDisplayListBoolean(true);
	int elapsed_time = glutGet(GLUT_ELAPSED_TIME);

	//GLReturnedError("Entering DisplayFunc");
	glClearColor(0.0, 0.0, 0.0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//MAKE SURE IT IS BIT AND not GL_COLOR_BUFFER
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(*zoom, width / double(height), nearPlane, farPlane);
	glViewport(GLint(0), GLint(0), GLsizei(width), GLsizei(height));


	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	cameraPosition = ComputeCameraPosition();
	gluLookAt(cameraPosition.x, cameraPosition.y, cameraPosition.z, 0.0, 0.0, 0.0, 0.0, 1.0, 0);

	glPolygonMode(GL_FRONT_AND_BACK, wireframe_mode ? GL_LINE : GL_FILL);
	
	glPushMatrix();
	glScaled(2,2,2);
	drawAxes();
	glPopMatrix();

	glPushMatrix();
	glScaled(1, 1, 1);
	glColor3d(red,green,blue);
	myLittleRocketShip.drawSquad(is_launch);
	glPopMatrix();

	glPushMatrix();
	glColor3d(0, 1, 0);
	instructions.DrawPanel();
	glPopMatrix();

	glutSwapBuffers();

	glutSetWindow(window_2);
	glutPostRedisplay();

}

void DisplayFunc_2()
{
	if (rapid_fire) {
		changetheColor();
	}

	//Lets the SpaceShip object know that we are in DisplayFunc_2
	myLittleRocketShip.setDisplayListBoolean(false);
	int elapsed_time = glutGet(GLUT_ELAPSED_TIME);
	
	//GLReturnedError("Entering DisplayFunc");
	glClearColor(0.0, 0.0, 0.0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//MAKE SURE IT IS BIT AND not GL_COLOR_BUFFER
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5, 5, -5, 5.0f, 0.0f, 20.0f);
	glViewport(GLint(0), GLint(0), GLsizei(width2/2.0), GLsizei(height));
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslated(0, 0, -1);
	gluLookAt(0.0, 0.0, 4.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0);
	drawSphere();
	//
	/*We draw our camera before we do anything else because the transformations
	that we make to draw the rockets will effect where the camera is drawn.
	In short, drawing camera before rockets will make things easier*/
	glTranslated(cameraPosition.x, cameraPosition.y, cameraPosition.z);
	glutSolidSphere(.1, 20, 20);
	glTranslated(-1 * cameraPosition.x, -1 * cameraPosition.y, -1 * cameraPosition.z);
	//In line above we reset the transformation to (0,0,0) 
	glPolygonMode(GL_FRONT_AND_BACK, wireframe_mode ? GL_LINE : GL_FILL);
	glTranslated(0, 0, radius);
	glRotated(45, 0, 1, 0);
	glScaled(1, 1, 1);
	glColor3d(red, green, blue);
	myLittleRocketShip.drawSquad(is_launch);
	
	//SCREEN TWO ************************************************
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5, 5, -5, 5.0f, 0.0f, 10.0f);
	glViewport(GLint(width2 / 2.0), GLint(0.0), GLsizei(width2 / 2.0), GLsizei(height));

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 4.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0);
	//glScaled(.5, .5, .5);

	glRotated(90, 0, 1, 0);
	glTranslated(1, 0, 0);
	
	glTranslated(cameraPosition.x, cameraPosition.y, cameraPosition.z);
	glutSolidSphere(.1, 20, 20);
	glTranslated(-1 * cameraPosition.x, -1 * cameraPosition.y, -1 * cameraPosition.z);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	drawSphere();

	glPolygonMode(GL_FRONT_AND_BACK, wireframe_mode ? GL_LINE : GL_FILL);
	
	glTranslated(-1 * radius, 0, 0);
	//glScaled(2, 2, 2);
	glRotated(45, 0, 1, 0);
	glColor3d(red, green, blue);
	myLittleRocketShip.drawSquad(is_launch);
	glTranslated(radius, 0, 0);

	glutSwapBuffers();
	
	glutSetWindow(window_1);
	glutPostRedisplay();
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
	wireframe_mode = false;
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
	glutKeyboardFunc(KeyboardFunc);
	glutSpecialFunc(SpecialFunc);
	glutReshapeFunc(ReshapeFunc_2);
	glutTimerFunc(1000 / 60, TimerFunc, 1000 / 60);

	glutMainLoop();
	



	delete latitude;
	delete longitude;
	delete zoom;
}