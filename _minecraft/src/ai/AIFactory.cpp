#include "AIFactory.hpp"

#include "ParasiteSelector.hpp"

using namespace DatNS;

AIFactory* AIFactory::_inst = 0;

AIFactory::AIFactory()
{
}

AIFactory* AIFactory::get()
{

}
const BehaviorTree* AIFactory::createParasiteAI()
{
	if (!_parasiteAI)
	{
		_parasiteAI = new BehaviorTree();
		
		ParasiteSelector* parasiteSel = new ParasiteSelector();
		
		_parasiteAI->setSelector(parasiteSel);
	}
	return _parasiteAI;
}
