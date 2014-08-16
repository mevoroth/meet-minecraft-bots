#ifndef _GROUP_ELEMENT_HPP_
#define _GROUP_ELEMENT_HPP_

#include "engine\utils\types_3d.h"
#include "actors\GroupActor.hpp"

namespace DatNS
{
	class GroupActor;

	class GroupElement
	{
	private:
		GroupActor* group;
	public:
		virtual NYVert3Df getPosition() = 0;
		void setGroup(GroupActor* group) { this->group = group; };
		GroupActor* getGroup() { return group; };
	};
}

#endif
