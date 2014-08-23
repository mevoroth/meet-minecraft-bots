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
		/**
		 * Actor
		 */
		Actor(const NYVert3Df& pos, const NYVert3Df& speed, const NYVert3Df& rotation);
		/**
		 * Position setter
		 */
		NYVert3Df& Position() { return _pos; };
		/**
		 * Position getter
		 */
		NYVert3Df getPosition() const { return _pos; };
		NYVert3Df& Speed() { return _speed; };
		NYVert3Df getSpeed() const { return _speed; };
		/**
		 * Forward vector setter
		 */
		NYVert3Df& Forward() { return _fw; };
		/**
		 * Forward vector getter
		 */
		NYVert3Df getForward() const { return _fw; };
		
		/**
		 * Tick
		 * @param[in] elapsed time
		 */
		virtual void update(float elapsedTime) = 0;
		/**
		 * render actor
		 */
		virtual void render() = 0;
		/**
		 * for std::find() purpose
		 */
		virtual bool operator==(const Actor& actor) { return this == &actor; };
		/**
		 * for std::find() purpose
		 */
		virtual bool operator!=(const Actor& actor) { return this != &actor; };
	};
};

#endif
