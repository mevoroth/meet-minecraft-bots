#ifndef _NEW_POSITION_HPP_
#define _NEW_POSITION_HPP_

#include "engine\utils\types_3d.h"

namespace DatNS
{
	class NewPosition
	{
	public:
		virtual NYVert3Df getNewPosition() const = 0;
	};
}

#endif
