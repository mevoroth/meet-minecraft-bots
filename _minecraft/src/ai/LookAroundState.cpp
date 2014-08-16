#include "LookAroundState.hpp"

#include "actors\Actor.hpp"

using namespace DatNS;

void LookAroundState::update()
{
	dynamic_cast<Actor&>(*this);
}
