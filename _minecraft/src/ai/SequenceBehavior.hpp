#ifndef _SEQUENCE_BEHAVIOR_HPP_
#define _SEQUENCE_BEHAVIOR_HPP_

#include "Behavior.hpp"

namespace DatNS
{
	class SequenceBehavior : public Behavior
	{
	private:
		vector<Behavior*> _sequence;
		std::string _tag;
	public:
		SequenceBehavior(const std::string& tag);
		/**
		 * Add Sub behavior
		 */
		virtual void addSubBehavior(Behavior* behavior);
		/**
		* Tick
		* @param[inout] Actor
		* @return Return code of action
		*/
		virtual ReturnCode update(Actor& actor, float elapsedTime) const;

		/**
		* On Finished event
		* @param[inout] Actor
		*/
		virtual void onFinished(Actor& actor) const {};
		/**
		* On Started event
		* @param[inout] Actor
		*/
		virtual void onStarted(Actor& actor) const {};
		/**
		* On Doing event
		* @param[inout] Actor
		*/
		virtual void onDoing(Actor& actor) const {};
		/**
		* On Abort event
		* @param[inout] Actor
		*/
		virtual void onAbort(Actor& actor) const {};
		/**
		* On Invalid event
		* @param[inout] Actor
		*/
		virtual void onInvalid(Actor& actor) const {};
	};
}

#endif
