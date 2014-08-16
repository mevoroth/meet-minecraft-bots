#ifndef _GROUP_ACTOR_HPP_
#define _GROUP_ACTOR_HPP_

#include <list>

#include "ai\GroupElement.hpp"
#include "Actor.hpp"

using namespace std;

namespace DatNS
{
	class GroupElement;

	class GroupActor
	{
	private:
		list<GroupElement*> _actors;
	public:
		enum {
			MIN = 1,
			MAX = 10
		};
		bool add(GroupElement* actor);
		bool remove(GroupElement* actor);
		inline bool full() const;
		inline bool one() const;
		inline int size() const { return _actors.size(); };
		NYVert3Df getPosition();
		list<GroupElement*> getElements() { return _actors; };
	};
}

#endif
