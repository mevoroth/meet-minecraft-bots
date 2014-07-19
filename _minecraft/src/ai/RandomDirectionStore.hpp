#ifndef _RANDOM_DIRECTION_STORE_HPP_
#define _RANDOM_DIRECTION_STORE_HPP_

#include "engine\utils\types_3d.h"

namespace DatNS
{
	class RandomDirectionStore
	{
	public:
		virtual void storeRandomDirection(const NYVert3Df& dir) = 0;
	};
}

#endif