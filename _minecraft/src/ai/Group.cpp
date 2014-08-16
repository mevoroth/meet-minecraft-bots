#include "Group.hpp"

#include "actors\ActorsRepository.hpp"

using namespace DatNS;
using namespace std;

Behavior::ReturnCode Group::update(Actor& actor, float elapsedTime) const
{
	vector<GroupActor*> groups = ActorsRepository::get()->getGroups();
	GroupActor* gactor = 0;
	double distance = INFINITY;
	for (vector<GroupActor*>::const_iterator it = groups.cbegin();
		it != groups.cend();
		++it)
	{
		NYVert3Df tmpDist = (*it)->getPosition();
		if ((tmpDist - actor.getPosition()).getMagnitude() < distance && !(*it)->full())
		{
			gactor = *it;
			distance = (tmpDist - actor.getPosition()).getMagnitude();
		}
	}
	dynamic_cast<GroupElement&>(actor).setGroup(gactor);
	gactor->add(dynamic_cast<GroupElement*>(&actor));
	onFinished(actor);
	return FINISHED;
}
