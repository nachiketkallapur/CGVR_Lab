#include<iostream>
#include<gl/glut.h>
using namespace std;
typedef GLfloat point[3];
point tetra[4] = {{0,250,-250},{0,0,250},{250,-250,-250},{-250,-250,-250}};
int n;

void drawTriangle(point a, point b, point c) {
	glBegin(GL_TRIANGLES);
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
	glEnd();
}

void drawTetrahedron(point a, point b, point c, point d) {
	glColor3d(1, 0, 0);
	drawTriangle(a, b, c);
	glColor3d(0, 1, 0);
	drawTriangle(a, c, d);
	glColor3d(0, 0, 1);
	drawTriangle(a,b,d);
	glColor3d(1, 1, 0);
	drawTriangle(b,c,d);

	glFlush();

}

void divideTetrahedron(point a, point b, point c, point d, int n) {
	if (n > 0) {
		point ab, ac, ad, bc, bd, cd;

		for (int j = 0; j < 3; j++) ab[j] = (a[j] + b[j]) / 2;
		for (int j = 0; j < 3; j++) ac[j] = (a[j] + c[j]) / 2;
		for (int j = 0; j < 3; j++) ad[j] = (a[j] + d[j]) / 2;
		for (int j = 0; j < 3; j++) bc[j] = (b[j] + c[j]) / 2;
		for (int j = 0; j < 3; j++) bd[j] = (b[j] + d[j]) / 2;
		for (int j = 0; j < 3; j++) cd[j] = (c[j] + d[j]) / 2;

		divideTetrahedron(a, ab, ac, ad, n - 1);
		divideTetrahedron(ab, b, bc, bd, n - 1);
		divideTetrahedron(ac, bc, c, cd, n - 1);
		divideTetrahedron(ad, bd, cd, d, n - 1);
	}
	else {
		drawTetrahedron(a, b, c, d);
	}
}

void displayTetrahedron() {
	divideTetrahedron(tetra[0], tetra[1], tetra[2], tetra[3],n);
	glFlush();
}

void myInit() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1, 1, 1, 1);
	glOrtho(-250, 250, -250, 250,-250,250);
}

int main(int argc, char* argv[]) {
	cout << "Enter number of iterations: ";
	cin >> n;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("3D gasket");
	glutDisplayFunc(displayTetrahedron);
	glEnable(GL_DEPTH_TEST);
	myInit();

	glutMainLoop();

}