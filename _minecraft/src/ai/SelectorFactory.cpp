#include "SelectorFactory.hpp"

#include "ElfSelector.hpp"
#include "ZergSelector.hpp"
#include "ParasitingCondition.hpp"
#include "SequenceBehavior.hpp"
#include "Parasiting.hpp"
#include "Multiply.hpp"
#include "Teleport.hpp"
#include "Find.hpp"
#include "FindRandomDirection.hpp"
#include "Group.hpp"
#include "Move.hpp"
#include "Separate.hpp"
#include "Eat.hpp"
#include "LookAround.hpp"
#include "FindBush.hpp"
#include "SeparatingCondition.hpp"
#include "GroupingCondition.hpp"
#include "ReproducingCondition.hpp"

using namespace DatNS;

Selector* SelectorFactory::getElfSelector()
{
	Selector* sel = new ElfSelector();
	Behavior* behavior;
	Behavior* behaviorSub;

	behavior = new SequenceBehavior("Separating");
	dynamic_cast<SequenceBehavior*>(behavior)->addSubBehavior(new SeparatingCondition());
	dynamic_cast<SequenceBehavior*>(behavior)->addSubBehavior(new Separate());
	sel->addBehavior(behavior);

	behavior = new SequenceBehavior("Grouping");
	dynamic_cast<SequenceBehavior*>(behavior)->addSubBehavior(new GroupingCondition());
	dynamic_cast<SequenceBehavior*>(behavior)->addSubBehavior(new Group());
	sel->addBehavior(behavior);

	behavior = new SequenceBehavior("Reproducing");
	dynamic_cast<SequenceBehavior*>(behavior)->addSubBehavior(new LookAround());
	dynamic_cast<SequenceBehavior*>(behavior)->addSubBehavior(new ReproducingCondition());
	dynamic_cast<SequenceBehavior*>(behavior)->addSubBehavior(new Multiply());
	sel->addBehavior(behavior);

	behavior = new Eat();
	sel->addBehavior(behavior);

	behavior = new SequenceBehavior("MoveToBush");
	dynamic_cast<SequenceBehavior*>(behavior)->addSubBehavior(new LookAround());
	dynamic_cast<SequenceBehavior*>(behavior)->addSubBehavior(new FindBush());
	dynamic_cast<SequenceBehavior*>(behavior)->addSubBehavior(new Move());
	sel->addBehavior(behavior);

	return sel;
}

Selector* SelectorFactory::getZergSelector()
{
	Selector* sel = new ZergSelector();
	Behavior* behavior;
	Behavior* behaviorSub;
	//sel->addBehavior()

	/* BEGIN Parasiting Behavior */
	behavior = new SequenceBehavior("Parasiting");
	dynamic_cast<SequenceBehavior*>(behavior)->addSubBehavior(new ParasitingCondition());
	dynamic_cast<SequenceBehavior*>(behavior)->addSubBehavior(new Parasiting());
	dynamic_cast<SequenceBehavior*>(behavior)->addSubBehavior(new Multiply());
	sel->addBehavior(behavior);
	/* END Parasiting Behavior */

	/* BEGIN Hunt Behavior */
	behavior = new SequenceBehavior("Hunt");

	/* BEGIN Find SubBehavior */
	behaviorSub = new Find();
	dynamic_cast<SequenceBehavior*>(behavior)->addSubBehavior(behaviorSub);
	/* END Find SubBehavior */

	/* BEGIN Move Randomly */
	behaviorSub = new SequenceBehavior("MoveRandom");
	dynamic_cast<SequenceBehavior*>(behaviorSub)->addSubBehavior(new FindRandomDirection());
	dynamic_cast<SequenceBehavior*>(behaviorSub)->addSubBehavior(new Teleport());
	dynamic_cast<SequenceBehavior*>(behavior)->addSubBehavior(behaviorSub);
	/* END Move Randomly */

	sel->addBehavior(behavior);
	/* END Hunt Behavior */

	return sel;
}

Selector* SelectorFactory::getHunterSelector()
{
	/*Selector* sel = new HunterSelector();
	return sel;*/
	return 0;
}
