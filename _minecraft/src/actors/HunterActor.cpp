#include "HunterActor.hpp"

#include "gl/glut.h"
#include "utils/types_extended.hpp"
#include "ActorsRepository.hpp"
#include "ai/AStar.hpp"

using namespace DatNS;

HunterActor::HunterActor(const NYVert3Df& pos, const NYVert3Df& speed, const NYVert3Df& rotation)
	: Actor(pos, speed, rotation)
	, currentState(MULTIPLY)
	, eaten(0)
	, parasite(0)
	, foundDestination(false)
	, elapsedTime(0.f)
{
}

void HunterActor::update(float elapsedTime)
{
	switch (currentState)
	{
	case MULTIPLY:
		ActorsRepository::get()->createElf(*this);
		eaten = 0;
		setState(EAT);
		break;
	case LOOK_FOR_FOOD:
	{
		list<ZergActor*> parasites = ActorsRepository::get()->getParasites();
		float length = INFINITY;
		for (list<ZergActor*>::iterator it = parasites.begin();
			it != parasites.end();
			++it)
		{
			if (((*it)->getPosition() - getPosition()).getMagnitude() < length)
			{
				length = ((*it)->getPosition() - getPosition()).getMagnitude();
				parasite = *it;
			}
		}

		setState(length < EAT_RANGE ? EAT : MOVE);
	} break;
	case EAT:
		if (!parasite)
		{
			setState(LOOK_FOR_FOOD);
		}
		ActorsRepository::get()->removeParasite(parasite);
		parasite = 0;
		++eaten;

		if (eaten >= PARASITE_EAT_TO_REPRODUCE)
		{
			setState(MULTIPLY);
		}
		break;
	case MOVE:
		if (!foundDestination)
		{
			AStar astar(this->getPosition(), destination);
			currentPos = this->getPosition();
			next = astar.find();
			this->elapsedTime = 0.f;
		}

		if ((next - getPosition()).getMagnitude() > 0.01f)
		{
			Position() = lerp(currentPos, next, this->elapsedTime);
			this->elapsedTime += elapsedTime * HUNTER_MOVE_SPEED;
			return;
		}

		foundDestination = true;
		Position() = next;

		if ((destination - getPosition()).getMagnitude() > 0.01f)
		{
			return;
		}

		setState(EAT);
		break;
	}
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
