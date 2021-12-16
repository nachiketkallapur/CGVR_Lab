#include<iostream>
#include<gl/glut.h>

using namespace std;
int p1x, p1y, p2x, p2y;
int xc, yc, r;
int flag = 0;

void drawCircle(int x, int y) {
	glColor3f(1.0,0.0,0.0);
	glPointSize(3);
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

void bresCircle() {
	glClear(GL_COLOR_BUFFER_BIT);
	int x = 0, y = r;
	int d = 3 - 2 * r;
	while (x <= y) {
		drawCircle(x, y);
		x++;
		if (d < 0) {
			d = d + 4 * x + 6;
		}
		else {
			d = d + 4 * (x - y) + 10;
			y--;
		}
		drawCircle(x, y);
	}
}

void myDisplay(){}

void myMouse(int btn, int state, int x, int y) {

	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN && flag == 0) {
		p1x = x;
		p1y = 500 - y;
		flag++;
		xc = p1x;
		yc = p1y;
		cout << "p1x " << p1x << " p1y " << p1y << endl;
	} 
	else if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		p2x = x;
		p2y = 500 - y;
		r = sqrt((p1x - p2x) * (p1x - p2x) + (p1y - p2y) * (p1y - p2y));
		cout << "p2x " << p2x << " p2y " << p2y <<endl;
		cout << "xc " << xc << " yc " << yc << " r " << r << endl<<endl;
		flag = 0;
		bresCircle();
	}

}

void myInit() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1, 1, 1, 1);
	gluOrtho2D(0, 500, 0, 500);
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Bresenham's circle");

	int choice;
	printf("Enter 1 for keyboard and 2 for mouse: ");
	cin >> choice;
	if (choice == 1) {
		cout << "Enter center of the circle(xc yc): ";
		cin >> xc >> yc;
		cout << "Enter Radius: ";
		cin >> r;
		glutDisplayFunc(bresCircle);
	} 
	else if (choice == 2) {
		glutMouseFunc(myMouse);
		glutDisplayFunc(myDisplay);
	}

	myInit();
	glutMainLoop();
}