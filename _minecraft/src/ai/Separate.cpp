#include "Separate.hpp"

#include "actors\ActorsRepository.hpp"

using namespace DatNS;

Behavior::ReturnCode Separate::update(Actor& actor, float elapsedTime) const
{
	GroupActor* gactor = new GroupActor();
	dynamic_cast<GroupElement&>(actor).setGroup(gactor);
	gactor->add(dynamic_cast<GroupElement*>(&actor));
	ActorsRepository::get()->getGroups().push_back(gactor);
	onFinished(actor);
	return FINISHED;
}
