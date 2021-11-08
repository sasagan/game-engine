#include <iostream>
#include <math.h>

#include <GLFW/glfw3.h>
#include <GL/GL.h>
#include <gl/glut.h>
#include "objects.h"

#pragma comment (lib, "opengl32.lib")


int sizeWindowX = GetSystemMetrics(SM_CXSCREEN);
int sizeWindowY = GetSystemMetrics(SM_CYSCREEN);

GLfloat yaw = 0.0;
GLfloat pitch = 0.0;
float x = -15.0, z = 15.0, y = 8.0;

float lx = 0.69, lz = -0.63, ly = -0.35;

Plane plate;

void plane()
{
	glNormal3f(0, 0, 1);
	glBegin(GL_QUADS);
	glColor3f(0.23, 0.8, 0.25);
	glVertex3f(-10.0, 0.0, -10.0);
	glVertex3f(10.0, 0.0, -10.0);
	glVertex3f(10.0, 0.0, 10.0);
	glVertex3f(-10.0, 0.0, 10.0);
	glEnd();
}

void cube()
{
	glBegin(GL_QUADS);
	glColor3f(1.0, 0.0, 0.0);	//�������� �����
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);

	glColor3f(0.0, 1.0, 0.0);	//����� �����
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);

	glColor3f(0.0, 0.0, 1.0);	//������ �����
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);

	glColor3f(1.0, 1.0, 0.0);	//������ �����
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);

	glColor3f(1.0, 1.0, 1.0);	//������� �����
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
	glColor3f(1.0, 0.0, 0.0);	//�������� �����
	glVertex3f(-0.5, 0.5, 1.5);
	glVertex3f(0.5, 0.5, 1.5);
	glVertex3f(0.5, -0.5, 1.5);
	glVertex3f(-0.5, -0.5, 1.5);

	glColor3f(0.0, 1.0, 0.0);	//����� �����
	glVertex3f(-0.5, 0.5, 1.5);
	glVertex3f(-0.5, -0.5, 1.5);
	glVertex3f(-0.5, -0.5, 2.5);
	glVertex3f(-0.5, 0.5, 2.5);

	glColor3f(0.0, 0.0, 1.0);	//������ �����
	glVertex3f(0.5, 0.5, 1.5);
	glVertex3f(0.5, -0.5, 1.5);
	glVertex3f(0.5, -0.5, 2.5);
	glVertex3f(0.5, 0.5, 2.5);

	glColor3f(1.0, 1.0, 0.0);	//������ �����
	glVertex3f(0.5, -0.5, 1.5);
	glVertex3f(-0.5, -0.5, 2.5);
	glVertex3f(-0.5, -0.5, 2.5);
	glVertex3f(0.5, -0.5, 2.5);

	glColor3f(1.0, 1.0, 1.0);	//������� �����
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

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
}

void fooKeyboard(unsigned char key, int xx, int yy)
{
	float speedCameraMove = 0.2;

	if (GetKeyState('W') < 0)
	{
		x += cos(pitch) * cos(yaw) * speedCameraMove;
		z += cos(yaw) * sin(pitch) * speedCameraMove;
	}
	else if (GetKeyState('S') < 0)
	{
		x -= cos(pitch) * cos(yaw) * speedCameraMove;
		z -= cos(yaw) * sin(pitch) * speedCameraMove;
	}
	else if (GetKeyState(32) < 0)
	{
		y += speedCameraMove;
	}
	else if (GetKeyState('Z') < 0)
	{
		y -= speedCameraMove;
	}
	else if (GetKeyState(27) < 0)
	{
		exit(0);
	}
	/*else if (GetKeyState('D') < 0)
	{
		x += cos(pitch) * cos(yaw) * speedCameraMove;
		z += cos(yaw) * sin(pitch) * speedCameraMove;
	}
	else if (GetKeyState('A') < 0)
	{
		x -= cos(pitch) * cos(yaw) * speedCameraMove;
		z -= cos(yaw) * sin(pitch) * speedCameraMove;
	}*/

	/*switch (key) {
	case 32:
		y += speedCameraMove;
		break;
	case :
		y -= speedCameraMove;
		break;
	case 87:
		x += 2;
		z += 2;
		break;
	case 27:
		exit(0);
		break;
	}*/
}

void mouseMove(int ax, int ay)
{
	float speedMouseMove = 0.001;

	SetCursorPos(sizeWindowX / 2, sizeWindowY / 2);

	yaw += speedMouseMove * ((sizeWindowY / 2) - ay);
	pitch -= speedMouseMove * ((sizeWindowX / 2) - ax);

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


	plate.rotate[0] = 40.0, plate.rotate[1] = 1, plate.rotate[2] = 0, plate.rotate[3] = 0;
	plate.size[0] = 5, plate.size[1] = 5;
	plate.color[0] = 0.23, plate.color[0] = 0.8, plate.color[0] = 0.25;
	//plate.position[2] = 3;
	plate.render();


	cube();
	object();
	//plane();
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

	glutKeyboardFunc(fooKeyboard);
	glutPassiveMotionFunc(mouseMove);

	glutMainLoop();

	return 0;
}
