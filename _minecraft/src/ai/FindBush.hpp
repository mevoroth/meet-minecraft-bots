#ifndef _FIND_BUSH_HPP_
#define _FIND_BUSH_HPP_

#include "Behavior.hpp"

namespace DatNS
{
	class FindBush : public Behavior
	{
	public:
		virtual ReturnCode update(Actor& actor) const;

		virtual void onFinished(Actor& actor) const {};
		virtual void onStarted(Actor& actor) const {};
		virtual void onDoing(Actor& actor) const {};
		virtual void onAbort(Actor& actor) const {};
		virtual void onInvalid(Actor& actor) const {};
	};
}

#endif
