#include "SequenceBehavior.hpp"

#include "SequenceStore.hpp"

using namespace DatNS;

SequenceBehavior::SequenceBehavior(const std::string& tag)
	: _tag(tag)
{
}

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
Behavior::ReturnCode SequenceBehavior::update(Actor& actor, float elapsedTime) const
{
	int state = dynamic_cast<SequenceStore&>(actor).retrieveState(_tag);
	Behavior::ReturnCode ret = _sequence[state]->update(actor, elapsedTime);
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
			dynamic_cast<SequenceStore&>(actor).storeSequenceState(_tag, state);
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
