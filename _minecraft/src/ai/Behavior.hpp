#ifndef _BEHAVIOR_HPP_
#define _BEHAVIOR_HPP_

#include "actors\Actor.hpp"

namespace DatNS
{
	class Behavior
	{
	public:
		enum ReturnCode
		{
			DOING,
			FINISHED,
			ABORT,
			INVALID
		};
		/**
		 * Tick
		 * @param[inout] Actor
		 * @return Return code of action
		 */
		virtual ReturnCode update(Actor& actor) = 0;

		/**
		 * On Finished event
		 * @param[inout] Actor
		 */
		virtual void onFinished(Actor& actor) = 0;
		/**
		* On Started event
		* @param[inout] Actor
		*/
		virtual void onStarted(Actor& actor) = 0;
		/**
		* On Doing event
		* @param[inout] Actor
		*/
		virtual void onDoing(Actor& actor) = 0;
		/**
		* On Abort event
		* @param[inout] Actor
		*/
		virtual void onAbort(Actor& actor) = 0;
		/**
		* On Invalid event
		* @param[inout] Actor
		*/
		virtual void onInvalid(Actor& actor) = 0;
	};
}

#endif
