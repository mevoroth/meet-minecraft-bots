#include "ElfSelector.hpp"

#include "CurrentBehavior.hpp"

using namespace DatNS;

void ElfSelector::behave(Actor& actor, float elapsedTime) const
{

	//Selector* sel = new ElfSelector();
	//Behavior* behavior;
	//Behavior* behaviorSub;

	//behavior = new SequenceBehavior("Separating");
	//dynamic_cast<SequenceBehavior*>(behavior)->addSubBehavior(new SeparatingCondition());
	//dynamic_cast<SequenceBehavior*>(behavior)->addSubBehavior(new Separate());
	//sel->addBehavior(behavior);

	//behavior = new SequenceBehavior("Grouping");
	//dynamic_cast<SequenceBehavior*>(behavior)->addSubBehavior(new GroupingCondition());
	//dynamic_cast<SequenceBehavior*>(behavior)->addSubBehavior(new Group());
	//sel->addBehavior(behavior);

	//behavior = new SequenceBehavior("Reproducing");
	//dynamic_cast<SequenceBehavior*>(behavior)->addSubBehavior(new LookAround());
	//dynamic_cast<SequenceBehavior*>(behavior)->addSubBehavior(new ReproducingCondition());
	//dynamic_cast<SequenceBehavior*>(behavior)->addSubBehavior(new Multiply());
	//sel->addBehavior(behavior);

	//behavior = new Eat();
	//sel->addBehavior(behavior);

	//behavior = new SequenceBehavior("MoveToBush");
	//dynamic_cast<SequenceBehavior*>(behavior)->addSubBehavior(new LookAround());
	//dynamic_cast<SequenceBehavior*>(behavior)->addSubBehavior(new FindBush());
	//dynamic_cast<SequenceBehavior*>(behavior)->addSubBehavior(new Move());
	//sel->addBehavior(behavior);

	//return sel;

	int current = dynamic_cast<CurrentBehavior<int>&>(actor).getBehavior();
	Behavior::ReturnCode ret = getBehaviors()[current]->update(actor, elapsedTime);
	switch (ret)
	{
	case Behavior::ABORT:
	case Behavior::FINISHED:
		dynamic_cast<CurrentBehavior<int>&>(actor).setBehavior((current + 1) % getBehaviors().size());
		break;
	}
}
