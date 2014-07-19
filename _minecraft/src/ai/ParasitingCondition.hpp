#ifndef _PARASITING_CONDITION_HPP_
#define _PARASITING_CONDITION_HPP_

#include "Condition.hpp"

namespace DatNS
{
	class ParasitingCondition : public Condition
	{
	protected:
		virtual bool _execute_condition(Actor& actor);
	public:
		static const double FOV;

		virtual void onFinished(Actor& actor) {};
		virtual void onStarted(Actor& actor) {};
		virtual void onDoing(Actor& actor) {};
		virtual void onAbort(Actor& actor) {};
		virtual void onInvalid(Actor& actor) {};
	};
}

#endif
