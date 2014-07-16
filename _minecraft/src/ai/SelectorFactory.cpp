#include "SelectorFactory.hpp"

#include "ElfSelector.hpp"
#include "ZergSelector.hpp"

using namespace DatNS;

Selector* SelectorFactory::getElfSelector()
{
	Selector* sel = new ElfSelector();
	//sel->addBehavior();
	return sel;
}

Selector* SelectorFactory::getZergSelector()
{
	Selector* sel = new ZergSelector();
	//sel->addBehavior()
	return sel;
}
