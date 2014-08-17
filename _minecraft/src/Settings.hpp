#ifndef _SETTINGS_HPP_
#define _SETTINGS_HPP_

#include "engine\utils\types_3d.h"

namespace DatNS
{
	/**
	 * Temps du check Herbivore
	 */
	const float LOOK_AROUND_TIMER = 1000.f; // 1s
	/**
	 * Cooldown reproduction
	 */
	const float MULTIPLY = 10000.f; // 10s
	const float SHEEP_MOVE_SPEED = 0.001f; // 0.001 px/frame
	const int SHEEP_EAT_TO_REPRODUCE = 1;
	const float EAT_RANGE = 2.f;
	const int GROUP_SIZE = 10;
	const int PARASITE_EAT_TO_REPRODUCE = 10;
	const float HUNTER_MOVE_SPEED = 0.001f; // 0.001 px/frame
	const float SHEEP_VISION = 0.75f;
	const float SHEEP_VISION_RANGE = 3.f;
	const float HUNTER_RANGE_TO_REPRODUCE = 5.f;
}

#endif
