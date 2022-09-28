//
//  Main3.cpp
//
//

#include <string>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include "GetGlut.h"
#include "Sleep.h"
#include "Vector2.h"
#include "Square.h"

using namespace std;
using namespace ObjLibrary;

// prototypes
void initDisplay();
void keyboard(unsigned char key, int x, int y);
void special(int special_key, int x, int y);
void update();
void reshape(int w, int h);
void display();


// declare global variables here
const unsigned int SQUARE_COUNT = 100;
Square squares[SQUARE_COUNT];
unsigned int next_square = 0;
bool emitter_on = true;
float red = 0.25; // Global variable to send red colour to function
float green = 0.25; // Global variable to send green color to function
float blue = 0.25; // Global variable to send blue color to function
float transparency = 1.0; // Global variable to send transparency to initialize function
float scale = 1.0; // Global variable to send scale to initialize function to alter size
float xPosition = 0.0; // Global variable to alter the translate function
float yPosition = 0.0; // Global variable to alter the translate function
float speed = 5.0; // Global variable to alter the speed
float newX = 1.0; // Global variable to alter the direction the particles are moving in
float newY = 0.0;
float angle = 0.0; // Used to alter the rotation of the particles
float windowR = 0.0; // Used to change the color of the background
float windowG = 0.0; 
float windowB = 0.0;
float radian = 0.0174533f; // Used to alter the direction the particles are moving in changing it to degrees
float pass = 0.0f; // Global key, essentially boolean that if 1 something will happen and if 0 then something else will happen
float tempX; // Used to change the direction the particles are moving in
float tempY;
float translateIncrement = 1.0; // Increments used to += or -=
float scaleIncrement = 0.05;
float increment = 0.01f;
float gate = 0.5f; // Used in changing the shapes of the particles
float gateIncrement = 0.5f;


int main (int argc, char** argv)
{
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);

	srand(time(0)); // Set random initial time for random number generating

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutCreateWindow("Particles");
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutIdleFunc(update);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);

	initDisplay();

	glutMainLoop();
	return 1;
}

