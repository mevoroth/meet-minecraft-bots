#ifndef _PARASITE_SELECTOR_HPP_
#define _PARASITE_SELECTOR_HPP_

#include "Selector.hpp"

namespace DatNS
{
	class ParasiteSelector : public Selector
	{
	public:
		virtual const Behavior* getBehavior() const;
	};
};

#endif
