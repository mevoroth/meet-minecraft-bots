#include "Eat.hpp"

#include "Eater.hpp"

using namespace DatNS;

Behavior::ReturnCode Eat::update(Actor& actor, float elapsedTime) const
{
	dynamic_cast<Eater&>(actor).eat();
	onFinished(actor);
	return FINISHED;
}
