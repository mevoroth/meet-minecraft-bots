#ifndef _CONDITION_HPP_
#define _CONDITION_HPP_

#include "Behavior.hpp"

namespace DatNS
{
	/**
	 * Condition in behavior tree
	 */
	class Condition : public Behavior
	{
	protected:
		/**
		 * Override this to create condition for behavior
		 */
		virtual bool _execute_condition(Actor& actor, float elapsedTime) const = 0;
	public:
		/**
		 * Tick
		 * @param[inout] Actor
		 * @return Return code of action
		 */
		virtual ReturnCode update(Actor& actor, float elapsedTime) const;

		virtual void onFinished(Actor& actor) const = 0;
		virtual void onStarted(Actor& actor) const = 0;
		virtual void onDoing(Actor& actor) const = 0;
		virtual void onAbort(Actor& actor) const = 0;
		virtual void onInvalid(Actor& actor) const = 0;
	};
};

#endif
