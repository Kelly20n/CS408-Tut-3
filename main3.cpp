//
//  Main3.cpp
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
float red = 0.25;
float green = 0.25;
float blue = 0.25;
float transparency = 1.0;
float scale = 1.0;
float xPosition = 0.0;
float yPosition = 0.0;
float speed = 5.0;
float newX = 1.0;
float newY = 0.0;
float angle = 0.0;
float windowR = 0.0;
float windowG = 0.0;
float windowB = 0.0;
float radian = 0.0174533f;
float pass = 0.0f;
float tempX;
float tempY;
float translateIncrement = 1.0;
float scaleIncrement = 0.05;
float increment = 0.01f;
float gate = 0.5f;
float keyIncrement = 0.5f;


int main (int argc, char** argv)
{
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);

	srand(time(0));

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
	glClearColor(windowR, windowG, windowB, 0.0f);

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
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
	case 'H':
		if (gate == 3.0)
		{
			break;
		}
		gate += keyIncrement;
		break;
	case 'h':
		if (gate == 0.5)
		{
			break;
		}
		gate -= keyIncrement;
		break;
	case 'c':
		windowR = (float)(rand()) / ((float)RAND_MAX + 1.0f);
		windowG = (float)(rand()) / ((float)RAND_MAX + 1.0f);
		windowB = (float)(rand()) / ((float)RAND_MAX + 1.0f);
		break;
	case 'C':
		windowR = 0.0f;
		windowG = 0.0f;
		windowB = 0.0f;
		break;
	case 'q':
		xPosition = 1 + (rand() % 480) - 240;
		yPosition = 1 + (rand() % 480) - 240;
		red = (float)(rand()) / ((float)RAND_MAX + 1.0f);
		green = (float)(rand()) / ((float)RAND_MAX + 1.0f);
		blue = (float)(rand()) / ((float)RAND_MAX + 1.0f);
		pass = 1.0;
		break;
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

void special(int special_key, int x, int y)
{
	switch (special_key)
	{
	case GLUT_KEY_UP:
		if (speed == 10.0)
		{
			break;
		}
		speed += translateIncrement;
		break;
	case GLUT_KEY_DOWN:
		if (speed == 0.0)
		{
			break;
		}
		speed -= translateIncrement;
		break;
	case GLUT_KEY_LEFT:
		tempX = newX;
		tempY = newY;
		newX = tempX * cos(radian) - tempY * sin(radian);
		newY = tempX * sin(radian) + tempY * cos(radian);
		break;
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
	glClearColor(windowR, windowG, windowB, 0.0f);

	for (int i = 0; i < SQUARE_COUNT; i++)
	{
		squares[i].update();
	}
	next_square++;
	if (next_square >= SQUARE_COUNT)
		next_square = 0;
	if (emitter_on)
		squares[next_square].init(red, green, blue, transparency, scale, xPosition, yPosition, speed, newX, newY, angle, pass);
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
			squares[i].display(gate);
		}
	}
	
	// send the current image to the screen - any drawing after here will not display
	glutSwapBuffers();
}


