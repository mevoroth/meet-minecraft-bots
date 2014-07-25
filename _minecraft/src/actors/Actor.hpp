#ifndef _ACTOR_HPP_
#define _ACTOR_HPP_

#include "engine/utils/types_3d.h"

namespace DatNS
{
	class Actor
	{
	private:
		NYVert3Df _pos;
		NYVert3Df _speed;
		NYVert3Df _fw;
	public:
		Actor(const NYVert3Df& pos, const NYVert3Df& speed, const NYVert3Df& rotation);
		NYVert3Df& Position() { return _pos; };
		NYVert3Df& Speed() { return _speed; };
		NYVert3Df& Forward() { return _fw; };

		virtual void update() = 0;
	};
};

#endif
