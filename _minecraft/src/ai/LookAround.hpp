#ifndef _LOOK_AROUND_HPP_
#define _LOOK_AROUND_HPP_

#include "Behavior.hpp"

namespace DatNS
{
	class LookAround : public Behavior
	{
	public:
		virtual ReturnCode update(Actor& actor, float elapsedTime) const;

		virtual void onFinished(Actor& actor) const {};
		virtual void onStarted(Actor& actor) const {};
		virtual void onDoing(Actor& actor) const {};
		virtual void onAbort(Actor& actor) const {};
		virtual void onInvalid(Actor& actor) const {};
	};
}

#endif
