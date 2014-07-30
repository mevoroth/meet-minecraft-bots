#ifndef _PARASITING_H_
#define _PARASITING_H_

#include "Behavior.hpp"

namespace DatNS
{
	class Parasiting : public Behavior
	{
	public:
		enum { MULTIPLY = 10 };
		virtual ReturnCode update(Actor& actor) const;

		virtual void onFinished(Actor& actor) const {};
		virtual void onStarted(Actor& actor) const {};
		virtual void onDoing(Actor& actor) const {};
		virtual void onAbort(Actor& actor) const {};
		virtual void onInvalid(Actor& actor) const {};
	};
};

#endif
