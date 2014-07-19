#include "AIFactory.hpp"

#include "SelectorFactory.hpp"

using namespace DatNS;

AIFactory* AIFactory::_inst = 0;

AIFactory::AIFactory()
{
}

AIFactory* AIFactory::get()
{

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
