#ifndef _ZERG_ACTOR_HPP_
#define _ZERG_ACTOR_HPP_

#include "Actor.hpp"

// ai
#include "ai\Multiplyable.hpp"
#include "ai\Parasite.hpp"
#include "ai\SequenceStore.hpp"
#include "ai\CurrentBehavior.hpp"
#include "ai\RandomDirectionStore.hpp"
#include "ai\NewPosition.hpp"

#include "gl/glew.h"

//#include <vector>
#include <map>

using namespace std;

namespace DatNS
{
	class ZergActor
		: public Actor
	{
	public:
		enum ZergState
		{
			MULTIPLY,
			LOOK_FOR_HOST,
			TELEPORT
		};
	private:
		ZergState currentState;
	public:
		ZergActor(const NYVert3Df& pos, const NYVert3Df& speed, const NYVert3Df& fw);

		void update(float elapsedTime);
		void render();
		void setState(ZergState state) { currentState = state; }
	};
};

#endif
