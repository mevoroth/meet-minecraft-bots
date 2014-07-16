#ifndef _PARASITE_ACTOR_HPP_
#define _PARASITE_ACTOR_HPP_

#include "Actor.hpp"

// ai
#include "ai\Multiplyable.hpp"
#include "ai\Parasite.hpp"

namespace DatNS
{
	class ParasiteActor
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
