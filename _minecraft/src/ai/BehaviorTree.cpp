#include "BehaviorTree.hpp"

using namespace DatNS;

void BehaviorTree::setSelector(Selector* sel)
{
	_selector = sel;
}
const Behavior* BehaviorTree::currentBehavior(const Actor& actor)
{
	return _selector->getBehavior();
}
