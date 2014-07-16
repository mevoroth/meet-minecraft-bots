#ifndef _CONDITION_HPP_
#define _CONDITION_HPP_

#include "Behavior.hpp"

namespace DatNS
{
	class Condition : public Behavior
	{
	protected:
		virtual bool _execute_condition(Actor& actor) = 0;
	public:
		/**
		 * Tick
		 * @param[inout] Actor
		 * @return Return code of action
		 */
		virtual ReturnCode update(Actor& actor);

		virtual void onFinished(Actor& actor) = 0;
		virtual void onStarted(Actor& actor) = 0;
		virtual void onDoing(Actor& actor) = 0;
		virtual void onAbort(Actor& actor) = 0;
		virtual void onInvalid(Actor& actor) = 0;
	};
};

#endif
