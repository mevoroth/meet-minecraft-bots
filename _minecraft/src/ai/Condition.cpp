#include "Condition.hpp"

using namespace DatNS;

Behavior::ReturnCode Condition::update(Actor& actor) const
{
	bool ret = _execute_condition(actor);
	if (ret)
	{
		onFinished(actor);
		return Behavior::FINISHED;
	}
	onAbort(actor);
	return Behavior::ABORT;
}
