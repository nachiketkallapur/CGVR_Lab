#include<iostream>
#include<gl/glut.h>
#include<math.h>
using namespace std;

GLfloat house[11][3] = { {100,250},{250,400},{400,250},{100,250},{100,50},{200,50},{200,150},{300,150},{300,50},{400,50},{400,250} };

float angle, c, m;

void myInit() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1, 1, 1, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-450, 450, -450, 450);
}

//Rotated House
void display1() {
	myInit();
	//drawHouse
	glColor3d(1, 0, 0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 11; i++) {
		glVertex2fv(house[i]);
	}
	glEnd();
	glFlush();

	glPushMatrix();
	glTranslatef(100, 100, 0);
	glRotatef(angle, 0, 0, 1);
	glTranslatef(-100, -100, 0);

	//drawHouse
	glColor3d(1, 0, 1);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 11; i++) {
		glVertex2fv(house[i]);
	}
	glEnd();

	glPopMatrix();
	glFlush();

}

//Reflection
void display2() {
	myInit();
	//drawHouse
	glColor3d(1, 0, 0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 11; i++) {
		glVertex2fv(house[i]);
	}
	glEnd();
	glFlush();

	float x1 = 0, x2 = 400;
	float y1 = m * x1 + c;
	float y2 = m * x2 + c;
	//drawLines
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();

	glPushMatrix();
	glTranslatef(0, c, 0);
	float theta = atan(m) * 180/3.14;
	glRotatef(theta, 0, 0, 1);
	glScalef(1, -1, 1);
	glRotatef(-theta, 0, 0, 1);
	glTranslatef(0, -c, 0);

	//drawHouse
	glColor3d(1, 0, 1);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 11; i++) {
		glVertex2fv(house[i]);
	}
	glEnd();

	glPopMatrix();
	glFlush();

}

void myMouse(int btn, int state, int x, int y){
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		display1();
	} 
	else if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		display2();
	}
}

int main(int argc, char* argv[]) {
	cout << "ENter angle of rotation: ";
	cin >> angle;
	cout << "Enter c and m values: ";
	cin >> c >> m;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(900, 900);
	glutCreateWindow("House");

	glutDisplayFunc(display1);
	glutMouseFunc(myMouse);

	myInit();
	glutMainLoop();

}