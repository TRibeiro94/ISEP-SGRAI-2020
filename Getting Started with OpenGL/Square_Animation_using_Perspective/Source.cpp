#include <GL/glut.h>				

void display();							
void init();							
void reshape(int,int);					
void timer(int);						

int main(int argc, char** argv) {
		
	glutInit(&argc, argv);							
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);	
	glutInitWindowPosition(400, 150);	
	glutInitWindowSize(500, 500);		

	glutCreateWindow("Z-Axis Manipulation");	
	glutDisplayFunc(display);			
	glutReshapeFunc(reshape);			
	glutTimerFunc(0, timer, 0);		
	init();							
	glutMainLoop();	

	return 0;	
}

float z_Position = 0.0;					
int state = 1;						

void display() {						

	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();	
	glTranslatef(0.0, 0.0, z_Position);
	
	glBegin(GL_POLYGON);

	glColor3f(1.0,  0.0, 0.0);
	glVertex3f(-1.0,1.0, 0.0);			//Top left corner
	glColor3f(0.0, 1.0,  0.0);
	glVertex3f(-1.0,-1.0,0.0);			//Bottom left corner
	glColor3f(0.0, 0.0,  1.0);
	glVertex3f(1.0,-1.0, 0.0);			//Bottom right corner
	glColor3f(1.0, 1.0,  1.0);
	glVertex3f(1.0, 1.0, 0.0);			//Top right corner
	
	glEnd();
	glutSwapBuffers();
}

void init() {
	glClearColor(0.1,0.0,0.0,1.0);
}

void reshape(int w, int h) {

	glViewport(0, 0, w, h);	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1, 5.0, 50.0);	/*1st Argument: degrees of the field of view, 2nd argument: aspect ratio, 3rd: Z distance from the
										origin to the near clip plane, 4th: Z far clip plane distance*/ 
	glMatrixMode(GL_MODELVIEW);	
}

void timer(int){

	glutPostRedisplay();				
	glutTimerFunc(1000/60, timer, 0);		
	
	switch (state) {
		case 1:							//Case state = 1 means: Moving nearer
			if (z_Position < -8.0) {	//Updates the z_Position of our square, so it 'moves' it on the z-axis. If it's value is < -8
				z_Position += 0.25;		//it keeps updating it, if not, stops.
			} else {
				state = -1;				//When it reaches the nearest point, it updates the state flag to -1, to make it go 'away'
			} break;
		case -1:						//Case state = -1 means: Moving further
			if (z_Position > -20.0) {	//if z_Position > -20, meaning it it hasn't reached the furthest defined point, it will continue	
				z_Position -= 0.25;		//to move further away from the 'camera' until it hits it
			} else {
				state = 1;				//When it reaches the furthest point , it updates the state flag back to 1, to make it come towards us
			} break;
	}
}