#include "Actor.hpp"

#include <cmath>
#include "utils\types_extended.hpp"

using namespace DatNS;

Actor::Actor(const NYVert3Df& pos, const NYVert3Df& speed, const NYVert3Df& rotation)
	: _pos(pos)
	, _speed(speed)
	, _rotation(rotation)
{
}

const NYVert3Df& Actor::getForward() const
{
	return eulerToDirection(_rotation);
}
void Actor::setForward(const NYVert3Df& fw)
{
	float rotX = atan2f(fw.Y, fw.Z);
	float rotY = atan2f(fw.X * cosf(rotX), fw.Z);
	float rotZ = atan2f(cosf(rotX), sinf(rotX) * sinf(rotY));
	_rotation = NYVert3Df(
		rotX,
		rotY,
		rotZ
	);
}
