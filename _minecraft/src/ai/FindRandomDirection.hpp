#ifndef _FIND_RANDOM_DIRECTION_HPP_
#define _FIND_RANDOM_DIRECTION_HPP_

#include "Behavior.hpp"

namespace DatNS
{
	class FindRandomDirection : public Behavior
	{
	public:
		virtual ReturnCode update(Actor& actor);

		virtual void onFinished(Actor& actor) {};
		virtual void onStarted(Actor& actor) {};
		virtual void onDoing(Actor& actor) {};
		virtual void onAbort(Actor& actor) {};
		virtual void onInvalid(Actor& actor) {};
	};
}

#endif
