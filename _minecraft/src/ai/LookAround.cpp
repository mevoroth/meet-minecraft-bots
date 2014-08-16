#include "LookAround.hpp"

#include "Settings.hpp"

#include "LookAroundState.hpp"

using namespace DatNS;

Behavior::ReturnCode LookAround::update(Actor& actor, float elapsedTime) const
{
	float t = dynamic_cast<LookAroundState&>(actor).getElapsedTime();

	if (t <= LOOK_AROUND_TIMER)
	{
		dynamic_cast<LookAroundState&>(actor).updateLookAround();
		dynamic_cast<LookAroundState&>(actor).setElapsedTime(t + LOOK_AROUND_TIMER);
		onDoing(actor);
		return DOING;
	}

	onFinished(actor);
	return FINISHED;
}
