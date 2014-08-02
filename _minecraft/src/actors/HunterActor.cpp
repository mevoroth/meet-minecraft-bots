#include "HunterActor.hpp"

#include "gl/glut.h"

using namespace DatNS;

void HunterActor::update(float elapsedTime)
{

}

void HunterActor::render()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

	glColor3f(0.f, 1.f, 0.f);

	glPushMatrix();
	//glMultMatrixf(m);
	glTranslatef(Position().X * 10 + 5, Position().Y * 10 + 5, Position().Z * 10 + 5);
	glutSolidCube(9);
	glPopMatrix();
}
