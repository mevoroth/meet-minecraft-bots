#include "FindBush.hpp"

#include "actors\ActorsRepository.hpp"
#include "Eater.hpp"

using namespace DatNS;

Behavior::ReturnCode FindBush::update(Actor& actor, float elapsedTime) const
{
	float dist = INFINITY;
	BushActor* eatable = 0;
	list<BushActor*> bushes = ActorsRepository::get()->getBushes();
	for (list<BushActor*>::iterator it = bushes.begin();
		it != bushes.end();
		++it)
	{
		float magn = (actor.getPosition() - (*it)->getPosition()).getMagnitude();
		if (magn < dist)
		{
			dist = magn;
			eatable = *it;
		}
	}
	dynamic_cast<Eater&>(actor).setEatable(eatable);
	onFinished(actor);
	return FINISHED;
}
