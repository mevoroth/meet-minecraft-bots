#include "ParasitingCondition.hpp"

#include "actors\ActorsRepository.hpp"

using namespace DatNS;

const double ParasitingCondition::FOV = 0.8f;

bool ParasitingCondition::_execute_condition(Actor& actor)
{
	// Use Octree for optimization
	list<ElfActor*> elves = ActorsRepository::get()->getElves();
	for (list<ElfActor*>::const_iterator it = elves.cbegin();
		it != elves.cend();
		++it)
	{
		NYVert3Df fw = (*it)->getForward();
		float dot = fw.scalProd(((*it)->Position() - actor.Position()).normalize());
		if (dot > 0.8f)
		{
			return true;
		}
	}
	return false;
}
