#ifndef _SELECTOR_FACTORY_HPP_
#define _SELECTOR_FACTORY_HPP_

#include "Selector.hpp"

namespace DatNS
{
	class SelectorFactory
	{
	private:
		SelectorFactory() {}
	public:
		static Selector* getElfSelector();
		static Selector* getZergSelector();
		static Selector* getHunterSelector();
	};
};

#endif
