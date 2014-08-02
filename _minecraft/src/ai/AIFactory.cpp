#include "AIFactory.hpp"

#include "SelectorFactory.hpp"

using namespace DatNS;

AIFactory* AIFactory::_inst = 0;

AIFactory::AIFactory()
	: _zergAI(0)
{
}
AIFactory::~AIFactory()
{
	delete _zergAI;
}

AIFactory* AIFactory::get()
{
	if (!_inst)
	{
		_inst = new AIFactory();
	}
	return _inst;
}
const BehaviorTree* AIFactory::createZergAI()
{
	if (!_zergAI)
	{
		_zergAI = new BehaviorTree();
		_zergAI->setSelector(SelectorFactory::getZergSelector());
	}
	return _zergAI;
}
