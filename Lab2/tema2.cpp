#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

// dimensiunea ferestrei in pixeli
#define dim 300
float pi = 4 * atan(1);

unsigned char prevKey;

void Display1() {

}


void Display2() {

	float a = 0.3;
	float b = 0.2;

	glBegin(GL_LINE_LOOP);
	for (float i = 0; i < 2 * pi; i = i + 0.005)
	{
		float x = 2 * (a * cos(i) + b) * cos(i);
		float y = 2 * (a * cos(i) + b) * sin(i);

		glVertex2f(x - 0.5, y);
	}
	glEnd();
}

void Display3() {
	float a = 0.2;
	float yvector[1000];
	float xvector[1000];
	int j = 0;

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
	for (float i = -pi / 2 + 0.005; i < -pi / 6; i = i + 0.005) {

		float x = a / (4 * cos(i) * cos(i) - 3);
		float y = (a * tan(i)) / (4 * cos(i) * cos(i) - 3);

		glVertex2f(x, y);

		xvector[j] = x;
		yvector[j] = y;
		j++;
	}
	glEnd();

	glColor3f(1, 0.1, 0.1);
	glBegin(GL_TRIANGLES);
	for (int i = 1; i < j / 4; i += 2) {

	    glVertex2f(-1.0, 1.0);
	    glVertex2f(xvector[i], yvector[i]);
	    glVertex2f(xvector[i + 1], yvector[i + 1]);
	}
	for (int i = 3 *j / 4; i < j - 1; i += 2) {

		glVertex2f(-1.0, 1.0);
		glVertex2f(xvector[i], yvector[i]);
		glVertex2f(xvector[i + 1], yvector[i + 1]);
	}
	glEnd();
}

void Display4() {
	float a = 0.1;
	float b = 0.2;

	glBegin(GL_LINE_STRIP);
	for (float i = 0;i< 8 * pi; i = i + 0.005)
	{

		float x = a * i - b * sin(i);
		float y = a - b * cos(i);

		glVertex2f(x - 1.25, y);
	}
	glEnd();
}

void Display5() {
	float R = 0.1;
	float r = 0.3;
	
	glBegin(GL_LINE_STRIP);
	for (float i = 0; i < 2 * pi; i = i + 0.005)
	{

		float x = (R + r) * cos((r / R) * i) - r * cos(i + (r / R) * i);
		float y = (R + r) * sin((r / R) * i) - r * sin(i + (r / R) * i);

		glVertex2f(x, y);
	}
	glEnd();
}

void Display6() {

	float r = 0.3;
	float R = 0.1;

	glBegin(GL_LINE_STRIP);
	for (float i = 0; i < 2 * pi; i = i + 0.005){

		float x = (R - r) * cos((r / R) * i) - r * cos(i - (r / R) * i);
		float y = (R - r) * sin((r / R) * i) - r * sin(i - (r / R) * i);

		glVertex2f(x, y);
	}
	glEnd();
}

void Display7() {

	float a = 0.4;

	glBegin(GL_LINE_LOOP);

	for (float i = -(pi / 4);i >= -pi * 3 / 2; i = i - 0.005) {

		float r = a * sqrt(2 * cos(2 * i));
		float x = r * cos(i);
		float y = r * sin(i);

		glVertex2f(x, y);
	}

	for (float i = -pi / 4; i <= pi / 4; i = i + 0.005) {

		float r = a * sqrt(2 * cos(2 * i));
		float x = r * cos(i);
		float y = r * sin(i);

		glVertex2f(x, y);
	}

	glEnd();
}

void Display8() {
	float ratia = 0.05;
	float a = 0.02;


	glBegin(GL_LINE_STRIP);
	for (float i = 0; i < 1000; i = i + 0.005) {

		float x = a * exp(1 + i) * cos(i);
		float y = a * exp(1 + i) * sin(i);

		glVertex2f(x, y);
	}
	glEnd();
}

void Init(void) {

	glClearColor(1.0, 1.0, 1.0, 1.0);

	glLineWidth(1);

	//   glPointSize(4);

	glPolygonMode(GL_FRONT, GL_LINE);
}

void Display(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	switch (prevKey) {
	case '1':
		Display1();
		break;
	case '2':
		Display2();
		break;
	case '3':
		Display3();
		break;
	case '4':
		Display4();
		break;
	case '5':
		Display5();
		break;
	case '6':
		Display6();
		break;
	case '7':
		Display7();
		break;
	case '8':
		Display8();
		break;
	default:
		break;
	}

	glFlush();
}

void Reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void KeyboardFunc(unsigned char key, int x, int y) {
	prevKey = key;
	if (key == 27) // escape
		exit(0);
	glutPostRedisplay();
}

void MouseFunc(int button, int state, int x, int y) {
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);

	glutInitWindowSize(dim, dim);

	glutInitWindowPosition(100, 100);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutCreateWindow(argv[0]);

	Init();

	glutReshapeFunc(Reshape);

	glutKeyboardFunc(KeyboardFunc);

	glutMouseFunc(MouseFunc);

	glutDisplayFunc(Display);

	glutMainLoop();

	return 0;
}