void initDisplay()
{
	// CREATIVE FEATURE
	glClearColor(windowR, windowG, windowB, 0.0f);

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	// For colors increasing the red variables value by the increment value and sending it to the init function allows the particles to change their hue over time
	case 'R':
		if(red < 1.0)
		{
			red += increment;
			break;
		}
		break;
	case 'r':
		if (red > 0.0)
		{
			red -= increment;
			break;
		}
		break;
	case 'G':
		if (green < 1.0)
		{
			green += increment;
			break;
		}
		break;
	case 'g':
		if (green > 0.0)
		{
			green -= increment;
			break;
		}
		break;
	case 'B':
		if (blue < 1.0)
		{
			blue += increment;
			break;
		}
		break;
	case 'b':
		if (blue > 0.0)
		{
			blue -= increment;
			break;
		}
		break;
	// Transparency is same situation as colours, it is sent to the init function, all if statements are to create the min and max
	case 'T':
		if (transparency == 1.0)
		{
			break;
		}
		transparency += increment;
		break;
	case 't':
		if (transparency > 0.0)
		{
			transparency -= increment;
			break;
		}
		break;
	case '+':
		if (scale < 200)
		{
			scale += scaleIncrement;
			break;
		}
		break;
	case '-':
		if (scale <= 1.0)
		{
			break;
		}
		scale -= scaleIncrement;
		break;
	case 'd':
		if (xPosition == 160)
		{
			break;
		}
		xPosition += translateIncrement;
		break;
	case 'a':
		if (xPosition == -160)
		{
			break;
		}
		xPosition -= translateIncrement;
		break;
	case 'w':
		if (yPosition == 120)
		{
			break;
		}
		yPosition += translateIncrement;
		break;
	case 's':
		if (yPosition == -120)
		{
			break;
		}
		yPosition -= translateIncrement;
		break;
	// Added this extra step that I learnt in the labs to rotate the particles
	case '<':
		if (angle == 359.0)
		{
			angle = 0.0;
			break;
		}
		angle += translateIncrement;
		break;
	case '>':
		if (angle == 0.0)
		{
			angle = 359.0;
			break;
		}
		angle -= translateIncrement;
		break;
	// Used to change the shape of the particles
	case 'H':
		if (gate == 3.0)
		{
			break;
		}
		gate += gateIncrement;
		break;
	case 'h':
		if (gate == 0.5)
		{
			break;
		}
		gate -= gateIncrement;
		break;
	// CREATIVE FEATURE
	case 'c':
		windowR = (float)(rand()) / ((float)RAND_MAX + 1.0f); // Randomize the value of the red value in a range from 0-1
		windowG = (float)(rand()) / ((float)RAND_MAX + 1.0f);
		windowB = (float)(rand()) / ((float)RAND_MAX + 1.0f);
		break;
	// CREATIVE FEATURE
	// Set background back to black
	case 'C':
		windowR = 0.0f;
		windowG = 0.0f;
		windowB = 0.0f;
		break;
	// CREATIVE FEATURE
	// Create a firework effect where the emitter teleports to random locations on a range and sends particles all over the place while also randomizing the colors
	case 'q':
		xPosition = 1 + (rand() % 480) - 240;
		yPosition = 1 + (rand() % 480) - 240;
		red = (float)(rand()) / ((float)RAND_MAX + 1.0f);
		green = (float)(rand()) / ((float)RAND_MAX + 1.0f);
		blue = (float)(rand()) / ((float)RAND_MAX + 1.0f);
		pass = 1.0;
		break;
	// CREATIVE FEATURE
	// Set the positions back to normal rather than randomly going in all directions
	case 'Q':
		pass = 0.0;
		break;
	case ' ': // on [SPACEBAR]
		emitter_on = !emitter_on;
		break;
	case 27: // on [ESC]
		exit(0); // normal exit
		break;
	}
}
// Used for the special keys up, down, left, right
void special(int special_key, int x, int y)
{
	switch (special_key)
	{
	// Speed particles up
	case GLUT_KEY_UP:
		if (speed == 10.0)
		{
			break;
		}
		speed += translateIncrement;
		break;
	// Slow particles down
	case GLUT_KEY_DOWN:
		if (speed == 0.0)
		{
			break;
		}
		speed -= translateIncrement;
		break;
	// Change the direction the particles are moving in a counterclockwise manner
	case GLUT_KEY_LEFT:
		tempX = newX; // Store the value of the x value so that when calculating newY we aren't using the new value of x.
		tempY = newY;
		newX = tempX * cos(radian) - tempY * sin(radian); // Calculating the angle to create a new x point for the new position vector
		newY = tempX * sin(radian) + tempY * cos(radian);
		break;
	// Same as above just in a clockwise manner now
	case GLUT_KEY_RIGHT:
		tempX = newX;
		tempY = newY;
		newX = tempX * cos(radian) + tempY * sin(radian);
		newY = -(tempX * sin(radian)) + tempY * cos(radian);
		break;
	}
	
}


void update()
{
	// update your variables here
	glClearColor(windowR, windowG, windowB, 0.0f); // Change the background colour if the window variables have been changed

	for (int i = 0; i < SQUARE_COUNT; i++)
	{
		squares[i].update(); // Update the position of a particle as it moves across the screen
	}
	next_square++;
	if (next_square >= SQUARE_COUNT)
		next_square = 0;
	if (emitter_on)
		squares[next_square].init(red, green, blue, transparency, scale, xPosition, yPosition, speed, newX, newY, angle, pass); // Initialize the next particle with the new values that have potentially been altered by user input
	sleep(1.0 / 60.0);
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	glViewport (0, 0, w, h);

	int x_center = w / 2;
	int y_center = h / 2;

	// set up a 2D view
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-x_center, w - x_center, -y_center, h - y_center);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutPostRedisplay();
}

void display (void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// clear the screen - any drawing before here will not display
	for (int i = 0; i < SQUARE_COUNT; i++)
	{
		if (squares[i].isAlive())
		{
			squares[i].display(gate); // Display the particle on the screen sending the gate variable to determine which shape will display
		}
	}
	
	// send the current image to the screen - any drawing after here will not display
	glutSwapBuffers();
}


