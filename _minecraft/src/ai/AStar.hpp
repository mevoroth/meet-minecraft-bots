#ifndef _A_STAR_HPP_
#define _A_STAR_HPP_

#include "engine\utils\types_3d.h"

namespace DatNS
{
	class AStar
	{
	public:
		AStar(const NYVert3Df& begin, const NYVert3Df& end);
		NYVert3Df find();
	};
}

#endif
