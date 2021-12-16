#include<iostream>
#include<gl/glut.h>
#include<math.h>
using namespace std;

void drawSphere() {

	double c = 3.142 / 180;
	double phi, theta, x, y, z;
	for (phi = -80.0; phi <= 80.0; phi += 10.0) {
		glBegin(GL_QUAD_STRIP);

		for (theta = -180.0; theta <= 180.0; theta += 10.0) {
			x = sin(c * theta) * cos(c * phi);
			y = cos(c * theta) * cos(c * phi);
			z = sin(c * phi);
			glVertex3f(x, y, z);

			x = sin(c * theta) * cos(c * (phi + 10.0));
			y = cos(c * theta) * cos(c * (phi + 10.0));
			z = sin(c * (phi + 10.0));
			glVertex3f(x, y, z);
		}
		glEnd();
	}

	glBegin(GL_TRIANGLE_FAN);
	x = y = 0;
	z = 1;
	glVertex3f(x, y, z);
	z = sin(c * 80.0);
	for (theta = -180.0; theta <= 180.0; theta += 10.0) {
		x = sin(c * theta) * cos(c * 80.0);
		y = cos(c * theta) * cos(c * 80.0);
		glVertex3f(x, y, z);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	x = y = 0;
	z = -1;
	glVertex3f(x, y, z);
	z = -sin(c * 80.0);
	for (theta = -180.0; theta <= 180.0; theta += 10.0) {
		x = sin(c * theta) * cos(c * 80.0);
		y = cos(c * theta) * cos(c * 80.0);
		glVertex3f(x, y, z);
	}
	glEnd();

}

void myDisplay() {

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -1.0);
	glRotatef(-110.0, 0.0, 1.0, 0.0);
	
	glColor3d(0, 0, 1);
	drawSphere();
	glFlush();

}

void myInit() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1, 1, 1, 1);
	gluOrtho2D(-1, 1, -1, 1);
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Sphere");
	glutDisplayFunc(myDisplay);
	glEnable(GL_DEPTH_TEST);
	myInit();
	glutMainLoop();
}