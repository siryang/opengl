#include "share_util.h"
#include "opengl_stdafx.h"
#include <windows.h>
#include <iostream>
#include <gl/gl.h>
#include <gl/glu.h>
#include <string>

int frameWidth = 256;
int frameHeight = 256;
GLubyte* pixels;

GLuint fboId;
GLuint rboColor;
GLuint rboDepth;


void showErrorIfExist()
{
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE) {
		cout << "framebuffer error:" << endl;
		switch (status) {
				case GL_FRAMEBUFFER_UNDEFINED: {
					cout << "GL_FRAMEBUFFER_UNDEFINED" << endl;
					break;
											   }
				case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT: {
					cout << "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT" << endl;
					break;
														   }
				case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT: {
					cout << "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT" << endl;
					break;
																   }
				case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER: {
					cout << "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER" << endl;
					break;
															}
				case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER: {
					cout << "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER" << endl;
					break;
															}
				case GL_FRAMEBUFFER_UNSUPPORTED: {
					cout << "GL_FRAMEBUFFER_UNSUPPORTED" << endl;
					break;
												 }
				case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE: {
					cout << "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE" << endl;
					break;
															}
				case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS: {
					cout << "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS" << endl;
					break;
															  }
				case 0: {
					cout << "0" << endl;
					break;
						}
		}
		exit(EXIT_FAILURE);
	}
}

void init(int argc, char** argv) 
{
	// create and hide window
	glutInit(&argc, argv);
	glutInitWindowSize(frameWidth, frameHeight);
	glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH );
	//glutInitWindowPosition(0, 0);
	glutCreateWindow(argv[0]);
	//glutHideWindow();

	pixels = new GLubyte[frameWidth * frameHeight * 4];

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		exit(0);
	}
	// Create a new renderbuffer unique name.
	glGenRenderbuffers(1, &rboColor);
	// Set it as the current.
	glBindRenderbuffer(GL_RENDERBUFFER, rboColor);
	// Sets storage type for currently bound renderbuffer.
	glRenderbufferStorage(
		GL_RENDERBUFFER,
		GL_RGBA8,
		frameWidth,
		frameHeight
		);

	// Create a new renderbuffer unique name.
	glGenRenderbuffers(1, &rboDepth);
	// Set it as the current.
	glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
	// Sets storage type for currently bound renderbuffer.
	glRenderbufferStorage(
		GL_RENDERBUFFER,
		GL_DEPTH_COMPONENT24,
		frameWidth,
		frameHeight
		);

	// Framebuffer.

	// Create a framebuffer and a renderbuffer object.
	// You need to delete them when program exits.
	glGenFramebuffers(1, &fboId);
	glBindFramebuffer(GL_FRAMEBUFFER, fboId);
	//from now on, operate on the given framebuffer
	//GL_FRAMEBUFFER        read write
	//GL_READ_FRAMEBUFFER   read
	//GL_FRAMEBUFFER        write

	// Adds color renderbuffer to currently bound framebuffer.
	glFramebufferRenderbuffer(
		GL_FRAMEBUFFER,
		GL_COLOR_ATTACHMENT0,
		GL_RENDERBUFFER,
		rboColor
		);

	glFramebufferRenderbuffer(
		GL_FRAMEBUFFER,
		GL_DEPTH_ATTACHMENT,
		GL_RENDERBUFFER,
		rboDepth
		);

	//glCopyTexImage2D(,)
	//glMapBuffer(,)
	//glReadBuffer(GL_COLOR_ATTACHMENT0);


	showErrorIfExist();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, 1.0, 1.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, -5, 0, 0, 0, 0, 1, 0);

	// ÉèÖÃ»æÍ¼»º³åÇø
	glDrawBuffers(1, &fboId);

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
}

void cleanup()
{
	glDeleteRenderbuffers(1, &rboColor);
	glDeleteRenderbuffers(1, &rboDepth);
	glDeleteFramebuffers(1, &fboId);
	delete[] pixels;
}

void writeFBO2File(const char* filename)
{
	// Tell glReadPixels where to read from.
	glReadBuffer(GL_COLOR_ATTACHMENT0);
	glReadPixels(
		0,                  // top X rectangle
		0,          // top Y rectangle
		frameWidth,        // rectangle width
		frameHeight,                  // rectangle height
		GL_RGB,      // GL_RGB, output format
		GL_UNSIGNED_BYTE,   // output data type
		pixels              // where output will be saved
		);

	write_ppm(pixels, frameWidth, frameHeight, filename);
}

void draw()
{
	glClearColor(1.0f,1.0f,1.0f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
		glColor3d(1, 0, 0);
		glVertex3d(0, 1, 0);
		glColor3d(0, 1, 0);
		glVertex3d(-1, -1, 0);
		glColor3d(0, 0, 1);
		glVertex3d(1, -1, 0);
	glEnd();

	glFlush(); // remember to flush GL output!
	writeFBO2File("Triangles.ppm");

	glClearColor(.0f,.0f,.0f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3d(1.0, 0, 0);
	glutSolidSphere(1.0, 20, 20);
	glFlush();
	writeFBO2File("SolidSphere.ppm");

	//glMapBuffer() 
	showErrorIfExist();

	//glBlitFramebuffer(0, 0, 10, 10,
	//	10, 10, 30, 30, GL_COLOR_BUFFER_BIT, GL_LINEAR);
}

int main(int argc, char** argv)
{
	init(argc, argv);
	draw();
	cleanup();
	return 0;
}

