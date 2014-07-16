#ifndef _ELF_SELECTOR_HPP_
#define _ELF_SELECTOR_HPP_

#include "Selector.hpp"

namespace DatNS
{
	class ElfSelector : public Selector
	{
	public:
		virtual const Behavior* getBehavior() const;
	};
};

#endif
