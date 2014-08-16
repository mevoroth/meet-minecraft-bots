#include "ZergActor.hpp"

#include <cmath>
#include "gl/glut.h"

#include "ActorsRepository.hpp"
#include "ai\AIFactory.hpp"

using namespace DatNS;

ZergActor::ZergActor(const NYVert3Df& pos, const NYVert3Df& speed, const NYVert3Df& fw)
	: Actor(pos, speed, fw)
{
}

void ZergActor::update(float elapsedTime)
{
	switch (currentState)
	{
	case MULTIPLY:
	{
		// if isSeen
		// if
		list<ElfActor*> elves = ActorsRepository::get()->getElves();
		for (list<ElfActor*>::iterator it = elves.begin();
			it != elves.end();
			++it)
		{
			if ((*it)->getForward().scalProd((getPosition() - (*it)->getPosition()).normalize()) > SHEEP_VISION)
			{
				this->elapsedTime = 0.f;
				setState(LOOK_FOR_HOST);
				return;
			}
		}

		if (this->elapsedTime < MULTIPLY)
		{
			return;
		}

		ActorsRepository::get()->createZerg(*this);
		setState(TELEPORT);
	} break;
	case LOOK_FOR_HOST:
		break;
	case TELEPORT:
		break;
	}
}

void ZergActor::render()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

	glColor3f(1.f, 0.f, 0.f);

	glPushMatrix();
	//glMultMatrixf(m);
	glTranslatef(Position().X * 10 + 5, Position().Y * 10 + 5, Position().Z * 10 + 5);
	glutSolidCube(9);
	glPopMatrix();
}
