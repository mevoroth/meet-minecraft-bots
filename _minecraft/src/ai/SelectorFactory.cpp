#include "SelectorFactory.hpp"

#include "ElfSelector.hpp"
#include "ZergSelector.hpp"
#include "ParasitingCondition.hpp"
#include "SequenceBehavior.hpp"
#include "Parasiting.hpp"
#include "Multiply.hpp"
#include "Teleport.hpp"
#include "Find.hpp"

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
	Behavior* behavior;
	Behavior* behaviorSub;
	//sel->addBehavior()

	/* BEGIN Parasiting Behavior */
	behavior = new SequenceBehavior();
	dynamic_cast<SequenceBehavior*>(behavior)->addSubBehavior(new ParasitingCondition());
	dynamic_cast<SequenceBehavior*>(behavior)->addSubBehavior(new Parasiting());
	dynamic_cast<SequenceBehavior*>(behavior)->addSubBehavior(new Multiply());
	sel->addBehavior(behavior);
	/* END Parasiting Behavior */

	/* BEGIN Hunt Behavior */
	behavior = new SequenceBehavior();

	/* BEGIN Find SubBehavior */
	behaviorSub = new Find();
	dynamic_cast<SequenceBehavior*>(behavior)->addSubBehavior(behaviorSub);
	/* END Find SubBehavior */

	/* BEGIN Move Randomly */
	behaviorSub = new SequenceBehavior();
	dynamic_cast<SequenceBehavior*>(behaviorSub)->addSubBehavior(new FindRandomDirection());
	dynamic_cast<SequenceBehavior*>(behaviorSub)->addSubBehavior(new Teleport());
	dynamic_cast<SequenceBehavior*>(behavior)->addSubBehavior(behaviorSub);
	/* END Move Randomly */

	sel->addBehavior(behavior);
	/* END Hunt Behavior */

	return sel;
}
