#ifndef _SEQUENCE_BEHAVIOR_HPP_
#define _SEQUENCE_BEHAVIOR_HPP_

#include "Behavior.hpp"

namespace DatNS
{
	class SequenceBehavior : public Behavior
	{
	public:
		/**
		 * Add Sub behavior
		 */
		virtual void addSubBehavior(Behavior* behavior);
		/**
		* Tick
		* @param[inout] Actor
		* @return Return code of action
		*/
		virtual ReturnCode update(Actor& actor);

		/**
		* On Finished event
		* @param[inout] Actor
		*/
		virtual void onFinished(Actor& actor);
		/**
		* On Started event
		* @param[inout] Actor
		*/
		virtual void onStarted(Actor& actor);
		/**
		* On Doing event
		* @param[inout] Actor
		*/
		virtual void onDoing(Actor& actor);
		/**
		* On Abort event
		* @param[inout] Actor
		*/
		virtual void onAbort(Actor& actor);
		/**
		* On Invalid event
		* @param[inout] Actor
		*/
		virtual void onInvalid(Actor& actor);
	};
}

#endif
