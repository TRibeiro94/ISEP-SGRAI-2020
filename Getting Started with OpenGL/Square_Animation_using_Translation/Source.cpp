#include <GL/glut.h>

void display();
void init();
void reshape(int,int);
void timer(int);

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(200, 100);
	glutInitWindowSize(500, 500);

	glutCreateWindow("Window Test");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutTimerFunc(0, timer, 0);
	init();
	glutMainLoop();

	return 0;
}

float x_Position = 0.0;
int state = 1;

void display() {

	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(x_Position,x_Position,0.0);

	glBegin(GL_POLYGON);

	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(-1.0, 1.0);
	glColor3f(0.0, 1.0, 0.0);
	glVertex2f(-1.0, -1.0);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(1.0,-1.0);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(1.0, 1.0);

	glEnd();

	glutSwapBuffers();
}

void init() {
	glClearColor(0.7,0.0,0.0,1.0);
}

void reshape(int w, int h) {

	glViewport(0,0,w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-10, 10, -10, 10);
	glMatrixMode(GL_MODELVIEW);
}

void timer(int){

	glutPostRedisplay();
	glutTimerFunc(1000/60,timer,0);

	switch (state) {
		case 1:
			if (x_Position < 9.0) {
				x_Position += 0.15;
			}
			else {
				state = -1;
			}
			break;
		case -1:
			if (x_Position > -9.0) {
				x_Position -= 0.15;
			}
			else {
				state = 1;				
			}
			break;
	}
}
