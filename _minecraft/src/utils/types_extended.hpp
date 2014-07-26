#ifndef _TYPES_EXTENDED_HPP_
#define _TYPES_EXTENDED_HPP_

#include "engine\utils\types_3d.h"

#include "world.h"

const NYVert3Df UP = NYVert3Df(0, 0, 1);
const NYVert3Df RIGHT = NYVert3Df(1, 0, 0);
const NYVert3Df FORWARD = NYVert3Df(0, 1, 0);

class UniqWorld
{
private:
	static UniqWorld* instance;
	NYWorld* world;
	UniqWorld();
	~UniqWorld();
public:
	static UniqWorld* get();
	inline NYWorld* World() { return world; };
};

#endif
