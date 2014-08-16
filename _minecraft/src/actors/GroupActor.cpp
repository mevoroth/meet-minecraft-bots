#include "GroupActor.hpp"

using namespace DatNS;

bool GroupActor::add(GroupElement* actor)
{
	if (full())
	{
		return false;
	}
	_actors.push_back(actor);
	return true;
}

bool GroupActor::remove(GroupElement* actor)
{
	if (one())
	{
		return false;
	}
	_actors.remove(actor);
	return true;
}

inline bool GroupActor::full() const
{
	return _actors.size() >= MAX;
}

inline bool GroupActor::one() const
{
	return _actors.size() <= MIN;
}

NYVert3Df GroupActor::getPosition()
{
	NYVert3Df distance;
	for (list<GroupElement*>::const_iterator it = _actors.begin();
		it != _actors.end();
		++it)
	{
		distance += (*it)->getPosition();
	}
	return distance / _actors.size();
}
