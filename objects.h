#include <iostream>
#include <math.h>

#include <GLFW/glfw3.h>
#include <GL/GL.h>
#include <gl/glut.h>

#pragma comment (lib, "opengl32.lib")

class Plane
{
public:
	float rotate[4] = {0, 0, 0, 0};
	float size[2] = {0, 0};
	float position[3] = {0, 0, 0};
	float color[3] = {0, 0, 0};

	void render()
	{
		
		
		glBegin(GL_QUADS);
		
		glColor3f(color[0], color[1], color[2]);
		
		glVertex3f(position[0] - size[0] / 2, position[1] - size[1] / 2, position[2]);
		glVertex3f(position[0] - size[0] / 2, position[1] + size[1] / 2, position[2]);
		glVertex3f(position[0] + size[0] / 2, position[1] + size[1] / 2, position[2]);
		glVertex3f(position[0] + size[0] / 2, position[1] - size[1] / 2, position[2]);
		glRotatef(rotate[0], rotate[1], rotate[2], rotate[3]);
		glEnd();
	}
};

