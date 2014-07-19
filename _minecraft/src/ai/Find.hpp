#ifndef _FIND_HPP_
#define _FIND_HPP_

#include "Behavior.hpp"

namespace DatNS
{
	class Find : public Behavior
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
