#ifndef _ZERG_ACTOR_HPP_
#define _ZERG_ACTOR_HPP_

#include "Actor.hpp"

// ai
#include "ai\Multiplyable.hpp"
#include "ai\Parasite.hpp"

namespace DatNS
{
	class ZergActor
		: public Actor,
		public Multiplyable,
		public Parasite
	{
	public:
		void multiply();
		void update();
	};
};

#endif
