#ifndef _BUSH_ACTOR_HPP_
#define _BUSH_ACTOR_HPP_

#include "Actor.hpp"
#include "ai\Eatable.hpp"

namespace DatNS
{
	class BushActor
		: public Actor
	{
	private:
		int amount;
	public:
		BushActor(const NYVert3Df& pos, const NYVert3Df& speed, const NYVert3Df& fw);
		virtual void update(float elapsedTime) {};
		virtual void render();
		void consume() { --amount; };
		void destroy();
		bool empty() { return !amount; }
	};
}

#endif
