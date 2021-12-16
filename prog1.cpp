#include<iostream>
#include<gl/glut.h>

using namespace std;

int x1, yc1, x2, y2;
int flag = 0;

void myDisplay() {}


void myInit() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1, 1, 1, 1);
	gluOrtho2D(0, 600, 0, 600);
}

void drawPixel(int x, int y) {
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	glVertex2d(x,y);
	glEnd();
	glFlush();
}

void drawLine(){
	int x=x1, y=yc1;
	int dx = x2 - x1, dy = y2 - yc1;
	int p;
	int incx = 1, incy = 1;

	if (x1 > x2) {
		incx = -1;
	}
	if (yc1 > y2) {
		incy = -1;
	}
	if (dx < 0) {
		dx = -dx;
	}
	if (dy < 0) {
		dy = -dy;
	}

	if (dx == 0) {
		for (int i = 0; i <= dy;i++) {
				drawPixel(x, y);
				y += incy;
			}
	}
	else if (dy == 0) {
		for (int i = 0; i <= dx; i++) {
				drawPixel(x, y);
				x += incx;
			}
	} 
	else if (dx == dy) {
		
		for (int i = 0; i <= dx; i++) {
			drawPixel(x, y);
			x += incx;
			y += incy;
		}
	}

	if (dy / dx <= 1) {
		p = 2 * dy - dx;
		int i = 0;
		while (i <= dx) {
			drawPixel(x, y);
			x+=incx;
			if (p < 0) {
				p += 2 * dy;
			} 
			else {
				p += 2 * dy - 2 * dx;
				y+=incy;
			}
			i++;
		}
	} 
	else {
		p = 2 * dx - dy;
		int i = 0;
		while (i <= dy) {
			drawPixel(x, y);
			y+=incy;
			if (p < 0) {
				p += 2 * dx;
			}
			else {
				p += 2 * dx - 2 * dy;
				x+=incx;
			}
			i++;
		}
	}

	glFlush();
}

void myMouse(int btn, int state, int X, int Y) {
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

		if (flag == 0) {
			x1 = X;
			yc1 = 600 - Y;
			cout << "x1 " << x1 << " y1 " << yc1 << endl;
			flag++;
		}
		else {
			flag = 0;
			x2 = X;
			y2 = 600 - Y;
			cout << "x2 " << x2 << " y2 " << y2 << endl;
			drawLine();
		}
	}
}


int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Bresenham Line Algorithm");

	int choice;
	
	cout << "Enter 1 for keyboard and 2 for mouse: ";
	cin >> choice;

	if (choice == 1) {
		cout << "Enter x1(0-600) and y1(0-600): ";
		cin >> x1 >> yc1;
		cout << "Enter x2(0-600) and y2(0-600): ";
		cin >> x2 >> y2;
		glutDisplayFunc(drawLine);
	}
	else if (choice == 2) {
		glutMouseFunc(myMouse);
		glutDisplayFunc(myDisplay);
	}

	myInit();

	glutMainLoop();
}