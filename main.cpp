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
float x = -7.0, z = 0.0, y = 3.0;

float lx = 0.69, lz = -0.63, ly = -0.35;

Plane plate;
Plane square;
int t;
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
	glColor3f(1.0, 0.0, 0.0);	
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);

	glColor3f(0.0, 1.0, 0.0);	
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);

	glColor3f(0.0, 0.0, 1.0);	
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);

	glColor3f(1.0, 1.0, 0.0);	
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);

	glColor3f(1.0, 1.0, 1.0);	
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
	glColor3f(1.0, 0.0, 0.0);	
	glVertex3f(-0.5, 0.5, 1.5);
	glVertex3f(0.5, 0.5, 1.5);
	glVertex3f(0.5, -0.5, 1.5);
	glVertex3f(-0.5, -0.5, 1.5);

	glColor3f(0.0, 1.0, 0.0);	
	glVertex3f(-0.5, 0.5, 1.5);
	glVertex3f(-0.5, -0.5, 1.5);
	glVertex3f(-0.5, -0.5, 2.5);
	glVertex3f(-0.5, 0.5, 2.5);

	glColor3f(0.0, 0.0, 1.0);	
	glVertex3f(0.5, 0.5, 1.5);
	glVertex3f(0.5, -0.5, 1.5);
	glVertex3f(0.5, -0.5, 2.5);
	glVertex3f(0.5, 0.5, 2.5);

	glColor3f(1.0, 1.0, 0.0);	
	glVertex3f(0.5, -0.5, 1.5);
	glVertex3f(-0.5, -0.5, 2.5);
	glVertex3f(-0.5, -0.5, 2.5);
	glVertex3f(0.5, -0.5, 2.5);

	glColor3f(1.0, 1.0, 1.0);	
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
	glLoadIdentity();

	
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
	//glEnable(GL_CULL_FACE);
	//glFrontFace(GL_CCW);
	//glCullFace(GL_BACK);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_COLOR_MATERIAL);
	glMatrixMode(GL_MODELVIEW);
	
	glLoadIdentity();

	gluLookAt(x, y, z,
			  lx + x, ly + y, lz + z,
			  0.0f, 1.0f, 0.0f);

	plate.rotate[0] = -90.0, plate.rotate[1] = 0, plate.rotate[2] = 0;
	plate.size[0] = 1, plate.size[1] = 1;
	plate.color[0] = 0.23, plate.color[0] = 1, plate.color[0] = 0.25;
	//plate.position[2] = 3;
	
	glPushMatrix();
	
	glPushMatrix();
	

	square.size[0] = 1, square.size[1] = 1;
	square.color[1] = 1;
	glRotatef(t, 1, 0, 0);
	float light_ambient[] = { 1.0,1.0,1.0,0.1 };
	float position[] = { 0, 0, 1, 0 };
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	 
	//glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);

	glTranslatef(0, 0, 1);
	glScalef(0.2, 0.2, 0.2);
	square.render();

	
	glPopMatrix();
	//glShadeModel(GL_SMOOTH);
	
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient);
	plate.render();

	
	

	

	glPopMatrix();
	//cube();
	//object();
	//plane();
	glutSwapBuffers();
	t+= 1;
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
