#include<iostream>
#include<gl/glut.h>
using namespace std;
int wid1, wid2, t;
float spin = 0.0;

void display1() {
	glutSetWindow(t);
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glLoadIdentity();
	if (t == wid2) {
		glRotatef(spin, 0.0, 0.0, 1.0);
	}
	glBegin(GL_POLYGON);
	glColor3f(1, 0, 0);
	glVertex2f(0.25, 0.25);
	glColor3f(0, 1, 0);
	glVertex2f(-0.25, 0.25);
	glColor3f(0, 0, 1);
	glVertex2f(-0.25,-0.25);
	glColor3f(1, 1, 0);
	glVertex2f(0.25,-0.25);
	glEnd();
	glPopMatrix();

	if (t == wid1) {
		t = wid2;
		glFlush();
	}
	else {
		glutSwapBuffers();
		t = wid1;
	}
}

void spinDisplay() {
	spin += 0.02;
	glutPostRedisplay();
}

void mouse1(int btn, int state, int x, int y) {
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		glutIdleFunc(spinDisplay);
	}
	else if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		glutIdleFunc(NULL);
	}
}

void myInit() {                     
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, -1, 1);
	glClearColor(1, 1, 1, 1);
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	
	glutInitWindowSize(500, 500);
	wid1 = glutCreateWindow("Single");
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutDisplayFunc(display1);
	glutMouseFunc(mouse1);

	glutInitWindowSize(500, 500);
	wid2 = glutCreateWindow("Double");
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutDisplayFunc(display1);
	glutMouseFunc(mouse1);

	t = wid1;

	myInit();
	glutMainLoop();


}