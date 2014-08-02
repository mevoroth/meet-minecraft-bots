#ifndef _HUNTER_HPP_
#define _HUNTER_HPP_

#include "Actor.hpp"

namespace DatNS
{
	class HunterActor
		: public Actor
	{
	public:
		virtual void update(float elapsedTime);
		virtual void render();
	};
};

#endif
