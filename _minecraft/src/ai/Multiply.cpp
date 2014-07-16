#include "Multiply.hpp"

#include "Multiplyable.hpp"

using namespace DatNS;

Behavior::ReturnCode Multiply::update(Actor& actor)
{
	reinterpret_cast<Multiplyable&>(actor).multiply();
	onFinished(actor);
	return Behavior::FINISHED;
}

void Multiply::onFinished(Actor& actor) {}
void Multiply::onStarted(Actor& actor) {}
void Multiply::onDoing(Actor& actor) {}
void Multiply::onAbort(Actor& actor) {}
void Multiply::onInvalid(Actor& actor) {}
