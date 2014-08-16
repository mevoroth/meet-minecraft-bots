#include "Condition.hpp"

using namespace DatNS;

Behavior::ReturnCode Condition::update(Actor& actor, float elapsedTime) const
{
	bool ret = _execute_condition(actor, elapsedTime);
	if (ret)
	{
		onFinished(actor);
		return Behavior::FINISHED;
	}
	onAbort(actor);
	return Behavior::ABORT;
}
