#ifndef _RANDOM_DIRECTION_STORE_HPP_
#define _RANDOM_DIRECTION_STORE_HPP_

#include "engine\utils\types_3d.h"

namespace DatNS
{
	class RandomDirectionStore
	{
	public:
		virtual void store(const NYVert3Df& dir) = 0;
		virtual NYVert3Df retrieve() const = 0;
	};
}

#endif
