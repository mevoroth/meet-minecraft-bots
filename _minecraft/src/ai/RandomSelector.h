#ifndef _RANDOM_SELECTOR_H_
#define _RANDOM_SELECTOR_H_

#include "Selector.h"

namespace DatNS
{
	class RandomSelector : public Selector
	{
	public:
		RandomSelector();
		virtual const Behavior* getBehavior() const;
		virtual void addBehavior(Behavior* behavior);
	};
};

#endif
