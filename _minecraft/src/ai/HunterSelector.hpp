#ifndef _HUNTER_SELECTOR_HPP_
#define _HUNTER_SELECTOR_HPP_

#include "Selector.hpp"

namespace DatNS
{
	class HunterSelector : public Selector
	{
	public:
		virtual void behave(Actor& actor, float elapsedTime) const;
	};
}

#endif
