#include "Move.hpp"

#include "Destination.hpp"

using namespace DatNS;

Behavior::ReturnCode Move::update(Actor& actor, float elapsedTime) const
{
	NYVert3Df dest = dynamic_cast<Destination&>(actor).getDest();
	float ms = dynamic_cast<Destination&>(actor).getMoveSpeed();
	if ((actor.getPosition() - dest).getMagnitude() > 0.001f)
	{
		actor.Position() += (actor.getPosition() - dest).normalize() * ms * elapsedTime;
		onDoing(actor);
		return DOING;
	}
	actor.Position() = dest;

	onFinished(actor);
	return FINISHED;
}
