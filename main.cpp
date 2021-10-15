#include <iostream>
#include <math.h>
#include <stdlib.h>

#include <GLFW/glfw3.h>
#include <GL/GL.h>
#include <gl/glut.h>

#include <Windows.h>

#pragma comment (lib, "opengl32.lib")


int sizeWindowX = GetSystemMetrics(SM_CXSCREEN);
int sizeWindowY = GetSystemMetrics(SM_CYSCREEN);

GLfloat yaw = 0.0;
GLfloat pitch = 0.0;
float x = 0.0, z = 5.0, y = 1.0;

float lx = 0, lz = 10.0, ly = 0;

float speed = 0.001;


void cube()
{
	glBegin(GL_QUADS);
	glColor3f(1.0, 0.0, 0.0);	//передн€€ грань
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);

	glColor3f(0.0, 1.0, 0.0);	//лева€ грань
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);

	glColor3f(0.0, 0.0, 1.0);	//права€ грань
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);

	glColor3f(1.0, 1.0, 0.0);	//нижн€€ грань
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);

	glColor3f(1.0, 1.0, 1.0);	//верхн€€ грань
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);

	glColor3f(0.8, 0.6, 0.2);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glEnd();
}

void object()
{
	glBegin(GL_QUADS);
	glColor3f(1.0, 0.0, 0.0);	//передн€€ грань
	glVertex3f(-0.5, 0.5, 1.5);
	glVertex3f(0.5, 0.5, 1.5);
	glVertex3f(0.5, -0.5, 1.5);
	glVertex3f(-0.5, -0.5, 1.5);

	glColor3f(0.0, 1.0, 0.0);	//лева€ грань
	glVertex3f(-0.5, 0.5, 1.5);
	glVertex3f(-0.5, -0.5, 1.5);
	glVertex3f(-0.5, -0.5, 2.5);
	glVertex3f(-0.5, 0.5, 2.5);

	glColor3f(0.0, 0.0, 1.0);	//права€ грань
	glVertex3f(0.5, 0.5, 1.5);
	glVertex3f(0.5, -0.5, 1.5);
	glVertex3f(0.5, -0.5, 2.5);
	glVertex3f(0.5, 0.5, 2.5);

	glColor3f(1.0, 1.0, 0.0);	//нижн€€ грань
	glVertex3f(0.5, -0.5, 1.5);
	glVertex3f(-0.5, -0.5, 2.5);
	glVertex3f(-0.5, -0.5, 2.5);
	glVertex3f(0.5, -0.5, 2.5);

	glColor3f(1.0, 1.0, 1.0);	//верхн€€ грань
	glVertex3f(-0.5, 0.5, 1.5);
	glVertex3f(0.5, 0.5, 1.5);
	glVertex3f(0.5, 0.5, 2.5);
	glVertex3f(-0.5, 0.5, 2.5);

	glColor3f(0.8, 0.6, 0.2);
	glVertex3f(-0.5, 0.5, 2.5);
	glVertex3f(0.5, 0.5, 2.5);
	glVertex3f(0.5, -0.5, 2.5);
	glVertex3f(-0.5, -0.5, 2.5);
	glEnd();
}

void WindowOpen(int a, int h)
{
	if (h == 0)
	{
		h = 1;
	}
	float ratio = 1.0 * a / h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, a, h);
	gluPerspective(45, ratio, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
}

void mouseMove(int ax, int ay)
{
	SetCursorPos(sizeWindowX / 2, sizeWindowY / 2);

	yaw += speed * ((sizeWindowY / 2) - ay);
	pitch -= speed * ((sizeWindowX / 2) - ax);

	lx = cos(pitch) * cos(yaw);
	ly = sin(yaw);
	lz = cos(yaw) * sin(pitch);
}

void quad(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);

	glLoadIdentity();

	gluLookAt(x, y, z,
		lx + x, ly + y, lz + z,
		0.0f, 1.0f, 0.0f);

	cube();
	object();

	glBegin(GL_QUADS);
	glColor3f(0.23, 0.23, 0.25);
	glVertex3f(-10.0, 0.0, -10.0);
	glVertex3f(10.0, 0.0, -10.0);
	glVertex3f(10.0, 0.0, 10.0);
	glVertex3f(-10.0, 0.0, 10.0);
	glEnd();

	glutSwapBuffers();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);


	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	glutCreateWindow("Window");
	glutFullScreen();

	glutDisplayFunc(quad);
	glutReshapeFunc(WindowOpen);
	glutIdleFunc(quad);

	glutPassiveMotionFunc(mouseMove);

	glutMainLoop();

	return 0;
}
