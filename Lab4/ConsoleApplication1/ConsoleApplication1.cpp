// Daca se doreste utilizarea bibliotecii GLUT trebuie
// inclus fisierul header GL/glut.h (acesta va include
// la GL/gl.h si GL/glu.h, fisierele header pentru
// utilizarea bibliotecii OpenGL). Functiile din biblioteca
// OpenGL sunt prefixate cu gl, cele din GLU cu glu si
// cele din GLUT cu glut.
#include <stdlib.h>
#include <GL/glut.h>
#include <list>
#include <vector>
#include <stdio.h>
#include <math.h>
#define PI  3.141592

using namespace std;
int numarLinii = 10, numarColoane = 10;
int global_w, global_h;
double raza_cerc = 1;
int grosime = 1;
unsigned char prevKey;

class Point {
public:
	int x, y;
	Point() {
		this->x = -1;
		this->y = -1;
	}
	Point(int x, int y) {
		this->x = x;
		this->y = y;
	}
};
Point prevMousePoz, currentMousePoz;

class GrilaCarteziana
{
	double DLinii, DColoane;
public:
	void writePixel(int i, int j) {
		double radius = DLinii / 5;
		double centru_x = i * DLinii - 1;
		double centru_y = j * DColoane - 1;

		glColor3f(0, 0, 0);
		glBegin(GL_TRIANGLE_FAN);

		glVertex2f(centru_x, centru_y);
		for (double i = 0; i <= 10; i += 0.1f) {
			double x = centru_x + (radius * cos(i * 2 * PI / 10));
			double y = centru_y + (radius * sin(i * 2 * PI / 10));
			glVertex2f(x, y);
		}
		glEnd();
	}
	void init(double numarLinii, double numarColoane)
	{
		this->DLinii = 2 / numarLinii;
		this->DColoane = 2 / numarColoane;

		glColor3f(1, 0.1, 0.1);
		glBegin(GL_LINES);

		for (double i = -1; i <= 1; i = i + DLinii)
		{
			glVertex2d(i, 1);
			glVertex2d(i, -1);
		}
		for (double i = -1; i <= 1; i = i + DColoane)
		{
			glVertex2d(-1, i);
			glVertex2d(1, i);
		}
		glEnd();

		writePixel(-1, -1); //bugfix 
	}  
};
GrilaCarteziana gc;

void Init(void) {
	// specifica culoarea unui buffer dupa ce acesta
	// a fost sters utilizand functia glClear. Ultimul
	// argument reprezinta transparenta (1 - opacitate
	// completa, 0 - transparenta totala)
	glClearColor(1.0, 1.0, 1.0, 1.0);

	// grosimea liniilor
	glLineWidth(3);

	// dimensiunea punctelor
	glPointSize(4);

	// functia void glPolygonMode (GLenum face, GLenum mode)
	// controleaza modul de desenare al unui poligon
	// mode : GL_POINT (numai vf. primitivei) GL_LINE (numai
	//        muchiile) GL_FILL (poligonul plin)
	// face : tipul primitivei geometrice dpdv. al orientarii
	//        GL_FRONT - primitive orientate direct
	//        GL_BACK  - primitive orientate invers
	//        GL_FRONT_AND_BACK  - ambele tipuri
	glPolygonMode(GL_FRONT, GL_LINE);
}

void drawCircle(Point origin, double range) {
	glBegin(GL_LINE_LOOP);
	glColor3f(1, 0, 0);
	for (double i = 0; i <= 2*PI; i+=0.2) {
		double x = origin.x + range * cos(i);
		double y = origin.y + range * sin(i);
		glVertex2d(x, y);
	}
	glEnd();
}

void AfisarePuncteCerc3(int x, int y, list<Point> &M)
{
	//M.push_back(Point(x, y));
	//M.push_back(Point(-x, -y));
	//M.push_back(Point(-x, y));
	//M.push_back(Point(x, -y));
	if (x != y) {
		M.push_back(Point(y, x));
		M.push_back(Point(-y, -x));
		//M.push_back(Point(-y, x));
		//M.push_back(Point(y, -x));
	}
}

void AfisareCerc4(int R)
{
	int x = 0, y = R;
	int d = 1 - R;
	int dE = 3, dSE = -2 * R + 5;
	list<Point> M;
	AfisarePuncteCerc3(x, y, M);
	while (y > x)
	{
		if (d < 0)
		{
			d += dE;
			dE += 2;
			dSE += 2;
		}
		else
		{
			d += dSE;
			dE += 2;
			dSE += 4;
			y--;
		}
		x++;
		AfisarePuncteCerc3(x, y, M);
	}
	 
	list<Point>::iterator it;
	for (it = M.begin(); it != M.end(); ++it) {
		gc.writePixel(it->x, it->y);
		for (int g = 1; g < grosime; g++) {
			gc.writePixel(it->x - g, it->y);
			gc.writePixel(it->x + g, it->y);
		}
		//printf("%d %d \n", it->x, it->y);
	}
}

void graphics() {
	glClear(GL_COLOR_BUFFER_BIT);
	gc.init(numarLinii, numarColoane);
	drawCircle(Point(-1, -1), 2 * raza_cerc);
	AfisareCerc4(numarLinii * raza_cerc);
	glFlush();
}

