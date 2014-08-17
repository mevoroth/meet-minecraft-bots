#ifndef _HUNTER_HPP_
#define _HUNTER_HPP_

#include "Actor.hpp"
#include "ZergActor.hpp"

namespace DatNS
{
	class ZergActor;
	class HunterActor
		: public Actor
	{
	public:
		enum HunterState
		{
			MULTIPLY,
			LOOK_FOR_FOOD,
			EAT,
			MOVE,
			NONE

		};
	private:
		HunterState currentState;
		HunterState nextState;
		int eaten;
		ZergActor* parasite;
		bool foundDestination;
		NYVert3Df destination;
		NYVert3Df currentPos;
		NYVert3Df next;
		float elapsedTime;
	public:
		HunterActor(const NYVert3Df& pos, const NYVert3Df& speed, const NYVert3Df& rotation);
		virtual void update(float elapsedTime);
		virtual void render();
		void setState(HunterState state) { currentState = state; }
	};
};

#endif
