#include <cstdlib>
#include "GetGlut.h"
#include "Square.h"

using namespace std;
// Initialization function, that initializes a particle
void Square::init(float x, float y, float z, float t, float s, float xPos, float yPos, float speed, float newX, float newY, float angle, float pass)
{
	pos.set(0.0, 0.0);
	// if pass = 1.0 we will send particles flying in any random direction
	if (pass == 1.0)
	{
		vel = Vector2::getRandomUnitVector();
	}
	else
	{
		vel.set(newX, newY); // we move a particle in a specific direction based on a calculation done in main
	}
	age = 0;
	// Below we are just initializing the particle with the pertinent information, it's colour how transparent, how large the speed at which it travels, it's rotation, it's current position on the screen
	red = x;
	green = y;
	blue = z;
	transparency = t;
	scale = s;
	xPosition = xPos;
	yPosition = yPos;
	velocity = speed;
	degrees = angle;
}
// Update the position of the particle
void Square::update()
{
	pos += vel * velocity;
	age++;
}
// Display the particle
void Square::display(float key)
{
	glPushMatrix();
	glTranslated(pos.x, pos.y, 0.0f); // The direction the particles are traveling in currently
	// draw a white square
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(red, green, blue, transparency); // Shows the color based on the above variable values
	glTranslatef(xPosition, yPosition, 0.0f); // The emitter location
	glScalef(scale, scale, scale); // Scale the particle
	glRotatef(degrees, 0.0f, 0.0f, 1.0f); // Rotate the particle

	// Shape 1, the default shape, if the user hasn't hit 'H' then a square will be produced
	if (key == 0.5)
	{
		glBegin(GL_TRIANGLE_FAN); // used Triangle fan to create all shapes
		glVertex2f(-50.0, -50.0);
		glVertex2f(-50.0, 50.0);
		glVertex2f(50.0, 50.0);
		glVertex2f(50.0, -50.0);
		glEnd();
	}
	// Shape 2, if the user hit 'H' once then this shape will be shown, etc...
	else if (key == 1.0)
	{
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(0, 0);
		glVertex2f(-25.0, 0);
		glVertex2f(-50.0, 50.0);
		glVertex2f(0.0, 25.0);
		glVertex2f(50.0, 50.0);
		glVertex2f(25.0, 0.0);
		glVertex2f(50.0, -50.0);
		glVertex2f(0.0, -25.0);
		glVertex2f(-50.0, -50.0);
		glVertex2f(-25.0, 0);
		glEnd();
	}
	else if (key == 1.5)
	{
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(-50.0, -50.0);
		glVertex2f(-50.0, 50.0);
		glVertex2f(50.0, 50.0);
		glVertex2f(50.0, -50.0);
		glEnd();
	}
	else if (key == 2.0)
	{
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(0.0, 0.0);
		glVertex2f(-50.0, 50.0);
		glVertex2f(0.0, 75.0);
		glVertex2f(50.0, 50.0);
		glVertex2f(75.0, 0.0);
		glVertex2f(50.0, -50.0);
		glVertex2f(0.0, -75.0);
		glVertex2f(-50.0, -50.0);
		glVertex2f(-75.0, 0.0);
		glVertex2f(-50.0, 50.0);
		glEnd();
	}
	else if (key == 2.5)
	{
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(0.0, 0.0);
		glVertex2f(-100.0, 0.0);
		glVertex2f(-50.0, 50.0);
		glVertex2f(0.0, 100.0);
		glVertex2f(50.0, 50.0);
		glVertex2f(100.0, 0.0);
		glVertex2f(50.0, -50.0);
		glVertex2f(0.0, -100.0);
		glVertex2f(-50.0, -50.0);
		glVertex2f(-100.0, 0.0);
		glEnd();
	}
	else if (key == 3.0)
	{
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(0.0, 0.0);
		glVertex2f(-100.0, 0.0);
		glVertex2f(-25.0, 25.0);
		glVertex2f(0.0, 100.0);
		glVertex2f(25.0, 25.0);
		glVertex2f(100.0, 0.0);
		glVertex2f(25.0, -25.0);
		glVertex2f(0.0, -100.0);
		glVertex2f(-25.0, -25.0);
		glVertex2f(-100.0, 0.0);
		glEnd();
	}
	
	glDisable(GL_BLEND);

	glPopMatrix();
}
// How long the particles last, so they don't live forever.
bool Square::isAlive()
{
	if (age <= 60)
		return true;
	else
		return false;
}
