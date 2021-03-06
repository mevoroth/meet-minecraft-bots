#include "HunterActor.hpp"

#include "gl/glut.h"
#include "utils/types_extended.hpp"
#include "ActorsRepository.hpp"
#include "ai/AStar.hpp"
#include "Settings.hpp"

using namespace DatNS;

HunterActor::HunterActor(const NYVert3Df& pos, const NYVert3Df& speed, const NYVert3Df& rotation)
	: Actor(pos, speed, rotation)
	, currentState(MULTIPLY)
	, nextState(NONE)
	, eaten(0)
	, parasite(0)
	, foundDestination(false)
	, elapsedTime(0.f)
{
}

void HunterActor::update(float elapsedTime)
{
	static float noflick = 0.f;
	noflick += elapsedTime;
	if (noflick < ACTION_PER_SEC)
	{
		return;
	}
	noflick = 0.f;
	switch (currentState)
	{
	case MULTIPLY:
	{
		if (eaten < PARASITE_EAT_TO_REPRODUCE)
		{
			setState(EAT);
			return;
		}

		float length = INFINITY;
		list<HunterActor*> hunters = ActorsRepository::get()->getHunters();
		HunterActor* hunter = 0;

		for (list<HunterActor*>::iterator it = hunters.begin();
			it != hunters.end();
			++it)
		{
			if (((*it)->getPosition() - getPosition()).getMagnitude() < length)
			{
				length = ((*it)->getPosition() - getPosition()).getMagnitude();
				hunter = *it;
				if (length <= HUNTER_RANGE_TO_REPRODUCE)
				{
					break;
				}
			}
		}

		if (length > HUNTER_RANGE_TO_REPRODUCE)
		{
			nextState = MULTIPLY;
			destination = hunter->getPosition();
			setState(MOVE);
			return;
		}

		ActorsRepository::get()->createHunter(*this);
		eaten = 0;
		setState(EAT);
	} break;
	case LOOK_FOR_FOOD:
	{
		list<ZergActor*> parasites = ActorsRepository::get()->getParasites();
		if (!parasites.size())
		{
			setState(NONE);
			return;
		}
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

		destination = parasite->getPosition();
		setState(length < EAT_RANGE ? EAT : MOVE);
		if (length >= EAT_RANGE)
		{
			nextState = EAT;
		}
	} break;
	case EAT:
		if (!parasite)
		{
			setState(LOOK_FOR_FOOD);
			return;
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
			Forward() = (next - currentPos).normalize();
			foundDestination = true;
			this->elapsedTime = 0.f;
		}

		if (this->elapsedTime <= 1.f)
		{
			Position() = lerp(currentPos, next, this->elapsedTime);
			this->elapsedTime += elapsedTime * HUNTER_MOVE_SPEED;
			return;
		}

		foundDestination = false;
		Position() = next;
		currentPos = this->getPosition();
		this->elapsedTime = 0.f;

		NYVert3Df dest(destination);
		dest.Z = 0.f;
		NYVert3Df pos(getPosition());
		pos.Z = 0.f;

		if ((dest - pos).getMagnitude() > 0.01f)
		{
			return;
		}

		setState(nextState);
		break;
	}
}

void HunterActor::render()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

	glColor3f(1.f, 0.64453125f, 0.f);

	glPushMatrix();
	//glMultMatrixf(m);
	glRotatef(NYVert3Df(FORWARD).angleZ(getForward()), 0, 0, 1);
	glRotatef(NYVert3Df(FORWARD).angleY(getForward()), 0, 1, 0);
	glTranslatef(Position().X * 10 + 5, Position().Y * 10 + 5, Position().Z * 10 - 5);
	glutSolidCube(9);
	glPopMatrix();
}
;