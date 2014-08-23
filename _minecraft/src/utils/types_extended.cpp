#include "types_extended.hpp"


UniqWorld* UniqWorld::instance = 0;
UniqWorld::UniqWorld()
{
	world = new NYWorld();
}
UniqWorld::~UniqWorld()
{
	delete world;
}
UniqWorld* UniqWorld::get()
{
	if (!instance)
	{
		instance = new UniqWorld();
	}
	return instance;
}

NYVert3Df lerp(const NYVert3Df& a, const NYVert3Df& b, float t)
{
	t = clamp<float>(t, 0, 1);
	return (NYVert3Df(a) - b) * t + b;
}
