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
