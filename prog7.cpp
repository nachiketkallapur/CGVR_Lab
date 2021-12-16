#include<iostream>
#include<algorithm>
#include<gl/glut.h>
#include<Windows.h>
using namespace std;

float x[10], y[10];
float intx[10] = { 0 };
int m,n;
int wx = 500, wy = 500;

void drawLine(float x1, float y1, float x2, float y2) {
	Sleep(50);
	glColor3d(0, 0, 1);
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
	glFlush();
}

void edgeDetect(float x1, float y1, float x2, float y2, int scanline) {
	if (y1 > y2) {
		swap(x1, x2);
		swap(y1, y2);
	}
	if (scanline > y1 && scanline < y2) {
		intx[m++] = x1 + (scanline - y1) * (x2 - x1) / (y2 - y1);
	}
}

void scanFill(float x[], float y[]) {
	for (int s1 = 0; s1 <= wy; s1++) {
		m = 0;
		for (int i = 0; i < n; i++) {
			edgeDetect(x[i], y[i], x[(i + 1) % n], y[(i + 1) % n], s1);
		}
		sort(intx, intx + m);

		if (m >= 2) {
			for (int i = 0; i < m; i+=2) {
				drawLine(intx[i], s1, intx[i + 1], s1);
			}
		}
	}
}

void displayFilledPolygon() {
	
	glColor3d(1, 0, 0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < n; i++) {
		glVertex2f(x[i], y[i]);
	}
	glEnd();
	glFlush();
	scanFill(x,y);
}

void myInit() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1, 1, 1, 1);
	gluOrtho2D(0, 200, 0, 200);
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	cout << "Enter number of edges of polygon: ";
	cin >> n;
	cout << "Enter the coordinates of the vertices: " << endl;
	for (int i = 0; i < n; i++) {
		cin >> x[i] >> y[i];
	}

	glutInitWindowSize(wx, wy);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Scanline fill algorithm");
	glutDisplayFunc(displayFilledPolygon);

	myInit();
	glutMainLoop();
}
