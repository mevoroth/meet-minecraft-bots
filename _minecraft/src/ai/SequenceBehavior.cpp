#include "SequenceBehavior.hpp"

#include "SequenceStore.hpp"

using namespace DatNS;

/**
* Add Sub behavior
*/
void SequenceBehavior::addSubBehavior(Behavior* behavior)
{
	_sequence.push_back(behavior);
}
/**
* Tick
* @param[inout] Actor
* @return Return code of action
*/
Behavior::ReturnCode SequenceBehavior::update(Actor& actor) const
{
	int state = reinterpret_cast<SequenceStore&>(actor).retrieveState();
	Behavior::ReturnCode ret = _sequence[state]->update(actor);
	switch (ret)
	{
	case DOING:
		onDoing(actor);
		break;
	case FINISHED:
		onFinished(actor);
		++state;
		if (state < _sequence.size())
		{
			reinterpret_cast<SequenceStore&>(actor).storeSequenceState(state);
			return DOING;
		}
		break;
	case ABORT:
		onAbort(actor);
		break;
	//case INVALID:
	default:
		onInvalid(actor);
		break;
	}
	return ret;
}
