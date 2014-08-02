#include "Parasiting.hpp"

#include "ai\Parasite.hpp"

using namespace DatNS;


Behavior::ReturnCode Parasiting::update(Actor& actor) const
{
	uint64_t elapsed = dynamic_cast<Parasite&>(actor).parasiting();
	if (elapsed > MULTIPLY)
	{
		onFinished(actor);
		return Behavior::FINISHED;
	}
	else if (elapsed > 0)
	{
		onDoing(actor);
		return Behavior::DOING;
	}
	else
	{
		onAbort(actor);
		return Behavior::ABORT;
	}
}
