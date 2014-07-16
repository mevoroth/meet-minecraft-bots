#ifndef _MULTIPLY_HPP_
#define _MULTIPLY_HPP_

#include "Behavior.hpp"

namespace DatNS
{
	class Multiply : public Behavior
	{
	public:
		virtual ReturnCode update(Actor& actor) = 0;

		virtual void onFinished(Actor& actor) = 0;
		virtual void onStarted(Actor& actor) = 0;
		virtual void onDoing(Actor& actor) = 0;
		virtual void onAbort(Actor& actor) = 0;
		virtual void onInvalid(Actor& actor) = 0;
	};
};

#endif
