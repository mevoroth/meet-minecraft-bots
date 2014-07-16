#ifndef _PARASITING_H_
#define _PARASITING_H_

#include "Behavior.hpp"

namespace DatNS
{
	class Parasiting : public Behavior
	{
	public:
		enum { MULTIPLY = 10 };
		virtual ReturnCode update(Actor& actor);

		virtual void onFinished(Actor& actor);
		virtual void onStarted(Actor& actor);
		virtual void onDoing(Actor& actor);
		virtual void onAbort(Actor& actor);
		virtual void onInvalid(Actor& actor);
	};
};

#endif
