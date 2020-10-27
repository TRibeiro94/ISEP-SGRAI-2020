#define _USE_MATH_DEFINES		//M_PI
#define _CRT_SECURE_NO_WARNINGS //Disables depracation (scanf)
#define DEBUG 1
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <GL/glut.h>

typedef struct {
	double x, y;
} point;

void display();
void menu();
void key(unsigned char, int, int);
void init();
void reshape(int, int);
void polygon(GLint,GLfloat,GLfloat,GLfloat);
float randomFloat(float, float);
float d, radius, alpha, x, y, t;
point c;
int n;

int main(int argc, char** argv) {

	point p0, p1;
	int i;
	
	//Standard points for the polygon to have a decent size within the window
	p0.x = -5; p0.y = 5;
	p1.x = 5; p1.y = -5;
	
	//Reads N
	printf("Insert a value for N:"); (void)scanf("%d", &n); printf("---------------------------\n");

	//Calculates C (Straight segment's middle point between P0 and P1) - Will be (0,0) considering the pre-defined P0 & P1 values
	c.x = (p0.x + p1.x) / 2.0;
	c.y = (p0.y + p1.y) / 2.0;
	printf("(C)  X = %.2lf; Y = %.2lf", c.x, c.y); printf("\n---------------------------\n");

	//Calculates D (Distance between P0 and P1)
	d = sqrt(pow((p1.x - p0.x), 2) + pow((p1.y - p0.y), 2));
	printf("(D) Distance = %.2lf", d); printf("\n---------------------------\n");

	alpha = ((360 * (M_PI / 180)) / n); //Alpha must be in radians to later use the COS/SEN functions
	radius = d / 2;
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowPosition(200, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("PL2 - Polygon");
	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutKeyboardFunc(key);
	init();

	glutMainLoop();

	return 0;
}

void display() {

	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	
	glBegin(GL_POLYGON);
	polygon((GLint)n, (GLfloat)x, (GLfloat)y, (GLfloat)radius);
	glEnd();

	glFlush();
}

/*According to the table, draws a polygon with n sides, r radius and center at (x0,y0)*/
void polygon(GLint n, GLfloat x0, GLfloat y0, GLfloat r) {
	int i;
	GLfloat angle = 2 * M_PI / n;

	for(i = 0; i < n; i++){
		x0 = radius * cos(t) + c.x;
		y0 = radius * sin(t) + c.y;
		t += alpha;

		glColor3f(randomFloat(0.0,1.0), randomFloat(0.0,1.0), randomFloat(0.0,1.0)); //Generates a random color
		glVertex2f(radius * cos((double)i * angle), radius * sin((double)i * angle));	
	}
	printf("-------------------------\n\n");
}

void init() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
}

void reshape(int w, int h) {

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-10, 10, -10, 10);
	glMatrixMode(GL_MODELVIEW);
}

void key(unsigned char key, int x, int y) {
	
	switch (key) {
	//Escape Key
	case 27:  
		exit(1);

	case 'h':
	case 'H':
		menu();
		break;
	case '+':
		if (n < 50){
			n++;
			glutPostRedisplay();
		}
		break;
	case '-':
		if (n > 3){
			n--;
			glutPostRedisplay(); 
		}
		break;
		
	}

	if (DEBUG) {
		printf("You've pressed: %c\n", key);
	}
}

void menu(void) {
	printf("\n\nPolygon:\n");
	printf("(h) - Help \n");
	printf("(+) - Increase number of sides\n");
	printf("(-) - Decrease number of sides\n");
	printf("(ESC) - Exit\n");
}

float randomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}