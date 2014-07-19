#include "types_extended.hpp"

NYVert3Df eulerToDirection(const NYVert3Df& euler)
{
	return NYVert3Df(
		cosf(euler.Z)*cosf(euler.X),
		sinf(euler.Z)*cosf(euler.X),
		sinf(euler.X)
	);
}
