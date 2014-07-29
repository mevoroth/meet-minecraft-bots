#ifndef _ZERG_ACTOR_HPP_
#define _ZERG_ACTOR_HPP_

#include "Actor.hpp"

// ai
#include "ai\Multiplyable.hpp"
#include "ai\Parasite.hpp"

#include "gl/glew.h"

#include <vector>

using namespace std;

namespace DatNS
{
	class ZergActor
		: public Actor,
		public Multiplyable,
		public Parasite
	{
	public:
		ZergActor(const NYVert3Df& pos, const NYVert3Df& speed, const NYVert3Df& fw);

		static void reset();

		void multiply();
		void update();
		void render();
	};
};

#endif
