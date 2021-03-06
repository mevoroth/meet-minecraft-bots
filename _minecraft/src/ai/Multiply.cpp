#include "Multiply.hpp"

#include "Multiplyable.hpp"

using namespace DatNS;

Behavior::ReturnCode Multiply::update(Actor& actor, float elapsedTime) const
{
	dynamic_cast<Multiplyable&>(actor).multiply();
	onFinished(actor);
	return Behavior::FINISHED;
}
