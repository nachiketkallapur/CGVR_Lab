#include<iostream>
#include<gl/glut.h>
using namespace std;

void drawPixels(int xc,int yc,int x, int y) {
	glColor3d(1, 0, 0);
	glBegin(GL_POINTS);
	glVertex2f(xc + x, yc + y);
	glVertex2f(xc - x, yc + y);
	glVertex2f(xc + x, yc - y);
	glVertex2f(xc - x, yc - y);
	glVertex2f(xc + y, yc + x);
	glVertex2f(xc - y, yc + x);
	glVertex2f(xc + y, yc - x);
	glVertex2f(xc - y, yc - x);
	glEnd();
	glFlush();

}

void bresCircle(int xc, int yc, int r) {
	int x = 0, y = r;
	int d = 3 - 2 * r;
	while (x <= y) {
		drawPixels(xc,yc,x, y);
		x++;
		if (d < 0) {
			d = d + 4*x + 6;
		}
		else {
			d = d + 4 * (x - y) + 10;
			y--;
		}
	}

	glFlush();
}



void displayCylinder() {
	glColor3d(1, 0, 0);
	int xc = 300, yc = 300, r = 50;
	for (int i = 0; i < 50; i+=2) {
		bresCircle(xc + i, yc + i, r);
	}
	
	for (int i = 0; i < r; i+=2) {
		bresCircle(xc, yc, i);
	}
}

void drawParalellopiped(int x1, int y1, int x2, int y2) {
	glColor3d(0, 0, 1);
	glBegin(GL_LINE_LOOP);
	glVertex2d(x1, y1);
	glVertex2d(x2, y1);
	glVertex2d(x2, y2);
	glVertex2d(x1, y2);
	glEnd();
	glFlush();
}

void displayParalellopiped() {
	glColor3d(0, 0, 1);
	int x1 = 250, y1 = 250, x2 = 350, y2 = 300;
	for (int i = 0; i < 50; i+=2) {
		drawParalellopiped(x1+i, y1+i, x2+i, y2+i);
	}
}



void myInit() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1, 1, 1, 1);
	gluOrtho2D(0, 500, 0, 500);
}

int main(int argc,char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	int wid1 = glutCreateWindow("Cylinder");
	glutSetWindow(wid1);
	glutDisplayFunc(displayCylinder);
	myInit();

	int wid2 = glutCreateWindow("Paralellopiped");
	glutSetWindow(wid2);
	glutDisplayFunc(displayParalellopiped);
	myInit();

	glutMainLoop();

}