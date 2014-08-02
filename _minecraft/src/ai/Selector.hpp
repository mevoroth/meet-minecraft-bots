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
		const vector<Behavior*>& getBehaviors() const { return _behaviors; };

		virtual void addBehavior(Behavior* behavior) { _behaviors.push_back(behavior); };
		virtual void behave(Actor& actor) const = 0;
	};
};

#endif
