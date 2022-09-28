#include <cstdlib>
#include "GetGlut.h"
#include "Square.h"

using namespace std;

void Square::init(float x, float y, float z, float t, float s, float xPos, float yPos, float speed, float newX, float newY, float angle, float pass)
{
	pos.set(0.0, 0.0);
	if (pass == 1.0)
	{
		vel = Vector2::getRandomUnitVector();
	}
	else
	{
		vel.set(newX, newY);
	}
	age = 0;
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

void Square::update()
{
	pos += vel * velocity;
	age++;
}

void Square::display(float key)
{
	glPushMatrix();
	glTranslated(pos.x, pos.y, 0.0f);
	// draw a white square
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(red, green, blue, transparency);
	glTranslatef(xPosition, yPosition, 0.0f);
	glScalef(scale, scale, scale);
	glRotatef(degrees, 0.0f, 0.0f, 1.0f);

	if (key == 0.5)
	{
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(-50.0, -50.0);
		glVertex2f(-50.0, 50.0);
		glVertex2f(50.0, 50.0);
		glVertex2f(50.0, -50.0);
		glEnd();
	}
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

bool Square::isAlive()
{
	if (age <= 60)
		return true;
	else
		return false;
}

/*float Square::random0to1()
{
	return (float)(rand()) / ((float)RAND_MAX + 1.0f);
}*/