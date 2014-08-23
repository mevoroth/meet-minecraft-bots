#include "Group.hpp"

#include "ElfActor.hpp"

using namespace DatNS;

NYVert3Df Group::getPosition()
{
	NYVert3Df p;
	for (list<ElfActor*>::iterator it = elements.begin();
		it != elements.end();
		++it)
	{
		p += (*it)->getPosition();
	}
	return p / elements.size();
}

void Group::remove(ElfActor* actor)
{
	elements.remove(actor);
}

void Group::add(ElfActor* actor)
{
	assert(elements.size() < GROUP_SIZE);
	elements.push_back(actor);
};
