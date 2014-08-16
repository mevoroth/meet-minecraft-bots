#include "Parasiting.hpp"

#include "Settings.hpp"

#include "ai\Parasite.hpp"

using namespace DatNS;


Behavior::ReturnCode Parasiting::update(Actor& actor, float elapsedTime) const
{
	float elapsed = dynamic_cast<Parasite&>(actor).parasiting();
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
