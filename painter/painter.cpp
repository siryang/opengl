#include "share_util.h"
#include "opengl_stdafx.h"
#include <windows.h>
#include <iostream>
#include <gl/gl.h>
#include <gl/glu.h>
#include <vector>
//#include "common_types.h"
struct Point
{
	int x, y;
};

using namespace std;

int width = 512, height = 512;

template<class Iter>
void drawPolygon(Iter begin, Iter end)
{
	glBegin (GL_POLYGON);
	for (; begin < end; begin++)
	{
		glVertex3f((float)(*begin).x, (float)(*begin).y, 0);
	}
	glEnd();
}

void render()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	//glLoadIdentity();

	//// Draw a filled rectangle with current color
	//glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
	//glBegin(GL_TRIANGLE_FAN);
	//glVertex3f(0, 0, 0);
	//glVertex3f(0, 20, 0);
	//glVertex3f(20, 20, 0);
	//glEnd();

	// rect
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	Point polygonRect[] = {
		{0, 0},
		{0, 100},
		{100, 100},
		{100, 0},
	};

	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);

	drawPolygon(&polygonRect[0], &polygonRect[0] + element_of(polygonRect));

	glTranslatef(10.0f, 0, 0);
	drawPolygon(&polygonRect[0], &polygonRect[0] + element_of(polygonRect));

	glTranslatef(.0f, 10.0f, 0);
	drawPolygon(&polygonRect[0], &polygonRect[0] + element_of(polygonRect));
	glPopMatrix();

	//glMatrixMode(GL_MODELVIEW);
	//glTranslatef(.0f, 10.0f, 0);
	//glTranslatef(.0f, 10.0f, 0);
	//glTranslatef(.0f, 10.0f, 0);

	glFlush();
}

void resize(GLsizei w, GLsizei h)
{
	GLfloat aspectRatio;
	width = w;
	height = h;
	// Prevent a divide by zero
	if(h == 0)
		h = 1;
	// Set Viewport to window dimensions
	glViewport(0, 0, w, h);
	// Reset coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//// Establish clipping volume (left, right, bottom, top, near, far)
	if (w <= h)
	{
		aspectRatio = (GLfloat)h / (GLfloat)w;
		glOrtho (-100.0, 100.0, -100 * aspectRatio, 100.0 * aspectRatio, 1.0, -1.0);
	//	//gluPerspective(90.0f, 1/aspectRatio, 255.99f, 1024.0f);
	//	//glFrustum(-50, 50, -50*aspectRatio, 50*aspectRatio, 0.1f, 100.0f);
	//	//glFrustum(-1.00, 1.00, 1.00, -1.00, 0.1f, 100000.0f);

	//	//glFrustum(0, h/2, 0, w/2, 256.0f, 1024.0f);
	//	//glOrtho (-h/2, h/2, -w/2, w/2, 1.0, 1024.0);
	//	//glOrtho (0, h, 0, w, 1.0, 1024.0);
	}
	else
	{
		aspectRatio = (GLfloat)w / (GLfloat)h;
		//glFrustum(-50*aspectRatio, 50*aspectRatio, -50, 50, 1.0, -1.0);
		glOrtho (-100.0 * aspectRatio, 100.0 * aspectRatio, -100.0, 100.0, 1.0, -1.0);
	} 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 1.0f, 0, 0, 0, 0.0f, 1.0f, 0.0f);
}


#define MOUSE_BUTTON_WHEEL_UP 1
#define MOUSE_BUTTON_WHEEL_DOWN -1
void mouseWheel(int state, int dir, int x, int y)
{
	if (dir == 0)
		return;

	if (dir == MOUSE_BUTTON_WHEEL_UP){
		
	}
	else{
		
	}
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(width, height);
	glutInitDisplayMode( GLUT_SINGLE | GLUT_RGBA | GLUT_ALPHA);
	glutCreateWindow(argv[0]);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glutDisplayFunc(render);
	glutReshapeFunc(resize);
	glutMouseWheelFunc(mouseWheel);

	glutMainLoop();
}