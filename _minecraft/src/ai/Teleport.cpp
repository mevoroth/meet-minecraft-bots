#include "Teleport.hpp"

#include "NewPosition.hpp"

using namespace DatNS;

Behavior::ReturnCode Teleport::update(Actor& actor, float elapsedTime) const
{
	actor.Position() = dynamic_cast<NewPosition&>(actor).getNewPosition();
	return FINISHED;
}
