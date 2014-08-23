#ifndef _SELECTOR_HPP_
#define _SELECTOR_HPP_

#include <vector>

#include "Behavior.hpp"

using namespace std;

namespace DatNS
{
	class Selector
	{
	private:
		vector<Behavior*> _behaviors;
	public:
		/**
		 * get behaviors stored
		 */
		const vector<Behavior*>& getBehaviors() const { return _behaviors; };
		/**
		 * Add behavior to selector
		 * @param[in] behavior
		 */
		virtual void addBehavior(Behavior* behavior) { _behaviors.push_back(behavior); };
		/**
		 * Override this function to create behavior selector and execute it
		 * @param[inout] Actor
		 * @param[in] Elapsed Time
		 */
		virtual void behave(Actor& actor, float elapsedTime) const = 0;
	};
};

#endif
