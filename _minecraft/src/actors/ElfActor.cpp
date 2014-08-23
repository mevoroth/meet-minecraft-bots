#include "ElfActor.hpp"
#include <typeinfo.h>
#include "gl/glew.h"
#include "gl/glut.h"
#include "Settings.hpp"
#include "ActorsRepository.hpp"
#include "ai/AStar.hpp"
#include "utils/types_extended.hpp"
#include "Group.hpp"

using namespace DatNS;

ElfActor::ElfActor(const NYVert3Df& pos, const NYVert3Df& speed, const NYVert3Df& rotation)
	: Actor(pos, speed, rotation)
	, currentState(MULTIPLY)
	, nextState(NONE)
	, bush(0)
	, eaten(0)
	, foundDestination(false)
	, parasited(false)
	, elapsedTime(0.f)
{
}

void ElfActor::update(float elapsedTime)
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
	case GROUP:
	{
		if (nextState == GROUP)
		{
			nextState = NONE;
			setState(LOOK_FOR_BUSH);
			return;
		}

		Group* group = 0;
		list<Group*> groups = ActorsRepository::get()->getGroups();
		float length = INFINITY;
		for (list<Group*>::iterator it = groups.begin();
			it != groups.end();
			++it)
		{
			if (this->group != *it && !(*it)->full() &&
				((*it)->getPosition() - getPosition()).getMagnitude() < length)
			{
				length = ((*it)->getPosition() - getPosition()).getMagnitude();
				group = *it;
			}
		}

		if (group == 0)
		{
			setState(EAT);
			return;
		}

		destination = group->getPosition();
		this->group->remove(this);
		if (this->group->size() == 0) {
			ActorsRepository::get()->remove(this->group);
		}
		group->add(this);
		this->group = group;
		nextState = GROUP;
		setState(MOVE);
	} break;
	case LOOK_FOR_BUSH:
	{
		if (nextState != LOOK_FOR_BUSH)
		{
			setState(STARE);
			nextState = LOOK_FOR_BUSH;
			this->elapsedTime = 0.f;
			return;
		}
		nextState = NONE;
		list<BushActor*> bushes = ActorsRepository::get()->getBushes();
		if (!bushes.size())
		{
			setState(NONE);
			return;
		}
		float length = INFINITY;
		for (list<BushActor*>::iterator it = bushes.begin();
			it != bushes.end();
			++it)
		{
			if (((*it)->getPosition() - getPosition()).getMagnitude() < length)
			{
				length = ((*it)->getPosition() - getPosition()).getMagnitude();
				bush = *it;
			}
		}

		if (length < EAT_RANGE)
		{
			setState(EAT);
		}
		else
		{
			nextState = EAT;
			setState(MOVE);
		}
	} break;
	case STARE:
		Forward().rotate(NYVert3Df(UP), sin(this->elapsedTime)*M_PI_4*STARE_SPEED_SHEEP);
		this->elapsedTime += elapsedTime;
		if (this->elapsedTime >= 1.f)
		{
			this->elapsedTime = 0.f;
			currentState = nextState;
		}
		break;
	case EAT:
		if (nextState != EAT)
		{
			setState(STARE);
			nextState = EAT;
			this->elapsedTime = 0.f;
			return;
		}
		nextState = NONE;
		if (!bush)
		{
			setState(LOOK_FOR_BUSH);
			return;
		}
		bush->consume();
		if (bush->empty())
		{
			bush->destroy();
			bush = 0;
		}
		++eaten;

		if (eaten >= SHEEP_EAT_TO_REPRODUCE)
		{
			setState(MULTIPLY);
		}
		break;
	case MOVE:
		// A*
		if (!foundDestination)
		{
			AStar astar(this->getPosition(), destination);
			currentPos = this->getPosition();
			next = astar.find();
			Forward() = (next - currentPos).normalize();
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

		setState(nextState);

		break;
	case MULTIPLY:
	{
		if (group->size() == 1)
		{
			setState(GROUP);
			return;
		}
		int unparasited = 0;
		list<ElfActor*> actors = group->getElements();
		for (list<ElfActor*>::const_iterator it = actors.begin();
			it != actors.end();
			++it)
		{
			if (!(*it)->isParasited())
			{
				++unparasited;
				if (unparasited == 2)
				{
					break;
				}
			}
		}

		if (unparasited != 2)
		{
			return;
		}

		ActorsRepository::get()->createElf(*this);
		eaten = 0;
		setState(EAT);
	} break;
	};
}
void ElfActor::render()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

	glColor3f(1.f, 1.f, 1.f);

	glPushMatrix();
	//glMultMatrixf(m);
	glTranslatef(Position().X * 10 + 5, Position().Y * 10 + 5, Position().Z * 10 + 5);
	glutSolidCube(9);
	glPopMatrix();
}

void ElfActor::setGroup(Group* group)
{
	this->group = group;
}

Group* ElfActor::getGroup()
{
	return group;
}
