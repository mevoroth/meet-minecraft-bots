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
