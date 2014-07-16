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
		Behavior* behavior;
		Behavior* behaviorSub;

		_parasiteAI = new BehaviorTree();
		
		ParasiteSelector* parasiteSel = new ParasiteSelector();

		behavior = new ParasitingBehavior();
		behavior->addSubBehavior(new ParasitingCondition());
		behavior->addSubBehavior(new Parasiting());
		behavior->addSubBehavior(new Multiply());
		parasiteSel->addBehavior(behavior);

		behavior = new HuntBehavior();

		behaviorSub = new Find();
		behavior->addSubBehavior(behaviorSub);

		behaviorSub = new MoveRandomly();
		behaviorSub->addSubBehavior(new FindRandomDirection());
		behaviorSub->addSubBehavior(new Teleport());
		behavior->addSubBehavior(behaviorSub);

		parasiteSel->addBehavior(behavior);

		_parasiteAI->setSelector(parasiteSel);
	}
	return _parasiteAI;
}