void Display(void) {
	switch (prevKey) {
		case '0':
			glClear(GL_COLOR_BUFFER_BIT);
			glFlush();
			break;
		case '1': 
			if (numarLinii > 1) {
				numarLinii--;
				numarColoane--;
			}
			graphics();
			break;
		case '2': 
			numarLinii++;
			numarColoane++;
			graphics();
			break;
		case '3':
			if (raza_cerc > 0) raza_cerc -= 0.1;
			graphics();
			break;
		case '4':
			raza_cerc += 0.1;
			graphics();
			break;
		case '5':
			if (grosime > 0) grosime -= 1;
			graphics();
			break;
		case '6':
			grosime += 1;
			graphics();
			break;
		default:
			break;
	}
	prevKey = ' ';
}

/*
   Parametrii w(latime) si h(inaltime) reprezinta noile
   dimensiuni ale ferestrei
*/
void Reshape(int w, int h) {
	global_w = w;
	global_h = h;
	printf("Call Reshape : latime = %d, inaltime = %d\n", w, h);

	// functia void glViewport (GLint x, GLint y,
	//                          GLsizei width, GLsizei height)
	// defineste poarta de afisare : acea suprafata dreptunghiulara
	// din fereastra de afisare folosita pentru vizualizare.
	// x, y sunt coordonatele pct. din stg. jos iar 
	// width si height sunt latimea si inaltimea in pixeli.
	// In cazul de mai jos poarta de afisare si fereastra coincid
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

/*
   Parametrul key indica codul tastei iar x, y pozitia
   cursorului de mouse
*/
void KeyboardFunc(unsigned char key, int x, int y) {
	prevKey = key;
	if (key == 27) // escape
		exit(0);
	glutPostRedisplay();
}
 

int main(int argc, char** argv) {
	// Initializarea bibliotecii GLUT. Argumentele argc
	// si argv sunt argumentele din linia de comanda si nu 
	// trebuie modificate inainte de apelul functiei 
	// void glutInit(int *argcp, char **argv)
	// Se recomanda ca apelul oricarei functii din biblioteca
	// GLUT sa se faca dupa apelul acestei functii.
	glutInit(&argc, argv);

	// Argumentele functiei
	// void glutInitWindowSize (int latime, int latime)
	// reprezinta latimea, respectiv inaltimea ferestrei
	// exprimate in pixeli. Valorile predefinite sunt 300, 300.
	glutInitWindowSize(300, 300);

	// Argumentele functiei
	// void glutInitWindowPosition (int x, int y)
	// reprezinta coordonatele varfului din stanga sus
	// al ferestrei, exprimate in pixeli. 
	// Valorile predefinite sunt -1, -1.
	glutInitWindowPosition(100, 100);

	// Functia void glutInitDisplayMode (unsigned int mode)
	// seteaza modul initial de afisare. Acesta se obtine
	// printr-un SAU pe biti intre diverse masti de display
	// (constante ale bibliotecii GLUT) :
	// 1. GLUT_SINGLE : un singur buffer de imagine. Reprezinta
	//    optiunea implicita ptr. nr. de buffere de
	//    de imagine.
	// 2. GLUT_DOUBLE : 2 buffere de imagine.
	// 3. GLUT_RGB sau GLUT_RGBA : culorile vor fi afisate in
	//    modul RGB.
	// 4. GLUT_INDEX : modul indexat de selectare al culorii.
	// etc. (vezi specificatia bibliotecii GLUT)
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	// Functia int glutCreateWindow (char *name)
	// creeaza o fereastra cu denumirea data de argumentul
	// name si intoarce un identificator de fereastra.
	glutCreateWindow(argv[0]);

	Init();

	// Functii callback : functii definite in program si 
	// inregistrate in sistem prin intermediul unor functii
	// GLUT. Ele sunt apelate de catre sistemul de operare
	// in functie de evenimentul aparut

	// Functia 
	// void glutReshapeFunc (void (*Reshape)(int width, int height))
	// inregistreaza functia callback Reshape care este apelata
	// oridecate ori fereastra de afisare isi modifica forma.
	glutReshapeFunc(Reshape);

	// Functia 
	// void glutKeyboardFunc (void (*KeyboardFunc)(unsigned char,int,int))
	// inregistreaza functia callback KeyboardFunc care este apelata
	// la actionarea unei taste.
	glutKeyboardFunc(KeyboardFunc); 

	// Functia 
	// void glutDisplayFunc (void (*Display)(void))
	// inregistreaza functia callback Display care este apelata
	// oridecate ori este necesara desenarea ferestrei: la 
	// initializare, la modificarea dimensiunilor ferestrei
	// sau la apelul functiei
	// void glutPostRedisplay (void).
	glutDisplayFunc(Display);

	// Functia void glutMainLoop() lanseaza bucla de procesare
	// a evenimentelor GLUT. Din bucla se poate iesi doar prin
	// inchiderea ferestrei aplicatiei. Aceasta functie trebuie
	// apelata cel mult o singura data in program. Functiile
	// callback trebuie inregistrate inainte de apelul acestei
	// functii.
	// Cand coada de evenimente este vida atunci este executata
	// functia callback IdleFunc inregistrata prin apelul functiei
	// void glutIdleFunc (void (*IdleFunc) (void))
	glutMainLoop();

	return 0;
}