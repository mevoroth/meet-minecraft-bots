#ifndef _DESTINATION_HPP_
#define _DESTINATION_HPP_

#include "engine\utils\types_3d.h"

namespace DatNS
{
	class Destination
	{
	private:
		NYVert3Df dest;
	public:
		NYVert3Df getDest() { return dest; };
		virtual float getMoveSpeed() = 0;
	};
}

#endif
