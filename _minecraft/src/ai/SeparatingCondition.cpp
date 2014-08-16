#include "SeparatingCondition.hpp"

#include "GroupElement.hpp"

using namespace DatNS;

bool SeparatingCondition::_execute_condition(Actor& actor, float elapsedTime) const
{
	return dynamic_cast<GroupElement&>(actor).getGroup()->full();
}
