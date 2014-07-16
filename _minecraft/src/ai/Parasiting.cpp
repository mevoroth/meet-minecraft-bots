#include "Parasiting.hpp"

#include "ai\Parasite.hpp"

using namespace DatNS;


Behavior::ReturnCode Parasiting::update(Actor& actor)
{
	uint64_t elapsed = reinterpret_cast<Parasite&>(actor).parasiting();
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

void Parasiting::onFinished(Actor& actor) {}
void Parasiting::onStarted(Actor& actor) {}
void Parasiting::onDoing(Actor& actor) {}
void Parasiting::onAbort(Actor& actor) {}
void Parasiting::onInvalid(Actor& actor) {}
