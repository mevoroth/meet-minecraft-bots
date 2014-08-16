#include "ReproducingCondition.hpp"

#include "actors\ActorsRepository.hpp"

using namespace DatNS;

bool ReproducingCondition::_execute_condition(Actor& actor, float elapsedTime) const
{
	if (dynamic_cast<GroupElement&>(actor).getGroup()->one())
	{
		return false;
	}
	if (!dynamic_cast<Parasited&>(actor).isParasited())
	{
		return false;
	}
	list<GroupElement*> elements = dynamic_cast<GroupElement&>(actor).getGroup()->getElements();
	for (list<GroupElement*>::iterator it = elements.begin();
		it != elements.end();
		++it)
	{
		if ((Actor&)**it != actor && !dynamic_cast<Parasited*>(*it)->isParasited())
		{
			return true;
		}
	}
	return false;
}
