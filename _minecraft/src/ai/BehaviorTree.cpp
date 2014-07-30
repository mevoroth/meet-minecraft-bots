#include "BehaviorTree.hpp"

using namespace DatNS;

void BehaviorTree::setSelector(Selector* sel)
{
	_selector = sel;
}
const Behavior* BehaviorTree::currentBehavior(const Actor& actor) const
{
	printf("currentBehavior\n");
	return _selector->getBehavior();
}
