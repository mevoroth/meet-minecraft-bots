#include "Actor.hpp"

#include <cmath>
#include "utils\types_extended.hpp"

using namespace DatNS;

Actor::Actor(const NYVert3Df& pos, const NYVert3Df& speed, const NYVert3Df& fw)
	: _pos(pos)
	, _speed(speed)
	, _fw(fw)
{
}
