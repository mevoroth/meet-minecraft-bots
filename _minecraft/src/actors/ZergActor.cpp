#include "ZergActor.hpp"

#include <cmath>
#include "gl/glut.h"

#include "ActorsRepository.hpp"

using namespace DatNS;

ZergActor::ZergActor(const NYVert3Df& pos, const NYVert3Df& speed, const NYVert3Df& fw)
	: Actor(pos, speed, fw)
{
}

void ZergActor::multiply()
{
	ActorsRepository::get()->createParasite(*this);
}

void ZergActor::update()
{

}

void ZergActor::render()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

	glColor3f(1.f, 0.f, 0.f);

	glPushMatrix();
	//glMultMatrixf(m);
	glTranslatef(Position().X * 10, Position().Y * 10, Position().Z * 10 + 10);
	glutSolidCube(9);
	glPopMatrix();
}

void ZergActor::reset()
{

}
