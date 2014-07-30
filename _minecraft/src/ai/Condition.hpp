#ifndef _CONDITION_HPP_
#define _CONDITION_HPP_

#include "Behavior.hpp"

namespace DatNS
{
	class Condition : public Behavior
	{
	protected:
		virtual bool _execute_condition(Actor& actor) const = 0;
	public:
		/**
		 * Tick
		 * @param[inout] Actor
		 * @return Return code of action
		 */
		virtual ReturnCode update(Actor& actor) const;

		virtual void onFinished(Actor& actor) const = 0;
		virtual void onStarted(Actor& actor) const = 0;
		virtual void onDoing(Actor& actor) const = 0;
		virtual void onAbort(Actor& actor) const = 0;
		virtual void onInvalid(Actor& actor) const = 0;
	};
};

#endif
