#ifndef _BUSH_ACTOR_HPP_
#define _BUSH_ACTOR_HPP_

#include "Actor.hpp"

namespace DatNS
{
	class BushActor
		: public Actor
	{
	public:
		BushActor(const NYVert3Df& pos, const NYVert3Df& speed, const NYVert3Df& fw);
		virtual void update(float elapsedTime) {};
		virtual void render();
	};
}

#endif
