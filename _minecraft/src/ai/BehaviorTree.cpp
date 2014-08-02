#include "BehaviorTree.hpp"

using namespace DatNS;

void BehaviorTree::setSelector(Selector* sel)
{
	_selector = sel;
}
void BehaviorTree::currentBehavior(Actor& actor) const
{
	_selector->behave(actor);
}
