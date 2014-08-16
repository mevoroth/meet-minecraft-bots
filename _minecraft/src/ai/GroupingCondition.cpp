#include "GroupingCondition.hpp"

#include "GroupElement.hpp"

using namespace DatNS;

bool GroupingCondition::_execute_condition(Actor& actor, float elapsedTime) const
{
	return dynamic_cast<GroupElement&>(actor).getGroup()->one();
}
