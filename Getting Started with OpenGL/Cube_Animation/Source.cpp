#include <GL/glut.h>				

void display();							
void init();							
void reshape(int,int);					
void timer(int);						

int main(int argc, char** argv) {
		
	glutInit(&argc, argv);							
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);	
	glutInitWindowPosition(400, 150);	
	glutInitWindowSize(500, 500);		

	glutCreateWindow("Cube");	
	glutDisplayFunc(display);			
	glutReshapeFunc(reshape);			
	glutTimerFunc(0, timer, 0);		
	init();							
	glutMainLoop();	

	//return 0;	
}

float angle = 0.0;						

void display() {						

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();	

	glTranslatef(0.0, 0.0, -8.0);
	glRotatef(angle, 2.0, 2.0, 1.0);
	glRotatef(angle, 0.0, 0.0, 1.0);
	glRotatef(angle, 1.0, 1.0, 1.0);
	
	glBegin(GL_QUADS);

	//front
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-1.0, 1.0, 1.0);
	glVertex3f(-1.0, -1.0, 1.0);
	glVertex3f(1.0, -1.0, 1.0);
	glVertex3f(1.0, 1.0, 1.0);
	//back
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(1.0, 1.0, -1.0);
	glVertex3f(1.0, -1.0, -1.0);
	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	//right
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(1.0, -1.0, 1.0);
	glVertex3f(1.0, -1.0, -1.0);
	glVertex3f(1.0, 1.0, -1.0);
	//left
	glColor3f(1.0, 1.0, 0.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(-1.0, -1.0, 1.0);
	glVertex3f(-1.0, 1.0, 1.0);
	//top
	glColor3f(0.0, 1.0, 1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glVertex3f(-1.0, 1.0, 1.0);
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(1.0, 1.0, -1.0);
	//bottom
	glColor3f(1.0, 0.0, 1.0);
	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(-1.0, -1.0, 1.0);
	glVertex3f(1.0, -1.0, 1.0);
	glVertex3f(1.0, -1.0, -1.0);
	
	glEnd();
	glutSwapBuffers();
}

void init() {
	glClearColor(0.0,0.0,0.0,1.0);
	glEnable(GL_DEPTH_TEST);			//Hidden Surface Removal
}

void reshape(int w, int h) {

	glViewport(0, 0, w, h);	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1, 5.0, 15.0);	/*1st Argument: degrees of the field of view, 2nd argument: aspect ratio, 3rd: Z distance from the
										origin to the near clip plane, 4th: Z far clip plane distance*/ 
	glMatrixMode(GL_MODELVIEW);	
}

void timer(int){

	glutPostRedisplay();				
	glutTimerFunc(1000/60, timer, 0);		
	
	angle += 2.5;
	if (angle > 360.0) {				//If it reaches 360 degrees, we reset it back
		angle = angle - 360.0;
	}
}