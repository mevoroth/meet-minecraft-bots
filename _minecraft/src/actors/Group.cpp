#include "Group.hpp"

using namespace DatNS;

NYVert3Df Group::getPosition()
{
	NYVert3Df p;
	for (list<Actor*>::iterator it = elements.begin();
		it != elements.end();
		++it)
	{
		p += (*it)->getPosition();
	}
	return p / elements.size();
}

void Group::remove(Actor* actor)
{
	elements.remove(actor);
}
