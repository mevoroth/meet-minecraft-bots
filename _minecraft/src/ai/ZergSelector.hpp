#ifndef _ZERG_SELECTOR_HPP_
#define _ZERG_SELECTOR_HPP_

#include "Selector.hpp"

namespace DatNS
{
	class ZergSelector : public Selector
	{
	public:
		virtual const Behavior* getBehavior() const;
	};
};

#endif
