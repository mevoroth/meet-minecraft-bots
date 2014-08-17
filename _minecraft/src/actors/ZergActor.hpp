#ifndef _ZERG_ACTOR_HPP_
#define _ZERG_ACTOR_HPP_

#include "ActorsRepository.hpp"
#include "Actor.hpp"
#include "gl/glew.h"

using namespace std;

namespace DatNS
{
	class ElfActor;

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
		float elapsedTime;
		ElfActor* host;
		NYVert3Df destination;
		NYVert3Df currentPos;
		NYVert3Df next;
		bool foundDestination;
	public:
		ZergActor(const NYVert3Df& pos, const NYVert3Df& speed, const NYVert3Df& fw);

		void update(float elapsedTime);
		void render();
		void setState(ZergState state) { currentState = state; }
	};
};

#endif
