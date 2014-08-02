#include "ZergSelector.hpp"

#include "ai\CurrentBehavior.hpp"

using namespace DatNS;

void ZergSelector::behave(Actor& actor) const
{
	int current = dynamic_cast<CurrentBehavior<int>&>(actor).getBehavior();
	Behavior::ReturnCode ret = getBehaviors()[current]->update(actor);
	switch (ret)
	{
	case Behavior::ABORT:
	case Behavior::FINISHED:
		dynamic_cast<CurrentBehavior<int>&>(actor).setBehavior((current + 1) % getBehaviors().size());
		break;
	}
}
