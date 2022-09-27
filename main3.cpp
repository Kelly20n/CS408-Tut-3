//
//  Main3.cpp
//

#include <string>

#include "GetGlut.h"
#include "Sleep.h"
#include "Vector2.h"

using namespace std;
using namespace ObjLibrary;

// prototypes
void initDisplay();
void keyboard(unsigned char key, int x, int y);
void update();
void reshape(int w, int h);
void display();

// declare global variables here
Vector2 square_pos(0.0, 0.0);
Vector2 square_vel(5.0, 1.0);
double square_age = 0.0;


int main (int argc, char** argv)
{
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutCreateWindow("Particles");
	glutKeyboardFunc(keyboard);
	glutIdleFunc(update);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);

	initDisplay();

	glutMainLoop();

	return 1;
}

void initDisplay()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27: // on [ESC]
		exit(0); // normal exit
		break;
	}
}

void update()
{
	// update your variables here
	square_pos += square_vel;
	square_age++;
	if (square_age > 60)
	{
		// restart square movement
		square_age = 0.0;
		square_pos.set(0.0, 0.0);
	}
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
	glPushMatrix();
	glTranslated(square_pos.x, square_pos.y, 0.0f);
	// draw a white square
	glColor3d(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
		glVertex2f(-50.0, -50.0);
		glVertex2f(-50.0,  50.0);
		glVertex2f( 50.0,  50.0);
		glVertex2f( 50.0, -50.0);
	glEnd();

	glPopMatrix();

	// send the current image to the screen - any drawing after here will not display
	glutSwapBuffers();
}


