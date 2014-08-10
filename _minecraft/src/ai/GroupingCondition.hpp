#ifndef _GROUPING_CONDITION_HPP_
#define _GROUPING_CONDITION_HPP_

#include "Condition.hpp"

namespace DatNS
{
	class GroupingCondition : public Condition
	{
	protected:
		virtual bool _execute_condition(Actor& actor) const;
	public:
		virtual void onFinished(Actor& actor) const {};
		virtual void onStarted(Actor& actor) const {};
		virtual void onDoing(Actor& actor) const {};
		virtual void onAbort(Actor& actor) const {};
		virtual void onInvalid(Actor& actor) const {};
	};
}

#endif
