#include <GL/glut.h>					//Glut Library (includes gl.h and glu.h)

void display();							//display callback
void init();							//window initializer
void reshape(int,int);					//reshape callback
void timer(int);						//animation timer

int main(int argc, char** argv) {
		
	glutInit(&argc, argv);							//'glutInit' - Initializes the glut library
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);	//'glutInitDisplayMode' - Initialize display mode that glut will use, in this case: RBG
	
	glutInitWindowPosition(200, 100);	//'glutInitWindowPosition' - where on the screen will the window be displayed (pixels)
	glutInitWindowSize(500, 500);		//'glutInitWindowSize' - widht and height of the window (pixels)

	glutCreateWindow("Window Test");	/*'glutCreateWindow' - actually creates the window with the name, if these past 5 instructions 
										were to be ran as is, the window would not be created because there is no loop, so it would create 
										the window and instantly close it and terminate the program because there is no extra instructions 
										past the window creation*/
		
	glutDisplayFunc(display);			/*'glutDisplayFunc' - The glut library requires callbacks for all types of interactions.
										This one will take care of the window display. (must be called after the window is created)*/

	glutReshapeFunc(reshape);			/* Like the display callback, the reshape callback is called when the window is first created, and
										after that is called whenever the window is resized, maximized or minimized, basically when the window
										is reshaped, like the name suggests. The window is reshaped according to the new widht and height 
										of the window so there is no graphic distortion of whatever is on the screen.*/

	glutTimerFunc(0, timer, 0);			/*Calls a certain function, in this case 'timer', after a specified amount of time. 1st argument is
										the time, which is in milliseconds (1000 = 1sec), 2nd argument is the function we want to call, and
										3rd argument is the integer that is passed into the 2nd argument function. This is the first call,
										meaning that after the 1st parameter amount of seconds, the function within will be called.*/

	init();								//Makes the window a determined color, instead of the default black after the frame buffer is cleared

	glutMainLoop();						/*'glutMainLoop' - This loop takes care of all the interactions with the program. It keeps the 
										program running while this loop is running, when this loop terminates, the program terminates*/

	

	return 0;	
}

float x_Position = 0.0;					/*the x position that will be updated for the animation, in each frame. The smaller this value is
										//, the slower the animation seems. The bigger it is, the faster it seems to be going.*/
int state = 1;							//If it's 1, it's going right, if it's -1, it's going to left. Flag to help make the square go back and forth

void display() {						/*In animation, a SINGLE call to the display function is equal to a single frame*/

	//1. Clear
	glClear(GL_COLOR_BUFFER_BIT);		/*'glClear' - Before drawing on the window, the windows 'canvas' needs to be cleaned
										we draw on the frame buffer, its an area of the memory which corresponds to a frame on the screen
										a unit inside a frame buffer corresponds to a pixel on the screen, so first, all pixels on the 
										frame buffer must be cleaned to a default color. GL_COLOR_BUFFER_BIT is the flag that must be used
										for it to be cleared to the default color, which is black.*/
	
	//2. Reset
	glLoadIdentity();					/*'glLoadIdentity'- It resets all the transformations of the current matrix we're currently in. 
										It essentially resets any transformations, rotations etc. from the previous frame or that was carried 
										out earlier. So, it resets the coordinate system*/
	
	//3. Draw stuff
	//glPointSize(6.0);
	glTranslatef(x_Position,x_Position,0.0);	/*The translate function has to be called before the glBegin. In essence, the translate function
										knows it's next position, but it "listens" to what will be drawn next, and from THAT position, 
										it translates to the coordinates defined on it's parameters*/
	
	glBegin(GL_POLYGON);				/*Primitives drawings are done using vertices, so to begin drawing, we need to tell openGl that we're
										beginning the specification the vertices by calling 'glBegin'. The argument it takes, specifies what
										type of primite we're going to draw.*/
	glColor3f(1.0, 0.0, 0.0);
										/*Draws a cube at the left of the screen, that has the size of 2 units. Always go counter clockwise*/
	glVertex2f(-1.0, 1.0);				//Top left corner
	glColor3f(0.0, 1.0, 0.0);
	glVertex2f(-1.0, -1.0);				//Bottom left corner
	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(1.0,-1.0);				//Bottom right corner
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(1.0, 1.0);				//Top right corner
	
	glEnd();							/* 'glEnd' - Tells openGl we're done drawing the vertices, so openGl can actually take that information 
										to draw the primitive.*/

	//4.Display the frame buffer on the screen
	//glFlush();						//'glFlush' - Displays onto the screen with whatever is drawn on it

	glutSwapBuffers();					/*Swaps the front buffer to the back buffer and so on, with the primitives values being changed that's
										what will make the animation work. Replaces the glFlush, that is only meant for still 'drawings'*/

}

