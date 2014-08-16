#include "ZergSelector.hpp"

#include "ai\CurrentBehavior.hpp"

using namespace DatNS;

void ZergSelector::behave(Actor& actor, float elapsedTime) const
{
	int current = dynamic_cast<CurrentBehavior<int>&>(actor).getBehavior();
	Behavior::ReturnCode ret = getBehaviors()[current]->update(actor, elapsedTime);
	switch (ret)
	{
	case Behavior::ABORT:
		dynamic_cast<CurrentBehavior<int>&>(actor).setBehavior((current + 1) % getBehaviors().size());
		break;
	case Behavior::FINISHED:
		dynamic_cast<CurrentBehavior<int>&>(actor).setBehavior(current != 0 ? current - 1 : current);
		break;
	}
}
