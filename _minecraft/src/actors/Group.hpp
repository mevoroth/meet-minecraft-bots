#ifndef _GROUP_HPP_
#define _GROUP_HPP_

#include <cassert>
#include <list>
#include "Actor.hpp"
#include "Settings.hpp"

using namespace std;

namespace DatNS
{
	class Group
	{
	private:
		list<Actor*> elements;
	public:
		list<Actor*> getElements() { return elements; };
		void add(Actor* actor) { assert(elements.size() < GROUP_SIZE); elements.push_back(actor); };
		void remove(Actor* actor);
		int size() const { return elements.size(); }
		NYVert3Df getPosition();
		bool full() const { return size() == GROUP_SIZE; }
	};
}

#endif
