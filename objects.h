#include <iostream>
#include <math.h>

#include <GLFW/glfw3.h>
#include <GL/GL.h>
#include <gl/glut.h>

#pragma comment (lib, "opengl32.lib")

class Plane
{
public:
	float rotate[3] = { 0, 0, 0 };
	float size[2] = { 0, 0 };
	float position[3] = { 0, 0, 0 };
	float color[3] = { 0, 0, 0 };


	void rotation()
	{
		glRotatef(rotate[0], 1.0, 0.0, 0.0); // x axis
		glRotatef(rotate[1], 0.0, 1.0, 0.0); // y axis
		glRotatef(rotate[2], 0.0, 0.0, 1.0); // z axis
	}

	void render()
	{
		glPushMatrix();
		rotation();
		glNormal3f(position[0], position[1], position[2] + 1);
		glBegin(GL_QUADS);
		glColor3f(color[0], color[1], color[2]);
		  glVertex3f(position[0] - size[0] / 2, position[1] - size[1] / 2, position[2]);
		  glVertex3f(position[0] - size[0] / 2, position[1] + size[1] / 2, position[2]);
		  glVertex3f(position[0] + size[0] / 2, position[1] + size[1] / 2, position[2]);
		  glVertex3f(position[0] + size[0] / 2, position[1] - size[1] / 2, position[2]);
		glEnd();
		glPopMatrix();
	}
};


class lightSource
{
public:
	float rotate[3] = { 0, 0, 0 };
	float size[2] = { 0, 0 };
	float position[4] = { 0, 0, 0, 0};
	float color[3] = { 0, 0, 0 };


};