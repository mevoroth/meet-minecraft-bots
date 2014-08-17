#include "ZergActor.hpp"

#include <cmath>
#include "gl/glut.h"

#include "utils/types_extended.hpp"
#include "ActorsRepository.hpp"
#include "ai\AIFactory.hpp"
#include "ai\Astar.hpp"

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
		list<ElfActor*> elves = ActorsRepository::get()->getElves();
		for (list<ElfActor*>::iterator it = elves.begin();
			it != elves.end();
			++it)
		{
			NYVert3Df dist = (getPosition() - (*it)->getPosition());
			if (dist.getMagnitude() < SHEEP_VISION_RANGE && (*it)->getForward().scalProd(dist.normalize()) > SHEEP_VISION)
			{
				this->elapsedTime = 0.f;
				setState(LOOK_FOR_HOST);
				return;
			}
		}

		if (this->elapsedTime < MULTIPLY)
		{
			host->setParasited(true);
			this->elapsedTime += elapsedTime;
			return;
		}

		host->setParasited(false);
		this->elapsedTime = 0.f;
		ActorsRepository::get()->createParasite(*this);
		setState(LOOK_FOR_HOST);
	} break;
	case LOOK_FOR_HOST:
	{
		float dist = INFINITY;
		list<ElfActor*> elves = ActorsRepository::get()->getElves();
		for (list<ElfActor*>::iterator it = elves.begin();
			it != elves.end();
			++it)
		{
			NYVert3Df distv = (getPosition() - (*it)->getPosition());
			if (distv.getMagnitude() < dist
				&& distv.getMagnitude() < SHEEP_VISION_RANGE
				&& (*it)->getForward().scalProd(distv.normalize()) > SHEEP_VISION)
			{
				dist = distv.getMagnitude();
				host = *it;
			}
		}


		NYVert3Df fw(FORWARD);
		NYVert3Df up(UP);
		NYVert3Df right(RIGHT);

		while (fw.scalProd(FORWARD) > SHEEP_VISION)
		{
			fw = NYVert3Df(FORWARD);
			fw.rotate(up, static_cast<float>(rand()) * 2.0f * M_PI / static_cast<float>(RAND_MAX));
			fw.rotate(right, static_cast<float>(rand()) * 2.0f * M_PI / static_cast<float>(RAND_MAX));
		}

		destination = host->getPosition() - fw;

		setState(TELEPORT);
	} break;
	case TELEPORT:
		if (!foundDestination)
		{
			AStar astar(this->getPosition(), destination);
			currentPos = this->getPosition();
			next = astar.find();
			foundDestination = true;
			this->elapsedTime = 0.f;
		}

		if ((next - getPosition()).getMagnitude() > 0.01f)
		{
			Position() = lerp(currentPos, next, this->elapsedTime);
			this->elapsedTime += elapsedTime * SHEEP_MOVE_SPEED;
			return;
		}

		foundDestination = false;
		Position() = next;

		if ((destination - getPosition()).getMagnitude() > 0.01f)
		{
			return;
		}

		setState(MULTIPLY);
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