void init() {
	
	glClearColor(0.7,0.0,0.0,1.0);		/*1st argument: intensity of red, 2nd argument: intensity of green, 3rd argument: intensity of blue
										4th argument: Alpha, which is the opacity.
										Calling this function after the 'displayFunc' will make the window be displayed in the color that
										is defined in this method.*/
}

void reshape(int w, int h) {

	//1. Viewport
	glViewport(0,0,w, h);				/* The viewport is the actual rectangular clipping area where the drawings will be displayed.
										Everything drawn inside the API will only be displayed inside this viewport. To specify the viewport 
										inside the screen, this 'glViewport' is called.
										First 2 arguments are X and Y (origin), other two are widht and height. By definig x and y as (0,0)
										we're defining our viewport to be the same size of the actual window*/
	
	//2. Projection
	glMatrixMode(GL_PROJECTION);		/*The standard matrix we're usually in, is the MODELVIEW, that's used for rotation, scaling, etc.
										All the functions called to manipulate the matrix, will only affect the current matrix. This function
										will change the matrix mode to the projection matrix.*/

	glLoadIdentity();					/*As in the display, the 'loadIdentity' will reset the parameters, in this case, of the projection matrix*/
	
	gluOrtho2D(-10, 10, -10, 10);		/*A projection is just a cartesian plane. The projection actually specified how the vertices and 
										the primitives are mapped inside the space in the screen. 2D Ortographic projection. The arguments
										are: leftmost, rightmost, bottommost, topmost*/ 
	
	glMatrixMode(GL_MODELVIEW);			/*After having the projection, switches back to the MODELVIEW matrix*/

}

void timer(int){

	glutPostRedisplay();				/*This function calls the display function, every time it has a chance. In essense, if the below
										function 'glutTimerFunc' is being called 60 times in 1 second, so is 'glutPostRedisplay'*/

	glutTimerFunc(1000/60,timer,0);		/*We need to keep calling this periodically. We want it at 60FPS, meaning every 1/60th of a second
										a new frame needs to be displayed. After that amount of time, the function is called again.*/
	
	switch (state) {
		case 1:							//Case state = 1 means: Moving to the right side
			if (x_Position < 9.0) {		//Updates the x_Position of our square, so it 'moves' it on the x-axis. If it's value is < 8
				x_Position += 0.15;		//it keeps updating it, if not, stops. 8 is chosen because the square is 2 units, and our ortho
			}							//plane has 10, so when the x_Position is at 8, the right side of the cube is at the end of the screen.
			else {
				state = -1;				//When it reaches the right side, it updates the state flag to -1, to make it now go left
			}
			break;
		case -1:						//Case state = -1 means: Moving to the left side
			if (x_Position > -9.0) {	//if x_Position > -10, meaning it it hasn't reached the left side of the window, it will continue	
				x_Position -= 0.15;		//to move left, until it reaches it.
			}
			else {
				state = 1;				//When it reaches the left side, it updates the state flag back to 1, to make it now go right
			}
			break;
	}
}