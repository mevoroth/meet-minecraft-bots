#ifndef _TELEPORT_HPP_
#define _TELEPORT_HPP_

#include "Behavior.hpp"

namespace DatNS
{
	class Teleport : public Behavior
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
